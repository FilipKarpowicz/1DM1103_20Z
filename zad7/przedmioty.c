#include "baza.h"

Przedmiot *wczytaj_przedmioty(FILE *fin)
{
    char bufor[255];
    int n, i;
    char *s;
    Przedmiot *last = NULL;
    Przedmiot *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i = 0; i < n; i++)
    {
        Przedmiot *przedmiot = (Przedmiot *)malloc(sizeof(Przedmiot));
        przedmiot->nast = NULL;

        if (last == NULL)
            glowa = przedmiot;
        else
            last->nast = przedmiot;
        last = przedmiot;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        przedmiot->id = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(przedmiot->id, s);

        s = strtok(NULL, ";");
        przedmiot->nazwa = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(przedmiot->nazwa, s);

        s = strtok(NULL, "\n");
        przedmiot->sem = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(przedmiot->sem, s);
    }
    return glowa;
}

SPrzedmiot *wczytaj_baze_sbj(FILE *fin, char *nazwa_pliku)
{
    if (fin == NULL)
    {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    SPrzedmiot *baza = (SPrzedmiot *)malloc(sizeof(SPrzedmiot));
    baza->lista_przedmiotow = wczytaj_przedmioty(fin);

    return baza;
}

int ile_przedmiotow(SPrzedmiot *baza)
{
    int n = 0;
    Przedmiot *sbj = baza->lista_przedmiotow;
    while (sbj != NULL)
    {
        n++;
        sbj = sbj->nast;
    }
    return n;
}

void listuj_przedmioty(SPrzedmiot *baza)
{
    Przedmiot *stud = baza->lista_przedmiotow;
    while (stud != NULL)
    {
        printf("%s %s %s\n", stud->id, stud->nazwa, stud->sem);
        stud = stud->nast;
    }
}

SPrzedmiot *dodaj_przedmiot(SPrzedmiot *baza, char *id, char *nazwa, char *sem)
{
    int ile = ile_przedmiotow(baza);
    Przedmiot *nowy = (Przedmiot *)malloc(sizeof(Przedmiot));
    Przedmiot *sbj = baza->lista_przedmiotow;
    for (int i = 0; i < ile; i++)
    {
        if (sbj->nast == NULL)
            sbj->nast = nowy;
        else
        {
            sbj = sbj->nast;
        }
    }
    sbj = nowy;
    sbj->id = (char *)malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(sbj->id, id);

    sbj->nazwa = (char *)malloc(sizeof(char) * (strlen(nazwa) + 1));
    strcpy(sbj->nazwa, nazwa);

    sbj->sem = (char *)malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(sbj->sem, sem);

    sbj->nast = NULL;

    return baza;
}

void zwolnij_przedmiot(Przedmiot *s)
{
    free(s->id);
    free(s->nazwa);
    free(s->sem);
    free(s);
}

void zwolnij_liste_przedmiotow(Przedmiot *s)
{
    Przedmiot *n;
    while (s != NULL)
    {
        n = s->nast;
        zwolnij_przedmiot(s);
        s = n;
    }
}

void zwolnij_P(SPrzedmiot *baza)
{
    zwolnij_liste_przedmiotow(baza->lista_przedmiotow);
    free(baza);
}

