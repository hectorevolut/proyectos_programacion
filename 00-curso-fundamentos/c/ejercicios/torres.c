#include <stdio.h>

void imprime_array(int *array_int, size_t size)
{
    size_t i;

    i = 0;
    while (i < size)
    {
        printf("%d ", array_int[i]);
        i++;
    }
    printf("\n");
}

int main(void)
{
    size_t i;
    int torre[] = {4, 1, 2, 3, 4, 10, 11, 12, 3, 4};
    size_t size;
    int torre_base;
    int movimiento;

    movimiento = 0;
    torre_base = torre[0];
    size = sizeof(torre) / sizeof(int);
    i = 0;
    while (i < size - 1)
    {
        while ((torre[i] < torre[i + 1]) && (torre[i + 1] > torre_base))
        {
            --torre[i + 1];
            movimiento++;
            imprime_array(torre, size);
        }
        i++;
    }
    if (movimiento == 0)
        imprime_array(torre, size);
    return (0);
}