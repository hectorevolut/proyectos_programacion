# Temario — Git / GitHub

## Módulo 1 — Flujo básico (✅ ya completado en la práctica)
- 1.1 `git init`, `git add`, `git commit` — qué es realmente un commit
  (una fotografía, no un "guardado incremental")
- 1.2 Repositorio remoto: `git remote add`, `git push -u`
- 1.3 `git status`, `git log`, `git diff` — inspeccionar antes de actuar
- 1.4 Checkpoint: ya hecho — repo creado, primer commit, push a GitHub

## Módulo 2 — Ramas
> Objetivo: una rama por fase del roadmap, como se definió en el README raíz.

- 2.1 Qué es una rama de verdad (un puntero móvil a un commit, no una
  "copia" de archivos)
- 2.2 `git branch`, `git switch`/`git checkout -b`
- 2.3 Fusionar: `git merge` vs qué es un conflicto y cómo se resuelve
- 2.4 Checkpoint práctico: crear `fase-1-parser-csv`, trabajar ahí, y
  fusionarla a `main` cuando el Módulo 1 de C esté cerrado

## Módulo 3 — Pull Requests (aunque trabajes en solitario)
- 3.1 Por qué merece la pena aunque no haya nadie revisando
- 3.2 Abrir un PR desde una rama, leer el diff generado
- 3.3 Checkpoint práctico: primer PR de una fase completa

## Módulo 4 — Buenas prácticas de commits
- 4.1 Commits atómicos: qué significa y por qué facilita revertir errores
- 4.2 Mensajes descriptivos en imperativo
- 4.3 `.gitignore`: qué no debe entrar nunca en el repo (ya aplicado en
  `02-pipeline-datos/.gitignore`)

## Módulo 5 — GitHub Actions (fase avanzada del roadmap, Fase 6)
- 5.1 Qué es un workflow, sintaxis mínima de un `.yml`
- 5.2 Workflow que compila `c-core` en cada push
- 5.3 Workflow que ejecuta tests de `java-service` en cada push
- 5.4 Checkpoint práctico: badge de "build passing" en el README
