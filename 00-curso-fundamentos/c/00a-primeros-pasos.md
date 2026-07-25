# Lección 0.1 – 0.6 — Primeros pasos: qué es programar y cómo se hace en C

> Módulo 0 — Fundamentos absolutos. No se asume nada previo. Si algo te
> resulta obvio, mejor — significa que vamos bien de ritmo.

## 0.1 — Qué es un programa y qué hace un compilador

Un ordenador, en el fondo, solo sabe ejecutar instrucciones muy simples y
muy concretas, escritas en un formato binario que un humano no puede leer
cómodamente. **C** es un lenguaje de programación: una forma de escribir
instrucciones de manera legible para una persona, que luego una herramienta
llamada **compilador** traduce a ese formato binario que la máquina sí
entiende.

```
tu_programa.c  →  [ compilador ]  →  ejecutable binario  →  el ordenador lo corre
 (texto legible)                      (ceros y unos)
```

En tu caso, el compilador es `clang` (ya lo comprobaste en el proyecto:
`clang --version`). Cuando escribes `clang archivo.c -o programa`, le estás
diciendo "traduce `archivo.c` y guarda el resultado ejecutable con el
nombre `programa`".

## 0.2 — Tu primer programa: "Hola mundo"

```c
#include <stdio.h>

int main(void)
{
    printf("Hola, mundo\n");
    return 0;
}
```

Desglosemos cada línea, porque cada una tiene un motivo:

- **`#include <stdio.h>`**: le dice al compilador "voy a usar funciones de
  la librería estándar de entrada/salida" (`stdio` = *standard input/output*).
  `printf` vive ahí. Sin este include, el compilador no sabría qué es
  `printf`.
- **`int main(void)`**: todo programa en C necesita una función llamada
  `main` — es el punto donde el sistema operativo empieza a ejecutar tu
  programa. `int` antes del nombre significa que esta función va a devolver
  un número entero al terminar. `(void)` significa "no recibe argumentos"
  (más adelante verás `main(int argc, char **argv)`, que sí los recibe —
  pero de momento no lo necesitas).
- **`printf("Hola, mundo\n");`**: llama a la función `printf` (*print
  formatted*), que escribe texto por pantalla. `\n` es un carácter especial
  que representa un salto de línea — no son dos caracteres, es uno solo que
  se escribe con dos símbolos por convención.
- **`return 0;`**: la función `main` termina devolviendo 0. Por convención
  universal en programación, **0 significa "todo salió bien"**, y cualquier
  otro valor indica algún tipo de error. Esto es importante: lo volverás a
  ver constantemente (de hecho, ya lo usaste en `lista_push`, devolviendo 0
  para éxito y -1 para error, siguiendo esta misma convención).

### Cómo compilarlo y ejecutarlo

```bash
clang hola.c -o hola
./hola
```

`./hola` significa "ejecuta el fichero llamado `hola` que está en el
directorio actual" (`.` es "aquí mismo"). Sin el `./` delante, el sistema
buscaría un programa llamado `hola` en otros sitios del sistema, no en tu
carpeta.

## 0.3 — Variables y tipos

Una variable es un nombre que representa un valor guardado en memoria. En C,
**tienes que decir de qué tipo es** antes de usarla — a diferencia de otros
lenguajes (Python, JavaScript), C necesita saber de antemano cuánto espacio
reservar.

```c
int edad = 25;           // entero, sin decimales
float precio = 9.99f;    // decimal, precisión simple (la 'f' indica que
                          // es literal float y no double)
double saldo = 1500.75;  // decimal, precisión doble (más exacto, más
                          // espacio en memoria)
char letra = 'A';        // UN solo carácter (comillas simples)
```

Un tipo que ya usaste sin que te lo explicara del todo: **`size_t`**. Es un
entero especial, sin signo (nunca negativo), que el lenguaje usa para
representar tamaños y conteos — por eso `count` y `capacity` en tu
`t_lista_movimientos` son `size_t`, no `int`: un "número de elementos" nunca
tiene sentido que sea negativo.

## 0.4 — Operadores

```c
+  -  *  /  %      // aritméticos: suma, resta, multiplicación, división,
                    // módulo (resto de la división entera)
==  !=  <  >  <=  >=   // comparación: devuelven 1 (verdadero) o 0 (falso)
&&  ||  !           // lógicos: Y, O, NO
```

Una trampa clásica de principiante en C: `=` es **asignación** (guardar un
valor), `==` es **comparación** (preguntar si son iguales). Confundirlos es
uno de los bugs más comunes y el compilador no siempre te avisa:

```c
if (x = 5)   // esto ASIGNA 5 a x, y luego evalúa si 5 es "verdadero"
             // (siempre lo es, porque no es 0) — probablemente NO es lo
             // que querías
if (x == 5)  // esto sí COMPARA x con 5
```

## 0.5 — Control de flujo

```c
if (edad >= 18) {
    printf("Mayor de edad\n");
} else {
    printf("Menor de edad\n");
}

int i = 0;
while (i < 5) {
    printf("%d\n", i);
    i++;          // equivale a i = i + 1
}

for (int i = 0; i < 5; i++) {
    printf("%d\n", i);
}
```

El `for` es, en el fondo, un `while` con tres partes empaquetadas:
inicialización (`int i = 0`), condición de continuación (`i < 5`), y paso
(`i++`, ejecutado al final de cada vuelta). Es la estructura que más vas a
usar para recorrer arrays.

## 0.6 — Funciones

Una función agrupa código reutilizable, con una **firma** que describe qué
recibe y qué devuelve:

```c
int sumar(int a, int b)
{
    return a + b;
}

int main(void)
{
    int resultado = sumar(3, 4);   // resultado vale 7
    printf("%d\n", resultado);
    return 0;
}
```

`int sumar(int a, int b)` es la firma: devuelve un `int`, recibe dos `int`
como parámetros. Ya has visto (y escrito) firmas más complejas, como:

```c
int lista_push(t_lista_movimientos *lista, t_movimiento mov);
```

Misma idea exacta: devuelve `int`, recibe un puntero a lista y un
movimiento por valor. Nada distinto conceptualmente a `sumar`, solo con
tipos más elaborados.

## Checkpoint 0.1–0.6

1. ¿Qué imprime este programa y por qué? (razónalo paso a paso, no hace
   falta que lo compiles todavía)
   ```c
   int x = 3;
   if (x = 0) {
       printf("A\n");
   } else {
       printf("B\n");
   }
   ```
2. Escribe una función `int es_par(int n)` que devuelva 1 si `n` es par y 0
   si es impar (pista: el operador `%`).
3. ¿Por qué `main` devuelve `int` y no, por ejemplo, `void`? ¿Qué
   información se pierde si no devuelve nada?

Contesta estas tres y seguimos con la Lección 0.7–0.11 (arrays, cadenas,
punteros y las fases de compilación) — la última parte del Módulo 0 antes
de reencontrarte con `movimientos.c`, esta vez sabiendo *por qué* funciona
cada línea desde el principio.
