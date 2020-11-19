#include <stdio.h>
#include "studenci.h"
#include "dziekanat.h"


int main(int argc, char **argv)
{
    student dane[100];
    int ile;
    // dane == &dane[0]
    ile = wczytaj(dane, argv[1]);
    //wypisz(dane, ile);
    if (strcmp(argv[3], "student") == 0)
        najlepszy_student(dane, ile);
    else if (strcmp(argv[3], "ocena") == 0)
    {
        if (strcmp(argv[2], "najlepsza") == 0)
            najlepsza_ocena(dane, ile);
        else if (strcmp(argv[2], "najgorsza") == 0)
            najgorsza_ocena(dane, ile);
    }
    return 0;
}