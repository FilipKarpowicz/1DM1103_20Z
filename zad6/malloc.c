#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

float **tworzenie(int a, int b)
{
    float **tablica;
    tablica = (float *)malloc((sizeof(float *)) * a);
    for (int i = 0; i < a; i++)
        tablica[i] = malloc(sizeof(float) * b);
    //printf("jd\n");
    return tablica;
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
float **wczytaj(int *a, int *b, FILE *plik);

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

float **odejmij(float **m1, float **m2, int *a1, int a2, int *b1, int b2);

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

float norma(float **m, int a, int b)
{
    float suma = 0;
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++)
            suma = suma + (m[i][j] * m[i][j]);
    suma = sqrtf(suma);
    return suma;
}

void zwalnianie(float **macierz, int b)
{
    for (int i = 0; i < b; i++)
        free(macierz[i]);
    free(macierz);
}

int main(int argc, char *argv[])
{
    FILE *plik, *plik2;
    plik = fopen("m3.txt", "r");
    plik2 = fopen("m4.txt", "r");
    int a, b, a1, b1, a3, b3;
    float **macierz, **macierz2, **wynik;
    macierz = wczytaj(&a, &b, plik);
    macierz2 = wczytaj(&a1, &b1, plik2);
    printf("%d %d\n", a, b);
    wypisz(macierz, a, b);
    wypisz(macierz2, a1, b1);
    wynik = suma(macierz, macierz2, &a, a1, &b, b1);
    wypisz(wynik, a, b);
    zwalnianie(wynik, b);
    wynik = odejmij(macierz, macierz2, &a, a1, &b, b1);
    wypisz(wynik, a, b);
    zwalnianie(wynik, b);
    wynik = skalar(macierz, a, b, 3);
    wypisz(wynik, a, b);
    zwalnianie(wynik, b);
    wynik = mnozenie(macierz, macierz2, a, b, a1, b1, &a3, &b3);
    wypisz(wynik, a, b1);
    float wynik1 = norma(macierz, a, b);
    printf("%f\n", wynik1);
    zapisz("wynik.txt", wynik, a, b1);
    zwalnianie(macierz, b);
    zwalnianie(macierz2, b1);
    zwalnianie(wynik, b3);
}

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
        exit(-2);
    }
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