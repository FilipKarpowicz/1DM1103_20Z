#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* nie wiem czy dobrze zrozumialem ale z przykladu wynikalo ze program sam ma dobrac wektor dla danej macierzy 
dlatego program bierze tylko te dane ktore umozliwiaja mnozenie*/

void wpisywanie(FILE *a, float *tab2, int x2)
{
    float liczba;
    for (int i = 0; i < x2; i++)
    {
        fscanf(a, "%f", &liczba);
        tab2[i] = liczba;
    }
}
float wynik(float *tab1, float *tab2, int x)
{
    float suma = 0;
    for (int i = 0; i < x; i++)
    {
        suma = suma + (tab1[i] * tab2[i]);
    }
    return suma;
}
void wypisanie(float *tab3, int x)
{
    for (int i = 0; i < x; i++)
        printf("%4.1f ", tab3[i]);
}

int main(int argc, char *argv[])
{
    FILE *a, *b;
    a = fopen(argv[1], "r");
    b = fopen(argv[2], "r");
    int x1, y1, x2, y2;
    fscanf(a, "%d", &y1);
    fscanf(a, "%d", &x1);
    fscanf(b, "%d", &y2);
    fscanf(b, "%d", &x2);
    float tab1[y1][x1], tab2[y2];
    float liczba;
    for (int i = 0; i < y1; i++)
    {
        wpisywanie(a, tab1[i], x1);
    }
    wpisywanie(b, tab2, x1);
    /*for (int i = 0; i < y1; i++)
    {
        for (int j = 0; j < x1; j++)
            printf("%4.1f", tab1[i][j]);
        printf("\n");
    }*/
    float tab3[y1];
    for (int i = 0; i < y1; i++)
    {
        tab3[i] = wynik(tab1[i], tab2, x1);
    }
    printf("(%d) [", y1);
    wypisanie(tab3, y1);
    printf("]\n");
    return 0;
}