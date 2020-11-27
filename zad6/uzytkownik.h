#ifndef UZYTKOWNIK_H
#define UZYTKOWNIK_H

#include "pamiec.h"

void zapisz(char nazwa[], float **macierz, int a, int b);
float **wczytaj(int *a, int *b, FILE *plik);
void wypisz(float **m, int a, int b);


#endif