#ifndef GESTIRE_FILE_H_
#define GESTIRE_FILE_H_


#include <stdio.h>
#include <limits.h>

#define LETTURA_TESTO "r"
#define SCRITTURA_TESTO "w"
#define LETTURA_BINARIA "rb"
#define SCRITTURA_BINARIA "wb"
#define INTERFACCIA_INIZIALE 1
#define PRINCIPALE 2
#define PARTITA 3
#define CARICA 4
#define AIUTO 5
#define CLASSIFICA 6
#define CLASSIFICA_BINARIA 6
#define REGOLE 7
#define MANUALE 8
#define PARTITA_IN_CORSO 9
#define LINEA '\n'
#define FINE_STRINGA '\0'
#define MAX_SLOT 5
#define SOTTOMENU  "Premi 0 per andare indietro o 1 per uscire-> "
#define ERRORE_FILE INT_MIN

void leggere_file_di_testo(FILE *file_testo, int num_caratteri, char *stringa_file);


void scrivere_file_di_testo(FILE *file_testo, char *stringa);


int calcolare_lunghezza_file_di_testo(FILE *file);

void stampare_file_di_testo(FILE *file_testo);


void stampare_stringa_da_file(char *stringa);


FILE* ricercare_slots(int slot, char tipo_apertura[]);


FILE* ricercare_il_menu(int riga, char tipo_apertura[]);


int leggere_tastiera_int_verificato();


int scegliere_opzione_di_menu(FILE *file_menu, int min_scelta, int max_scelta);

int convertire_ascii_intero(char numero_char[], int dim);

int calcolare_potenza(int base_numero, int esponente);

void leggere_riga_di_file(FILE* file, char riga[]);
#endif
