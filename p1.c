#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float v, a1, a2;
    a1 = atof("12.3");
    a2 = atof("0.1");
    v = a1 + a2;

    printf("[%s] Suma %f\n", argv[0], v);
}