# Lección 1.4 – 1.6 — Structs, `sizeof`, copia por valor y el array dinámico completo

> Módulo 1 — Memoria dinámica y structs. Al final de esta lección escribes
> `lista_crear` tú mismo.

## 1.4 — Structs: memoria contigua y `sizeof`

Un `struct` en C es, por debajo, un bloque de memoria contiguo donde cada
campo ocupa un hueco fijo, uno detrás de otro (con algo de relleno que añade
el compilador para alinear los datos — no afecta a lo que vamos a hacer,
pero por eso `sizeof(t_movimiento)` no es exactamente "la suma de los
tamaños de cada campo", puede ser un poco más grande).

```c
typedef struct {
    char    fecha[11];
    double  importe;
    char    tipo[8];
    char    categoria[32];
    char    descripcion[128];
} t_movimiento;
```

`sizeof(t_movimiento)` te da ese tamaño total en bytes — el número exacto
que necesitas cuando reservas memoria para varios movimientos seguidos:

```c
malloc(10 * sizeof(t_movimiento));  // sitio para 10 movimientos, contiguos
```

Esto es justo lo que hace posible el "array dinámico": como todos los
`t_movimiento` ocupan el mismo tamaño fijo, el sistema (y tú) puede calcular
dónde está el elemento `i` con pura aritmética: `items + i` (el compilador
hace `i * sizeof(t_movimiento)` por ti automáticamente al indexar).

## 1.5 — Copia por valor vs por puntero

Esto es distinto a lo que sueles hacer con cadenas en 42, así que presta
atención.

```c
t_movimiento a = {...};
t_movimiento b = a;      // COPIA completa: b tiene sus propios bytes,
                          // independientes de a
b.importe = 999;         // esto NO afecta a a.importe
```

Cuando pasas un struct **por valor** a una función (no un puntero a él), la
función recibe una copia:

```c
int lista_push(t_lista_movimientos *lista, t_movimiento mov) {
    // 'mov' aquí es una copia. Modificarla dentro de la función no afecta
    // al 'mov' que tenía quien llamó a la función.
}
```

¿Por qué diseñamos `lista_push` así, recibiendo el struct por valor en vez
de un puntero (`t_movimiento *mov`)? Para un struct pequeño como este es
perfectamente razonable y simplifica el código de quien lo llama (no tiene
que preocuparse por punteros a variables locales que podrían dejar de
existir). Para structs muy grandes, se preferiría pasar por puntero
(`const t_movimiento *mov`) para no copiar de más — es un trade-off entre
claridad y rendimiento que verás constantemente en C.

## 1.6 — Diseño completo de `t_lista_movimientos`

Ya tienes todo lo necesario. Repasemos el struct que ya está en tu
`movimientos.h`:

```c
typedef struct {
    t_movimiento *items;     // puntero al bloque de memoria en el heap
    size_t        count;     // cuántos movimientos hay metidos de verdad
    size_t        capacity;  // para cuántos hay sitio reservado
} t_lista_movimientos;
```

### El ciclo de vida completo

```
lista_crear(4)
    │
    ▼
items → [ ?? ][ ?? ][ ?? ][ ?? ]     count=0  capacity=4

lista_push(mov0)
    │
    ▼
items → [mov0][ ?? ][ ?? ][ ?? ]     count=1  capacity=4

... (tres pushes más) ...

items → [mov0][mov1][mov2][mov3]     count=4  capacity=4

lista_push(mov4)   ← count == capacity, hay que crecer PRIMERO
    │
    ▼ (realloc a capacidad 8, luego se copia mov4)
items → [mov0][mov1][mov2][mov3][mov4][ ?? ][ ?? ][ ?? ]   count=5  capacity=8

lista_destruir(lista)
    │
    ▼
free(items)   ← libera el bloque de movimientos
free(lista)   ← libera el struct contenedor en sí
```

Fíjate en el último paso, que conecta con lo que ya intuías en el checkpoint
anterior: `lista` (el struct contenedor, con `count`/`capacity`/`items`) y
`lista->items` (el array de movimientos) son **dos bloques de memoria
distintos**, reservados por separado, así que hay que liberarlos por
separado. Si solo haces `free(lista)`, el array `items` queda huérfano — una
fuga de memoria idéntica a la del checkpoint 1.

### Ahora te toca a ti: `lista_crear`

Escribe la función con esta firma (ya está en tu `movimientos.h`):

```c
t_lista_movimientos *lista_crear(size_t capacidad_inicial);
```

Tiene que:
1. Reservar memoria para el struct `t_lista_movimientos` en sí (`malloc`,
   comprobar que no es `NULL`).
2. Reservar memoria para `capacidad_inicial` elementos de `items`
   (`malloc`, comprobar que no es `NULL` — y si falla, no olvides liberar lo
   que ya habías reservado en el paso 1, o tendrás una fuga).
3. Inicializar `count` a 0 y `capacity` a `capacidad_inicial`.
4. Devolver el puntero a la lista ya lista para usar.

**Pistas, no solución:**
- El struct devuelto es un puntero (`t_lista_movimientos *`), así que dentro
  de la función necesitas una variable puntero, no una variable struct
  normal.
- Si el segundo `malloc` falla después de que el primero tuvo éxito, ¿qué
  tienes que liberar antes de devolver `NULL`? (Pista: exactamente lo que
  reservaste en el paso 1 — si no lo liberas ahí, se pierde para siempre,
  igual que en el checkpoint anterior.)

## Checkpoint 1.4–1.6

Escribe tu versión de `lista_crear` en `src/movimientos.c` y pégamela aquí
(compile o no). La reviso contigo línea a línea antes de seguir con
`lista_push`, que es donde entra en juego todo lo de `realloc` de la
lección anterior.
