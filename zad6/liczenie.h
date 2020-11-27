#ifndef LICZENIE_H
#define LICZENIE_H

#include"pamiec.h"

float **skalar(float **m, int a, int b, float k);
float **mnozenie(float **m1, float **m2, int a1, int b1, int a2, int b2, int *a3, int *b3);
float norma(float **m, int a, int b);
float **odejmij(float **m1, float **m2, int *a1, int a2, int *b1, int b2);
float **suma(float **m1, float **m2, int *a1, int a2, int *b1, int b2);


#endif