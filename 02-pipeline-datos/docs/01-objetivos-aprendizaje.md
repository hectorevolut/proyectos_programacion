# Objetivos de aprendizaje

Objetivos concretos que este proyecto debe dejar dominados, agrupados por
tecnología. Se marcarán como completados a medida que se cierren fases del
roadmap (`03-roadmap-fases.md`).

## C

- [ ] Repaso de fundamentos post-parón: punteros, gestión manual de memoria,
      structs, Makefiles, compilación con flags de warnings estrictos.
- [ ] E/S de ficheros eficiente (lectura por buffers, evitar reservas de memoria
      innecesarias en bucles).
- [ ] Estructuras de datos propias (hash table o árbol, según dominio elegido)
      implementadas desde cero, sin librerías externas.
- [ ] Concurrencia con **pthreads**: creación/join de hilos, `mutex`, condiciones
      de carrera provocadas y luego corregidas a propósito (para entenderlas de
      verdad, no solo evitarlas).
- [ ] Paralelismo de datos con **OpenMP** (`#pragma omp parallel for`,
      reducciones, comparación de rendimiento frente a pthreads manuales).
- [ ] Medición de rendimiento real (tiempo secuencial vs paralelo, speedup,
      número óptimo de hilos según núcleos disponibles).
- [ ] Interfaz de salida de datos hacia Java: formato de intercambio (JSON desde
      C, ficheros intermedios, o pipe/socket — se decide en `02-arquitectura.md`).

## Java

- [ ] Invocación de procesos externos (`ProcessBuilder`) y gestión de su
      entrada/salida.
- [ ] Concurrencia en Java (`ExecutorService`, colas de trabajos) para gestionar
      varios procesamientos en paralelo sin bloquear el servicio.
- [ ] Diseño en capas (controlador / servicio / repositorio) en vez de todo en
      una clase.
- [ ] Acceso a base de datos con **JDBC** (y valorar un mapeo ligero tipo
      DAO antes de dar el salto a un ORM).
- [ ] Exposición de una API REST mínima (framework ligero: Javalin o Spark) para
      lanzar procesamientos y consultar resultados.
- [ ] Manejo de errores y logging (no solo `try/catch` con `printStackTrace`).
- [ ] Tests unitarios básicos (JUnit) de la lógica de negocio.

## SQL

- [ ] Diseño de esquema normalizado a partir de datos reales generados por el
      pipeline (no un esquema de ejemplo de libro).
- [ ] Tipos de datos apropiados, claves primarias/foráneas, restricciones.
- [ ] Índices: cuándo ayudan y cómo comprobarlo (`EXPLAIN`).
- [ ] Consultas de agregación (`GROUP BY`, funciones de ventana si el motor lo
      permite) sobre los resultados del procesamiento.
- [ ] Transacciones: cuándo son necesarias en este pipeline y cómo se gestionan
      desde Java (commit/rollback).
- [ ] Migraciones versionadas del esquema (aunque sea con scripts `.sql`
      numerados, sin herramienta externa al principio).

## HTML / CSS (+ JS mínimo)

- [ ] Estructura semántica de una página de reporting (no todo `<div>`).
- [ ] CSS con un sistema mínimo de diseño propio (variables CSS, sin frameworks
      pesados al principio, para entender el porqué de las cosas).
- [ ] Consumo de la API Java desde `fetch()` y render dinámico de tablas.
- [ ] Al menos una visualización gráfica (librería ligera tipo Chart.js).
- [ ] Diseño responsive básico.

## Git / GitHub

- [ ] Commits atómicos y descriptivos desde el primer día.
- [ ] Ramas por fase/funcionalidad, sin trabajar nunca directamente en `main`
      una vez arrancado el desarrollo real.
- [ ] Pull requests (aunque se trabaje en solitario) para forzar el hábito de
      revisar el propio diff antes de fusionar.
- [ ] `.gitignore` correcto por tecnología (evitar subir `.class`, `.o`,
      binarios, `node_modules` si aplica, credenciales de BD).
- [ ] GitHub Actions básico: al menos un workflow que compile el C y ejecute
      los tests de Java en cada push (se aborda en fase avanzada).
