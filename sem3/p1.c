#include <stdio.h>
#include <stdlib.h>

int main(int argv, char *argc[])
{
    float v, a1, a2;
    a1 = atof("12.3");
    a2 = atof("0.1");
    v = a1 + a2;

    printf("[%s] Suma %f\n", argc[0], v);
}