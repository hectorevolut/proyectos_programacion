# Roadmap por fases

Cada fase produce algo ejecutable y verificable — nunca se avanza a la
siguiente fase con la anterior "a medias". Cada fase se desarrolla en su
propia rama de Git (`fase-N-nombre`) y se fusiona a `main` mediante PR cuando
está completa y probada.

Las casillas se marcan en este mismo fichero a medida que se completan.

---

## Fase 0 — Preparación
- [ ] Repositorio Git inicializado en `Programación/` con `.gitignore` correcto
      (excluye CSVs reales de movimientos, binarios compilados, `.class`, etc.)
- [ ] Documentación base cerrada (este set de `.md`)
- [ ] Entorno de desarrollo verificado: `gcc`/`clang`, JDK (versión LTS actual),
      motor SQL elegido instalado (ver `04-stack-tecnologico.md`)
- [ ] Dataset de ejemplo/anonimizado creado para desarrollo (CSV ficticio con
      movimientos plausibles, varios meses y categorías)

## Fase 1 — `c-core` secuencial (repaso de C)
**Objetivo pedagógico:** recuperar soltura en C antes de meter concurrencia.

- [ ] Parser de CSV robusto (líneas mal formadas no deben tumbar el programa)
- [ ] Estructura de datos en memoria para los movimientos (array dinámico o
      lista enlazada — justificar la elección en `05-decisiones-tecnicas.md`)
- [ ] Cálculo secuencial de: total ingresos, total gastos, balance
- [ ] Cálculo secuencial de agregados por mes
- [ ] Cálculo secuencial de agregados por categoría
- [ ] Salida en JSON escrita a mano (sin librerías) por `stdout`
- [ ] Gestión de memoria verificada sin fugas (`valgrind`)
- [ ] Makefile con flags estrictos (`-Wall -Wextra -Werror` como mínimo)
- [ ] Tests manuales con varios CSVs (vacío, con errores, con un solo mes, con
      varios años)

## Fase 2 — `c-core` paralelo
**Objetivo pedagógico:** el núcleo de la reconstrucción de conocimientos de
concurrencia.

- [ ] Identificar qué cálculo se paraleliza primero (candidato natural: los
      agregados por mes, al ser independientes entre sí)
- [ ] Versión con **pthreads**: un hilo por bloque de meses (o por año),
      sincronización con mutex al escribir el resultado compartido
- [ ] Provocar una condición de carrera a propósito (quitando el mutex) y
      documentar en `05-decisiones-tecnicas.md` qué se observó — es más
      formativo verlo fallar primero que evitarlo por instinto
- [ ] Versión equivalente con **OpenMP** (`#pragma omp parallel for` +
      reducción), comparando legibilidad y rendimiento frente a pthreads
- [ ] Medición de tiempos: secuencial vs pthreads vs OpenMP, con datasets de
      distinto tamaño (pequeño/mediano/grande, generados sintéticamente si
      hace falta para tener suficiente volumen)
- [ ] Documentar resultados de rendimiento en el propio repo (tabla o gráfica
      simple, puede ir en el README de `c-core/`)

## Fase 3 — `java-service` básico
**Objetivo pedagógico:** integración de procesos externos y diseño en capas.

- [ ] Estructura de paquetes en capas (controller / service / repository)
- [ ] Invocación de `c-core` vía `ProcessBuilder`, captura de `stdout`/`stderr`
      y del código de salida
- [ ] Parseo del JSON devuelto por C (librería estándar tipo Jackson o Gson)
- [ ] Endpoint `POST /movimientos/importar` funcional de extremo a extremo
      (recibe CSV → invoca C → obtiene JSON), **sin base de datos todavía**
      (se devuelve directamente al cliente)
- [ ] Manejo explícito de errores (CSV inválido, binario de C falla, etc.) con
      códigos HTTP apropiados
- [ ] Tests unitarios de la capa de servicio con JUnit (mockeando la
      invocación al proceso externo)

## Fase 4 — `sql` — persistencia
**Objetivo pedagógico:** modelado de datos real y JDBC.

- [ ] Diseño del esquema (`movimientos`, `categorias`, `agregados_mensuales`)
      documentado antes de crear las tablas
- [ ] Script de creación (`sql/schema/`) versionado, no ejecutado a mano una
      sola vez y olvidado
- [ ] Conexión JDBC desde `java-service`, capa `repository` separada de la
      lógica de negocio
- [ ] `INSERT` de resultados tras cada importación (con transacción: si falla
      a medio guardar, se hace rollback)
- [ ] `GET /resumen` y `GET /categorias` ahora leen de la base de datos, no
      del JSON en memoria
- [ ] Al menos una consulta de agregación en SQL puro (no recalculada en
      Java) para practicar `GROUP BY`/funciones de agregación
- [ ] Índices añadidos donde tengan sentido, verificados con `EXPLAIN`

## Fase 5 — `web` — panel de análisis
**Objetivo pedagógico:** consumo de API y visualización.

- [ ] Maquetación HTML/CSS del panel (sin frameworks al principio)
- [ ] `fetch()` a los endpoints de `java-service`, render de tabla de
      resumen mensual
- [ ] Gráfica de evolución ingresos/gastos por mes (Chart.js u otra librería
      ligera)
- [ ] Gráfica/desglose por categoría
- [ ] Filtro por rango de fechas (reutilizando los parámetros de `GET
      /resumen`)
- [ ] Diseño responsive mínimo verificado en móvil y escritorio

## Fase 6 — Cierre de ciclo y calidad
**Objetivo pedagógico:** hábitos de ingeniería de software, no solo "que
funcione".

- [ ] Revisión completa de la documentación (`docs/`) para que refleje lo
      realmente implementado, no lo planeado inicialmente
- [ ] GitHub Actions: workflow que compile `c-core` y ejecute sus tests, y
      otro que ejecute los tests de `java-service`, en cada push
- [ ] README de cada subcarpeta (`c-core/`, `java-service/`, `sql/`, `web/`)
      con instrucciones de build/ejecución local
- [ ] Revisión de seguridad básica: el CSV subido por el usuario no debe poder
      ejecutar nada ni inyectar SQL (verificar que se usan prepared
      statements en toda la capa JDBC)

## Ampliaciones opcionales (una vez cerrado lo anterior)
- [ ] Sustituir la comunicación por `stdout` entre C y Java por un socket
      Unix, para practicar IPC más realista
- [ ] Autenticación básica en la API (para no dejarla abierta si se despliega)
- [ ] Exportar el resumen a PDF/CSV desde el panel web
- [ ] Dockerizar los tres componentes
