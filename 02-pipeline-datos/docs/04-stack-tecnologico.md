# Stack tecnológico

Se fija aquí para evitar decisiones improvisadas a mitad de desarrollo. Si algo
cambia, se actualiza este documento y se añade una entrada en
`05-decisiones-tecnicas.md` explicando el motivo del cambio.

## C

- **Compilador:** GCC o Clang (el que ya se use en el entorno de 42).
- **Estándar:** C11 (para poder usar `<threads.h>` si se quiere comparar con la
  API de hilos estándar, aunque el foco principal será **pthreads** por ser el
  estándar de facto en Linux/macOS).
- **Paralelismo:**
  - `pthreads` (POSIX Threads) — ya disponible en el sistema, sin instalación.
  - `OpenMP` — requiere compilar con `-fopenmp`; comprobar disponibilidad en
    macOS (con Clang de Xcode no viene por defecto, puede requerir
    `libomp` vía Homebrew: `brew install libomp`).
- **Build:** Makefile propio (sin CMake por ahora, para no añadir una capa de
  abstracción antes de necesitarla).
- **Debugging/memoria:** `valgrind` si está disponible en el entorno, o
  `AddressSanitizer` (`-fsanitize=address`) como alternativa en macOS.
- **JSON:** escritura manual en la Fase 1-2 (ejercicio formativo). Si más
  adelante se complica demasiado, valorar `cJSON` (documentar el cambio como
  ADR si ocurre).

## Java

- **JDK:** versión LTS más reciente disponible en el sistema (verificar con
  `java -version` al empezar la Fase 3 y anotar aquí la versión exacta usada).
- **Build:** Maven (más extendido y con más documentación para quien viene de
  DAM que Gradle; se puede reconsiderar más adelante).
- **Framework HTTP:** **Javalin** (mínimo, sin las convenciones "mágicas" de
  Spring Boot — para esta fase interesa entender qué hace cada pieza, no
  delegarlo todo en el framework).
- **JDBC:** driver oficial del motor SQL elegido (ver abajo).
- **JSON:** **Jackson** (`jackson-databind`), estándar de facto.
- **Tests:** JUnit 5.

## SQL

- **Motor:** **PostgreSQL** si se puede instalar localmente (más cercano a lo
  que se usa en la industria y con mejor soporte de tipos), con **SQLite**
  como alternativa de arranque rápido si instalar Postgres supone fricción al
  principio (permite empezar la Fase 4 sin bloquear por infraestructura).
  → Decisión final a tomar al llegar a la Fase 4, documentada como ADR.
- **Migraciones:** scripts `.sql` numerados en `sql/schema/` al principio
  (`001_create_movimientos.sql`, `002_create_categorias.sql`, ...). Se puede
  valorar Flyway más adelante si se quiere practicar esa herramienta.

## Web

- **Sin framework de JS al principio** (Vanilla JS + `fetch`), para entender
  el ciclo completo antes de añadir React/Vue u otros.
- **Gráficas:** Chart.js (ligero, buena documentación, CDN disponible).
- **CSS:** propio, con variables CSS (`:root { --color-... }`), sin frameworks
  tipo Bootstrap al principio.

## Git / GitHub

- Un repositorio único (monorepo) para todo `Programación/`, con carpetas por
  proyecto. Se reconsiderará separar en repos independientes si el proyecto
  crece mucho.
- Convención de ramas: `fase-N-nombre-corto` (ej. `fase-2-pthreads`).
- Convención de commits: imperativo, en español, con prefijo opcional de tipo
  (`feat:`, `fix:`, `docs:`, `test:`) — a decidir si se adopta Conventional
  Commits formalmente (anotar como ADR si se adopta).

## Política de datos sensibles

Este proyecto trabaja con datos financieros reales de un negocio propio. Reglas
no negociables:

1. **Nunca** se sube al repositorio ningún CSV con movimientos económicos
   reales. El `.gitignore` de `02-pipeline-datos/` debe excluir explícitamente
   cualquier ruta de datos reales (por ejemplo, una carpeta `data/real/` fuera
   de control de versiones).
2. Para desarrollo y para cualquier ejemplo en la documentación se usan
   **datos ficticios o anonimizados**, generados a propósito para el proyecto.
3. Si en el futuro se despliega la API fuera de `localhost`, se añade
   autenticación antes de exponer cualquier endpoint (recogido como tarea
   opcional en la Fase 6 del roadmap).
