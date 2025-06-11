#ifndef GESTIRE_GIOCO_H_
#define GESTIRE_GIOCO_H_


#include "gestire_percorso.h"
#define NOME 6
#define PARTITA_INTERROTTA -1

#define MIN_GIOCATORI 2
#define MAX_GIOCATORI 4

typedef struct
{
    int posizione;
    int lanci;
    int blocco;
    char nome_giocatore[NOME];
}giocatore;


typedef struct
{
    tabellone tabellone_percorso;
    int num_giocatori;
    int turno;
    giocatore giocatori[MAX_GIOCATORI];
}competizione_oca;


void scrivere_nome_giocatore(giocatore *giocatore, int pos, char c);


char leggere_nome_giocatore(giocatore giocatore, int pos);



void scrivere_posizione(giocatore *giocatore, int posizione_casella);


int leggere_posizione(giocatore giocatore);


void scrivere_lanci(giocatore *giocatore, int lanci_totali);


int leggere_lanci(giocatore giocatore);


void scrivere_blocco(giocatore *giocatore, int valore_blocco);


int leggere_blocco(giocatore giocatore);


void scrivere_tabellone_percorso(competizione_oca *partita, tabellone serpentina);


void leggere_tabellone_percorso(competizione_oca partita, tabellone *serpentina);


void scrivere_num_giocatori(competizione_oca *partita, int num_giocatori);


int leggere_num_giocatori(competizione_oca partita);


void scrivere_giocatori(competizione_oca *partita, int pos, giocatore giocatore);


void leggere_giocatori(competizione_oca partita, int pos, giocatore *giocatore);


void scrivere_turno(competizione_oca *partita, int turno);


int leggere_turno(competizione_oca partita);


void gestire_turno(competizione_oca partita_in_corso, giocatore *vincitore);


void configurare_partita(competizione_oca *partita);

void configurare_partita_p(competizione_oca *partita);


void visualizzare_partita(competizione_oca partita_in_corso, int posizione_attuale);


void stampare_posizioni(competizione_oca partita_in_corso, int turno);

void loading_bar();

void fissare_turno(competizione_oca *partita_in_corso);

void stampare_vincitore(giocatore vincitore);

void gestire_turno_blocco(competizione_oca *partita_in_corso, giocatore giocatore_attuale, int turno);

int aggiornare_turno(competizione_oca *partita_in_corso);

void gestire_turno_generale(competizione_oca *partita_in_corso, giocatore giocatore_attuale, int turno);

void gestire_caselle_speciali(competizione_oca *partita_in_corso, int primo_lancio, int secondo_lancio, int casella_speciale);

void gestire_casella_oca(competizione_oca *partita_in_corso, int primo_lancio, int secondo_lancio);

void gestire_casella_ponte(competizione_oca *partita_in_corso, int lancio);

void gestire_casella_locanda(competizione_oca *partita_in_corso);

void liberare_giocatore(competizione_oca *partita_in_corso);

void gestire_casella_blocco(competizione_oca *partita_in_corso);

void gestire_casella_labirinto(competizione_oca *partita_in_corso);

void gestire_casella_scheletro(competizione_oca *partita_in_corso);

void gestire_tabellone_lancio_vittoria(int num_caselle, int *pos_attuale, int lancio);

void liberare_prigione_lancio(giocatore *giocatore_prigione);

void configurare_partita_classica(competizione_oca *partita);

void configurare_partita_personalizzata(competizione_oca *partita);

void configurare_giocatori(competizione_oca *partita_attuale, int num_giocatori);

void usleep();

int verifica_numero(char c);

int verifica_carattere_speciale(char c);

int generare_numero(int limite_superiore);

#endif

