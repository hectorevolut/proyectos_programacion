# Temario — C

Curso desde cero absoluto: no se asume ningún conocimiento previo, ni
siquiera haber compilado un programa alguna vez. Cada módulo se apoya
estrictamente en el anterior.

## Módulo 0 — Fundamentos absolutos (🔵 EN CURSO)
> Objetivo: poder leer y escribir un programa en C sencillo, entendiendo
> cada línea, antes de tocar memoria dinámica.

- 0.1 Qué es un programa y qué hace un compilador (de código fuente a
  ejecutable, en términos generales — se detalla en 0.9)
- 0.2 Primer programa: "Hola mundo", compilarlo y ejecutarlo paso a paso
- 0.3 Variables y tipos (`int`, `char`, `float`, `double`, `size_t`)
- 0.4 Operadores (aritméticos, comparación, lógicos)
- 0.5 Control de flujo (`if`/`else`, `while`, `for`, `switch`)
- 0.6 Funciones: firma, parámetros, retorno, por qué existen
- 0.7 Arrays de tamaño fijo
- 0.8 Cadenas de caracteres (`char *`) y funciones típicas de librería
- 0.9 Punteros: qué son de verdad (una dirección de memoria, nada mágico)
- 0.10 Las 4 fases de la compilación (preprocesado, compilación, ensamblado,
  enlazado) y por qué importa para leer errores
- 0.11 Checkpoint práctico: programa pequeño que combine todo lo anterior

## Módulo 1 — Memoria dinámica y structs (✅ contenido ya escrito y superado)
> Objetivo: `movimientos.c` — la estructura de datos central del proyecto.
> Este módulo ya se completó en la práctica (`lista_crear`, `lista_push`,
> `lista_destruir`, verificado con AddressSanitizer). Se mantiene aquí como
> registro y punto de repaso si hace falta volver a él.

- 1.1 Stack vs heap: qué vive dónde y por qué importa
- 1.2 `malloc`/`free`: contrato básico (quien pide, libera)
- 1.3 `realloc` y el patrón array dinámico (capacity vs count)
- 1.4 Structs: memoria contigua, `sizeof`, copia por valor vs por puntero
- 1.5 Punteros a structs y el operador `->`
- 1.6 Checkpoint práctico: `t_lista_movimientos` completo — ✅ superado

## Módulo 2 — Parsing y manejo de cadenas a fondo
> Objetivo: `parsear_linea` y `parsear_csv`.

- 2.1 Recorrer un `char *` a mano (sin `strtok`) — punteros que avanzan
- 2.2 Conversión de texto a número: `strtod`, `strtol` y cómo detectar errores
- 2.3 Buffers y `fgets`/`getline`: leer un fichero línea a línea sin desbordar
- 2.4 Validación defensiva: qué hacer con una línea mal formada sin crashear
- 2.5 Checkpoint práctico: `movimientos.c` completo y probado contra el CSV
  de ejemplo

## Módulo 3 — Cálculo secuencial (agregados)
> Objetivo: `agregados.c`, base sobre la que luego se paraleliza.

- 3.1 Recorrer arrays de structs y acumular resultados
- 3.2 Agrupar por clave (mes, categoría) sin librerías — estrategia con
  arrays paralelos o una tabla hash simple
- 3.3 Precisión con `double` para dinero: por qué hay que tener cuidado
  (y por qué en un proyecto real se evitaría `double` para dinero — se
  discute como nota, sin sobre-ingenierizar esta fase)
- 3.4 Checkpoint práctico: totales, por mes y por categoría funcionando

## Módulo 4 — Escritura de JSON a mano
> Objetivo: `json_writer.c`, la salida hacia Java.

- 4.1 Construir cadenas dinámicamente (buffer que crece, similar al array
  dinámico del Módulo 1 pero con `char`)
- 4.2 Escapado básico de caracteres especiales en JSON
- 4.3 Checkpoint práctico: `c-core` completo, ejecutándose de extremo a
  extremo (CSV → JSON por stdout)

## Módulo 5 — Concurrencia con pthreads (🔴 lo nuevo de verdad)
> Objetivo: paralelizar el cálculo de agregados. Aquí es donde se reconstruye
> conocimiento que no tenías antes del parón.

- 5.1 Qué es un hilo y en qué se diferencia de un proceso
- 5.2 `pthread_create`/`pthread_join`: ciclo de vida básico
- 5.3 Condición de carrera: provocarla a propósito y verla fallar
- 5.4 `pthread_mutex_t`: proteger una sección crítica
- 5.5 Repartir trabajo entre hilos (dividir el array en bloques)
- 5.6 Checkpoint práctico: versión con pthreads de los agregados, con y sin
  mutex, viendo la diferencia

## Módulo 6 — Paralelismo con OpenMP
> Objetivo: comparar con pthreads, entender cuándo usar cada uno.

- 6.1 `#pragma omp parallel for`: paralelismo declarativo
- 6.2 Reducciones (`reduction(+:total)`) — evitar mutex manuales
- 6.3 Comparativa de legibilidad y rendimiento: pthreads vs OpenMP
- 6.4 Checkpoint práctico: medir tiempos secuencial vs pthreads vs OpenMP con
  datasets de distinto tamaño

## Módulo 7 — Herramientas de calidad (transversal, se aplica desde el Módulo 1)
- 7.1 Flags del compilador (`-Wall -Wextra -Werror`) y por qué no son opcionales
- 7.2 Detección de fugas de memoria (`valgrind` o `AddressSanitizer` en macOS)
- 7.3 Makefiles: targets, dependencias, `re`/`clean`/`fclean`

## Módulo 2 — Parsing y manejo de cadenas a fondo
> Objetivo: `parsear_linea` y `parsear_csv`.

- 2.1 Recorrer un `char *` a mano (sin `strtok`) — punteros que avanzan
- 2.2 Conversión de texto a número: `strtod`, `strtol` y cómo detectar errores
- 2.3 Buffers y `fgets`/`getline`: leer un fichero línea a línea sin desbordar
- 2.4 Validación defensiva: qué hacer con una línea mal formada sin crashear
- 2.5 Checkpoint práctico: `movimientos.c` completo y probado contra el CSV
  de ejemplo

## Módulo 3 — Cálculo secuencial (agregados)
> Objetivo: `agregados.c`, base sobre la que luego se paraleliza.

- 3.1 Recorrer arrays de structs y acumular resultados
- 3.2 Agrupar por clave (mes, categoría) sin librerías — estrategia con
  arrays paralelos o una tabla hash simple
- 3.3 Precisión con `double` para dinero: por qué hay que tener cuidado
  (y por qué en un proyecto real se evitaría `double` para dinero — se
  discute como nota, sin sobre-ingenierizar esta fase)
- 3.4 Checkpoint práctico: totales, por mes y por categoría funcionando

## Módulo 4 — Escritura de JSON a mano
> Objetivo: `json_writer.c`, la salida hacia Java.

- 4.1 Construir cadenas dinámicamente (buffer que crece, similar al array
  dinámico del Módulo 1 pero con `char`)
- 4.2 Escapado básico de caracteres especiales en JSON
- 4.3 Checkpoint práctico: `c-core` completo, ejecutándose de extremo a
  extremo (CSV → JSON por stdout)

## Módulo 5 — Concurrencia con pthreads (🔴 lo nuevo de verdad)
> Objetivo: paralelizar el cálculo de agregados. Aquí es donde se reconstruye
> conocimiento que no tenías antes del parón.

- 5.1 Qué es un hilo y en qué se diferencia de un proceso
- 5.2 `pthread_create`/`pthread_join`: ciclo de vida básico
- 5.3 Condición de carrera: provocarla a propósito y verla fallar
- 5.4 `pthread_mutex_t`: proteger una sección crítica
- 5.5 Repartir trabajo entre hilos (dividir el array en bloques)
- 5.6 Checkpoint práctico: versión con pthreads de los agregados, con y sin
  mutex, viendo la diferencia

## Módulo 6 — Paralelismo con OpenMP
> Objetivo: comparar con pthreads, entender cuándo usar cada uno.

- 6.1 `#pragma omp parallel for`: paralelismo declarativo
- 6.2 Reducciones (`reduction(+:total)`) — evitar mutex manuales
- 6.3 Comparativa de legibilidad y rendimiento: pthreads vs OpenMP
- 6.4 Checkpoint práctico: medir tiempos secuencial vs pthreads vs OpenMP con
  datasets de distinto tamaño

## Módulo 7 — Herramientas de calidad (transversal, se aplica desde el Módulo 1)
- 7.1 Flags del compilador (`-Wall -Wextra -Werror`) y por qué no son opcionales
- 7.2 Detección de fugas de memoria (`valgrind` o `AddressSanitizer` en macOS)
- 7.3 Makefiles: targets, dependencias, `re`/`clean`/`fclean`
