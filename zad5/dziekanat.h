#ifndef DZIEKANAT_H
#define DZIEKANAT_H

#include "studenci.h"

int znajdz_oceny(char nr_albumow[100][10], student dane[100], int n);
void najlepsza_ocena(student dane[100], int ile_rekordow);
void najgorsza_ocena(student dane[100], int ile_rekordow);
int znajdz_studentow(char nr_albumow[100][10], student dane[100], int n);
void najlepszy_student(student dane[100], int ile_rekordow);
#endif