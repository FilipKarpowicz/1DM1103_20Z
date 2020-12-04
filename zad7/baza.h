#ifndef _BAZA_H
#define _BAZA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Student
{
    char *imie;
    char *nazwisko;
    char *nr_albumu;
    char *email;

    struct _Student *nast;
} Student;

typedef struct _Przedmiot
{
    char *id;
    char *nazwa;
    char *sem;

    struct _Przedmiot *nast;
} Przedmiot;

typedef struct _Ocena
{
    char *nr_albumu;
    char *id;
    float ocena;
    char *komentarz;

    struct _Ocena *nast;
} Ocena;

typedef struct _SBaza
{
    Student *lista_studentow; /* Głowa listy! */
} SBaza;

typedef struct _SPrzedmiot
{
    Przedmiot *lista_przedmiotow; /* Głowa listy! */
} SPrzedmiot;

typedef struct _tablica
{
    char **nr_albumu;
    char **imie;
    char **tablica;
    int ile;
} tablica;

typedef struct _Socena
{
    Ocena *lista_przedmiotow; /* Głowa listy! */
} Socena;

void imie_do_nazwiska(tablica *nazwiska, SBaza *studenci);
SBaza *wczytaj_baze_stud(FILE *fin, char *nazwa_pliku);
SBaza *zapisz_baze(char *nazwa_pliku, SBaza *baza);
void listuj_studentow(SBaza *baza);
void zwolnij(SBaza *baza);
int ile_studentow(SBaza *baza);
SBaza *dodaj_studenta(SBaza *baza, char *imie, char *nazwisko, char *id, char *mail);
Przedmiot *wczytaj_przedmioty(FILE *fin);
SPrzedmiot *wczytaj_baze_sbj(FILE *fin, char *nazwa_pliku);
int ile_przedmiotow(SPrzedmiot *baza);
void listuj_przedmioty(SPrzedmiot *baza);
SPrzedmiot *dodaj_przedmiot(SPrzedmiot *baza, char *id, char *nazwa, char *sem);
void zwolnij_P(SPrzedmiot *baza);
Socena *wczytaj_baze_ocen(FILE *fin, char *nazwa_pliku);
void listuj_oceny(Socena *baza);
Socena *dodaj_ocene(Socena *baza, char *nr_alb, char *id, float ocena, char *komentarz);
void zwolnij_O(Socena *baza);
float srednia(char *nr_albumu, Socena *baza);
tablica *sortowanie_uczniow_dla_oceny(Socena *oceny, SBaza *stud, char *id);
void wypisz_chary(tablica *sort);
int ile_przedmiotow(SPrzedmiot *baza);
int ile_ocen_przedmiot(Socena *glowa, char *id);
float srednia_ocena(Socena *glowa, char *id);
int ile_ocen_przedmiot(Socena *glowa, char *id);
int ile_ocen(Socena *baza);
void zapis_bazy(Socena *glowa_ocen, SBaza *glowa_stud, SPrzedmiot *glowa_sbj, FILE *zapis);
void zwolnij_tab(tablica *tab);

#endif