#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    float a;
    a = atof(argv[1]);
    printf("potega z liczby %s to %f\n", argv[1], a * a);
    return 0;
}
