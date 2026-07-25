# Lección 1.1 – 1.3 — Stack, Heap, `malloc` y `realloc`

> Módulo 1 — Memoria dinámica y structs. Objetivo de esta lección: entender
> por qué necesitamos memoria dinámica antes de escribir ni una línea de
> `lista_crear`.

## 1.1 — Stack vs Heap

Cuando un programa en C corre, usa dos zonas de memoria muy distintas:

**Stack (pila):** donde viven las variables locales normales.

```c
void foo(void) {
    int x = 5;              // vive en el stack
    t_movimiento mov;       // también vive en el stack
}                            // al salir de foo(), x y mov desaparecen SOLOS
```

Es automático y rápido, pero tiene una limitación clave: **el tamaño tiene
que conocerse en tiempo de compilación**, y la variable muere en cuanto
termina la función donde se declaró.

**Heap (montón):** memoria que tú pides explícitamente, que sigue viva hasta
que tú la liberas explícitamente, sin importar qué función la pidió.

```c
void foo(void) {
    int *x = malloc(sizeof(int));  // vive en el heap
    *x = 5;
}                                    // foo() termina, pero la memoria de x
                                     // SIGUE VIVA — y ahora está perdida
                                     // porque nadie más tiene el puntero
```

Ese último comentario es importante: si no guardas el puntero en algún sitio
antes de que la función termine, tienes una **fuga de memoria** (memory
leak) — memoria reservada que ya nadie puede liberar porque se perdió la
única referencia a ella.

### ¿Por qué nos importa aquí?

Nuestra lista de movimientos tiene que:
1. Sobrevivir más allá de la función que lee el CSV.
2. Crecer sin que sepamos de antemano cuántos movimientos habrá.

Ninguna de las dos cosas es posible con el stack. Por eso `t_lista_movimientos`
y su array interno `items` van a vivir en el heap.

## 1.2 — `malloc` / `free`: el contrato básico

```c
void *malloc(size_t tamaño_en_bytes);
```

Pide `tamaño_en_bytes` bytes al sistema operativo. Devuelve un puntero al
inicio de ese bloque, o `NULL` si no hay memoria disponible (raro, pero
**siempre** hay que comprobarlo — es un error de examen en 42 no hacerlo, y
en producción puede ser un crash real).

```c
int *numeros = malloc(10 * sizeof(int));
if (!numeros) {
    // manejar el error — normalmente devolver un código de fallo
    return NULL;
}
```

El contrato es simple pero absoluto: **quien hace `malloc`, es responsable
de hacer `free` exactamente una vez**, ni antes de tiempo (si liberas y
luego usas el puntero, es *use-after-free*, comportamiento indefinido) ni
nunca (fuga de memoria).

```c
free(numeros);
numeros = NULL;  // buena práctica: evita usarlo por error después de liberarlo
```

## 1.3 — `realloc` y por qué existe

Imagina que tu array de 10 enteros se queda pequeño y necesitas 20.
`realloc` le pide al sistema "cambia el tamaño de este bloque que ya tengo":

```c
void *realloc(void *ptr, size_t nuevo_tamaño);
```

Por dentro hace una de estas dos cosas:
- Si hay sitio libre justo después del bloque actual, lo agranda ahí mismo
  (rápido, no mueve nada).
- Si no hay sitio, reserva un bloque nuevo en otro lugar, **copia el
  contenido antiguo automáticamente**, libera el bloque viejo, y te devuelve
  el puntero al bloque nuevo.

Esto es clave: **no sabes cuál de los dos casos ha pasado**, así que siempre
tienes que quedarte con el puntero que `realloc` te devuelve, no asumir que
es el mismo de antes.

### La trampa que hay que evitar siempre

```c
// MAL
lista->items = realloc(lista->items, nueva_capacidad * sizeof(t_movimiento));
```

Si `realloc` falla, devuelve `NULL`. Si lo asignas directamente a
`lista->items`, acabas de **sobrescribir tu único puntero al bloque
original** con `NULL` — ese bloque antiguo, que seguía siendo válido, ahora
es inalcanzable. Fuga de memoria garantizada, y además tu lista queda rota.

```c
// BIEN
t_movimiento *tmp = realloc(lista->items, nueva_capacidad * sizeof(t_movimiento));
if (!tmp) {
    // lista->items sigue intacto, puedes manejar el error con calma
    return -1;
}
lista->items = tmp;
```

## Checkpoint 1.1–1.3

Antes de seguir a la Lección 2 (structs y el diseño completo del array
dinámico), respóndeme con tus propias palabras:

1. Tienes `int *p = malloc(40);` (10 enteros) y luego pierdes la única copia
   de `p` haciendo `p = malloc(80);` sin guardar el valor antiguo antes.
   ¿Qué ha pasado con esos primeros 40 bytes? ¿Se puede recuperar ese
   puntero de alguna forma?

2. ¿Por qué `realloc` puede devolver una dirección de memoria **distinta**
   a la que tenía el bloque original? ¿Qué tiene que hacer `realloc`
   internamente si decide moverlo?

No hace falta que sea una respuesta perfecta ni larga — dos o tres frases
por pregunta son suficientes. Cuando me las mandes, pasamos a la Lección 2,
donde por fin diseñamos `t_lista_movimientos` entero y escribes tú
`lista_crear`.
