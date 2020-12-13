#include "baza.h"

Przedmiot *skok_o(Przedmiot *baza)
{
    while (baza->nast != NULL)
    {
        baza = baza->nast;
    }
    return baza;
}

void wypisz_up_o(Przedmiot *lista)
{
    // Student *lista=glowa->lista_studentow;
    //printf("co do cholery\n");
    if (lista != NULL)
    {
        //printf("cokolwiek\n");
        printf("%s %s %s\n", lista->id, lista->nazwa, lista->sem);
        wypisz_up_o(lista->nast);
    }
}

void od_tylu_o(Przedmiot *baza, Przedmiot *poprzedni)
{
    if (baza != NULL)
    {
        baza->poprz = poprzedni;
        //printf(" essa %s\n", baza->nazwisko);
        od_tylu_o(baza->nast, baza);
        //printf("%s\n", baza->nazwisko);
        //baza->poprz = poprzedni;
    }
}

void wypisz_pop_up_o(Przedmiot *lista)
{
    // Przedmiot
    //*lista = glowa->lista;
    //printf("co do cholery\n");
    if (lista != NULL)
    {
        //printf("cokolwiek\n");
        //printf("%s %s %s %s\n", lista->imie, lista->nazwisko, lista->nr_albumu, lista->email);
        wypisz_pop_up_o(lista->poprz);
        printf("%s %s %s\n", lista->nazwa, lista->id, lista->sem);
    }
}

void wypisz_pop_down_o(Przedmiot *lista)
{
    // Przedmiot
    //*lista = glowa->lista_studentow;
    //printf("co do cholery\n");
    if (lista != NULL)
    {
        //printf("cokolwiek\n");
        printf("%s %s %s\n", lista->id, lista->nazwa, lista->sem);
        wypisz_pop_down_o(lista->poprz);
        //printf(" xd     %s %s %s %s\n", lista->imie, lista->nazwisko, lista->nr_albumu, lista->email);
    }
}

Przedmiot *usun_o(Przedmiot *glowa, Przedmiot *co)
{
    Przedmiot *lista = glowa;
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

Przedmiot *sortuj_o(Przedmiot *baza)
{
    Przedmiot
        *wynik = baza;
    while (baza != NULL)
    {
        if (strcmp(baza->nazwa, wynik->nazwa) <= 0)
        {
            wynik = baza;
        }
        baza = baza->nast;
    }
    return wynik;
}

void alfabet_o(SPrzedmiot *glowa, int tryb)
{
    Przedmiot *wynik = NULL;
    Przedmiot *pom;
    Przedmiot *lista = glowa->lista_przedmiotow;
    int ile = ile_przedmiotow(glowa);
    for (int i = 0; i < ile; i++)
    {
        if (wynik == NULL)
        {
            pom = sortuj_o(lista);
            lista = usun_o(lista, pom);
            pom->poprz = NULL;
            wynik = pom;
        }
        else
        {
            pom = sortuj_o(lista);
            //printf("yyyy\n");
            lista = usun_o(lista, pom);
            // printf("aaaaay\n");
            pom->poprz = wynik;
            wynik->nast = pom;
            wynik = wynik->nast;
        }
        //printf("xd\n");
    }
    if (tryb == 1)
        wypisz_pop_down_o(wynik);
    if (tryb == 0)
        wypisz_pop_up_o(wynik);
}

void funkcja_o(SPrzedmiot *glowa, int tryb)
{
    Przedmiot *lista = glowa->lista_przedmiotow;
    Przedmiot *wynik;
    //sortuj_p(glowa, wynik);
    //lista = usun_p(lista, lista->nast);
    //printf("%s\n", sortuj(lista)->nazwisko);
    //wypisz_up(wynik);
    //printf("xd\n");
    //od_tylu(lista, NULL);
    //lista = skok(lista);
    //wypisz_pop(lista);
    // printf("                                   xd\n");
    alfabet_o(glowa, tryb);
}

void list_by_course(Socena *glowa, char *co)
{
    Ocena *lista = glowa->lista_przedmiotow;
    while (lista != NULL)
    {
        if (strcmp(co, lista->id) == 0)
        {
            printf("%s %4.2f %s\n", lista->nr_albumu, lista->ocena, lista->komentarz);
        }
        lista = lista->nast;
    }
}

void list_grades_by_student(Socena *glowa, char *co)
{
    Ocena *lista = glowa->lista_przedmiotow;
    while (lista != NULL)
    {
        if (strcmp(co, lista->nr_albumu) == 0)
        {
            printf("%s %4.2f %s\n", lista->id, lista->ocena, lista->komentarz);
        }
        lista = lista->nast;
    }
}