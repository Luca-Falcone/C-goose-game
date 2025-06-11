#include "gestire_percorso.h"
#include <stdio.h>


const char NUOVA_RIGA = '\n';
const char SEPARATORE = '|';
const char GIALLO[] = "\033[1;33m";
const char ROSSO[] = "\033[1;31m";
const char MARRONE[] = "\033[0;33;31m";
const char VERDE[] = "\033[1;32m";
const char BLU[] = "\033[1;34m";
const char ARANCIONE[] = "\033[1;91m";
const char VIOLA[] = "\033[1;35m";
const char CYAN[] = "\033[1;36m";

void scrivere_percorso(tabellone *tabellone_percorso, int pos, int n)
{
	tabellone_percorso->percorso[pos] = n;
}


int leggere_percorso(tabellone tabellone_percorso, int pos)
{
    int n = tabellone_percorso.percorso[pos];
    return n;
}


void scrivere_dimensione(tabellone *tabellone_percorso, int n)
{
	tabellone_percorso->dimensione = n;
}


int leggere_dimensione(tabellone tabellone_percorso)
{
    int n = tabellone_percorso.dimensione;
    return n;
}

void generare_percorso(tabellone *tabellone_percorso)
{

	const int PONTE = 6; // posizione della casella speciale PONTE quando il numero di caselle è standard, ovvero 90
    const int LOCANDA = 19; // posizione della casella speciale LOCANDA quando il numero di caselle è standard, ovvero 90
	const int POZZO = 31; // posizione della casella speciale POZZO quando il numero di caselle è standard, ovvero 90
	const int LABIRINTO = 42; // posizione della casella speciale LABIRINTO quando il numero di caselle è standard, ovvero 90
	const int PRIGIONE = 52; // posizione della casella speciale PRIGIONE quando il numero di caselle è standard, ovvero 90
	const int SCHELETRO = 58; // posizione della casella speciale SCHELETRO quando il numero di caselle è standard, ovvero 90

    int dimensione = leggere_dimensione(*tabellone_percorso);
    stabilire_percorso(tabellone_percorso);


    int ponte = calcolare_proporzione(dimensione,MAX_PERCORSO,PONTE) - 1;
    scrivere_percorso(tabellone_percorso, ponte,POSIZIONE_PONTE);

    int locanda = calcolare_proporzione(dimensione,MAX_PERCORSO,LOCANDA) - 1;
    scrivere_percorso(tabellone_percorso, locanda,POSIZIONE_LOCANDA);

    int pozzo = calcolare_proporzione(dimensione, MAX_PERCORSO,POZZO) - 1;
    scrivere_percorso(tabellone_percorso, pozzo, POSIZIONE_POZZO);

    int labirinto = calcolare_proporzione(dimensione, MAX_PERCORSO,LABIRINTO) - 1;
    scrivere_percorso(tabellone_percorso, labirinto, POSIZIONE_LABIRINTO);

    int prigione = calcolare_proporzione(dimensione, MAX_PERCORSO, PRIGIONE) - 1;
    scrivere_percorso(tabellone_percorso, prigione, POSIZIONE_PRIGIONE);

    int scheletro = calcolare_proporzione(dimensione, MAX_PERCORSO,SCHELETRO) - 1;
    scrivere_percorso(tabellone_percorso, scheletro,POSIZIONE_SCHELETRO);

    inserire_caselle_oca(tabellone_percorso);
}


void stabilire_percorso(tabellone *tabellone_percorso)
{
    int dimensione = leggere_dimensione(*tabellone_percorso);

    int i = 0;
    while(i < dimensione){
        scrivere_percorso(tabellone_percorso, i, CASELLA_VUOTA);
        i = i + 1;
    }
}


void inserire_caselle_oca(tabellone *tabellone_percorso)
{
    const int DISTANZA_OCA = 9; // numero di caselle presenti tra due caselle oche

    int dimensione = leggere_dimensione(*tabellone_percorso);
    int distanza = 0;
    int pos = 0;
    int casella_percorso;

    while (pos < (dimensione - 1)) { // il -1 è necessario in quanto l'ultima casella non può essere una casella speciale
        distanza = distanza + 1;
        if (distanza == DISTANZA_OCA) {
        	casella_percorso = leggere_percorso(*tabellone_percorso, pos);
            if (casella_percorso == CASELLA_VUOTA) {
                scrivere_percorso(tabellone_percorso, pos, POSIZIONE_OCA);
                distanza = 0;
            } else {
                scrivere_percorso(tabellone_percorso, pos + 1, casella_percorso); // è spostata in avanti di uno la casella speciale in conflitto con la casella oca
                scrivere_percorso(tabellone_percorso, pos, POSIZIONE_OCA);
                distanza = 0;
            }
        }
        pos = pos + 1;
    }
}


void stampare_percorso(tabellone tabellone_percorso, int posizione_attuale)
{
    const int RIGA = 24;

    printf("%s", RESET_COLORE);

    int dimensione = leggere_dimensione(tabellone_percorso);
    int pos = 1;
    while (pos <= dimensione) {
        stampare_riga(tabellone_percorso, RIGA, &pos, posizione_attuale);
        if (pos <= dimensione) {
            stampare_riga_invertita(tabellone_percorso,RIGA, &pos,posizione_attuale);
        }
    }
    printf("%c", NUOVA_RIGA);
}


int calcolare_proporzione(int numero_1, int numero_2, int numero_3)
{
    int numero_4;

    if (numero_2 != 0) {
    	numero_4 = (numero_1 * numero_3) / numero_2;
    } else {
    	numero_4 = 0;
    }

    return numero_4;
}


void stampare_caselle(tabellone tabellone_percorso_attuale, int pos, int posizione_attuale)
{
    // sigle caselle speciali
    const char OCA[] = "OC";
    const char PONTE[] = "PO";
    const char LOCANDA[] = "LO";
    const char POZZO[] = "PO";
    const char LABIRINTO[] = "LB";
    const char PRIGIONE[] = "PR";
    const char SCHELETRO[] = "SC";

    int casella = leggere_percorso(tabellone_percorso_attuale,pos - 1); // necessario per allineare la posizione con gli indici dell'array
    if (casella == CASELLA_VUOTA) {
        if (posizione_attuale == pos - 1) {
            printf("%c%s%s%02d%s",SEPARATORE, RESET_COLORE,COLORE_ARANCIONE, pos, RESET_COLORE);
        } else {
            printf("%c%s%02d%s",SEPARATORE,RESET_COLORE, pos, RESET_COLORE);
        }

    } else if (casella == POSIZIONE_OCA) {
        if (posizione_attuale == pos - 1) {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE,COLORE_ARANCIONE,OCA, RESET_COLORE);
        } else {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE, GIALLO,OCA, RESET_COLORE);
        }

    } else if (casella == POSIZIONE_PONTE) {
        if (posizione_attuale == pos - 1) {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE,COLORE_ARANCIONE,PONTE, RESET_COLORE);
        } else {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE, VERDE,PONTE, RESET_COLORE);
        }

    } else if (casella == POSIZIONE_LOCANDA) {
        if (posizione_attuale == pos - 1) {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE, COLORE_ARANCIONE,LOCANDA, RESET_COLORE);
        } else {
            printf("%c%s%s%s%s", SEPARATORE,RESET_COLORE, BLU,LOCANDA, RESET_COLORE);
        }

    } else if (casella == POSIZIONE_POZZO) {
        if (posizione_attuale == pos - 1) {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE, COLORE_ARANCIONE,POZZO, RESET_COLORE);
        } else {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE,MARRONE,POZZO, RESET_COLORE);
        }

    } else if (casella == POSIZIONE_LABIRINTO) {
        if (posizione_attuale == pos - 1) {
            printf("%c%s%s%s%s", SEPARATORE,RESET_COLORE, COLORE_ARANCIONE,LABIRINTO, RESET_COLORE);
        } else {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE,ARANCIONE ,LABIRINTO, RESET_COLORE);
        }

    } else if (casella == POSIZIONE_PRIGIONE) {
        if (posizione_attuale == pos - 1) {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE, COLORE_ARANCIONE,PRIGIONE, RESET_COLORE);
        } else {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE,VIOLA,PRIGIONE, RESET_COLORE);
        }

    } else if (casella == POSIZIONE_SCHELETRO) {
        if (posizione_attuale == pos - 1) {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE, COLORE_ARANCIONE, SCHELETRO, RESET_COLORE);
        } else {
            printf("%c%s%s%s%s",SEPARATORE,RESET_COLORE,CYAN, SCHELETRO, RESET_COLORE);
        }
    }
}

void stampare_riga(tabellone tabellone_percorso_attuale, int caselle_r, int *pos, int posizione_attuale)
{
    int dimensione = leggere_dimensione(tabellone_percorso_attuale);
    int n_riga = 0;

    printf("%c", NUOVA_RIGA);

    while ((*pos <= dimensione) && (n_riga < caselle_r)) {
        // stampa regolare
        stampare_caselle(tabellone_percorso_attuale, *pos,posizione_attuale);
        *pos = *pos + 1;
        n_riga = n_riga + 1;
    }

    printf("%c%s%c",SEPARATORE,RESET_COLORE,NUOVA_RIGA);
    printf("%s", RESET_COLORE);
}

void stampare_riga_invertita(tabellone tabellone_percorso_attuale, int caselle_r, int *pos, int posizione_attuale)
{
    int dimensione = leggere_dimensione(tabellone_percorso_attuale);

    // verifica numero di caselle da stampare
    int caselle_non_presenti = dimensione - *pos + 1;
    if (caselle_non_presenti < caselle_r) {
        stampare_riga_minima(tabellone_percorso_attuale, caselle_r, pos, posizione_attuale);
    } else {
        stampare_riga_massima(tabellone_percorso_attuale,caselle_r, pos, posizione_attuale);
    }
}


void stampare_riga_minima(tabellone tabellone_percorso_attuale, int caselle_r, int *pos, int posizione_attuale_2)
{
    const char SPAZIO[] = "   ";

    int dimensione = leggere_dimensione(tabellone_percorso_attuale);
    int n_riga = 0;

    printf("%c", NUOVA_RIGA);

    // stampa inversa di un numero di caselle minore del numero di caselle per riga
    int caselle_non_presenti = dimensione - *pos + 1;
    int caselle_vuote = caselle_r - caselle_non_presenti;
    while (caselle_vuote > 0) {
        printf("%s",SPAZIO);
        caselle_vuote = caselle_vuote - 1;
    }
    *pos = *pos + caselle_non_presenti - 1;
    while (n_riga != caselle_non_presenti) {
        stampare_caselle(tabellone_percorso_attuale, *pos, posizione_attuale_2);
        *pos = *pos - 1;
        n_riga = n_riga + 1;
    }
    n_riga = 0;
    *pos = *pos + caselle_non_presenti + 1; // il + 1 è necessario per indicare che sono state stampate tutte le caselle

    printf("%c%s%c",SEPARATORE,RESET_COLORE,NUOVA_RIGA);
    printf("%s", RESET_COLORE);
}

void stampare_riga_massima(tabellone tabellone_percorso_attuale, int caselle_r, int *pos, int posizione_attuale)
{
    int n_riga = 0;

    printf("%c",NUOVA_RIGA);

    *pos = *pos + caselle_r - 1;
    while (n_riga != caselle_r) {
        stampare_caselle(tabellone_percorso_attuale, *pos, posizione_attuale);
        *pos = *pos - 1;
        n_riga = n_riga + 1;
    }

    *pos = *pos + caselle_r + 1;

    printf("%c%s%c",SEPARATORE,RESET_COLORE, NUOVA_RIGA);
    printf("%s", RESET_COLORE);
}


















