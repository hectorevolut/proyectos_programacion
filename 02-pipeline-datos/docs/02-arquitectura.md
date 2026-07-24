# Arquitectura

## Vista general

```
┌─────────────┐     CSV movimientos      ┌──────────────┐
│   Usuario   │ ───────────────────────▶ │ java-service │
└─────────────┘                          │  (API REST)  │
                                          └──────┬───────┘
                                                  │ 1. lanza proceso (ProcessBuilder)
                                                  │    con el CSV como argumento
                                                  ▼
                                          ┌──────────────┐
                                          │    c-core    │
                                          │  (binario)   │
                                          │              │
                                          │ parsea CSV → │
                                          │ agrega en    │
                                          │ paralelo →   │
                                          │ escribe JSON │
                                          └──────┬───────┘
                                                  │ 2. JSON de resultados agregados
                                                  │    (stdout, capturado por Java)
                                                  ▼
                                          ┌──────────────┐
                                          │ java-service │
                                          │ 3. parsea    │
                                          │    JSON y    │
                                          │    persiste  │
                                          └──────┬───────┘
                                                  │ 4. INSERT vía JDBC
                                                  ▼
                                          ┌──────────────┐
                                          │  SQL (BD)    │
                                          │ movimientos  │
                                          │ agregados    │
                                          └──────┬───────┘
                                                  │ 5. SELECT vía JDBC
                                                  ▼
                                          ┌──────────────┐
                                          │ java-service │
                                          │ (API REST)   │
                                          └──────┬───────┘
                                                  │ 6. JSON de respuesta
                                                  ▼
                                          ┌──────────────┐
                                          │  web (panel) │
                                          │ fetch + charts│
                                          └──────────────┘
```

## Por qué esta comunicación C ↔ Java (y no otra)

Se decide **invocar el binario de C como proceso externo desde Java**
(`ProcessBuilder`), intercambiando datos por `stdin`/`stdout` en formato JSON,
en vez de otras alternativas más complejas (JNI, sockets locales, ficheros
intermedios). Motivo (ver ADR correspondiente en `05-decisiones-tecnicas.md`):

- Es el mecanismo más simple de entender y depurar para alguien reconstruyendo
  bases de concurrencia en C: el binario en C se puede ejecutar y probar de
  forma totalmente aislada desde la terminal, sin Java de por medio.
- Evita la complejidad añadida de JNI (gestión de referencias entre máquinas
  virtuales distintas), que no aporta valor pedagógico en esta fase.
- Es un patrón real y común en la industria (microservicios/scripts que
  invocan binarios nativos para tareas de cómputo intensivo).

Se revisará en el roadmap si, en una fase avanzada, tiene sentido sustituir el
intercambio por `stdout` por un socket Unix o TCP (esto sí aportaría práctica
extra de IPC más realista, y se podría explorar como ampliación opcional).

## Responsabilidad de cada componente

### `c-core`
- Recibe la ruta de un CSV de movimientos como argumento.
- Valida y parsea las líneas (fecha, importe, tipo, categoría, descripción).
- Calcula agregaciones: totales por mes, por categoría, medias móviles de cash
  flow, comparativas entre periodos.
- Paraleliza el cálculo de agregaciones (por ejemplo, un hilo/tarea OpenMP por
  mes o por categoría) — el diseño exacto de qué se paraleliza y cómo se
  decide en la fase correspondiente del roadmap, no antes de tener una versión
  secuencial funcionando.
- Escribe el resultado como JSON por `stdout`.
- No toca la base de datos ni sabe que existe Java o SQL. Su única
  responsabilidad es "CSV entra, JSON de agregados sale".

### `java-service`
- Expone una API REST mínima:
  - `POST /movimientos/importar` → recibe/referencia un CSV, invoca `c-core`,
    persiste el resultado.
  - `GET /resumen?desde=...&hasta=...` → devuelve agregados ya calculados.
  - `GET /categorias` → devuelve el desglose por categoría.
- Gestiona la ejecución del binario en C sin bloquear otras peticiones
  (`ExecutorService`).
- Es la única capa que habla con la base de datos (vía JDBC).
- Gestiona errores del binario en C (código de salida, stderr) de forma
  explícita, no los ignora.

### `sql`
- Esquema relacional (ver se detallará en fase correspondiente): tablas
  `movimientos`, `categorias`, y tablas de agregados (`agregados_mensuales`,
  por ejemplo) para no recalcular todo en cada consulta del panel.
- Las agregaciones "pesadas" las hace C; SQL se usa para las consultas de
  lectura del panel (filtrado por rango de fechas, por categoría, etc.), que
  es exactamente para lo que SQL está pensado.

### `web`
- Panel estático (HTML/CSS/JS) que consume la API de `java-service` vía
  `fetch()`.
- Sin frameworks pesados en las primeras fases (Vanilla JS + Chart.js), para
  entender bien el ciclo petición → render antes de añadir abstracciones.

## Formato de intercambio C → Java

Se usará JSON por ser legible, fácil de depurar a mano, y porque escribirlo a
mano en C (sin librerías externas al principio) es un buen ejercicio de manejo
de cadenas y buffers — más adelante se puede valorar usar una librería como
`cJSON` una vez entendido el problema "a pelo".

Ejemplo de salida esperada de `c-core` (formato orientativo, se cerrará al
implementar):

```json
{
  "periodo": {"desde": "2025-01-01", "hasta": "2025-12-31"},
  "totales": {"ingresos": 42000.50, "gastos": 31500.20, "balance": 10500.30},
  "por_mes": [
    {"mes": "2025-01", "ingresos": 3500.00, "gastos": 2600.00},
    {"mes": "2025-02", "ingresos": 3700.00, "gastos": 2450.00}
  ],
  "por_categoria": [
    {"categoria": "suministros", "total": 4200.00, "tipo": "gasto"},
    {"categoria": "ventas_producto_a", "total": 18000.00, "tipo": "ingreso"}
  ]
}
```
