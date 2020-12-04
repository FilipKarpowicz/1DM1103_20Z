#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baza.h"

int main(int argc, char **argv)
{
    FILE *fin = fopen(argv[1], "r");
    //FILE *fout = fopen("wynik.csv", "w+");
    //printf("xd\n");
    SBaza *baza_stud;
    SPrzedmiot *baza_sbj;
    Socena *baza_ocen;
    baza_stud = wczytaj_baze_stud(fin, argv[1]);
    baza_sbj = wczytaj_baze_sbj(fin, argv[1]);
    baza_ocen = wczytaj_baze_ocen(fin, argv[1]);
    fclose(fin);
    //zapis_bazy(baza_ocen, baza_stud, baza_sbj, fin);
    //printf("xd\n");
    if (strcmp("add", argv[2]) == 0)
    {
        if (strcmp(argv[3], "student") == 0)
        {
            // printf("xd\n");
            dodaj_studenta(baza_stud, argv[4], argv[5], argv[6], argv[7]);
        }
        else if (strcmp(argv[3], "course") == 0)
        {
            dodaj_przedmiot(baza_sbj, argv[4], argv[5], argv[6]);
        }
        else if (strcmp(argv[3], "student_to_course") == 0)
        {
            dodaj_ocene(baza_ocen, argv[4], argv[5], 0, " ");
        }
    }
    else if (strcmp("list_students", argv[2]) == 0)
    {
        listuj_studentow(baza_stud);
    }
    else if (strcmp("set_grade", argv[2]) == 0)
    {
        dodaj_ocene(baza_ocen, argv[3], argv[4], atof(argv[5]), argv[6]);
    }
    else if (strcmp("student_average", argv[2]) == 0)
    {
        printf("Student o nr indeksu: %s ma srednia ocen = %4.2f\n", argv[3], srednia(argv[3], baza_ocen));
    }
    else if (strcmp("list_students_by_cours", argv[2]) == 0)
    {
        tablica *sort = sortowanie_uczniow_dla_oceny(baza_ocen, baza_stud, argv[3]);
        wypisz_chary(sort);
        zwolnij_tab(sort);
    }
    else if (strcmp("course_average", argv[2]) == 0)
    {
        float a = srednia_ocena(baza_ocen, argv[3]);
        printf("srednia ocen dla przedmiotu %s to %4.2f\n", argv[3], a);
    }
    else if (strcmp("course_grades", argv[2]) == 0)
    {
        int a = ile_ocen_przedmiot(baza_ocen, argv[3]);
        printf("z przedmiotu %s jest %d ocen\n", argv[3], a);
    }
    else if (strcmp("show", argv[2]) == 0)
    {
        if (strcmp("students", argv[3]) == 0)
            listuj_studentow(baza_stud);
        else if (strcmp("courses", argv[3]) == 0)
            listuj_przedmioty(baza_sbj);
    }
    FILE *fout = fopen(argv[1], "w+");
    zapis_bazy(baza_ocen, baza_stud, baza_sbj, fin);
    //listuj_studentow(baza_stud);
    zwolnij_O(baza_ocen);
    zwolnij_P(baza_sbj);
    zwolnij(baza_stud);
    fclose(fout);
    return 0;
}