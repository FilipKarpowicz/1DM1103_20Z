#include "liczenie.h"
#include "uzytkownik.h"

int main(int argc, char *argv[])
{
    if (argv[1] && argv[2])
    {
        FILE *plik, *plik2;
        plik = fopen(argv[2], "r");
        int a, b, a1, b1, a3, b3;
        float **macierz, **macierz2, **wynik;
        macierz = wczytaj(&a, &b, plik);
        // printf("%d %d\n", a, b);
        //wypisz(macierz, a, b);
        if (strcmp(argv[1], "sum") == 0)
        {
            //printf("xd\n");
            plik2 = fopen(argv[3], "r");
            if (plik2)
            {
                macierz2 = wczytaj(&a1, &b1, plik2);
                wynik = suma(macierz, macierz2, &a, a1, &b, b1);
                if (!argv[4])
                    wypisz(wynik, a, b);
                else
                    zapisz(argv[4], wynik, a1, b1);
                zwalnianie(wynik, b);
                zwalnianie(macierz2, b1);
                fclose(plik2);
            }
            else
                printf("nieprawidlowe dane\n");
        }

        else if (strcmp(argv[1], "subtract") == 0)
        {
            plik2 = fopen(argv[3], "r");
            if (plik2)
            {
                macierz2 = wczytaj(&a1, &b1, plik2);
                wynik = odejmij(macierz, macierz2, &a, a1, &b, b1);
                if (!argv[4])
                    wypisz(wynik, a, b);
                else
                {
                    zapisz(argv[4], wynik, a1, b1);
                }
                zwalnianie(wynik, b);
                zwalnianie(macierz2, b1);
            }
            else
                printf("nieprawidlowe dane\n");
        }
        else if (strcmp(argv[1], "multiply") == 0)
        {
            wynik = skalar(macierz, a, b, atof(argv[3]));
            if (!argv[4])
                wypisz(wynik, a, b);
            else
                zapisz(argv[4], wynik, a, b);
            zwalnianie(wynik, b);
        }
        else if (strcmp(argv[1], "prod") == 0)
        {
            plik2 = fopen(argv[3], "r");
            if (plik2)
            {
                macierz2 = wczytaj(&a1, &b1, plik2);
                wynik = mnozenie(macierz, macierz2, a, b, a1, b1, &a3, &b3);
                if (!argv[4])
                    wypisz(wynik, a, b1);
                else
                    zapisz(argv[4], wynik, a, b1);
                zwalnianie(wynik, b1);
                zwalnianie(macierz2, b1);
            }
            else
                printf("nieprawidlowe dane\n");
        }
        else if (strcmp(argv[1], "norm") == 0)
        {
            // printf("xd\n");
            float wynik1 = norma(macierz, a, b);
            if (!argv[3])
                printf("%f\n", wynik1);
            else
                zapisz(argv[3], wynik, a, b1);
        }
        zwalnianie(macierz, b);
    }
    else
    {
        printf("nie podano zadania lub macierzy\n");
    }
    return 0;
}
