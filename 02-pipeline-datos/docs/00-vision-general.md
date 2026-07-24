# Visión general — Pipeline de procesamiento de datos

## Qué es este proyecto

Un sistema que procesa un volumen no trivial de datos en varias etapas:

1. **Ingesta y procesamiento intensivo** en C (parsing, limpieza, cómputo pesado,
   paralelizado con pthreads/OpenMP).
2. **Orquestación y lógica de negocio** en Java (invoca el procesador en C, gestiona
   trabajos, expone una API).
3. **Persistencia y análisis** en SQL (esquema relacional, agregaciones, consultas).
4. **Visualización** en HTML/CSS (+JS) (panel con tablas y gráficas de los resultados).

Todo el ciclo (Git/GitHub) se versiona con commits atómicos y, más adelante, con
integración continua vía GitHub Actions.

## Por qué este diseño enseña de verdad

- El **cuello de botella real** de rendimiento vive en C, así que ahí se nota de forma
  tangible la diferencia entre procesar en secuencial y en paralelo — no es un
  ejercicio artificial, es necesario para que el pipeline procese datos grandes en
  tiempo razonable.
- Java no es "el lenguaje donde repito la lógica de C", sino la capa que but no
  compite con C: hace lo que Java hace bien (orquestar, exponer servicios, gestionar
  colas de trabajo), reforzando cuándo usar cada herramienta.
- SQL dejará de ser "una tabla con dos SELECT" para convertirse en el sitio donde se
  toman decisiones de modelado (normalización, índices, agregaciones) sobre datos
  reales generados por el propio pipeline.
- El panel web cierra el ciclo: sin él, los resultados quedan "invisibles" en una
  base de datos. Con él, se practica consumo de una API/BD desde el navegador.

## Dominio de datos — DECISIÓN CERRADA (ver ADR-000)

**Serie temporal de ingresos y gastos de un pequeño negocio propio.**

El sistema ingiere movimientos económicos (fecha, importe, tipo ingreso/gasto,
categoría, descripción) exportados en CSV, y produce análisis agregados:
evolución mensual de ingresos/gastos, desglose por categoría, medias móviles de
cash flow, comparativas entre periodos (mes vs mes, año vs año).

Es un dominio con datos reales y propios, lo cual da motivación extra, y encaja
de forma natural con el patrón de series temporales: las agregaciones por
ventana temporal (día/semana/mes) y por categoría son perfectamente
paralelizables en C, y el resultado (un panel de salud financiera del negocio)
tiene utilidad más allá de lo puramente formativo.

> ⚠️ Al ser datos financieros reales, nunca se suben al repositorio. Ver
> `04-stack-tecnologico.md` para la política de datos (`.gitignore` y datos de
> ejemplo/anonimizados para desarrollo).

## Siguiente paso

Con el dominio cerrado, continuar con `02-arquitectura.md` (cómo se comunican
los componentes) y `03-roadmap-fases.md` (hitos ordenados de desarrollo).
