#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float a;
    a = atof(argv[1]);
    printf("wartosc %s do kwadratu to %f\n", argv[1], a * a);
    return 0;
}