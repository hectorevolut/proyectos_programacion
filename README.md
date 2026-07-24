# Programación — Curso práctico integrador

Este repositorio es la **única fuente de verdad** de mi proceso de aprendizaje y de los
proyectos que lo sostienen. Todo lo que se decide, se documenta aquí en Markdown antes
(o a la vez) que se escribe código. Si algo no está en un `.md`, no se considera decidido.

## Contexto de partida

- **C:** completado en 42 hasta `ft_printf`. Buen manejo de punteros, memoria manual,
  structs y Makefiles. Pendiente: concurrencia (pthreads, mutex), paralelismo (OpenMP),
  y en general "reset" por parón prolongado.
- **Java / SQL / HTML / CSS:** módulo DAM aprobado en su parte teórica, falta proyecto
  final y prácticas. Poca experiencia real integrando todo en un sistema completo.
- **Git / GitHub:** uso básico, se busca practicar flujo de ramas, PRs, commits
  atómicos y (más adelante) CI con GitHub Actions.

## Filosofía del curso

Cada proyecto es una excusa para tocar **todas** las tecnologías (C, Java, SQL,
HTML/CSS, Git/GitHub) en un sistema real, no en ejercicios sueltos. Los proyectos
están ordenados por dificultad creciente y cada uno construye sobre lo aprendido en
el anterior.

## Proyectos

| # | Carpeta | Nombre | Objetivo pedagógico principal | Estado |
|---|---|---|---|---|
| 1 | [`01-simulacion-paralela/`](./01-simulacion-paralela) | Motor de simulación paralela | Paralelismo en C (pthreads, OpenMP) medido y visualizado | 💤 Pendiente de diseñar |
| 2 | [`02-pipeline-datos/`](./02-pipeline-datos) | Pipeline de procesamiento de datos | Arquitectura completa C↔Java↔SQL↔Web, SQL en profundidad | 🚧 En diseño |
| 3 | [`03-cliente-servidor/`](./03-cliente-servidor) | Sistema cliente-servidor en tiempo real | Sockets, concurrencia real, redes | 💤 Pendiente de diseñar |

## Cómo se documenta cada proyecto

Cada carpeta de proyecto tiene su propia carpeta `docs/` con, como mínimo:

- `00-vision-general.md` — qué se construye y por qué.
- `01-objetivos-aprendizaje.md` — qué conceptos concretos se practican y en qué fase.
- `02-arquitectura.md` — cómo se comunican C, Java, SQL y Web entre sí.
- `03-roadmap-fases.md` — hitos ordenados, de lo más simple a lo más complejo.
- `04-stack-tecnologico.md` — herramientas, versiones, librerías elegidas y por qué.
- `05-decisiones-tecnicas.md` — registro tipo ADR (Architecture Decision Record) de
  cada decisión relevante, con alternativas consideradas y motivo del descarte.

## Flujo de trabajo con Git

- `main` siempre debe compilar/ejecutar correctamente.
- Una rama por fase o funcionalidad (`feature/...`, `fase-2-pthreads`, etc.).
- Commits atómicos y en español, en imperativo: `Añade parser de logs en C`.
- Nada se da por "decidido" hasta que está en un `.md` correspondiente.
