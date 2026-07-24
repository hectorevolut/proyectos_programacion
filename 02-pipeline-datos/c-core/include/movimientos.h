// include/movimientos.h
#ifndef MOVIMIENTOS_H
#define MOVIMIENTOS_H

#include <stddef.h>

#define FECHA_LEN 11 // "YYYY-MM-DD" + '\0'
#define TIPO_LEN 8   // "ingreso" o "gasto" + margen
#define CATEGORIA_LEN 32
#define DESCRIPCION_LEN 128

typedef struct
{
    char fecha[FECHA_LEN];
    double importe;
    char tipo[TIPO_LEN];
    char categoria[CATEGORIA_LEN];
    char descripcion[DESCRIPCION_LEN];
} t_movimiento;

// Array dinámico de movimientos (decisión: array, no lista enlazada —
// justificación abajo)
typedef struct
{
    t_movimiento *items;
    size_t count;
    size_t capacity;
} t_lista_movimientos;

// --- Ciclo de vida de la lista ---
t_lista_movimientos *lista_crear(size_t capacidad_inicial);
void lista_destruir(t_lista_movimientos *lista);
int lista_push(t_lista_movimientos *lista, t_movimiento mov);

// --- Parsing ---
// Lee el CSV completo y devuelve una lista poblada, o NULL si el fichero
// no se puede abrir. Las líneas mal formadas se descartan (no deben
// tumbar el programa) — decide tú si las cuentas/avisas por stderr.
t_lista_movimientos *parsear_csv(const char *ruta_fichero);

// Parsea UNA línea ya leída (sin '\n' final) a un t_movimiento.
// Devuelve 1 si la línea es válida y rellena *out, 0 si es inválida.
int parsear_linea(const char *linea, t_movimiento *out);

#endif