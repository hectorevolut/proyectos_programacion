# Lección 0.7 – 0.11 — Arrays, cadenas, punteros y cómo compila el compilador

> Módulo 0 — Fundamentos absolutos. Última parte antes de reencontrarte con
> `movimientos.c`, esta vez entendiendo cada pieza desde la base.

## 0.7 — Arrays de tamaño fijo

Un array es una secuencia de elementos del mismo tipo, guardados uno detrás
de otro en memoria, con tamaño fijo decidido al declararlo:

```c
int numeros[5] = {10, 20, 30, 40, 50};

printf("%d\n", numeros[0]);   // 10 — el primer elemento está en la posición 0
printf("%d\n", numeros[4]);   // 50 — el último de un array de 5 está en la 4
```

**Trampa clásica:** los índices empiezan en 0, así que un array de 5
elementos va de `numeros[0]` a `numeros[4]`. Acceder a `numeros[5]` es un
error grave (*out of bounds*) — el compilador normalmente no te avisa, y el
programa puede leer basura, corromper otra variable, o crashear. Es
responsabilidad tuya no pasarte.

```c
for (int i = 0; i < 5; i++) {
    printf("%d\n", numeros[i]);
}
```

Este patrón (`for` con `i` de 0 hasta el tamaño del array) es el que vas a
usar constantemente para recorrer `lista->items` en `agregados.c` más
adelante — con la diferencia de que ahí el "tamaño" no es un número fijo
escrito a mano, sino `lista->count`.

## 0.8 — Cadenas de caracteres

En C no existe un tipo "string" nativo. Una cadena es, por convención, un
array de `char` que termina en un byte especial: `\0` (carácter nulo, valor
numérico 0 — no es lo mismo que el carácter `'0'`, que es el dígito cero).

```c
char saludo[] = "hola";
```

En memoria, esto ocupa 5 bytes, no 4:

```
saludo → [ 'h' ][ 'o' ][ 'l' ][ 'a' ][ '\0' ]
            [0]    [1]    [2]    [3]    [4]
```

El `\0` no se ve al imprimir, pero es lo que le dice a funciones como
`printf` o `strlen` "aquí termina la cadena, no sigas leyendo memoria más
allá". Si un array de `char` no tiene ese `\0` en algún punto, técnicamente
no es una "cadena" válida, y funciones como `strlen` seguirían leyendo
memoria basura hasta encontrar un byte 0 por casualidad — otra fuente
clásica de bugs.

Funciones habituales de `<string.h>`:

```c
strlen(saludo);        // 4 — cuenta caracteres SIN contar el '\0'
strcmp(a, b);           // 0 si son iguales, distinto de 0 si no
                         // (NO es un booleano — el valor exacto indica
                         // además cuál es "mayor" alfabéticamente, aunque
                         // rara vez lo necesites)
strcpy(destino, origen); // copia origen a destino (cuidado: no comprueba
                         // que destino tenga sitio suficiente)
```

Esto es exactamente lo que vas a necesitar en el Módulo 2, cuando
`parsear_linea` tenga que recorrer una línea del CSV buscando las comas que
separan los campos.

## 0.9 — Punteros: qué son de verdad

Cada variable, al guardarse en memoria, ocupa una **dirección** — como una
casilla numerada en una calle muy larga. Un puntero es una variable que, en
vez de guardar un valor "normal", guarda esa dirección.

```c
int x = 5;
int *p = &x;   // '&x' significa "la dirección donde vive x"
               // p ahora guarda esa dirección, no el valor 5

printf("%d\n", x);    // 5
printf("%d\n", *p);   // 5 también — '*p' significa "ve a la dirección
                       // que guarda p, y dime qué valor hay ahí"

*p = 10;               // "ve a esa dirección y escribe 10"
printf("%d\n", x);    // 10 — cambió x, aunque modificaste a través de p
```

`&` = "dame la dirección de" (se usa sobre una variable, para obtener un
puntero a ella). `*` = "ve a esta dirección y opera sobre el valor que hay
ahí" (se usa sobre un puntero, para leer o escribir lo que apunta).

### Por qué esto importa tanto en C

Cuando una función recibe una variable normal (por valor), recibe una
**copia** — cambiarla dentro de la función no afecta al original:

```c
void incrementar(int n) {
    n = n + 1;   // esto NO afecta a la variable que se pasó
}
```

Cuando recibe un puntero, puede modificar el original a través de él:

```c
void incrementar(int *n) {
    *n = *n + 1;   // esto SÍ afecta a la variable original
}

int main(void) {
    int x = 5;
    incrementar(&x);
    printf("%d\n", x);   // 6
    return 0;
}
```

Esta es la razón profunda por la que `lista_push` recibe
`t_lista_movimientos *lista` (un puntero) en vez de `t_lista_movimientos
lista`: necesita poder modificar la lista original (añadir un elemento,
cambiar `count`), no trabajar sobre una copia inútil que desaparece al
terminar la función.

## 0.10 — Las 4 fases de la compilación

Cuando ejecutas `clang archivo.c -o programa`, por debajo pasan 4 fases:

1. **Preprocesado:** expande `#include`, `#define`. El resultado es un
   único fichero C "aplanado", sin includes ni macros — solo código C puro.
2. **Compilación:** traduce ese C aplanado a código ensamblador. Aquí
   aparecen la mayoría de errores de sintaxis y de tipos (`-Wall -Wextra
   -Werror` actúan en esta fase).
3. **Ensamblado:** convierte el ensamblador a código máquina, generando un
   fichero objeto (`.o`) por cada `.c`.
4. **Enlazado (linking):** une todos los `.o` con las librerías necesarias
   en un único ejecutable. Los errores de "undefined reference" pertenecen
   a esta fase — el compilador encontró la declaración de una función (en
   un `.h`) pero no su implementación en ningún `.o`.

Esto explica el `#ifndef MOVIMIENTOS_H ... #endif` de tu `movimientos.h`
(*include guard*): sin él, si dos `.c` distintos incluyen el mismo `.h`, la
fase de preprocesado podría duplicar declaraciones y romper la fase de
compilación.

## Checkpoint 0.7 – 0.11 (cierre del Módulo 0)

Programa pequeño que combina todo lo del módulo. Escríbelo, compílalo y
pégame la salida:

```c
#include <stdio.h>
#include <string.h>

// Completa tú esta función: recibe un array de enteros y su tamaño,
// y devuelve la suma de todos sus elementos.
int sumar_array(int *arr, int tamano)
{
    // tu código aquí
}

int main(void)
{
    int numeros[5] = {10, 20, 30, 40, 50};
    int total = sumar_array(numeros, 5);
    printf("Suma: %d\n", total);

    char nombre[] = "Hector";
    printf("El nombre tiene %zu caracteres\n", strlen(nombre));

    return 0;
}
```

Fíjate en la firma de `sumar_array`: recibe `int *arr` (un puntero a
`int`), no un array con tamaño fijo escrito en la firma. Esto es a
propósito — en C, cuando pasas un array a una función, en realidad se pasa
como puntero a su primer elemento (por eso hace falta pasar también el
`tamano` por separado; el puntero, por sí solo, no sabe cuántos elementos
hay detrás).

Complétala, compílala con las mismas flags estrictas que venimos usando:

```bash
clang -Wall -Wextra -Werror -std=c11 archivo.c -o archivo
./archivo
```

Con este checkpoint superado, el Módulo 0 queda cerrado del todo, y en la
siguiente lección volvemos directos al Módulo 1 — que ya tienes hecho, pero
esta vez con la base completa debajo.
