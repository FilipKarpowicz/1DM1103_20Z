#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

struct macierz
{
    float elementy[200][200];
    int a;
    int b;
};

void wczytaj(FILE *plik, struct macierz *m)
{

    fscanf(plik, "%d", &m->a);
    fscanf(plik, "%d", &m->b);
    for (int i = 0; i < m->a; i++)
        for (int j = 0; j < m->b; j++)
        {
            fscanf(plik, "%f", &m->elementy[i][j]);
        }
}

void wypisz(struct macierz m)
{
    for (int i = 0; i < m.a; i++)
    {
        if (i > 0)
            printf(" ");
        for (int j = 0; j < m.b; j++)
        {
            printf("%6.2f", m.elementy[i][j]);
        }
        if (i < (m.a - 1))
            printf("\n");
    }
}

void zapisz(char nazwa[], struct macierz m)
{
    FILE *fout = fopen(nazwa, "w+");
    for (int i = 0; i < m.a; i++)
    {
        for (int j = 0; j < m.b; j++)
        {
            fprintf(fout, "%6.2f", m.elementy[i][j]);
        }
        fprintf(fout, "\n");
    }
}

struct macierz suma(struct macierz m1, struct macierz m2)
{
    struct macierz wynik;
    if (m1.a == m2.a && m1.b == m2.b)
    {
        for (int i = 0; i < m1.a; i++)
            for (int j = 0; j < m1.b; j++)
            {
                wynik.elementy[i][j] = m1.elementy[i][j] + m2.elementy[i][j];
            }
        wynik.a = m1.a;
        wynik.b = m1.b;
        return wynik;
    }
    else
    {
        printf("nie da sie wykonac tego dzialania dla tych macierzy\n");
        exit(-1);
    }
}

struct macierz odejmij(struct macierz m1, struct macierz m2)
{
    struct macierz wynik;
    if (m1.a == m2.a && m1.a == m2.a)
    {
        for (int i = 0; i < m1.a; i++)
            for (int j = 0; j < m1.b; j++)
            {
                wynik.elementy[i][j] = m1.elementy[i][j] - m2.elementy[i][j];
            }
        wynik.a = m1.a;
        wynik.b = m1.b;
        return wynik;
    }
    else
    {
        printf("nie da sie wykonac tego dzialania dla tych macierzy\n");
        exit(-2);
    }
}
struct macierz skalar(struct macierz m, float k)
{
    struct macierz wynik;
    for (int i = 0; i < m.a; i++)
        for (int j = 0; j < m.b; j++)
        {
            wynik.elementy[i][j] = m.elementy[i][j] * k;
        }
    wynik.a = m.a;
    wynik.b = m.b;
    return wynik;
}

struct macierz mnozenie(struct macierz m1, struct macierz m2)
{
    struct macierz wynik;
    if (m1.b == m2.a)
    {
        for (int i = 0; i < m1.a; i++)
        {
            for (int j = 0; j < m2.b; j++)
            {
                float pom = 0;
                for (int k = 0; k < m1.b; k++)
                {
                    pom = pom + (m1.elementy[i][k] * m2.elementy[k][j]);
                    //printf("%4.2f\n", pom);
                }
                wynik.elementy[i][j] = pom;
                //printf("%4.2f\n", pom);
            }
        }
        wynik.a = m1.a;
        wynik.b = m2.b;
        return wynik;
    }
    else
    {
        printf("Nie mozna wykonac tej operacji dla danych macierzy");
        exit(-3);
    }
}

float norma(struct macierz m)
{
    float suma = 0;
    for (int i = 0; i < m.a; i++)
        for (int j = 0; j < m.a; j++)
            suma = suma + (m.elementy[i][j] * m.elementy[i][j]);
    suma = sqrtf(suma);
    return suma;
}

int main(int argc, char *argv[])
{
    FILE *m1, *m2;
    if (strcmp(argv[1], "norm") == 0)
    {
        if (!argv[2])
        {
            printf("nie podano pliku\n");
            return 2;
        }
        else
        {
            m1 = fopen(argv[2], "r");
            if (!m1)
            {
                printf("podany plik nie isntnieje \n");
                return 3;
            }
            else
            {
                struct macierz mac1;
                wczytaj(m1, &mac1);
                float wynik = norma(mac1);
                if (argc == 4)
                {
                    FILE *fout = fopen(argv[3], "w+");
                    fprintf(fout, "%6.2f", wynik);
                    fclose(fout);
                }
                else
                {
                    printf("%6.2f\n", wynik);
                }
                fclose(m1);
            }
        }
    }
    else
    {

        struct macierz wynik, mac1, mac2;
        if (strcmp(argv[1], "multiply") == 0)
        {
            if (!argv[2] || !argv[3])
            {
                printf("nie podano pliku z macierza lub liczby do mnozenia\n");
                return 2;
            }
            else
            {
                m1 = fopen(argv[2], "r");
                if (!m1)
                {
                    printf("taki plik nie istnieje \n");
                    return 3;
                }
                else
                {
                    wczytaj(m1, &mac1);
                    float k = atof(argv[3]);
                    wynik = skalar(mac1, k);
                    fclose(m1);
                }
            }
        }
        else
        {
            if (!argv[2] || !argv[3])
            {
                printf("nie podano lub podano za malo plkow z macierzami wejsciowymi\n");
                return 2;
            }
            else
            {
                m1 = fopen(argv[2], "r");
                m2 = fopen(argv[3], "r");
                if (!m1 || !m2)
                {
                    printf("plik1 lub plik2 nie istnieje\n");
                    return 3;
                }
                else
                {
                    wczytaj(m1, &mac1);
                    wczytaj(m2, &mac2);
                    if (strcmp(argv[1], "sum") == 0)
                    {
                        wynik = suma(mac1, mac2);
                    }
                    else if (strcmp(argv[1], "subtract") == 0)
                    {
                        wynik = odejmij(mac1, mac2);
                    }
                    else if (strcmp(argv[1], "prod") == 0)
                    {
                        wynik = mnozenie(mac1, mac2);
                    }
                    else
                    {
                        printf("nie podano prawidlowego argumentu dzialania (mozliwe: sum,subtract,prod,multiply,norm)\n");
                        return 1;
                    }
                    fclose(m2);
                    fclose(m1);
                }
            }
        }
        if (argc == 5)
        {
            zapisz(argv[4], wynik);
        }
        else
        {
            printf("[");
            wypisz(wynik);
            printf(" ]\n");
            // printf("%f", norma(mac1));
        }
    }

    return 0;
}