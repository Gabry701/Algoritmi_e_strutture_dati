#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define DEFAULT_FILENAME "corse.txt"

typedef enum {r_cambiaFile, r_stampaVideo, r_stampaFile, r_ordinaData, r_ordinaCodice, r_ordinaStazionePartenza, 
                r_ordinaStazioneArrivo, r_ricercaCodice, r_ricercaStazionePartenza} Comando;

typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    int ora;
    int minuti;
    int secondi;
} Orario;

//ordinato con le stringhe dopo per avere solo 2 byte di padding al posto di 6
typedef struct {
    Data data;
    Orario oraPartenza;
    Orario oraArrivo;
    int ritardo;
    char codice[30];
    char partenza[30];
    char destinazione[30];
} Corsa;

typedef struct {
    Corsa **data;
    Corsa **partenza;
    Corsa **arrivo;
    Corsa **codice; 
} Ordinato;


int leggiFileCorse(Corsa **v, Corsa ***refV, char *filename, int toFree) {
    FILE *fp;
    int numCorse;

    if (toFree) {
        free(*v);
        free(*refV);
    }
    fp = fopen(filename, "r");
    fscanf(fp, "%d", &numCorse);
    *v = malloc(numCorse*sizeof(Corsa));
    *refV = malloc(numCorse*sizeof(Corsa*));
    for (int i = 0; i < numCorse; i++) {
        fscanf(fp, "%s %s %s", (*v)[i].codice, (*v)[i].partenza, (*v)[i].destinazione);
        fscanf(fp, "%d/%d/%d", &((*v)[i]).data.anno, &((*v)[i]).data.mese, &((*v)[i]).data.giorno);
        fscanf(fp, "%d:%d:%d", &((*v)[i]).oraPartenza.ora, &((*v)[i]).oraPartenza.minuti, &((*v)[i]).oraPartenza.secondi);
        fscanf(fp, "%d:%d:%d", &((*v)[i]).oraArrivo.ora, &((*v)[i]).oraArrivo.minuti, &((*v)[i]).oraArrivo.secondi);
        fscanf(fp, "%d", &((*v)[i]).ritardo);
    }
    for (int i = 0; i < numCorse; i++)
        (*refV)[i] = &((*v)[i]);
    
    fclose(fp);
    return numCorse;
}



int main() {
    Corsa *corse;
    Corsa **refCorse;
    int numeroCorse;
    Comando richiestaUtente = 0;
    Ordinato orderedArrays;
    
    numeroCorse = leggiFileCorse(&corse, &refCorse, DEFAULT_FILENAME, 0);
    printf("%d", numeroCorse);
    
    do {
        richiestaUtente = registraComando();
        eseguiComando(richiestaUtente, corse, refCorse, numeroCorse, &orderedArrays);
    } while (richiestaUtente >= 0);
    
}