#include "gestire_classifica.h"
#include "gestire_file.h"
#include <stdlib.h>
#include <string.h>
#include "gestire_partite.h"


#define MAX_CLASSIFICATI 10
#define NO_RICERCA -1
#define FINE_LISTA -1


competizione_oca caricare_partita(int slot);
competizione_oca ricercare_impostazioni_partita(FILE *file_slot);

int gestire_menu_caricare_partita(FILE *file_menu_carica_partita)
{
    const int SCELTA_ESCI = 0;
    int slot;
    int flag = 1;

    do {

        slot = scegliere_opzione_di_menu(file_menu_carica_partita, SCELTA_ESCI, MAX_SLOT);

        if (slot == SCELTA_ESCI) {
            flag = 0;
        } else {
        	competizione_oca  partita_caricata;
            partita_caricata = caricare_partita(slot);
            int verifica_slot = leggere_num_giocatori(partita_caricata);
            if (verifica_slot != ERRORE_SLOT) {
                giocatore vincitore;
                gestire_turno(partita_caricata, &vincitore);
                aggiornare_classifica(vincitore);

                flag = 0;

            } else {
                printf("%c",LINEA);
                printf("%s", PROMPT_ERRORE_SLOT);
                printf("%c",LINEA);
                system("pause");
            }
        }
    } while ((flag == 1) && (flag != ERRORE_FILE));

    return flag;
}


competizione_oca caricare_partita(int slot)
{
	competizione_oca  partita_caricata;
    FILE *file_slot = ricercare_slots(slot, LETTURA_BINARIA);
    if (file_slot == NULL) {
        scrivere_num_giocatori(&partita_caricata, ERRORE_SLOT);
    } else {
        partita_caricata = ricercare_impostazioni_partita(file_slot);
    }

    return partita_caricata;
}


competizione_oca  ricercare_impostazioni_partita(FILE *file_slot)
{
    fseek(file_slot, 0, SEEK_END);
    int n = ftell(file_slot);
    rewind(file_slot);
    competizione_oca partita_caricata;
    if (n > 0) {
        fread(&partita_caricata, sizeof(partita_caricata), 1, file_slot);
    } else {
        scrivere_num_giocatori(&partita_caricata, ERRORE_SLOT);
    }

    fclose(file_slot);
    return partita_caricata;
}

void scrivere_nome_classifica(classifica *classifica, int pos, char c)
{
    classifica->nome_classifica[pos] = c;
}


char leggere_nome_classifica(classifica classifica, int pos)
{
    char c = classifica.nome_classifica[pos];
    return c;
}


void scrivere_lanci_classifica(classifica *classifica, int lanci)
{
    classifica->lanci = lanci;
}


int leggere_lanci_classifica(classifica classifica)
{
    int num_tiri = classifica.lanci;
    return num_tiri;
}


int aggiornare_classifica(giocatore vincitore)
{
    int flag = 1;
    FILE *file_classifica = ricercare_slots(CLASSIFICA_BINARIA, LETTURA_BINARIA);
    if (file_classifica == NULL) {
        file_classifica = ricercare_slots(CLASSIFICA_BINARIA, SCRITTURA_BINARIA);
        fclose(file_classifica);

        file_classifica = ricercare_slots(CLASSIFICA_BINARIA, LETTURA_BINARIA);
        if (file_classifica == NULL) {
            flag = ERRORE_FILE;
        }
    }

    if (flag != ERRORE_FILE) {

        classifica lista_classificati[MAX_CLASSIFICATI + 1]; // il + 1 è necessario per inserire il classificato fine lista
        ricercare_classificati(file_classifica, lista_classificati);
        fclose(file_classifica);

        classifica vincitore_convertito;
        convertire_giocatore(vincitore, &vincitore_convertito);

        classifica elemento_0 = lista_classificati[0];
        int verifica = leggere_lanci_classifica(elemento_0);
        if (verifica == FINE_LISTA) {
            scrivere_classifica_vuota(vincitore_convertito, lista_classificati);

        } else {

            int pos = confrontare_lista(lista_classificati, vincitore_convertito);
            if (pos == NO_RICERCA) {

                inserire_classifica(vincitore_convertito, lista_classificati);

            } else {

                aggiornare_classificato(pos, vincitore_convertito, lista_classificati);
            }
        }

        if (flag != ERRORE_FILE) {
            flag = scrivere_classifica_testo(lista_classificati);
        }
    }

    return flag;
}


void scrivere_classifica_vuota(classifica vincitore, classifica lista_classificati[])
{
    FILE *file_classifica = ricercare_slots(CLASSIFICA_BINARIA, SCRITTURA_BINARIA);

    inserire_elemento(lista_classificati, vincitore, 0);
    scrivere_classifica(file_classifica, lista_classificati);
    fclose(file_classifica);
}


void inserire_classifica(classifica vincitore, classifica lista_classificati[])
{

    int pos = confrontare_numero_tiri(lista_classificati, vincitore);
    if (pos != NO_RICERCA) {

        inserire_elemento(lista_classificati, vincitore, pos);

        FILE *file_classifica = ricercare_slots(CLASSIFICA_BINARIA, SCRITTURA_BINARIA);
        scrivere_classifica(file_classifica, lista_classificati);
        fclose(file_classifica);
    }
}


void aggiornare_classificato(int pos_classificato, classifica vincitore, classifica lista_classificati[])
{

    classifica corrispondente;
    corrispondente = lista_classificati[pos_classificato];
    int num_tiri_classifica = leggere_lanci_classifica(corrispondente);
    int num_tiri_vincitore = leggere_lanci_classifica(vincitore);

    if (num_tiri_classifica > num_tiri_vincitore) {

        pos_classificato = confrontare_numero_tiri(lista_classificati, vincitore);
        if (pos_classificato != NO_RICERCA) {

            inserire_elemento(lista_classificati, vincitore, pos_classificato);
        }

        FILE *file_classifica = ricercare_slots(CLASSIFICA_BINARIA, SCRITTURA_BINARIA);
        scrivere_classifica(file_classifica, lista_classificati);
        fclose(file_classifica);
    }
}


void convertire_giocatore(giocatore giocatore, classifica *classificato)
{

    int i = 0;
    char c;
    while (i < (NOME - 1)){
        c = leggere_nome_giocatore(giocatore, i);
        scrivere_nome_classifica(classificato, i, c);
        i = i + 1;
    }
    scrivere_nome_classifica(classificato, i, FINE_STRINGA);


    int lanci = leggere_lanci(giocatore);
    scrivere_lanci_classifica(classificato, lanci);
}


void ricercare_classificati(FILE *file_classifica, classifica lista_classificati[])
{

    int i = 0;
    int verifica = fread(&lista_classificati[i], sizeof(classifica), 1, file_classifica);
    while (verifica != 0) {
        i = i + 1;
        verifica = fread(&lista_classificati[i], sizeof(classifica), 1, file_classifica);
    }


    scrivere_lanci_classifica(&lista_classificati[i], FINE_LISTA);
}


int confrontare_lista(classifica lista_classifica[], classifica vincitore)
{
    int pos_corrispondenza = NO_RICERCA;


    int i = 0;
    char nome_vincitore[NOME];
    while (i < NOME) {
        nome_vincitore[i] = leggere_nome_classifica(vincitore, i);
        i = i + 1;
    }


    int pos = 0;
    int verifica = 1;
    int lanci_classifica;
    classifica classificato;
    do {
        classificato = lista_classifica[pos];


        i = 0;
        char nome_classificato[NOME];
        while (i < NOME){
            nome_classificato[i] = leggere_nome_classifica(lista_classifica[pos], i);
            i = i + 1;
        }


        verifica = strcmp(nome_vincitore, nome_classificato);
        if (verifica == 0) {
            pos_corrispondenza = pos;
        }


        lanci_classifica = leggere_lanci_classifica(classificato);
        pos = pos + 1;

    } while ((lanci_classifica != FINE_LISTA) && (verifica != 0));

    return pos_corrispondenza;
}


int confrontare_numero_tiri(classifica lista_classifica[], classifica vincitore)
{
    int pos_corrispondenza;
    int lanci_vincitore = leggere_lanci_classifica(vincitore);


    int pos = 0;
    int verifica = 0;
    int lanci_classifica;
    classifica classificato;
    do {

        classificato = lista_classifica[pos];
        lanci_classifica = leggere_lanci_classifica(classificato);


        if ((lanci_classifica > lanci_vincitore) || (lanci_classifica == FINE_LISTA)){
            verifica = 1;
            pos_corrispondenza = pos;
        }

        pos = pos + 1;
    } while ((lanci_classifica != FINE_LISTA) && (verifica != 1) && (pos < (MAX_CLASSIFICATI - 1)));

    if (verifica == 0){
        pos_corrispondenza = NO_RICERCA;
    }

    return pos_corrispondenza;
}


void scrivere_classifica(FILE *file_classifica, classifica lista_classifica[])
{
    int pos = 0;
    int verifica = leggere_lanci_classifica(lista_classifica[pos]);
    while (verifica != FINE_LISTA) {
        fwrite(&lista_classifica[pos], sizeof(classifica), 1, file_classifica);

        pos = pos + 1;
        verifica = leggere_lanci_classifica(lista_classifica[pos]);
    }
    fwrite(&lista_classifica[pos], sizeof(classifica), 1, file_classifica);
}


void inserire_elemento(classifica lista_classifica[], classifica classificato, int pos_inserimento)
{

    int pos_lista = 0;
    int verifica = leggere_lanci_classifica(lista_classifica[pos_lista]);
    while ((verifica != FINE_LISTA) && (pos_lista < MAX_CLASSIFICATI)){
        pos_lista = pos_lista + 1;
        verifica = leggere_lanci_classifica(lista_classifica[pos_lista]);
    }

    if (pos_lista == 0) {
        lista_classifica[pos_lista + 1] = lista_classifica[pos_lista];
    } else {
        if (pos_lista == (MAX_CLASSIFICATI - 1)) {
            pos_lista = pos_lista - 1;
        }


        while (pos_lista > pos_inserimento){
            lista_classifica[pos_lista] = lista_classifica[pos_lista - 1];
            pos_lista = pos_lista - 1;
        }
    }

    lista_classifica[pos_inserimento] = classificato;
}


int scrivere_classifica_testo(classifica lista_classificati[])
{

    const char TITOLO_CLASSIFICA[] = "+----------------------------------+\n|     CLASSIFICA VINCITORI         |\n+----------------------------------+";
    const char LAYOUT[] = "+-------+----------------+--------+";
    const int LARGHEZZA_NOME = 15;

    int flag = 1;
    FILE *file_classifica_testo = ricercare_il_menu(CLASSIFICA, SCRITTURA_TESTO);
    if (file_classifica_testo == NULL) {
        flag = ERRORE_FILE;

    } else {

        fprintf(file_classifica_testo, "%s\n", TITOLO_CLASSIFICA);
        fprintf(file_classifica_testo, "%s\n", LAYOUT);

        classifica classificato;
        int pos = 0;
        int num_tiri;
        do {
            classificato = lista_classificati[pos];


            num_tiri = leggere_lanci_classifica(classificato);
            if (num_tiri != FINE_LISTA) {


                int i = 0;
                char nome_classificato[NOME];
                while (i < NOME){
                    nome_classificato[i] = leggere_nome_classifica(lista_classificati[pos], i);
                    i = i + 1;
                }


                fprintf(file_classifica_testo, "| %3d   | %-*s | %3d   |\n", pos + 1, LARGHEZZA_NOME, nome_classificato, num_tiri);
            }

            pos = pos + 1;
        } while (num_tiri != FINE_LISTA) ;

        fprintf(file_classifica_testo, "%s\n", LAYOUT);
        fclose(file_classifica_testo);
    }

    return flag;
}



int aggiornamento_classifica(giocatore vincitore)
{
    int flag;

    int validita = leggere_lanci(vincitore);
    if ((validita != PARTITA_INTERROTTA) && (validita != ERRORE_FILE)) {
        flag = aggiornare_classifica(vincitore);
    }
    if (validita == ERRORE_FILE) {
        flag = ERRORE_FILE;
    } else if (flag != ERRORE_FILE){
        flag = 0;
    }

    return flag;
}
