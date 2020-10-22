
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int a = 0;
    if (argc == 1)
    {
        printf("nie podano ani jednej liczby\n");
    }
    else
    {
        for (int i = 0; i < argc; i++)
        {
            a = a + atof(argv[i]);
        }
        printf("suma tych liczb to %d\n", a);
    }
    return 0;
}
