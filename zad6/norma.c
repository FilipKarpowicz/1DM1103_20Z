#include "liczenie.h"
float norma(float **m, int a, int b)
{
    float suma = 0;
    for (int i = 0; i < a; i++)
        for (int j = 0; j < b; j++)
            suma = suma + (m[i][j] * m[i][j]);
    suma = sqrtf(suma);
    return suma;
}