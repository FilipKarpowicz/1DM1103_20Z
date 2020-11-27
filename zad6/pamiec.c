#include "pamiec.h"

float **tworzenie(int a, int b)
{
    float **tablica;
    tablica = (float *)malloc((sizeof(float *)) * a);
    for (int i = 0; i < a; i++)
        tablica[i] = malloc(sizeof(float) * b);
    //printf("jd\n");
    return tablica;
}

void zwalnianie(float **macierz, int b)
{
    for (int i = 0; i < b; i++)
        free(macierz[i]);
    free(macierz);
}
