#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char *extraer_campo(const char *origen, char *destino, size_t tamano_destino)
{
    const char *fin = origen;
    size_t longitud;

    while (*fin != ',' && *fin != '\0')
        fin++;
    longitud = fin - origen;
    if (longitud >= tamano_destino)
        return (NULL);
    else
    {
        memcpy(destino, origen, longitud);
        destino[longitud] = '\0';
    }
    if (*fin == ',')
        return (++fin);
    else
        return (fin);
}

int main(void)
{
    const char *origen = "2025-10-02,1200.00,gasto";
    char fecha[11];
    char importe[10];
    char tipo[9];

    origen = extraer_campo(origen, fecha, sizeof(fecha));
    printf("Origen: %s\n", origen);
    printf("Fecha: %s\n", fecha);

    origen = extraer_campo(origen, importe, sizeof(importe));
    printf("Origen: %s\n", origen);
    printf("Importe: %s\n", importe);

    origen = extraer_campo(origen, tipo, sizeof(tipo));
    printf("Origen: %s\n", origen);
    printf("Tipo: %s\n", tipo);

    return (0);
}