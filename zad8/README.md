Proszę zmodyfikować program do zarządzania bazą studentów tak aby:

Umożliwiał wyświetlanie posortowanej rosnąco i malejąco (alfabetycznie) po nazwisku wwszystkich studentów w bazie.
Umożliwiał wyświetlenie listy przedmiotów posortowanych alfabetycznie po kodzie przedmiotu.
Umożliwiał wyświetlenie listy przedmiotów posortowanych alfabetycznie po nazwie przedmiotu.
Umożliwiał wyświetlenie listy ocen z przedmiotu o zadanym kodzie.
Umożliwiał wyświetlenie listy wszystkich ocen danego studenta.
Proszę zaprojektować odpowiednie parametry przekazywane do programu main w momencie uruchomienia programu. Proszę samodzielnie wybrać metodę sortowania oraz wyświetlania.

Sugeruję, że przyda się, żebyście zaimplementowali sobie następujące funkcje:

Ad.1: to jest kalka z seminarium - powinno pójść łatwo, metodą Copiego i Pasty.
Ad.2: to jest kalka z seminarium - powinno pójść łatwo, metodą Copiego i Pasty tylko dla innych struktór danych.
Ad.3: to jest kalka z seminarium - powinno pójść łatwo, metodą Copiego i Pasty tylko dla innych struktór danych.
Ad.4. Sugeruję napisanie funkcji:

Przedmiot * filtruj(Przedmiot * glowa, char *kod_przedmiotu) {
    // tutaj powinniście utworzyć nową listę i dodać do niej wszystkie elementy,
    // ktore pasuja do zadanego kodu....
    return nowa_glowa;
}
Ad.5. Sugeruję napisanie funkcji:

Ocena * filtruj(Ocena * glowa, char *nr_albumu) {
    // tutaj powinniście utworzyć nową listę i dodać do niej wszystkie elementy,
    // ktore pasuja do zadanego numeru albumu....
    return nowa_glowa;
}
Proszę tutaj wgrać archiwum zip repozytorium na githubie.