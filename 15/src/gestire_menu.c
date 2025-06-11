#include "gestire_menu.h"
#include "gestire_classifica.h"
#include "gestire_partite.h"
#include "gestire_percorso.h"
#include "gestire_file.h"
#include <stdlib.h>
#include <stdbool.h>

const char PROMPT_ERRORE[] = "Nessuna Partita in corso";

const int SCELTA_ESCI = 0;
const int SCELTA_PARTITA_C = 1;
const int SCELTA_PARTITA_P = 2;


const int SCELTA_SALVA=1;
const int SCELTA_S_E=2;
const int SCELTA_ABBANDONA=3;
const int SCELTA_CONTINUA=4;

int gestire_menu_partita(FILE *file_menu)
{
    int flag = 1;
    int scelta;

    do {
        scelta = scegliere_opzione_di_menu(file_menu, SCELTA_ESCI,SCELTA_PARTITA_P);

        if (scelta == SCELTA_PARTITA_C) {
        	competizione_oca partita;
        	configurare_partita(&partita);
            giocatore vincitore;
            gestire_turno(partita, &vincitore);
            aggiornare_classifica(vincitore);

            flag = 0;

        } else if (scelta == SCELTA_PARTITA_P) {
        	competizione_oca  partita;
        	            configurare_partita_p(&partita);
        	            giocatore vincitore;
        	            gestire_turno(partita, &vincitore);
        	            aggiornare_classifica(vincitore);
        } else if (scelta == SCELTA_ESCI) {
            flag = 0;
        }
    } while ((flag == 1) && (flag != ERRORE_FILE));

    return flag;
}

int gestire_partita_in_corso(competizione_oca partita)
{


    int fine = 0;
    FILE *file_partita_in_corso = ricercare_il_menu(PARTITA_IN_CORSO, LETTURA_TESTO);
    if (file_partita_in_corso == NULL) {
        fine = ERRORE_FILE;

    } else {
        int flag = 1;
        int scelta_menu_g;


        tabellone tabellone_percorso;
        leggere_tabellone_percorso(partita, &tabellone_percorso);


        giocatore giocatore_turno;
        int turno = leggere_turno(partita);
        leggere_giocatori(partita, turno, &giocatore_turno);
        int pos_turno = leggere_posizione(giocatore_turno);

        do {
            do {
                setbuf(stdin, NULL);

                visualizzare_partita(partita, pos_turno);
                stampare_file_di_testo(file_partita_in_corso);
                scanf("%d",&scelta_menu_g);
                if (scelta_menu_g == SCELTA_SALVA) {
                                    	system("cls");
                                    	FILE *file_menu_carica = ricercare_il_menu(CARICA, LETTURA_TESTO);
                                    	stampare_file_di_testo(file_menu_carica);
                                        fine = salvare_partita(partita);
                }
            } while ((scelta_menu_g != SCELTA_CONTINUA) && (scelta_menu_g!=SCELTA_SALVA) && (scelta_menu_g!=SCELTA_S_E)&& (scelta_menu_g!=SCELTA_ABBANDONA));
                do {
                     if (scelta_menu_g == SCELTA_ABBANDONA) {
                        fine = 1;
                        flag = 0;
                    }else if (scelta_menu_g == SCELTA_S_E) {
                    	system("cls");
                    	    FILE *file_menu_carica = ricercare_il_menu(CARICA, LETTURA_TESTO);
                        	stampare_file_di_testo(file_menu_carica);
                            fine = salvare_partita(partita);
                            fine = 1;
                            flag = 0;
                        }
                    else{

                        flag = 0;
                    }
                } while ((flag == 1) && (fine != ERRORE_FILE));

        } while (((scelta_menu_g == SCELTA_SALVA) || (scelta_menu_g == SCELTA_S_E) || (scelta_menu_g == SCELTA_ABBANDONA)) && (fine != 1) && (fine != ERRORE_FILE));
    }
    return fine;
}
int salvare_partita(competizione_oca partita_salvata)
{
    const char PROMPT_SLOT[] = "";

    int slot;
    int fine = 0;

    do {
        printf("%s", PROMPT_SLOT);
        slot = leggere_tastiera_int_verificato();
    } while ((slot > MAX_SLOT) || (slot <= 0));

    FILE *file_salvataggio = ricercare_slots(slot, SCRITTURA_BINARIA);
    if (file_salvataggio == NULL) {
        fine = ERRORE_FILE;
    } else {
        fwrite(&partita_salvata, sizeof(partita_salvata), 1, file_salvataggio);
        fclose(file_salvataggio);
    }

    return fine;
}

int gestire_sottomenu_aiuto(FILE *sottomenu);

int gestire_menu_aiuto(FILE *menu_aiuto)
{
#define SCELTA_ESCI 0
    const int SCELTA_REGOLE = 1;
    const int SCELTA_MANUALE = 2;

    int flag = 1;
    int scelta;
    do {
        scelta = scegliere_opzione_di_menu(menu_aiuto, SCELTA_ESCI, SCELTA_MANUALE);


        if (scelta == SCELTA_REGOLE) {
            FILE *file_regole = ricercare_il_menu(REGOLE, LETTURA_TESTO);
            if (file_regole == NULL) {
                flag = ERRORE_FILE;
            } else {
                flag = gestire_sottomenu_aiuto(file_regole);
                flag = 1;
            }

        } else if (scelta == SCELTA_MANUALE) {
            FILE *file_manuale = ricercare_il_menu(MANUALE, LETTURA_TESTO);
            if (file_manuale == NULL) {
                flag = ERRORE_FILE;
            } else {
                flag = gestire_sottomenu_aiuto(file_manuale);
                flag = 1;
            }

        } else {
            flag = 0;
        }
    } while ((flag == 1) && (flag != ERRORE_FILE));

    return flag;
}


int gestire_sottomenu_aiuto(FILE *sottomenu)
{
    int flag = 1;

    do {
        system("cls");
        stampare_file_di_testo(sottomenu);
        printf("%s",SOTTOMENU);
        flag = leggere_tastiera_int_verificato();
    } while (flag != SCELTA_ESCI);

    return flag;
}

