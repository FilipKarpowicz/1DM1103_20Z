#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

typedef struct _Memory
{
    char *response;
    size_t size;
} Memory;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp)
{
    /* to jest rzeczywista liczba bajtów przekazanych przez curl */
    size_t realsize = size * nmemb;

    /* jawnie konwertujemy (void*) na naszą strukturę, bo wiemy, że będziemy ją tutaj otrzymywać */
    Memory *mem = (Memory *)userp;

    char *ptr = NULL;

    /* Sprawdzamy czy pierwszy raz wywołujemy funkcję i trzeba zaalokować pamięć po raz pierwszy,
    czy trzeba zrobić reallokację (która kopiuje automatycznie starą zawartość w nowe miejsce) */
    if (mem->response != NULL)
        ptr = realloc(mem->response, mem->size + realsize + 1);
    else
        ptr = malloc(mem->size + realsize + 1);

    if (ptr == NULL)
        return 0; /* brak pamięci! */

    /* teraz zapamiętujemy nowy wskaźnik i doklejamy na końcu dane przekazane przez curl w 
       obszarze pamięci wskazywanym przez data */
    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0; // to na końcu dodajemy bo to w końcu string, i zawsze powinien się skończyć!

    return realsize;
}

int req(char *token, char *request, char *direction)
{
    char adres[254] = "http://edi.iem.pw.edu.pl:30000/worlds/api/v1/worlds/";
    //printf("%s\n%s\n", adres, token);
    char *url = strcat(adres, request);
    url = strcat(adres, "/");
    url = strcat(adres, token);
    if (direction)
    {
        url = strcat(adres, "/");
        url = strcat(adres, direction);
    }
    // printf("%s\n", url);
    CURL *curl;
    CURLcode res;
    Memory chunk;
    chunk.size = 0;
    chunk.response = NULL;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "Błąd! curl_easy_perform() niepowodzenie: %s\n", curl_easy_strerror(res));
            return 1;
        }
        else if (strcmp(request, "info") == 0)
        {

            printf("%s", chunk.response);
        }

        /* zawsze po sobie sprzątaj */
        free(chunk.response);
        curl_easy_cleanup(curl);
    }
    return 0;
}

int main(int argc, char **argv)
{
    char *token = argv[1];
    int i = 2;
    while (argv[i])
    {
        if (strcmp(argv[i], "info") == 0)
        {
            printf("info request sent success\n");
            int kod = req(token, argv[i], NULL);
        }
        if (strcmp(argv[i], "move") == 0)
        {
            printf("move request sent success\n");
            int kod = req(token, argv[i], NULL);
        }
        if (strcmp(argv[i], "rotate") == 0)
        {
            int kod;
            if (strcmp(argv[i + 1], "left") == 0)
            {
                printf("rotate left request sent success\n");
                kod = req(token, argv[i], argv[i + 1]);
            }
            else if (strcmp(argv[i + 1], "right") == 0)
            {
                printf("rotate right request sent success\n");
                kod = req(token, argv[i], argv[i + 1]);
            }
            else
                printf("enter the correct direction success\n");
        }
        if (strcmp(argv[i], "explore") == 0)
        {
            printf("explore request sent success\n");
            int kod = req(token, argv[i], NULL);
        }
        if (strcmp(argv[i], "reset") == 0)
        {
            printf("reset request sent success\n");
            int kod = req(token, argv[i], NULL);
        }
        i = i + 1;
    }
    printf("tank position(json) after operations:\n");
    int kod = req(argv[1], "info", NULL);
    return 0;
}