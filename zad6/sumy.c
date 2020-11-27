#include "liczenie.h"

float **odejmij(float **m1, float **m2, int *a1, int a2, int *b1, int b2)
{
    float **wynik = tworzenie(*a1, *b1);
    if (*a1 == a2 && *b1 == b2)
    {
        for (int i = 0; i < a2; i++)
            for (int j = 0; j < b2; j++)
            {
                wynik[i][j] = m1[i][j] - m2[i][j];
            }
        return wynik;
    }
    else
    {
        printf("nie da sie wykonac tego dzialania dla tych macierzy\n");
    }
}

float **suma(float **m1, float **m2, int *a1, int a2, int *b1, int b2)
{
    float **wynik = tworzenie(*a1, *b1);
    if (*a1 == a2 && *b1 == b2)
    {
        for (int i = 0; i < *a1; i++)
            for (int j = 0; j < *b1; j++)
            {
                wynik[i][j] = m1[i][j] + m2[i][j];
            }
        return wynik;
    }
    else
    {
        printf("nie da sie wykonac tego dzialania dla tych macierzy\n");
        exit(-1);
    }
}