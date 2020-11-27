#include "uzytkownik.h"

void zapisz(char nazwa[], float **macierz, int a, int b)
{
    FILE *fout = fopen(nazwa, "w+");
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            fprintf(fout, "%6.2f", macierz[i][j]);
        }
        fprintf(fout, "\n");
    }
    // fclose(nazwa);
}

float **wczytaj(int *a, int *b, FILE *plik)
{
    fscanf(plik, "%d", a);
    fscanf(plik, "%d", b);
    //printf("%d %d \n", *a, *b);
    float **macierz = tworzenie(*a, *b);
    for (int i = 0; i < *a; i++)
    {
        for (int j = 0; j < *b; j++)
        {
            fscanf(plik, "%f", &macierz[i][j]);
            //printf("jd\n");
        }
    }
    return macierz;
}

void wypisz(float **m, int a, int b)
{
    for (int i = 0; i < a; i++)
    {
        if (i >= 0)
            printf(" ");
        for (int j = 0; j < b; j++)
        {
            printf("%6.2f", m[i][j]);
            // printf("jd\n");
        }
        if (i < a)
            printf("\n");
    }
}


