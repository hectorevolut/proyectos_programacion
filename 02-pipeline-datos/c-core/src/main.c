#include <stdio.h>
#include "movimientos.h"

/*int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <fichero.csv>\n", argv[0]);
        return 1;
    }

    t_lista_movimientos *lista = parsear_csv(argv[1]);
    if (!lista) {
        fprintf(stderr, "Error: no se pudo procesar %s\n", argv[1]);
        return 1;
    }

    printf("Movimientos leídos: %zu\n", lista->count);
    for (size_t i = 0; i < lista->count; i++) {
        printf("%s | %8.2f | %-8s | %-20s | %s\n",
               lista->items[i].fecha, lista->items[i].importe,
               lista->items[i].tipo, lista->items[i].categoria,
               lista->items[i].descripcion);
    }

    lista_destruir(lista);
    return 0;
}*/

int main(void)
{
    t_lista_movimientos *lista = lista_crear(0);
    if (!lista)
        return 1;

    t_movimiento mov1 = {"2025-01-05", 1200.00, "ingreso", "ventas_producto_a", "Venta pedido #101"};
    t_movimiento mov2 = {"2025-01-06", 1400.00, "ingreso", "ventas_producto_b", "Venta pedido #102"};
    lista_push(lista, mov1);
    lista_push(lista, mov2);

    printf("count=%zu capacity=%zu\n", lista->count, lista->capacity);
    while (lista->count > 0)
    {
        t_movimiento m = lista->items[--lista->count];
        printf("%s | %8.2f | %-8s | %-20s | %s\n",
            m.fecha, m.importe, m.tipo, m.categoria, m.descripcion);
    }

    lista_destruir(lista);
    return 0;
}