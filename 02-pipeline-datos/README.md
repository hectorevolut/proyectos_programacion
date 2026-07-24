# 02 — Pipeline de procesamiento de datos masivos

🚧 **En diseño.** Este es el proyecto activo actualmente.

## Estructura

```
02-pipeline-datos/
├── docs/            ← fuente de verdad: visión, arquitectura, roadmap, decisiones
├── c-core/           ← motor de procesamiento intensivo en C (parsing, paralelismo)
├── java-service/      ← orquestación, API, lógica de negocio en Java
├── sql/              ← esquema de base de datos, migraciones, queries
└── web/              ← panel de reporting (HTML/CSS/JS)
```

## Punto de partida

Antes de escribir una sola línea de código, hay que fijar en `docs/` el dominio de
datos concreto, la arquitectura de comunicación entre componentes y el roadmap por
fases. Ver [`docs/00-vision-general.md`](./docs/00-vision-general.md).

## Estado actual

- [ ] Dominio de datos decidido
- [ ] Arquitectura de comunicación C ↔ Java ↔ SQL ↔ Web definida
- [ ] Roadmap de fases definido
- [ ] Stack tecnológico y versiones fijadas
- [ ] Primer commit de esqueleto de código
