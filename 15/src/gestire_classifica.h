#ifndef GESTIRE_CLASSIFICA_H_
#define GESTIRE_CLASSIFICA_H_

// inclusione dei moduli necessari nella dichiarazione dei prototipi
#include <stdio.h>
#include "gestire_partite.h"

// dichiarazione delle costanti PUBBLICHE del modulo:
#define ERRORE_SLOT -1 // valore assunto dal campo num_giocatori della partita qualora la partita che si tenta di caricare sia vuota
#define PROMPT_ERRORE_SLOT "Slot non corretto" // prompt di errore

typedef struct
{
    char nome_classifica[NOME];
    int lanci;
}classifica;

int gestire_menu_caricare_partita(FILE *file_menu_carica_partita);

int aggiornamento_classifica(giocatore vincitore);

void scrivere_nome_classifica(classifica *classifica, int pos, char c);

char leggere_nome_classifica(classifica classifica, int pos);

void scrivere_lanci_classifica(classifica *classifica, int num_tiri);

int leggere_lanci_classifica(classifica classifica);

int aggiornare_classifica(giocatore vincitore);

void scrivere_classifica_vuota(classifica vincitore, classifica lista_classificati[]);

void inserire_classifica(classifica vincitore, classifica lista_classificati[]);

void aggiornare_classificato(int pos_classificato, classifica vincitore, classifica lista_classificati[]);

void convertire_giocatore(giocatore giocatore, classifica *classificato);

void ricercare_classificati(FILE *file_classifica, classifica lista_classifica[]);

int confrontare_lista(classifica lista_classifica[], classifica vincitore);

int confrontare_numero_tiri(classifica lista_classifica[], classifica vincitore);

void scrivere_classifica(FILE *file_classifica, classifica lista_classifica[]);

void inserire_elemento(classifica lista_classifica[], classifica classificato, int pos_inserimento);

int scrivere_classifica_testo(classifica lista_classificati[]);
#endif // GESTIRE_CLASSIFICA_H_
