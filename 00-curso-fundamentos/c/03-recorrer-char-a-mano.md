# Lección 2.1 — Recorrer un `char *` a mano (sin `strtok`)

> Módulo 2 — Parsing y manejo de cadenas a fondo. Objetivo: sentar la base
> para `parsear_linea`, que vas a escribir en la siguiente lección.

## El problema concreto

Una línea de tu CSV tiene esta pinta:

```
2025-01-05,1200.00,ingreso,ventas_producto_a,Venta pedido #101
```

Cinco campos separados por comas. Necesitas extraer cada uno por separado
para rellenar un `t_movimiento`. La aproximación "fácil" sería `strtok`,
pero la vamos a evitar a propósito — no porque esté prohibida, sino porque
recorrer la cadena tú mismo con punteros es exactamente el músculo que
`ft_printf` te hizo trabajar, y es el que queremos recuperar de verdad, no
delegarlo en una función de librería.

## La técnica: dos punteros que avanzan

La idea central: tienes un puntero que marca **dónde empieza el campo
actual**, y otro (o el mismo, moviéndose) que **busca el siguiente
separador** (la coma). Cuando lo encuentra, ya sabes dónde termina el campo.

```c
const char *inicio = linea;         // apunta al principio del campo actual
const char *fin = linea;

while (*fin != ',' && *fin != '\0') {
    fin++;                           // avanza mientras no encuentre coma
                                      // ni el final de la cadena
}

// en este punto: [inicio, fin) es el campo (fin apunta a la coma o al '\0')
size_t longitud_campo = fin - inicio;  // aritmética de punteros: la
                                         // diferencia entre dos punteros al
                                         // mismo array da su distancia
```

**Repasemos por qué `*fin != ','` funciona:** `fin` es un puntero a `char`.
`*fin` desreferencia ese puntero — te da el carácter que hay en esa
posición ahora mismo. Comparas ese carácter contra `','`. Mientras no sea
una coma (y no sea el final de cadena `'\0'`, para no salirte de la línea
si es el último campo), avanzas `fin` una posición con `fin++`.

## Copiar el campo extraído a un buffer

Una vez que sabes `inicio` y `longitud_campo`, necesitas copiar esos
caracteres a algún sitio permanente (por ejemplo, `mov->fecha`, que es un
array de tamaño fijo en tu struct):

```c
char destino[FECHA_LEN];

if (longitud_campo >= FECHA_LEN) {
    // el campo es más largo de lo que cabe — línea inválida, rechazar
}

memcpy(destino, inicio, longitud_campo);
destino[longitud_campo] = '\0';   // OJO: memcpy NO añade el '\0' por ti,
                                    // tienes que ponerlo tú a mano
```

`memcpy(destino, origen, n)` copia `n` bytes tal cual, sin mirar si hay un
`\0` en medio (a diferencia de `strcpy`, que copia hasta encontrar un
`\0`). Aquí es la herramienta correcta porque tú ya sabes exactamente
cuántos bytes quieres copiar (`longitud_campo`), calculados con la
aritmética de punteros de arriba.

**Por qué la comprobación de tamaño es obligatoria, no opcional:** si
`longitud_campo` fuera mayor o igual que `FECHA_LEN` (el tamaño del array
destino) y copiaras de todas formas, escribirías fuera de los límites del
array — un *buffer overflow*, el mismo tipo de bug de seguridad clásico que
en C hay que prevenir a mano en cada sitio donde copies datos externos
(y el CSV es, precisamente, datos externos: no confíes en que siempre viene
bien formado).

## Avanzar al siguiente campo

Después de procesar un campo, para pasar al siguiente:

```c
if (*fin == ',') {
    fin++;              // sáltate la coma
    inicio = fin;        // el siguiente campo empieza justo después
} else {
    // *fin == '\0' → era el último campo de la línea, no hay más que hacer
}
```

## Checkpoint 2.1

Escribe una función con esta firma:

```c
// Copia en 'destino' el contenido de 'origen' hasta la primera coma o el
// final de la cadena (lo que llegue antes). 'tamano_destino' es el tamaño
// del buffer 'destino', para no desbordarlo.
// Devuelve un puntero a la posición de 'origen' donde se quedó (justo
// después de la coma consumida, o al '\0' si era el último campo).
const char *extraer_campo(const char *origen, char *destino, size_t tamano_destino);
```

Pista de uso esperado, para que veas cómo se encadenaría en el futuro
`parsear_linea`:

```c
const char *cursor = linea;
char fecha[FECHA_LEN];
cursor = extraer_campo(cursor, fecha, FECHA_LEN);
char importe_texto[16];
cursor = extraer_campo(cursor, importe_texto, sizeof(importe_texto));
// ... y así con el resto de campos, "cursor" avanza cada vez
```

Tienes todos los ingredientes ya explicados en esta lección: el bucle de
búsqueda de la coma, el cálculo de longitud con aritmética de punteros, la
comprobación de que cabe en el destino, `memcpy` + `\0` manual, y avanzar el
puntero de origen saltándose la coma.

Escríbela, compílala con las flags estrictas de siempre, y pruébala con un
pequeño `main` que llame a `extraer_campo` un par de veces sobre una línea
de ejemplo (puedes usar directamente la primera línea de
`c-core/tests/ejemplo_movimientos.csv`) y compruebe que los campos
extraídos son los esperados. Pégame el código y la salida cuando lo tengas.
