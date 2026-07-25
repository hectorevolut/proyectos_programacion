# Temario — SQL

Curso desde cero absoluto: no se asume ninguna experiencia previa con bases
de datos ni con SQL.

## Módulo 0 — Fundamentos absolutos de bases de datos
- 0.1 Qué es una base de datos relacional (tablas, filas, columnas — con
  ejemplos concretos, no abstractos)
- 0.2 Instalar y arrancar un motor SQL local (SQLite para empezar, sin
  fricción de instalación)
- 0.3 Crear una tabla: `CREATE TABLE`, tipos de datos comunes
- 0.4 Insertar datos: `INSERT INTO`
- 0.5 Consultar datos: `SELECT`, `WHERE`, `ORDER BY`, `LIMIT`
- 0.6 Actualizar y borrar: `UPDATE`, `DELETE` (y por qué siempre hay que
  llevar un `WHERE`)
- 0.7 Diferencias prácticas SQLite vs PostgreSQL (para la decisión pendiente
  en `04-stack-tecnologico.md` del proyecto)
- 0.8 Checkpoint práctico: crear una tabla propia de ejemplo, insertar
  varias filas y consultarlas con distintos filtros

## Módulo 1 — Diseño de esquema
> Objetivo: tablas `movimientos`, `categorias`, `agregados_mensuales`.

- 1.1 De los datos reales al modelo: qué columnas, qué tipos, qué es
  obligatorio
- 1.2 Claves primarias y por qué casi nunca deberían ser "con significado"
  (usar un ID autonumérico en vez de la fecha como clave, por ejemplo)
- 1.3 Claves foráneas: relacionar `movimientos` con `categorias`
- 1.4 Normalización básica (evitar repetir el nombre de categoría en cada
  fila) sin sobre-normalizar para este caso de uso
- 1.5 Checkpoint práctico: script `001_create_movimientos.sql` y
  `002_create_categorias.sql`

## Módulo 2 — Consultas de agregación
> Objetivo: las consultas que alimentan el panel web.

- 2.1 `GROUP BY` y funciones de agregación (`SUM`, `AVG`, `COUNT`)
- 2.2 Filtrado con `WHERE` antes de agrupar vs `HAVING` después
- 2.3 `JOIN` entre `movimientos` y `categorias`
- 2.4 Checkpoint práctico: consulta de resumen mensual y de desglose por
  categoría

## Módulo 3 — Índices y rendimiento
- 3.1 Qué es un índice (intuición: el índice de un libro, no magia)
- 3.2 `EXPLAIN`: ver si una consulta usa un índice o no
- 3.3 Cuándo un índice ayuda y cuándo sobra (no todo se indexa)
- 3.4 Checkpoint práctico: añadir un índice y comprobar el cambio con
  `EXPLAIN`

## Módulo 4 — Transacciones
- 4.1 Qué garantiza una transacción (atomicidad, en términos simples)
- 4.2 `BEGIN`/`COMMIT`/`ROLLBACK`
- 4.3 Por qué la importación de un CSV entero debería ser una única
  transacción (todo o nada)
- 4.4 Checkpoint práctico: simular un fallo a mitad de importación y ver el
  rollback funcionando

## Módulo 5 — JDBC desde Java (cruce con el temario de Java, Módulo 6)
- Se desarrolla en el temario de Java para no duplicar contenido; este
  módulo queda como referencia cruzada.
