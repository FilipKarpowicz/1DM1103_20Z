#include "liczenie.h"

float **skalar(float **m, int a, int b, float k)
{
    float **wynik = tworzenie(a, b);
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++)
        {
            wynik[i][j] = m[i][j] * k;
            //printf("jd\n");
        }
    return wynik;
}

float **mnozenie(float **m1, float **m2, int a1, int b1, int a2, int b2, int *a3, int *b3)
{
    *a3 = a1;
    *b3 = b2;
    float **wynik = tworzenie(*a3, *b3);
    if (b1 == a2)
    {
        for (int i = 0; i < a1; i++)
        {
            for (int j = 0; j < b2; j++)
            {
                float pom = 0;
                for (int k = 0; k < b1; k++)
                {
                    pom = pom + (m1[i][k] * m2[k][j]);
                    //printf("%4.2f\n", pom);
                }
                wynik[i][j] = pom;
                //printf("%4.2f\n", pom);
            }
        }
        return wynik;
    }
    else
    {
        printf("Nie mozna wykonac tej operacji dla danych macierzy");
        exit(-3);
    }
}