# Registro de decisiones técnicas (ADR)

Cada decisión relevante se documenta aquí en el momento en que se toma, con el
formato: contexto → opciones consideradas → decisión → motivo → consecuencias.
No se borran decisiones antiguas aunque se reemplacen; se añade una nueva entrada
que referencia a la anterior como "superada".

---

## ADR-000 — Estado: CERRADA
**Fecha:** 2026-07-24
**Título:** Dominio de datos del pipeline

**Contexto:** el pipeline necesita un tipo de dato concreto sobre el que trabajar
(ver opciones en `00-vision-general.md`).

**Opciones consideradas:**
- A. Analizador de logs de servidor
- B. Analizador de corpus de texto (frecuencias / n-gramas)
- C. Analizador de series temporales (meteorología / finanzas)
- D. Otro dominio propuesto por el usuario

**Decisión:** Opción D (variante de C) — **serie temporal de ingresos y gastos de
un pequeño negocio propio**. El sistema ingiere movimientos económicos
(fecha, importe, tipo ingreso/gasto, categoría, descripción) y produce análisis
agregados: evolución mensual, desglose por categoría, medias móviles de cash
flow, comparativas entre periodos.

**Motivo:** es un dominio real y con datos propios (mayor motivación que un
dataset genérico), encaja perfectamente con el patrón de series temporales
(agregaciones por ventana, procesables en paralelo por mes/categoría/año), y el
resultado final (un panel de análisis financiero del propio negocio) tiene
utilidad práctica más allá del aprendizaje.

**Consecuencias:**
- El formato de entrada en C será CSV de movimientos (el formato típico de
  exportación bancaria/contable).
- El esquema SQL girará en torno a `movimientos`, `categorias` y tablas de
  agregados precalculados.
- El panel web mostrará gráficas de series temporales (línea/área) e ingresos
  vs gastos por categoría.
- Al tratarse de datos financieros reales del usuario, se documentará en
  `04-stack-tecnologico.md` cómo mantenerlos fuera de git (`.gitignore`) y
  usar únicamente datos de ejemplo/anonimizados en el repositorio público.
