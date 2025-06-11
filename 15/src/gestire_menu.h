#ifndef GESTIRE_MENU_H_
#define GESTIRE_MENU_H_

#include <stdio.h>
#include "gestire_partite.h"
#include "gestire_percorso.h"

int gestire_menu_partita(FILE *file_menu);
int gestire_partita_in_corso(competizione_oca partita);
int gestire_menu_aiuto(FILE *file_menu_aiuto);
int salvare_partita(competizione_oca partita_salvata);
#endif
