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

/*void wypisz(student dane[100], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("{ Student: %s - %s %s, z przedmiotu: [%s] %s za ECTS: %d otrzymał %.1f\n",
               dane[i].nr_albumu, dane[i].imie, dane[i].nazwisko,
               dane[i].kod_przed, dane[i].nazwa_przed,
               dane[i].ects, dane[i].ocena);
    }
}*/

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
    char nr_albumow[100][10];
    int ile_studentow;
    float sumy_wazonych_ocen[100] = {0};
    int sumy_ects[100] = {0};
    float sumy_wazonych_ocen1[100] = {0};
    int sumy_ects1[100] = {0};
    int i;
    int pozycja;
    int najlepsza_pozycja;
    int najgorsza_pozycja;
    float najlepsza = 0.0f;
    float najgorsza = 100.0f;
    char najlepszy_przedmiot[255];
    char najgorszy_przedmiot[255];

    ile_studentow = znajdz_studentow(nr_albumow, dane, ile_rekordow);

    for (i = 0; i < ile_rekordow; i++)
    {
        pozycja = znajdz(dane[i].kod_przed, nr_albumow, ile_studentow);
        // if (pozycje >= 0)
        sumy_wazonych_ocen[pozycja] += dane[i].ocena;
        sumy_ects[pozycja]++;
    }
    for (i = 0; i < ile_rekordow; i++)
    {
        pozycja = znajdz(dane[i].kod_przed, nr_albumow, ile_studentow);
        // if (pozycje >= 0)
        sumy_wazonych_ocen1[pozycja] += dane[i].ocena;
        sumy_ects1[pozycja]++;
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
    for (i = 0; i < ile_studentow; i++)
    {
        if (najgorsza > (sumy_wazonych_ocen1[i] / sumy_ects1[i]))
        {
            najgorsza = sumy_wazonych_ocen1[i] / sumy_ects1[i];
            najgorsza_pozycja = i;
        }
    }
    /* printf("najl %.1f %d\nnajg %.1f %d\n", sumy_wazonych_ocen[0], sumy_ects[0], sumy_wazonych_ocen1[1], sumy_ects1[1]);
    printf("najgorsza pozycja %d\n", najgorsza_pozycja);
    printf("ile %d\n", ile_studentow);
    for (i = 0; i < ile_studentow; i++)
    {
        printf("%s\n", nr_albumow[i]);
    }*/
    int a = 1, b = 1;
    for (i = 0; i < ile_rekordow; i++)
    {
        if (strcmp(nr_albumow[najlepsza_pozycja], dane[i].kod_przed) == 0)
        {
            strcpy(najlepszy_przedmiot, dane[i].nazwa_przed);
            a = 0;
        }
        if (strcmp(nr_albumow[najgorsza_pozycja], dane[i].kod_przed) == 0)
        {
            strcpy(najgorszy_przedmiot, dane[i].nazwa_przed);
            b = 0;
        }
        if (a == 0 && b == 0)
            break;
    }

    printf("Najlepsza srednia ");
    printf("%s -%s: %.2f\n",
           nr_albumow[najlepsza_pozycja], najlepszy_przedmiot,
           sumy_wazonych_ocen[najlepsza_pozycja] / sumy_ects[najlepsza_pozycja]);
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

    najlepszy_student(dane, ile);

    return 0;
}