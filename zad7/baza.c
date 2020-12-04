#include "baza.h"

Student *wczytaj_studentow(FILE *fin)
{
    char bufor[255];
    int n, i;
    char *s;
    Student *last_student = NULL;
    Student *glowa = NULL;
    fgets(bufor, 254, fin);
    sscanf(bufor, "%d", &n);

    for (i = 0; i < n; i++)
    {
        Student *stud = (Student *)malloc(sizeof(Student));
        stud->nast = NULL;

        if (last_student == NULL)
            glowa = stud;
        else
            last_student->nast = stud;
        last_student = stud;

        fgets(bufor, 254, fin);
        s = strtok(bufor, ";");
        stud->imie = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(stud->imie, s);

        s = strtok(NULL, ";");
        stud->nazwisko = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nazwisko, s);

        s = strtok(NULL, ";");
        stud->nr_albumu = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(stud->nr_albumu, s);

        s = strtok(NULL, "\n");
        stud->email = (char *)malloc(sizeof(char) * (strlen(s) + 1));
        strcpy(stud->email, s);
    }

    return glowa;
}

SBaza *dodaj_studenta(SBaza *baza, char *imie, char *nazwisko, char *id, char *mail)
{
    int ile = ile_studentow(baza);
    Student *nowy = (Student *)malloc(sizeof(Student));
    Student *stud = baza->lista_studentow;
    for (int i = 0; i < ile; i++)
    {
        if (stud->nast == NULL)
            stud->nast = nowy;
        else
        {
            stud = stud->nast;
        }
    }
    stud = nowy;
    stud->imie = (char *)malloc(sizeof(char) * (strlen(imie) + 1));
    strcpy(stud->imie, imie);

    stud->nazwisko = (char *)malloc(sizeof(char) * (strlen(nazwisko) + 1));
    strcpy(stud->nazwisko, nazwisko);

    stud->nr_albumu = (char *)malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(stud->nr_albumu, id);

    stud->email = (char *)malloc(sizeof(char) * (strlen(mail) + 1));
    strcpy(stud->email, mail);

    stud->nast = NULL;

    return baza;
}

SBaza *wczytaj_baze_stud(FILE *fin, char *nazwa_pliku)
{
    if (fin == NULL)
    {
        printf("BŁĄD! Nie moge otworzyc pliku: %s.\n", nazwa_pliku);
        exit(-1);
    }

    SBaza *baza = (SBaza *)malloc(sizeof(SBaza));
    baza->lista_studentow = wczytaj_studentow(fin);

    return baza;
}

SBaza *zapisz_baze(char *nazwa_pliku, SBaza *baza)
{
    return NULL;
}

int ile_studentow(SBaza *baza)
{
    int n = 0;
    Student *stud = baza->lista_studentow;
    while (stud != NULL)
    {
        n++;
        stud = stud->nast;
    }
    return n;
}

void listuj_studentow(SBaza *baza)
{
    Student *stud = baza->lista_studentow;
    while (stud != NULL)
    {
        printf("%s %s %s %s\n", stud->imie, stud->nazwisko, stud->nr_albumu, stud->email);
        stud = stud->nast;
    }
}

void zwolnij_student(Student *s)
{
    free(s->imie);
    free(s->nazwisko);
    free(s->nr_albumu);
    free(s->email);
    free(s);
}

void zwolnij_liste_studentow(Student *s)
{
    Student *n;
    while (s != NULL)
    {
        n = s->nast;
        zwolnij_student(s);
        s = n;
    }
}

void zwolnij(SBaza *baza)
{
    zwolnij_liste_studentow(baza->lista_studentow);
    free(baza);
}