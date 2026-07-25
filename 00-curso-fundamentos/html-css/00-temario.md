# Temario — HTML / CSS (+ JS mínimo)

Curso desde cero absoluto: no se asume ninguna experiencia previa
maquetando páginas web.

## Módulo 0 — Fundamentos absolutos
- 0.1 Qué es HTML y qué es CSS, y cómo se relacionan (contenido vs
  presentación)
- 0.2 Estructura mínima de un documento HTML (`<!DOCTYPE>`, `<html>`,
  `<head>`, `<body>`)
- 0.3 Etiquetas semánticas comunes (`<h1>`, `<p>`, `<table>`, `<section>`)
  vs `<div>` genérico
- 0.4 Cómo enlazar un CSS a un HTML, selectores básicos (por etiqueta,
  clase, id)
- 0.5 Especificidad CSS (por qué a veces un estilo "no se aplica")
- 0.6 Modelo de caja (`box-model`): margin, border, padding, content
- 0.7 Checkpoint práctico: página HTML mínima con algo de CSS propio,
  abierta y verificada en el navegador

## Módulo 1 — Maquetación del panel
> Objetivo: estructura visual del panel de análisis financiero.

- 1.1 Layout con Flexbox (para la disposición general de tarjetas/secciones)
- 1.2 Layout con Grid (para la tabla de resumen mensual, si aplica)
- 1.3 Variables CSS (`:root { --color-... }`) para un sistema de diseño
  propio mínimo
- 1.4 Checkpoint práctico: maqueta estática del panel, sin datos reales
  todavía

## Módulo 2 — JavaScript mínimo para consumir la API
> Objetivo: pasar de HTML estático a datos reales del backend.

- 2.1 `fetch()`: petición GET básica y manejo de la respuesta (`.then`/`async`)
- 2.2 Manipulación del DOM: insertar filas de tabla dinámicamente
- 2.3 Checkpoint práctico: la tabla de resumen mensual se rellena desde la
  API de Java

## Módulo 3 — Visualización con Chart.js
- 3.1 Incluir Chart.js vía CDN
- 3.2 Gráfica de líneas (evolución ingresos/gastos por mes)
- 3.3 Gráfica de barras/tarta (desglose por categoría)
- 3.4 Checkpoint práctico: panel con al menos una gráfica alimentada por
  datos reales

## Módulo 4 — Responsive básico
- 4.1 `@media queries`: adaptar el layout a móvil
- 4.2 Checkpoint práctico: el panel se ve usable en una ventana estrecha
