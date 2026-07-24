#include "movimientos.h"
#include <stdio.h>
#include <stdlib.h>

t_lista_movimientos *lista_crear(size_t capacidad_inicial)
{
    t_lista_movimientos *lista = malloc(sizeof(t_lista_movimientos));
    if (!lista)
    {
        return NULL;
    }

    lista->items = malloc(capacidad_inicial * sizeof(t_movimiento));
    if (!lista->items)
    {
        free(lista);
        return NULL;
    }

    lista->count = 0;
    lista->capacity = capacidad_inicial;
    return lista;
}

int lista_push(t_lista_movimientos *lista, t_movimiento mov)
{
    if (lista->count >= lista->capacity)
    {
        size_t nueva_capacidad = lista->capacity == 0 ? 1 : lista->capacity * 2;
        t_movimiento *nueva_lista = realloc(lista->items, nueva_capacidad * sizeof(t_movimiento));
        if (!nueva_lista)
        {
            return -1; // Error al redimensionar
        }
        lista->items = nueva_lista;
        lista->capacity = nueva_capacidad;
    }

    lista->items[lista->count++] = mov;
    return 0; // Éxito
}

void lista_destruir(t_lista_movimientos *lista)
{
    if (lista)
    {
        free(lista->items);
        free(lista);
    }
}