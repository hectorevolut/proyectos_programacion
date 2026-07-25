# Temario — Java

Curso desde cero absoluto: no se asume ninguna experiencia previa con Java
ni con programación orientada a objetos.

## Módulo 0 — Fundamentos absolutos de Java
- 0.1 Qué es la JVM y por qué Java "compila distinto" a C (bytecode,
  portabilidad)
- 0.2 Primer programa: `HolaMundo.java`, compilar con `javac` y ejecutar con
  `java`
- 0.3 Variables, tipos primitivos vs objetos, `String`
- 0.4 Operadores y control de flujo (mismo espíritu que en C, sintaxis Java)
- 0.5 Qué es una clase y qué es un objeto (la diferencia real, no la
  definición de manual)
- 0.6 Métodos: firma, parámetros, retorno, `static` vs no `static`
- 0.7 Colecciones básicas (`List`, `Map`) y por qué se prefieren a arrays en
  la mayoría de casos en Java (a diferencia de C)
- 0.8 Excepciones: `try/catch`, checked vs unchecked, por qué
  `printStackTrace()` a secas es una mala práctica
- 0.9 Maven: qué es un `pom.xml`, cómo se añade una dependencia, ciclo de
  vida básico (`compile`, `test`, `package`)
- 0.10 Checkpoint práctico: programa pequeño con al menos una clase propia,
  una colección y una excepción manejada

## Módulo 1 — Invocar procesos externos
> Objetivo: que Java sepa ejecutar `c-core` y leer su salida.

- 1.1 `ProcessBuilder`: lanzar un proceso, pasarle argumentos
- 1.2 Leer `stdout`/`stderr` del proceso sin bloquear el programa
- 1.3 Códigos de salida y cómo tratarlos como señal de éxito/error
- 1.4 Checkpoint práctico: invocar el binario de `c-core` desde Java y
  volcar su salida por consola

## Módulo 2 — Parsear JSON
> Objetivo: convertir el JSON que escribe C en objetos Java usables.

- 2.1 Añadir Jackson al proyecto (dependencia Maven)
- 2.2 Mapear JSON a clases Java (POJOs) — anotaciones básicas
- 2.3 Checkpoint práctico: parsear el JSON de ejemplo de `02-arquitectura.md`
  a un objeto Java

## Módulo 3 — Diseño en capas
> Objetivo: no todo en una clase `Main`.

- 3.1 Por qué separar controller / service / repository (motivación real,
  no dogma)
- 3.2 Inyección de dependencias manual (sin frameworks todavía) — pasar
  objetos por constructor
- 3.3 Checkpoint práctico: reestructurar el código del Módulo 1-2 en capas

## Módulo 4 — API REST con Javalin
> Objetivo: exponer `POST /movimientos/importar`, `GET /resumen`, etc.

- 4.1 Qué es un endpoint, verbos HTTP, códigos de estado
- 4.2 Javalin: arrancar un servidor mínimo, definir rutas
- 4.3 Serializar respuestas a JSON
- 4.4 Manejo de errores HTTP (400, 500) de forma explícita
- 4.5 Checkpoint práctico: endpoint funcional de extremo a extremo (sin BD
  todavía, devolviendo el JSON de C directamente)

## Módulo 5 — Concurrencia en Java
> Objetivo: no bloquear el servidor mientras se ejecuta `c-core`.

- 5.1 Hilos en Java vs pthreads en C — mismo concepto, distinta sintaxis
- 5.2 `ExecutorService`: pool de hilos gestionado
- 5.3 Checkpoint práctico: varias importaciones concurrentes sin bloquear la
  API

## Módulo 6 — JDBC y persistencia
> Objetivo: conectar con la base de datos SQL.

- 6.1 Qué es un driver JDBC, cómo se añade al proyecto
- 6.2 `Connection`, `PreparedStatement` (y por qué NUNCA se concatena SQL a
  mano — inyección SQL)
- 6.3 Transacciones desde Java: commit/rollback
- 6.4 Patrón DAO/Repository aplicado a `movimientos`
- 6.5 Checkpoint práctico: `INSERT` de resultados tras cada importación

## Módulo 7 — Tests con JUnit
- 7.1 Anatomía de un test (`@Test`, asserts)
- 7.2 Mocking básico (simular la invocación al proceso externo sin
  ejecutarlo de verdad en cada test)
- 7.3 Checkpoint práctico: tests de la capa de servicio
