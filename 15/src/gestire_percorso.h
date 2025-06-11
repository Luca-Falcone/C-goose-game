#ifndef GENERARE_TABELLONE_H_
#define GENERARE_TABELLONE_H_


#define MIN_PERCORSO 50
#define MAX_PERCORSO 90
#define RESET_COLORE "\033[0m"
#define COLORE_ARANCIONE "\033[38;5;208m"
#define CASELLA_VUOTA 0
#define POSIZIONE_OCA 1
#define POSIZIONE_PONTE 2
#define POSIZIONE_LOCANDA 3
#define POSIZIONE_POZZO 4
#define POSIZIONE_LABIRINTO 5
#define POSIZIONE_PRIGIONE 6
#define POSIZIONE_SCHELETRO 7


typedef struct
{
    int percorso[MAX_PERCORSO];
    int dimensione;
}tabellone;


void scrivere_percorso(tabellone *tabellone_percorso, int pos, int n);


int leggere_percorso(tabellone tabellone_percorso, int pos);


void scrivere_dimensione(tabellone *tabellone_percorso, int n);


int leggere_dimensione(tabellone tabellone_percorso);


void generare_percorso(tabellone *tabellone_percorso);


void stampare_percorso(tabellone tabellone_percorso, int posizione_attuale);

int calcolare_proporzione(int numero_1, int numero_2, int numero_3);

void stabilire_percorso(tabellone *tabellone_percorso);

void inserire_caselle_oca(tabellone *tabellone_percorso);

void stampare_caselle(tabellone tabellone_percorso_attuale, int pos,int posizione_attuale);

void stampare_riga(tabellone tabellone_percorso_attuale, int caselle_r, int *pos, int posizione_attuale);

void stampare_riga_invertita(tabellone tabellone_percorso_attuale, int caselle_r, int *pos, int posizione_attuale);

void stampare_riga_minima(tabellone tabellone_percorso_attuale, int caselle_r, int *pos, int posizione_attuale_2);

void stampare_riga_massima(tabellone tabellone_percorso_attuale, int caselle_r, int *pos, int posizione_attuale);


#endif
