# Lección 2.2 — Conversión de texto a número: `strtod` y detección de errores

> Módulo 2 — Parsing. Objetivo: convertir el campo `importe` (extraído como
> texto con `extraer_campo`) en un `double` de verdad, detectando si el
> texto no era un número válido.

## El problema

Ya tienes `importe_texto` como cadena, por ejemplo `"1200.00"`. Necesitas
un `double` para guardarlo en `mov->importe`. La función estándar para esto
es `strtod` (*string to double*):

```c
#include <stdlib.h>

double strtod(const char *str, char **endptr);
```

## Cómo funciona

```c
char *fin_conversion;
double valor = strtod("1200.00", &fin_conversion);
```

`strtod` empieza a leer `str` desde el principio, interpreta todos los
caracteres que formen un número válido (dígitos, un punto decimal opcional,
signo opcional, notación científica si la hay), y se detiene en el primer
carácter que ya no encaje. Devuelve el número interpretado, y además — esto
es la parte clave — **si le pasas la dirección de un puntero como segundo
argumento (`&fin_conversion`)**, `strtod` actualiza ese puntero para que
apunte a la posición exacta donde dejó de leer.

## Por qué el segundo argumento es la pieza que detecta errores

Aquí está el truco para saber si la conversión fue válida o no:

```c
const char *texto = "1200.00";
char *fin;
double valor = strtod(texto, &fin);

if (fin == texto) {
    // ni siquiera se pudo leer un solo carácter como número —
    // el texto no empezaba con nada numérico (ej: "abc")
    printf("Error: no es un número\n");
} else if (*fin != '\0') {
    // se leyó ALGO como número, pero sobraban caracteres después
    // (ej: "1200.00xyz" — leyó 1200.00 y 'fin' quedó apuntando a 'x')
    printf("Error: caracteres sobrantes después del número\n");
} else {
    // fin apunta justo al final de la cadena — todo el texto era el número
    printf("Conversión correcta: %f\n", valor);
}
```

Esto es exactamente el mismo patrón conceptual que ya usaste en
`extraer_campo`: un puntero que te dice "hasta dónde llegué", y tú decides
si eso significa éxito o fallo comparándolo contra lo que esperabas.

**Por qué esto importa para tu CSV real:** una línea mal formada podría
tener `importe` como `"mil doscientos"` o `"1200,00"` (con coma en vez de
punto, un error de formato realista si alguien exporta el CSV desde un
Excel en español) o simplemente estar vacío. Sin esta comprobación,
`strtod` no "falla" de forma ruidosa — simplemente devuelve `0.0` en
algunos de esos casos, y tu programa seguiría funcionando con datos
silenciosamente incorrectos. Eso es mucho peor que un crash: un crash lo
ves inmediatamente, un dato erróneo que pasa desapercibido puede colarse
hasta el panel financiero final sin que nadie se dé cuenta.

## Un detalle sobre `const` que te vas a encontrar

Fíjate en que `strtod` pide `char **endptr` (puntero a puntero **no**
`const`), aunque tu `texto` original pueda ser `const char *`. Esto es una
peculiaridad histórica de la librería estándar de C — no te va a impedir
compilar con tus flags actuales en la práctica, pero si alguna vez ves un
warning relacionado con "discards const qualifier" en una función así, ahora
sabes de dónde viene.

## Checkpoint 2.2

Escribe una función con esta firma:

```c
// Intenta convertir 'texto' a double. Si la conversión es válida (todo el
// texto era un número, sin caracteres sobrantes, y al menos un carácter se
// leyó), guarda el resultado en '*out' y devuelve 1.
// Si no es válida, devuelve 0 y no toca '*out'.
int convertir_importe(const char *texto, double *out);
```

Pruébala en un `main` contra al menos estos casos, imprimiendo si cada uno
se consideró válido o no, y el valor si lo fue:

```c
convertir_importe("1200.00", &resultado);   // válido, 1200.00
convertir_importe("-350.50", &resultado);   // válido, -350.50 (tu CSV usa
                                              // negativos para gastos)
convertir_importe("abc", &resultado);        // inválido
convertir_importe("", &resultado);           // inválido
convertir_importe("12.5kg", &resultado);     // inválido (sobran caracteres)
```

Compílalo con las flags estrictas de siempre y pégame el código junto con
la salida. Con esto tendrás las dos piezas necesarias (extraer texto +
convertir a número) para escribir `parsear_linea` completa en la siguiente
lección, que ya reúne todo el Módulo 2 en una sola función que rellena un
`t_movimiento` real.
