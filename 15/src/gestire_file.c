#include "gestire_file.h"
#include <stdlib.h>

#define MAX_PERCORSO_FILE 257

FILE* spostare_a_riga(FILE* file, int riga_attuale);

void leggere_file_di_testo(FILE *file_testo, int num_caratteri, char *stringa_file)
{
    fseek(file_testo, 0, SEEK_SET);

    int i = 0;
    char c;
    while (i < num_caratteri) {
        c = fgetc(file_testo);
        stringa_file[i] = c;
        i = i + 1;
    }
    stringa_file[i] = FINE_STRINGA;
}


void scrivere_file_di_testo(FILE *file_testo, char *stringa)
{
    int i = 0;
    while (stringa[i] != FINE_STRINGA) {
        fputc(stringa[i], file_testo);
        i = i + 1;
    }
}


int calcolare_lunghezza_file_di_testo(FILE *file)
{
    fseek(file, 0, SEEK_SET);

    int num_caratteri = 0;
    char c = fgetc(file);
    while (c != EOF) {
        num_caratteri = num_caratteri + 1;
        c = fgetc(file);
    }

    return num_caratteri;
}


void stampare_file_di_testo(FILE *file_testo)
{
    int lungh_file = calcolare_lunghezza_file_di_testo(file_testo);
    char *stringa_file = calloc(lungh_file + 1, sizeof(char)); // Il + 1 è necessario per l'inserimento del FINE_STRINGA

    leggere_file_di_testo(file_testo, lungh_file, stringa_file);
    stampare_stringa_da_file(stringa_file);
}


void stampare_stringa_da_file(char *stringa) {
    int i = 0;
    char c = stringa[i];

    while (c != FINE_STRINGA) {
        printf("%c", c);
        i = i + 1;
        c = stringa[i];
    }
}


FILE* ricercare_slots(int slot, char tipo_apertura[])
{
    const char PERCORSO_BINARI[] = "..//file//lista_file_bin.txt";

    FILE *file_percorsi_salvataggi = NULL;
    FILE *file_slot = NULL;
    file_percorsi_salvataggi = fopen(PERCORSO_BINARI, LETTURA_TESTO);
    if (file_percorsi_salvataggi != NULL) {

        file_percorsi_salvataggi = spostare_a_riga(file_percorsi_salvataggi, slot);


        char percorso[MAX_PERCORSO_FILE];
        leggere_riga_di_file(file_percorsi_salvataggi, percorso);

        file_slot = fopen(percorso, tipo_apertura);
        return file_slot;
    } else {
        return file_slot;
    }
}


FILE* ricercare_il_menu(int riga, char tipo_apertura[])
{
    const char PERCORSO_MENU[] = "..//menu//lista_menu.txt";
    FILE *file_percorsi_menu = NULL;
    FILE *file_menu = NULL;
    file_percorsi_menu = fopen(PERCORSO_MENU, LETTURA_TESTO);
    if (file_percorsi_menu == NULL) {
        return file_menu;
    } else {

        file_percorsi_menu = spostare_a_riga(file_percorsi_menu, riga);


        char percorso[MAX_PERCORSO_FILE];
        leggere_riga_di_file(file_percorsi_menu, percorso);

        file_menu = fopen(percorso, tipo_apertura);
        return file_menu;
    }
}


FILE* spostare_a_riga(FILE* file, int riga_attuale)
{

    int riga = 1;
    char c;
    if (riga_attuale != 1) {
        c = fgetc(file);
        while ((riga != riga_attuale) && (c != EOF)) {
            c = fgetc(file);
            while ((c != LINEA) && (c != EOF)) {
                c = fgetc(file);
            }
            riga = riga + 1;
        }
    }

    return file;
}


void leggere_riga_di_file(FILE* file, char riga[])
{

    int i = 0;
    char c;
    c = fgetc(file);
    while ((c != LINEA) && (c != EOF)) {
        riga[i] = c;
        i = i + 1;
        c = fgetc(file);
    }
    riga[i] = FINE_STRINGA;
}


int leggere_tastiera_int_verificato()
{
    const int MAX_INPUT = 2;

    int numero;

    char input[MAX_INPUT];
    int i = 0;
    input[i] = getchar();
    while ((input[i] != LINEA) && (i < MAX_INPUT)) {
        i = i + 1;
        if (i == MAX_INPUT) {
            char c = getchar();
            if (c != LINEA) {
                numero = INT_MIN;
            }
        } else {
            input[i] = getchar();
        }
    }

    if (numero != INT_MIN) {
        numero = convertire_ascii_intero(input, MAX_INPUT);
    }

    return numero;
}


int convertire_ascii_intero(char numero_char[], int dim)
{
    const int BASE_DECIMALE = 10;
    const int ASCII_9 = '9';
    const int ASCII_0 = '0';

    int numero = 0;
    int i = dim - 1;
    int potenza;
    int cifra;
    int esponente = 0;
    int valore_ascii;

    if (numero_char[dim - 1] == LINEA) {
        i = i - 1;
    }
    while ((i >= 0) && (numero != INT_MIN)) {
        valore_ascii = numero_char[i];
        if ((valore_ascii <= ASCII_9) && (valore_ascii >= ASCII_0)) {
            cifra = valore_ascii - ASCII_0;
            potenza = calcolare_potenza(BASE_DECIMALE, esponente);
            numero = numero + (cifra * potenza);

            i = i - 1;
            esponente = esponente + 1;
        } else {
            numero = INT_MIN;
        }
    }

    return numero;
}


int calcolare_potenza(int base_numero, int esponente)
{
    int i = 1;
    int potenza = 1;

    while (i <= esponente) {
        potenza = potenza * base_numero;
        i = i + 1;
    }

    return potenza;
}


int scegliere_opzione_di_menu(FILE *file_menu, int min_scelta, int max_scelta)
{
    int scelta;

    do {
        system("cls");
        stampare_file_di_testo(file_menu);
        scelta = leggere_tastiera_int_verificato();
    } while ((scelta > max_scelta) || (scelta < min_scelta));

    return scelta;
}
