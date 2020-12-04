#include "baza.h"

Ocena *wczytaj_oceny(FILE *fin)
{
    //printf("xd\n");
    char bufor[255];
    int n, i;
    char *s;
    Ocena *last = NULL;
    Ocena *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);
    // printf("%d\n", n);
    for (i = 0; i < n; i++)
    {
        //printf("%d\n", i);
        Ocena *ocena = (Ocena *)malloc(sizeof(Ocena));
        ocena->nast = NULL;

        if (last == NULL)
            glowa = ocena;
        else
            last->nast = ocena;
        last = ocena;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        ocena->id = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(ocena->id, s);
        //printf("%s\n", s);
        s = strtok(NULL, ";");
        ocena->nr_albumu = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(ocena->nr_albumu, s);
        ///printf("%s\n", s);
        s = strtok(NULL, ";");
        ocena->ocena = atof(s);
        //printf("%s\n", s);
        s = strtok(NULL, "\n");
        ocena->komentarz = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(ocena->komentarz, s);
        //printf("xd\n", s);
    }

    return glowa;
}

Socena *wczytaj_baze_ocen(FILE *fin, char *nazwa_pliku)
{

    if (fin == NULL)
    {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    Socena *baza = (Socena *)malloc(sizeof(Socena));
    baza->lista_przedmiotow = wczytaj_oceny(fin);
    //printf("xd\n");
    return baza;
}

int ile_ocen(Socena *baza)
{
    int n = 0;
    Ocena *o = baza->lista_przedmiotow;
    while (o != NULL)
    {
        n++;
        o = o->nast;
    }
    return n;
}

void listuj_oceny(Socena *baza)
{
    Ocena *o = baza->lista_przedmiotow;
    while (o != NULL)
    {
        printf("%s %s %4.2f %s\n", o->id, o->nr_albumu, o->ocena, o->komentarz);
        o = o->nast;
    }
}

Socena *dodaj_ocene(Socena *baza, char *nr_alb, char *id, float ocena, char *komentarz)
{
    int ile = ile_ocen(baza);
    Ocena *nowy = (Ocena *)malloc(sizeof(Ocena));
    Ocena *o = baza->lista_przedmiotow;
    for (int i = 0; i < ile; i++)
    {
        if (o->nast == NULL)
            o->nast = nowy;
        else
        {
            o = o->nast;
        }
    }
    o = nowy;
    o->id = (char *)malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(o->id, id);

    o->nr_albumu = (char *)malloc(sizeof(char) * (strlen(nr_alb) + 1));
    strcpy(o->nr_albumu, nr_alb);

    o->komentarz = (char *)malloc(sizeof(char) * (strlen(komentarz) + 1));
    strcpy(o->komentarz, komentarz);

    o->ocena = ocena;

    o->nast = NULL;

    return baza;
}

void zwolnij_ocene(Ocena *s)
{
    free(s->nr_albumu);
    free(s->id);
    free(s->komentarz);
    free(s);
}

void zwolnij_liste_ocen(Ocena *s)
{
    Ocena *n;
    while (s != NULL)
    {
        n = s->nast;
        zwolnij_ocene(s);
        s = n;
    }
}

void zwolnij_O(Socena *baza)
{
    zwolnij_liste_ocen(baza->lista_przedmiotow);
    free(baza);
}

float srednia(char *nr_albumu, Socena *baza)
{
    float pom = 0;
    int ile = ile_ocen(baza), n = 0;
    ;
    Ocena *blok = baza->lista_przedmiotow;
    for (int i = 0; i < ile; i++)
    {
        if (strcmp(nr_albumu, blok->nr_albumu) == 0)
        {
            if (blok->ocena != 0)
            {
                pom = pom + blok->ocena;
                n++;
            }
            blok = blok->nast;
        }
        else
        {
            blok = blok->nast;
        }
    }
    return pom / n;
}

int ile_uczniow(Socena *baza, char *id_przed)
{
    Ocena *blok = baza->lista_przedmiotow;
    int ile = ile_ocen(baza);
    //printf("%d\n", ile);
    int n = 0;
    //printf("xd\n");
    for (int i = 0; i < ile; i++)
    {
        if (strcmp(id_przed, blok->id) == 0)
        {
            n++;
            blok = blok->nast;
            //printf("\n");
        }
        else
        {
            blok = blok->nast;
        }
    }
    //printf("xd\n");
    return n;
}

void sort(char *n1, char *n2)
{
    char *pom = n1;
    if (strcmp(n1, n2) > 0)
    {
        n1 = n2;
        n2 = pom;
    }
}

char *id_na_nazwisko(char *tablica, SBaza *glowa, char *id)
{
    Student *blok = glowa->lista_studentow;
    int n = ile_studentow(glowa);
    for (int i = 0; i < n; i++)
    {
        if (strcmp(id, blok->nr_albumu) == 0)
        {

            tablica = (char *)malloc(sizeof(blok->nazwisko));
            tablica = blok->nazwisko;
            // printf("%s xd\n", tablica);
            return tablica;
        }
        else
        {
            blok = blok->nast;
        }
    }
    return "brak studenta";
}

void usun_duplikaty(tablica *studenci)
{
    int ile = studenci->ile;
    for (int i = 0; i < ile - 1; i++)
    {
        if (strcmp(studenci->tablica[i], studenci->tablica[i + 1]) == 0)
        {
            int j;
            for (j = i + 1; j < ile - 1; j++)
            {
                studenci->tablica[j] = studenci->tablica[j + 1];
            }
            studenci->ile--;
            printf("czy to sie wykona \n");
            free(studenci->tablica[j + 1]);
            free(studenci->nr_albumu[j + 1]);
            free(studenci->imie[j + 1]);
        }
    }
}

void sortuj_studentow(tablica *studenci)
{
    char *pom;
    //printf("xd\n");
    for (int i = 0; i < studenci->ile - 1; i++)
    {
        if (strcmp(studenci->tablica[i], studenci->tablica[i + 1]) > 0)
        {
            for (int j = i; j < studenci->ile - 1; j++)
            {
                if (strcmp(studenci->tablica[j], studenci->tablica[j + 1]) > 0)
                {
                    pom = studenci->tablica[j + 1];
                    studenci->tablica[j + 1] = studenci->tablica[j];
                    studenci->tablica[j] = pom;
                    pom = studenci->nr_albumu[j + 1];
                    studenci->nr_albumu[j + 1] = studenci->nr_albumu[j];
                    studenci->nr_albumu[j] = pom;
                }
            }
        }
    }
}

tablica *sortowanie_uczniow_dla_oceny(Socena *oceny, SBaza *stud, char *id)
{
    //printf("xd\n");
    tablica *studenci = (tablica *)malloc(sizeof(tablica));
    studenci->ile = ile_uczniow(oceny, id);
    // printf("%d\n", studenci.ile);
    int x = 0;
    //  printf("xd\n");
    studenci->tablica = (char **)malloc(sizeof(char *) * studenci->ile);
    studenci->imie = (char **)malloc(sizeof(char *) * studenci->ile);
    studenci->nr_albumu = (char **)malloc(sizeof(char *) * studenci->ile);
    // printf("xd\n");
    int k = ile_ocen(oceny);
    // printf("xd\n");
    Ocena *blok = oceny->lista_przedmiotow;

    //printf("a tego ile %d\n", k);
    for (int i = 0; i < k; i++)
    {
        if (strcmp(id, blok->id) == 0)
        {
            studenci->tablica[x] = id_na_nazwisko(studenci->tablica[x], stud, blok->nr_albumu);
            // printf("%s\n", studenci.tablica[x]);
            studenci->nr_albumu[x] = (char *)malloc(sizeof(blok->id));
            studenci->nr_albumu[x] = blok->nr_albumu;
            x++;
            blok = blok->nast;
        }
        else
        {
            blok = blok->nast;
        }
    }
    // printf("xd\n");

    usun_duplikaty(studenci);
    sortuj_studentow(studenci);
    imie_do_nazwiska(studenci, stud);
    //printf("ile bylo alokow%d\n", x);
    return studenci;
}

void imie_do_nazwiska(tablica *nazwiska, SBaza *studenci)
{
    //printf("xd\n");
    Student *baza;
    // printf("xd\n");
    int ile_stud = ile_studentow(studenci);
    //printf("%d\n", nazwiska->ile);
    for (int i = 0; i < nazwiska->ile; i++)
    {

        baza = studenci->lista_studentow;
        for (int j = 0; j < ile_stud; j++)
        {
            //printf("%s %s\n", nazwiska->nr_albumu[i], baza->nr_albumu);
            if (strcmp(nazwiska->nr_albumu[i], baza->nr_albumu) == 0)
            {
                //printf("xd\n");
                //strcpy(nazwiska->imie[i], baza->imie);
                nazwiska->imie[i] = baza->imie;
                //printf("%s %s\n", nazwiska->imie[i], baza->imie);
            }
            // printf("xd\n");
            baza = baza->nast;
        }
    }
    //printf("xd\n");
}

void wypisz_chary(tablica *sort)
{
    for (int i = 0; i < sort->ile; i++)
    {
        printf("%d. %s %s %s\n", i + 1, sort->tablica[i], sort->imie[i], sort->nr_albumu[i]);
    }
}

float srednia_ocena(Socena *glowa, char *id)
{
    float suma = 0;
    int ile = ile_ocen(glowa), n = 0;
    Ocena *dane = glowa->lista_przedmiotow;
    for (int i = 0; i < ile; i++)
    {
        //printf("%s %s\n", dane->id, id);
        if (strcmp(dane->id, id) == 0)
        {
            suma = suma + dane->ocena;
            n++;
            //printf("xd\n");
        }
        dane = dane->nast;
        //printf("%4.2f %d\n", suma, n);
    }
    return suma / n;
}

int ile_ocen_przedmiot(Socena *glowa, char *id)
{

    int ile = ile_ocen(glowa), n = 0;
    Ocena *dane = glowa->lista_przedmiotow;
    for (int i = 0; i < ile; i++)
    {
        if (strcmp(dane->id, id) == 0)
        {
            n++;
        }
        dane = dane->nast;
    }
    return n;
}

void zwolnij_tab(tablica *tab)
{
    //printf("ile tu jest tego %d\n", tab->ile);
    free(tab->tablica);
    free(tab->imie);
    free(tab->nr_albumu);
    free(tab);
}
