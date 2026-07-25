#include <stdio.h>
#include <string.h>

// Completa tú esta función: recibe un array de enteros y su tamaño,
// y devuelve la suma de todos sus elementos.
int sumar_array(int *arr, int tamano)
{
    int suma = 0;
    for (int i = 0; i < tamano; i++)
    {
        suma += arr[i];
    }
    return suma;
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