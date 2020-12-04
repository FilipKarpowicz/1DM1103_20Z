#include "baza.h"

void zapis_bazy(Socena *glowa_ocen, SBaza *glowa_stud, SPrzedmiot *glowa_sbj, FILE *zapis)
{

    //printf("xd\n");
    int ile_stud = ile_studentow(glowa_stud);
    int ile_sbj = ile_przedmiotow(glowa_sbj);
    int ile_o = ile_ocen(glowa_ocen);
    Student *std = glowa_stud->lista_studentow;
    Ocena *ocena = glowa_ocen->lista_przedmiotow;
    Przedmiot *sbj = glowa_sbj->lista_przedmiotow;
    fprintf(zapis, "%d\n", ile_stud);
    for (int i = 0; i < ile_stud; i++)
    {
        fprintf(zapis, "%s;", std->imie);
        fprintf(zapis, "%s;", std->nazwisko);
        fprintf(zapis, "%s;", std->nr_albumu);
        fprintf(zapis, "%s\n", std->email);
        std = std->nast;
    }
    fprintf(zapis, "%d\n", ile_sbj);
    for (int i = 0; i < ile_sbj; i++)
    {
        fprintf(zapis, "%s;", sbj->id);
        fprintf(zapis, "%s;", sbj->nazwa);
        fprintf(zapis, "%s\n", sbj->sem);
        sbj = sbj->nast;
    }
    fprintf(zapis, "%d\n", ile_o);
    for (int i = 0; i < ile_o; i++)
    {
        fprintf(zapis, "%s;", ocena->id);
        fprintf(zapis, "%s;", ocena->nr_albumu);
        fprintf(zapis, "%4.2f;", ocena->ocena);
        fprintf(zapis, "%s\n", ocena->komentarz);
        ocena = ocena->nast;
    }
    //fclose(zapis);
}