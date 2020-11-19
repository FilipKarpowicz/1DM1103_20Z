/**
Mamy mini bazę studentów (tabelę z studentami, przedmiotami i ocenami)
Cel: obliczyć ranking.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _student
{
    char imie[25];
    char nazwisko[50];
    char nr_albumu[10];
    char kod_przed[10];
    char nazwa_przed[255];
    float ocena;
    int ects;
} student, *pstudent;

int wczytaj(student dane[100], char *fnazwa)
{
    FILE *fin = fopen(fnazwa, "r");
    int cnt, i;
    char bufor[1024];
    char *w;

    fgets(bufor, 1023, fin);
    sscanf(bufor, "%d", &cnt);

    for (i = 0; i < cnt; i++)
    {
        fgets(bufor, 1023, fin);
        // printf("%s", bufor);
        w = strtok(bufor, "|");
        strncpy(dane[i].imie, w, 24);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwisko, w, 49);

        w = strtok(NULL, "|");
        strncpy(dane[i].nr_albumu, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].kod_przed, w, 9);

        w = strtok(NULL, "|");
        strncpy(dane[i].nazwa_przed, w, 254);

        w = strtok(NULL, "|");
        dane[i].ocena = atof(w);

        w = strtok(NULL, "|");
        dane[i].ects = atoi(w);
    }

    fclose(fin);
    return cnt;
}

void wypisz(student dane[100], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("{ Student: %s - %s %s, z przedmiotu: [%s] %s za ECTS: %d otrzymał %.1f\n",
               dane[i].nr_albumu, dane[i].imie, dane[i].nazwisko,
               dane[i].kod_przed, dane[i].nazwa_przed,
               dane[i].ects, dane[i].ocena);
    }
}

int znajdz(char *szukany_nr, char nr_albumow[100][10], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(szukany_nr, nr_albumow[i]) == 0)
            return i;
    }
    return -1;
}

int znajdz_studentow(char nr_albumow[100][10], student dane[100], int n)
{
    int ile_znalazlem = 0;
    int i;

    for (i = 0; i < n; i++)
    {
        if (znajdz(dane[i].nr_albumu, nr_albumow, ile_znalazlem) == -1)
        {
            strncpy(nr_albumow[ile_znalazlem], dane[i].nr_albumu, 9);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}

int znajdz_oceny(char nr_albumow[100][10], student dane[100], int n)
{
    int ile_znalazlem = 0;
    int i;

    for (i = 0; i < n; i++)
    {
        if (znajdz(dane[i].kod_przed, nr_albumow, ile_znalazlem) == -1)
        {
            strncpy(nr_albumow[ile_znalazlem], dane[i].kod_przed, 9);
            ile_znalazlem++;
        }
    }
    return ile_znalazlem;
}

void najlepszy_student(student dane[100], int ile_rekordow)
{
    char nr_albumow[100][10] = {0};
    int ile_studentow = 0;
    float sumy_wazonych_ocen[100] = {0};
    int sumy_ects[100] = {0};
    int i = 0;
    int pozycja = 0;
    int najlepsza_pozycja = 0;
    float najlepsza = 0.0f;

    ile_studentow = znajdz_studentow(nr_albumow, dane, ile_rekordow);

    for (i = 0; i < ile_rekordow; i++)
    {
        pozycja = znajdz(dane[i].nr_albumu, nr_albumow, ile_studentow);
        // if (pozycje >= 0)
        sumy_wazonych_ocen[pozycja] += dane[i].ocena * dane[i].ects;
        sumy_ects[pozycja] += dane[i].ects;
    }

    for (i = 0; i < ile_studentow; i++)
        printf("Student [%d]: %s - %f:%d - %f \n", i + 1, nr_albumow[i],
               sumy_wazonych_ocen[i], sumy_ects[i], sumy_wazonych_ocen[i] / sumy_ects[i]);

    for (i = 0; i < ile_studentow; i++)
    {
        if (najlepsza < sumy_wazonych_ocen[i] / sumy_ects[i])
        {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }

    printf("Najlepszy student: \n");
    printf("Student [%d]: %s - %f \n",
           najlepsza_pozycja + 1, nr_albumow[najlepsza_pozycja],
           sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]);
}

void najlepsza_ocena(student dane[100], int ile_rekordow)
{
    char nr_albumow[100][10];
    int ile_studentow = 0;
    float sumy_wazonych_ocen[100] = {0};
    int sumy_ects[100] = {0};
    int i = 0;
    int pozycja = 0;
    int najlepsza_pozycja = 0;
    float najlepsza = 0.0f;
    char najlepszy_przedmiot[255] = {0};

    ile_studentow = znajdz_oceny(nr_albumow, dane, ile_rekordow);

    for (i = 0; i < ile_rekordow; i++)
    {
        pozycja = znajdz(dane[i].kod_przed, nr_albumow, ile_studentow);
        // if (pozycje >= 0)
        sumy_wazonych_ocen[pozycja] += dane[i].ocena;
        sumy_ects[pozycja]++;
    }
    /*for (int i = 0; i < ile_rekordow; i++)
    {
        printf("[%d] %.1f %d\n", i, sumy_wazonych_ocen[i], sumy_ects[i]);
    }*/

    for (i = 0; i < ile_studentow; i++)
    {
        if (najlepsza < (sumy_wazonych_ocen[i] / sumy_ects[i]))
        {
            najlepsza = sumy_wazonych_ocen[i] / sumy_ects[i];
            najlepsza_pozycja = i;
        }
    }
    for (i = 0; i < ile_rekordow; i++)
    {
        if (strcmp(nr_albumow[najlepsza_pozycja], dane[i].kod_przed) == 0)
        {
            strcpy(najlepszy_przedmiot, dane[i].nazwa_przed);
        }
    }

    printf("Najlepsza srednia ");
    printf("%s -%s: %.2f\n",
           nr_albumow[najlepsza_pozycja], najlepszy_przedmiot,
           sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]);
}

void najgorsza_ocena(student dane[100], int ile_rekordow)
{
    char nr_albumow[100][10];
    int ile_studentow = 0;
    float sumy_wazonych_ocen1[100] = {0};
    int sumy_ects1[100] = {0};
    int i = 0;
    int pozycja = 0;
    int najgorsza_pozycja = 0;
    float najgorsza = 100.0f;
    char najgorszy_przedmiot[255] = {0};

    ile_studentow = znajdz_oceny(nr_albumow, dane, ile_rekordow);

    for (i = 0; i < ile_rekordow; i++)
    {
        pozycja = znajdz(dane[i].kod_przed, nr_albumow, ile_studentow);
        // if (pozycje >= 0)
        sumy_wazonych_ocen1[pozycja] += dane[i].ocena;
        sumy_ects1[pozycja]++;
    }

    for (i = 0; i < ile_studentow; i++)
    {
        if (najgorsza > (sumy_wazonych_ocen1[i] / sumy_ects1[i]))
        {
            najgorsza = sumy_wazonych_ocen1[i] / sumy_ects1[i];
            najgorsza_pozycja = i;
        }
    }

    for (i = 0; i < ile_rekordow; i++)
    {
        if (strcmp(nr_albumow[najgorsza_pozycja], dane[i].kod_przed) == 0)
        {
            strcpy(najgorszy_przedmiot, dane[i].nazwa_przed);
        }
    }
    printf(" 1. %s\n", nr_albumow[2]);
    printf("najgorsza srednia ");
    printf("%s -%s: %.2f\n",
           nr_albumow[najgorsza_pozycja], najgorszy_przedmiot,
           sumy_wazonych_ocen1[najgorsza_pozycja] / sumy_ects1[najgorsza_pozycja]);
}

int main(int argc, char **argv)
{
    student dane[100];
    int ile;
    // dane == &dane[0]
    ile = wczytaj(dane, argv[1]);
    //wypisz(dane, ile);
    if (strcmp(argv[3], "student") == 0)
        najlepszy_student(dane, ile);
    else if (strcmp(argv[3], "ocena") == 0)
    {
        if (strcmp(argv[2], "najlepsza") == 0)
            najlepsza_ocena(dane, ile);
        else if (strcmp(argv[2], "najgorsza") == 0)
            najgorsza_ocena(dane, ile);
    }
    return 0;
}