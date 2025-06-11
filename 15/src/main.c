#include <stdio.h>
#include <stdlib.h>

#include "gestire_classifica.h"
#include "gestire_file.h"
#include "gestire_menu.h"
#include "gestire_partite.h"

int main()
{
	 FILE *interfaccia_iniziale=ricercare_il_menu(INTERFACCIA_INIZIALE,LETTURA_TESTO);
	 stampare_file_di_testo(interfaccia_iniziale);
	 system("pause");
    const char PROMPT_ERRORE_FILE[] = "Errore nel file provare a buildare a aprire il progetto in .exe ";
    const int SCELTA_INIZIO = 1;
    const int SCELTA_CARICARE = 2;
    const int SCELTA_AIUTO = 3;
    const int SCELTA_CLASSIFICA = 4;
    const int SCELTA_ESCI = 0;
    const int SCELTA_CHIUDI = 1;

    setbuf(stdout, NULL);
    int flag = 0;
    int scelta;

    do {
        FILE *menu_principale = ricercare_il_menu(PRINCIPALE, LETTURA_TESTO);
        if (menu_principale == NULL) {
            flag = ERRORE_FILE;
        } else {
            scelta = scegliere_opzione_di_menu(menu_principale, SCELTA_ESCI, SCELTA_CLASSIFICA);

            if (scelta == SCELTA_INIZIO) {
                FILE *file_menu = ricercare_il_menu(PARTITA, LETTURA_TESTO);
                if (file_menu == NULL) {
                    flag = ERRORE_FILE;
                } else {
                    flag = gestire_menu_partita(file_menu);
                }

            } else if (scelta == SCELTA_CARICARE) {
                FILE *menu_carica = ricercare_il_menu(CARICA, LETTURA_TESTO);
                if (menu_carica == NULL) {
                    flag = ERRORE_FILE;
                } else {
                    flag = gestire_menu_caricare_partita(menu_carica);
                }

            } else if (scelta == SCELTA_AIUTO) {
                FILE *menu_aiuto =ricercare_il_menu(AIUTO, LETTURA_TESTO);
                if (menu_aiuto == NULL) {
                    flag = ERRORE_FILE;
                } else {
                    flag = gestire_menu_aiuto(menu_aiuto);
                }

            } else if (scelta == SCELTA_CLASSIFICA) {
                FILE *classifica = ricercare_il_menu(CLASSIFICA, LETTURA_TESTO);
                if (classifica == NULL) {
                    flag = ERRORE_FILE;
                } else {
                	do {
                	    system("cls");
                	    stampare_file_di_testo(classifica);
                	    printf("%s",SOTTOMENU);
                	    int flag = leggere_tastiera_int_verificato();

                	    if (flag == SCELTA_ESCI) {
                	        break;
                	    } else if (flag == SCELTA_CHIUDI) {
                	        return 0;
                	    }
                	} while (1);
                }

            } else {
                flag = 1;
            }
        }
    } while ((flag == 0) && (flag != ERRORE_FILE));

    if (flag == ERRORE_FILE) {
        printf("%s", PROMPT_ERRORE_FILE);
        printf("%c",LINEA);
        system("pause");
    }
}
