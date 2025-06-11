#include "gestire_partite.h"
#include "gestire_file.h"
#include "gestire_menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

const int INIZIO = -1;
const int FINE = 1;
const int LANCIO_MINIMO = 1;
const int LANCIO_MASSIMO = 6;
const int LANCIO_OCA = 9;

void scrivere_nome_giocatore(giocatore *giocatore, int pos, char c)
{
    giocatore->nome_giocatore[pos] = c;
}

char leggere_nome_giocatore(giocatore giocatore, int pos)
{
    char c = giocatore.nome_giocatore[pos];
    return c;
}

void scrivere_posizione(giocatore *giocatore, int posizione_casella)
{
    giocatore->posizione = posizione_casella;
}


int leggere_posizione(giocatore giocatore)
{
    int posizione_casella = giocatore.posizione;
    return posizione_casella;
}


void scrivere_lanci(giocatore *giocatore, int lanci_totali)
{
    giocatore->lanci = lanci_totali;
}


int leggere_lanci(giocatore giocatore)
{
    int lanci_totali = giocatore.lanci;
    return lanci_totali;
}


void scrivere_blocco(giocatore *giocatore, int valore_blocco)
{
    giocatore->blocco = valore_blocco;
}


int leggere_blocco(giocatore giocatore)
{
    int valore_blocco = giocatore.blocco;
    return valore_blocco;
}


void scrivere_tabellone_percorso(competizione_oca *partita, tabellone serpentina)
{
    partita->tabellone_percorso = serpentina;
}


void leggere_tabellone_percorso(competizione_oca partita, tabellone *serpentina)
{
    *serpentina = partita.tabellone_percorso;
}


void scrivere_num_giocatori(competizione_oca *partita, int num_giocatori)
{
    partita->num_giocatori = num_giocatori;
}


int leggere_num_giocatori(competizione_oca partita)
{
    int num_giocatori = partita.num_giocatori;
    return num_giocatori;
}


void scrivere_giocatori(competizione_oca *partita, int pos, giocatore giocatore)
{
    partita->giocatori[pos] = giocatore;
}


void leggere_giocatori(competizione_oca partita, int pos, giocatore *giocatore)
{
    *giocatore = partita.giocatori[pos];
}


void scrivere_turno(competizione_oca *partita, int turno)
{
    partita->turno = turno;
}


int leggere_turno(competizione_oca partita)
{
    int turno = partita.turno;
    return turno;
}

void gestire_turno(competizione_oca partita_in_corso, giocatore *vincitore)
{
    int num_giocatori = leggere_num_giocatori(partita_in_corso);
    fissare_turno(&partita_in_corso);

    int turno = leggere_turno(partita_in_corso);

    int fine = 0;
    giocatore giocatore_attuale;
    while (fine != 1) {
        while ((turno < num_giocatori) && (fine != 1)) {

            leggere_giocatori(partita_in_corso, turno, &giocatore_attuale);
            int blocco_turno = leggere_blocco(giocatore_attuale);

            if (blocco_turno >= 0) {
                fine = gestire_partita_in_corso(partita_in_corso);

                if ((fine != 1) && (fine != ERRORE_FILE)) {
                    gestire_turno_generale(&partita_in_corso, giocatore_attuale, turno);

                    num_giocatori = leggere_num_giocatori(partita_in_corso);
                    if (num_giocatori == FINE) {
                        fine = 1;

                        leggere_giocatori(partita_in_corso, turno, &giocatore_attuale);
                        *vincitore = giocatore_attuale;
                    }
                } else if (fine == 1) {
                    scrivere_lanci(vincitore, PARTITA_INTERROTTA);
                } else {
                    scrivere_lanci(vincitore, ERRORE_FILE);
                    fine = 1;
                }

            } else {
                gestire_turno_blocco(&partita_in_corso, giocatore_attuale, turno);
            }

            aggiornare_turno(&partita_in_corso);
            turno = leggere_turno(partita_in_corso);
        }
        turno = 0;
    }
    stampare_vincitore(*vincitore);
}


void fissare_turno(competizione_oca *partita_in_corso)
{
    int num_giocatori = leggere_num_giocatori(*partita_in_corso);

    int turno = leggere_turno(*partita_in_corso);
    if (turno == INIZIO) {
        turno = generare_numero(num_giocatori + 1) - 1;
        scrivere_turno(partita_in_corso, turno);
    }
}


void stampare_vincitore(giocatore vincitore)
{
    const char AVVISO_VITTORIA[] = "Hai vinto giocatore ";

    int validita_vittoria = leggere_lanci(vincitore);
    if ((validita_vittoria != PARTITA_INTERROTTA) && (validita_vittoria != ERRORE_FILE)) {
        char nome_vincitore[NOME];
        int i = 0;
        while (i < NOME) {
            nome_vincitore[i] = leggere_nome_giocatore(vincitore, i);
            i = i + 1;
        }
        printf("%c", LINEA);
        printf("%s%s", AVVISO_VITTORIA, nome_vincitore);
        printf("%c", LINEA);
        system("pause");
    }
}


void gestire_turno_blocco(competizione_oca *partita_in_corso, giocatore giocatore_attuale, int turno)
{
    int posizione_attuale = leggere_posizione(giocatore_attuale);
    int blocco_turno = leggere_blocco(giocatore_attuale);

    tabellone tabellone_percorso;
    leggere_tabellone_percorso(*partita_in_corso, &tabellone_percorso);
    int casella = leggere_percorso(tabellone_percorso, posizione_attuale);

    if (casella == POSIZIONE_PRIGIONE) {
        visualizzare_partita(*partita_in_corso, posizione_attuale);
        liberare_prigione_lancio(&giocatore_attuale);
    } else {
        blocco_turno = blocco_turno + 1;
        scrivere_blocco(&giocatore_attuale, blocco_turno);
    }
    scrivere_giocatori(partita_in_corso, turno, giocatore_attuale);

}


int aggiornare_turno(competizione_oca *partita_in_corso)
{
    int turno = leggere_turno(*partita_in_corso);
    int num_giocatori = leggere_num_giocatori(*partita_in_corso);

    turno = turno + 1;
    if (turno < num_giocatori) {
        scrivere_turno(partita_in_corso, turno);
    } else {
        scrivere_turno(partita_in_corso, 0);
    }
    return turno;
}


void gestire_turno_generale(competizione_oca *partita_in_corso, giocatore giocatore_attuale, int turno)
{
    const char LANCIO[] = "Il numero di casella di cui spostarsi e': ";

    int fine = 0;


    tabellone tabellone_percorso;
    leggere_tabellone_percorso(*partita_in_corso, &tabellone_percorso);
    int dimensione = leggere_dimensione(tabellone_percorso);


    int primo_lancio = generare_numero(LANCIO_MASSIMO + 1);
    int secondo_lancio = generare_numero(LANCIO_MASSIMO + 1);
    int lancio = primo_lancio + secondo_lancio;
    printf("%c%s%d%c", LINEA,LANCIO, lancio, LINEA);
    system("pause");

    int posizione_attuale = leggere_posizione(giocatore_attuale);
    posizione_attuale = posizione_attuale + lancio;
    scrivere_posizione(&giocatore_attuale, posizione_attuale);

    int lanci = leggere_lanci(giocatore_attuale);
    lanci = lanci + 1;
    scrivere_lanci(&giocatore_attuale, lanci);

    int indietro = 0;
    int casella = leggere_percorso(tabellone_percorso, posizione_attuale);
    int blocco_turno;
    do {
        if (posizione_attuale > dimensione) {
        	gestire_tabellone_lancio_vittoria(dimensione, &posizione_attuale, lancio);
            scrivere_posizione(&giocatore_attuale, posizione_attuale);

            indietro = (posizione_attuale - dimensione) + 1;
            casella = leggere_percorso(tabellone_percorso, posizione_attuale);

        } else if (posizione_attuale == dimensione - 1) {
            fine = 1;
            scrivere_num_giocatori(partita_in_corso, FINE);

        } else if (casella != CASELLA_VUOTA) {
            scrivere_giocatori(partita_in_corso, turno,giocatore_attuale);
            if (indietro < 0) {

                visualizzare_partita(*partita_in_corso, posizione_attuale);

                int pos_supporto = posizione_attuale;
                primo_lancio = 0;
                secondo_lancio = indietro;
                gestire_caselle_speciali(partita_in_corso,primo_lancio,secondo_lancio, casella);

                leggere_giocatori(*partita_in_corso, turno, &giocatore_attuale);
                posizione_attuale = leggere_posizione(giocatore_attuale);
                indietro = posizione_attuale - pos_supporto;

            } else {

                visualizzare_partita(*partita_in_corso, posizione_attuale);

                casella = leggere_percorso(tabellone_percorso, posizione_attuale);
                gestire_caselle_speciali(partita_in_corso,primo_lancio,secondo_lancio, casella);

                leggere_giocatori(*partita_in_corso, turno, &giocatore_attuale);
                posizione_attuale = leggere_posizione(giocatore_attuale);
            }


            casella = leggere_percorso(tabellone_percorso, posizione_attuale);
            blocco_turno = leggere_blocco(giocatore_attuale);
        }
    } while ((casella != CASELLA_VUOTA) && (blocco_turno >= 0) && (fine != 1) && (posizione_attuale != -1));

    scrivere_giocatori(partita_in_corso, turno,giocatore_attuale);
}


void gestire_caselle_speciali(competizione_oca *partita_in_corso, int primo_lancio, int secondo_lancio, int casella_speciale)
{
    int lancio = primo_lancio + secondo_lancio;

    if (casella_speciale == POSIZIONE_OCA) {
        gestire_casella_oca(partita_in_corso, primo_lancio, secondo_lancio);
    } else if (casella_speciale == POSIZIONE_PONTE) {
        gestire_casella_ponte(partita_in_corso, lancio);
    } else if (casella_speciale == POSIZIONE_LOCANDA) {
        gestire_casella_locanda(partita_in_corso);
    } else if ((casella_speciale == POSIZIONE_POZZO) || (casella_speciale == POSIZIONE_PRIGIONE)) {
        gestire_casella_blocco(partita_in_corso);
    } else if (casella_speciale == POSIZIONE_LABIRINTO) {
        gestire_casella_labirinto(partita_in_corso);
    } else if (casella_speciale == POSIZIONE_SCHELETRO) {
        gestire_casella_scheletro(partita_in_corso);
    }
}


void gestire_casella_oca(competizione_oca *partita_in_corso, int primo_lancio, int secondo_lancio)
{
    const char AVVISO_OCA_1[] = "Sei finito su un oca";
    const char AVVISO_OCA_2[] = "Avanza ancora";
    const int POS_SPECIALE_1 = 25;
    const int POS_SPECIALE_2 = 52;
    const int LANCIO_SPECIALE_1 = 3;
    const int LANCIO_SPECIALE_2 = 6;


    printf("%c", LINEA);
    printf("%s", AVVISO_OCA_1);
    printf("%c",LINEA);
    printf("%s", AVVISO_OCA_2);
    printf("%c", LINEA);
    system("pause");

    int turno = leggere_turno(*partita_in_corso);
    giocatore giocatore_attuale;
    leggere_giocatori(*partita_in_corso, turno, &giocatore_attuale);
    int lanci = leggere_lanci(giocatore_attuale);
    int posizione_attuale = leggere_posizione(giocatore_attuale);

    if (lanci == 1) {
        if (((primo_lancio == LANCIO_SPECIALE_1) && (secondo_lancio == LANCIO_SPECIALE_2)) || ((secondo_lancio == LANCIO_SPECIALE_1) && (primo_lancio == LANCIO_SPECIALE_2))) {
            posizione_attuale = POS_SPECIALE_1;
        } else {
            posizione_attuale = POS_SPECIALE_2;
        }
    } else {
        posizione_attuale = posizione_attuale + (primo_lancio + secondo_lancio);
    }

    scrivere_posizione(&giocatore_attuale, posizione_attuale);
    scrivere_giocatori(partita_in_corso, turno, giocatore_attuale);
}


void gestire_casella_ponte(competizione_oca *partita_in_corso, int lancio)
{
    const char AVVISO_POSTA[] = "Sei finito sulla casella ponte";
    printf("%s", AVVISO_POSTA);
    system("pause");


    int turno = leggere_turno(*partita_in_corso);
    giocatore giocatore_attuale;
    leggere_giocatori(*partita_in_corso, turno, &giocatore_attuale);
    int posizione_attuale = leggere_posizione(giocatore_attuale);


    posizione_attuale = posizione_attuale + lancio;

    scrivere_posizione(&giocatore_attuale, posizione_attuale);
    scrivere_giocatori(partita_in_corso, turno, giocatore_attuale);
}


void gestire_casella_locanda(competizione_oca *partita_in_corso)
{
    const char AVVISO_LOCANDA [] = "Sei arrivato sulla locanda sei bloccato!";
    const int FUNZIONE_LOCANDA = -3;

    printf("%c", LINEA);
    printf("%s", AVVISO_LOCANDA);
    printf("%c", LINEA);
    system("pause");


    int turno = leggere_turno(*partita_in_corso);
    giocatore giocatore_attuale;
    leggere_giocatori(*partita_in_corso, turno, &giocatore_attuale);


    scrivere_blocco(&giocatore_attuale, FUNZIONE_LOCANDA);
    scrivere_giocatori(partita_in_corso, turno, giocatore_attuale);
}


void liberare_giocatore(competizione_oca *partita_in_corso)
{
    const char LIBERA[] = "Sei bloccato! mai hai liberato l'altro giocatore";

    giocatore giocatore_controllo;
    giocatore giocatore_attuale;

    int turno = leggere_turno(*partita_in_corso);
    leggere_giocatori(*partita_in_corso, turno, &giocatore_attuale);
    int posizione_attuale = leggere_posizione(giocatore_attuale);

    int num_giocatori = leggere_num_giocatori(*partita_in_corso);
    int i = 0;
    int fine_ciclo = 0;
    while ((i <= num_giocatori) && (fine_ciclo == 0)) {

        if (i != turno) {

            leggere_giocatori(*partita_in_corso, i, &giocatore_controllo);
            int blocco_verifica = leggere_blocco(giocatore_controllo);

            if (blocco_verifica < 0) {
                int posizione_verifica = leggere_posizione(giocatore_controllo);


                if (posizione_verifica == posizione_attuale) {
                    scrivere_blocco(&giocatore_controllo, 0);
                    fine_ciclo = 1;

                    scrivere_giocatori(partita_in_corso, i, giocatore_controllo);

                    printf("%c", LINEA);
                    printf("%s", LIBERA);
                    printf("%c", LINEA);
                    system("pause");
                }
            }
        }
        i = i + 1;
    }
}


void gestire_casella_blocco(competizione_oca *partita_in_corso)
{
    const char AVVISO_BLOCCO[] = "Sei bloccato ";
    const int TURNI_BLOCCO = INT_MIN;

    printf("%c", LINEA);
    printf("%s", AVVISO_BLOCCO);
    printf("%c", LINEA);
    system("pause");


    int turno = leggere_turno(*partita_in_corso);
    giocatore giocatore_turno;
    leggere_giocatori(*partita_in_corso, turno, &giocatore_turno);


    scrivere_blocco(&giocatore_turno, TURNI_BLOCCO);
    scrivere_giocatori(partita_in_corso, turno, giocatore_turno);

    liberare_giocatore(partita_in_corso);
}


void gestire_casella_labirinto(competizione_oca *partita_in_corso)
{
    const char AVVISO_LABIRINTO[] = "oh no! sei sul labririnto torna alla: ";
    const int FUNZIONE_LABIRINTO = 33;

    printf("%c", LINEA);
    printf("%s", AVVISO_LABIRINTO);
    printf("%d", FUNZIONE_LABIRINTO);
    printf("%c", LINEA);
    system("pause");


    tabellone tabellone;
    leggere_tabellone_percorso(*partita_in_corso, &tabellone);
    int dimensione = leggere_dimensione(tabellone);
    int ritorno = calcolare_proporzione(FUNZIONE_LABIRINTO, dimensione, MAX_PERCORSO);


    int turno = leggere_turno(*partita_in_corso);
    giocatore giocatore_attuale;
    leggere_giocatori(*partita_in_corso, turno, &giocatore_attuale);
    int posizione_attuale = leggere_posizione(giocatore_attuale);

    posizione_attuale = ritorno;


    scrivere_posizione(&giocatore_attuale, posizione_attuale);
    scrivere_giocatori(partita_in_corso, turno, giocatore_attuale);
}


void gestire_casella_scheletro(competizione_oca *partita_in_corso)
{
    const char AVVISO_SCHELETRO[] = "oh no! sei sullo scheletro torna alla: ";
    const int FUNZIONE_SCHELETRO = 0;

    printf("%c", LINEA);
    printf("%s", AVVISO_SCHELETRO);
    printf("%d", FUNZIONE_SCHELETRO);
    printf("%c", LINEA);
    system("pause");


    int turno = leggere_turno(*partita_in_corso);
    giocatore giocatore_attuale;
    leggere_giocatori(*partita_in_corso, turno, &giocatore_attuale);
    int posizione_attuale = leggere_posizione(giocatore_attuale);

    posizione_attuale = FUNZIONE_SCHELETRO - 1;


    scrivere_posizione(&giocatore_attuale, posizione_attuale);
    scrivere_giocatori(partita_in_corso, turno, giocatore_attuale);
}


void gestire_tabellone_lancio_vittoria(int num_caselle, int *posizione_attuale, int lancio)
{
    int differenza = *posizione_attuale - num_caselle;
    *posizione_attuale = ((num_caselle - 1) - differenza) - 1;
}


void liberare_prigione_lancio(giocatore *giocatore_prigione)
{

    const char AVVISO_LIBERO [] = "Bravo! sei libero lancio fortunato di: ";
    const char AVVISO_BLOCCO [] = "Peccato! lancio sfortunato ritenta!";
    const int LIBERA_1 = 5;
    const int LIBERA_2 = 7;

    int lancio = generare_numero(LANCIO_MASSIMO + 1);
    if ((lancio == LIBERA_1) || (lancio == LIBERA_2)) {
        scrivere_blocco(giocatore_prigione, 0);
        printf("%c", LINEA);
        printf("%s", AVVISO_LIBERO);
        printf("%d", lancio);
        printf("%c", LINEA);
        system("pause");
    } else {
        printf("%s",AVVISO_BLOCCO);
        printf("%c", LINEA);
        system("pause");
    }
}

void configurare_partita_classica(competizione_oca *partita)
{
      configurare_partita(partita);
}
void configurare_partita_personalizzata(competizione_oca *partita)
{
    configurare_partita_p(partita);
    }
void configurare_partita(competizione_oca *partita)
{

    const int PERCORSO_STANDARD = 90;
    const int GIOCATORI_STANDARD = 4;
    tabellone tabellone;
    scrivere_dimensione(&tabellone, PERCORSO_STANDARD);
    generare_percorso(&tabellone);
    scrivere_tabellone_percorso(partita, tabellone);
    scrivere_num_giocatori(partita, GIOCATORI_STANDARD);
    configurare_giocatori(partita, GIOCATORI_STANDARD);
    loading_bar();
    scrivere_turno(partita, INIZIO);
}

void configurare_partita_p(competizione_oca *partita)
{
	system("cls");
	const char AVVISO_IMPOSTAZIONI_2[] = "---PARTITA PERSONALIZZATA---\n";
	printf("%s", AVVISO_IMPOSTAZIONI_2);
    const char AVVISO_CASELLE[] = "Inserire la dimensione delle caselle minimo 50 massimo 90: ";
    const char AVVISO_GIOCATORI[] = "Inserire il numero di giocatori minimo 2 massimo 4: ";

    tabellone tabellone;
    int dimensione;
    do {
        printf("%s", AVVISO_CASELLE);
        dimensione = leggere_tastiera_int_verificato();
    } while ((dimensione < MIN_PERCORSO) || (dimensione > MAX_PERCORSO));

    int num_giocatori;
    do {
        system("cls");
        printf("%s", AVVISO_GIOCATORI);
        num_giocatori = leggere_tastiera_int_verificato();
    } while ((num_giocatori < MIN_GIOCATORI) || (num_giocatori > MAX_GIOCATORI));

    scrivere_dimensione(&tabellone, dimensione);
    generare_percorso(&tabellone);
    scrivere_tabellone_percorso(partita, tabellone);
    scrivere_num_giocatori(partita, num_giocatori);
    configurare_giocatori(partita, num_giocatori);
    loading_bar();
    scrivere_turno(partita,INIZIO);
}

int verifica_numero(char c)
{
    return (c >= '0' && c <= '9');
}

int verifica_carattere_speciale(char c)
{
    return !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

void configurare_giocatori(competizione_oca *partita_in_corso, int num_giocatori)
{

    const char A_CAPO = '\n';

    giocatore giocatore;
    int i = 0;
    while (i < num_giocatori) {


        scrivere_posizione(&giocatore, -1);
        scrivere_lanci(&giocatore, 0);
        scrivere_blocco(&giocatore, 0);


        int j;
        int fine_input;

        do {
            char c = FINE_STRINGA;
            fine_input = 0;
            j = 0;
            while ((j < (NOME-1 )) && (fine_input != 1)) {
                system("cls");
                printf("NOME DA INSERIRE DI 5 CARATTERI\n");
                printf("Inserire il nome del giocatore(%d): ",i+1);
                scanf("%c", &c);
                if (c == A_CAPO) {
                    fine_input = 1;
                } else {
                    scrivere_nome_giocatore(&giocatore, j, c);
                }

                j = j + 1;
            }
            scrivere_nome_giocatore(&giocatore, j, FINE_STRINGA);
        } while ((j != NOME-1) || (fine_input == 1));

        scrivere_giocatori(partita_in_corso, i, giocatore);
        i = i + 1;
    }
}







int generare_numero(int numero)
{
    time_t t;
    srand((unsigned)time(&t));

    int num_casuale;
    do {
        num_casuale = (rand() % numero);
    } while (num_casuale == 0);

    return num_casuale;
}


void visualizzare_partita(competizione_oca partita_in_corso, int posizione_attuale)
{

    const char STAMPA_TAB[]="Tabellone";
    tabellone tabellone_percorso;
    leggere_tabellone_percorso(partita_in_corso, &tabellone_percorso);
    int turno = leggere_turno(partita_in_corso);

    system("cls");
    printf("%s\n",STAMPA_TAB);
    stampare_percorso(tabellone_percorso,posizione_attuale);



    stampare_posizioni(partita_in_corso, turno);
}


void stampare_posizioni(competizione_oca partita_in_corso, int turno)
{
    const char AVVISO_POSIZIONE_1[] = "La posizione del giocatore ";
    const char AVVISO_POSIZIONE_2[] = " e' ";

    tabellone tabellone_percorso;
    leggere_tabellone_percorso(partita_in_corso, &tabellone_percorso);
    int num_giocatori = leggere_num_giocatori(partita_in_corso);
   int contatore_turno=aggiornare_turno(&partita_in_corso);
   printf(" ====TURNO DEL GIOCATORE %d====\n",contatore_turno);

    int i = 0;
    while (i < num_giocatori) {

        giocatore giocatore_indice;
        leggere_giocatori(partita_in_corso, i, &giocatore_indice);
        int pos = leggere_posizione(giocatore_indice);


        char nome_giocatore[NOME];
        int j = 0;
        while (j < NOME) {
            nome_giocatore[j] = leggere_nome_giocatore(giocatore_indice, j);
            j = j + 1;
        }

        if (i  == turno) {
            printf("%s%s%s", COLORE_ARANCIONE, AVVISO_POSIZIONE_1, RESET_COLORE);
            printf("%s%s%s", COLORE_ARANCIONE, nome_giocatore, RESET_COLORE);
            printf("%s%s%s", COLORE_ARANCIONE, AVVISO_POSIZIONE_2, RESET_COLORE);
            printf("%s%d%s", COLORE_ARANCIONE, pos + 1, RESET_COLORE);
            printf("%c", LINEA);
        } else {
            printf("%s", AVVISO_POSIZIONE_1);
            printf("%s", nome_giocatore);
            printf("%s", AVVISO_POSIZIONE_2);
            printf("%d", pos + 1);
            printf("%c", LINEA);
        }
        i = i + 1;

    }
    printf("%c", LINEA);
}

void loading_bar() {
  int totale = 100;
  int progresso = 0;
  int barra_lunghezza = 50;
  usleep(1000);
  int i = 0;
  while ( i <= totale) {
    float percentuale = (float)progresso / totale;
    int larghezza_riempita = barra_lunghezza * percentuale;

    printf("\033[0;32m[");
    int j = 0;
    while (j < larghezza_riempita) {
      printf("=");
      j = j + 1;
    }
    int k = larghezza_riempita;
    while (k < barra_lunghezza - 1) {
      printf(" ");
      k = k + 1;
    }

    printf("] %.1f%%\033[0m", percentuale * 100);

    printf("\r");
    fflush(stdout);

    progresso = progresso + 1;
    usleep(1000);
    i = i + 1;
  }

  printf("\n\033[0;32mLoading completo!\033[0m\n");
}






