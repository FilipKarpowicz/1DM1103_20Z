#include "baza.h"

Student *skok(Student *baza)
{
    while (baza->nast != NULL)
    {
        baza = baza->nast;
    }
    return baza;
}

void wypisz_up(Student *lista)
{
    // Student *lista=glowa->lista_studentow;
    //printf("co do cholery\n");
    if (lista != NULL)
    {
        //printf("cokolwiek\n");
        printf("%s %s %s %s\n", lista->imie, lista->nazwisko, lista->nr_albumu, lista->email);
        wypisz_up(lista->nast);
    }
}

void od_tylu(Student *baza, Student *poprzedni)
{
    if (baza != NULL)
    {
        baza->poprz = poprzedni;
        //printf(" essa %s\n", baza->nazwisko);
        od_tylu(baza->nast, baza);
        //printf("%s\n", baza->nazwisko);
        //baza->poprz = poprzedni;
    }
}

void wypisz_pop_up(Student *lista)
{
    // Student *lista=glowa->lista_studentow;
    //printf("co do cholery\n");
    if (lista != NULL)
    {
        //printf("cokolwiek\n");
        //printf("%s %s %s %s\n", lista->imie, lista->nazwisko, lista->nr_albumu, lista->email);
        wypisz_pop_up(lista->poprz);
        printf("%s %s %s %s\n", lista->imie, lista->nazwisko, lista->nr_albumu, lista->email);
    }
}

void wypisz_pop_down(Student *lista)
{
    // Student *lista=glowa->lista_studentow;
    //printf("co do cholery\n");
    if (lista != NULL)
    {
        //printf("cokolwiek\n");
        printf("%s %s %s %s\n", lista->imie, lista->nazwisko, lista->nr_albumu, lista->email);
        wypisz_pop_down(lista->poprz);
        //printf(" xd     %s %s %s %s\n", lista->imie, lista->nazwisko, lista->nr_albumu, lista->email);
    }
}

Student *usun(Student *glowa, Student *co)
{
    Student *lista = glowa;
    if (glowa == co)
    {
        if (glowa->nast != NULL)
            glowa = glowa->nast;
        glowa->poprz = NULL;
        return glowa;
    }
    while (glowa != NULL)
    {
        //glowa = glowa->nast;
        if (glowa->nast == co)
        {
            glowa->nast = co->nast;
            // glowa->nast->poprz = glowa;
        }
        glowa = glowa->nast;
    }
    return lista;
}

Student *sortuj(Student *baza)
{
    Student *wynik = baza;
    while (baza != NULL)
    {
        if (strcmp(baza->nazwisko, wynik->nazwisko) <= 0)
        {
            wynik = baza;
        }
        baza = baza->nast;
    }
    return wynik;
}

void alfabet(SBaza *glowa, int tryb)
{
    Student *wynik = NULL;
    Student *pom;
    Student *lista = glowa->lista_studentow;
    int ile = ile_studentow(glowa);
    for (int i = 0; i < ile; i++)
    {
        if (wynik == NULL)
        {
            pom = sortuj(lista);
            lista = usun(lista, pom);
            pom->poprz = NULL;
            wynik = pom;
        }
        else
        {
            pom = sortuj(lista);
            //printf("yyyy\n");
            lista = usun(lista, pom);
            // printf("aaaaay\n");
            pom->poprz = wynik;
            wynik->nast = pom;
            wynik = wynik->nast;
        }
        //printf("xd\n");
    }
    if (tryb == 1)
        wypisz_pop_down(wynik);
    if (tryb == 0)
        wypisz_pop_up(wynik);
}

void funkcja(SBaza *glowa, int tryb)
{
    Student *lista = glowa->lista_studentow;
    Student *wynik;
    //sortuj(glowa, wynik);
    //lista = usun(lista, lista->nast);
    //printf("%s\n", sortuj(lista)->nazwisko);
    //wypisz_up(wynik);
    //printf("xd\n");
    //od_tylu(lista, NULL);
    //lista = skok(lista);
    //wypisz_pop(lista);
   // printf("                                   xd\n");
    alfabet(glowa, tryb);
}