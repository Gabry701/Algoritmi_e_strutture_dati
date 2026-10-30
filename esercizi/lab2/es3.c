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


//AGGIUNGERE PARAMETRO DI ORDINATO NELLE FUNZIONI DI ORDINAMENTO E ALLOCARE MEMORIA
Comando registraComando();
int leggiFileCorse(Corsa **v, Corsa ***refV, char *filename);
int bubbleSortCorse(Corsa *v[], int n, char cond);
int confrontaDate(Corsa a, Corsa b);
int ricercaDicotomicaCodice(Corsa *v[], int l, int r, char *x);
void stampaCorsa(Corsa c, FILE *fp);
void eseguiComando(Comando richiesta, Corsa **corse, Corsa ***pCorse, int *pnCorse, Ordinato *ordType);
void stampaVettoreCorse(Corsa *c[], int n);
void ordinaVettore(Corsa ***v, Corsa *refCorse[], int n, char cond);
void ricercaPartenza(Corsa *pCorse[], int nCorse, char *x);
void freeArrays(Corsa **v, Corsa ***refV, Ordinato *ord);



int main() {
    Corsa *corse;
    Corsa **refCorse;
    int numeroCorse;
    Comando richiestaUtente = 0;
    Ordinato orderedArrays = {NULL, NULL, NULL, NULL};
    numeroCorse = leggiFileCorse(&corse, &refCorse, DEFAULT_FILENAME);
    printf("%d", numeroCorse);
    
    do {
        richiestaUtente = registraComando();
        eseguiComando(richiestaUtente, &corse, &refCorse, &numeroCorse, &orderedArrays);
    } while (richiestaUtente >= 0 && richiestaUtente <= 8);
}



int leggiFileCorse(Corsa **v, Corsa ***refV, char *filename) {
    FILE *fp;
    int numCorse;
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

void stampaCorsa(Corsa c, FILE *fp) {
    //cercando il modo di unire le due funzioni di stampa, sia a file che a video senza aprire e chiudere
    //ripetutamente il file in un ciclo ho scoperto dell'esistenza della costante stdout
    //e che printf("...", ...) <=> fprintf(stdout, "...", ...)
    fprintf(fp, "%s %s %s %d/%02d/%02d %02d:%02d:%02d %02d:%02d:%02d %d\n",
        c.codice, c.partenza, c.destinazione,
        c.data.anno, c.data.mese, c.data.giorno,
        c.oraPartenza.ora, c.oraPartenza.minuti, c.oraPartenza.secondi,
        c.oraArrivo.ora, c.oraArrivo.minuti, c.oraArrivo.secondi,
        c.ritardo );   
}


Comando registraComando() {
    Comando usrPrompt = -1;
    printf("======================== SCEGLIERE IL COMANDO DA ESEGUIRE ========================\n");
    printf("    0. Cambia file\n");
    printf("    1. Stampa a video dei contenuti\n");
    printf("    2. Stampa su file dei contenuti\n");
    printf("    3. Ordina il vettore di corse per data\n");
    printf("    4. Ordina il vettore di corse per codice di tratta\n");
    printf("    5. Ordina il vettore di corse per stazione di partenza\n");
    printf("    6. Ordina il vettore di corse per stazione di arrivo\n");
    printf("    7. Trova la prima corsa registrata nel vettore tramite il codice di tratta\n");
    printf("    8. Trova tutte le corse che partono da una fermata specifica\n");
    printf("\nINSERIRE IL COMANDO DA ESEGUIRE: ");
    scanf("%d", &usrPrompt);
    printf("\n");
    return usrPrompt;
}


//nel testo non è specificato ma penso si intenda l'orario di partenza nel confronto
// quindi userò quello.
int confrontaDate(Corsa a, Corsa b) {
    //returna 1 se data a > data b
   int dataA, dataB;
   int orarioA, orarioB;
   dataA = a.data.anno*1e4 + a.data.mese*1e2 + a.data.giorno;
   dataB = b.data.anno*1e4 + b.data.mese*1e2 + b.data.giorno;
   if (dataA > dataB)  return 1;
   if (dataA == dataB) {
        orarioA = a.oraPartenza.ora*1e4 + a.oraPartenza.minuti*1e2 + a.oraPartenza.secondi;
        orarioB = b.oraPartenza.ora*1e4 + b.oraPartenza.minuti*1e2 + b.oraPartenza.secondi;
        if (orarioA > orarioB) return 1;
   }
   return 0;
}


//dato che ci sono solo 1000 dati da ordinare userò algoritmi quadratici di ordinamento.
//Nel caso in cui la velocità sia prioritaria si potrebbe usare un algoritmo linearitmico 
//come il bottom up merge sort di TDP ma, in questo caso, non vedo i benefici di sacrificare
//memoria usando un algoritmo non in loco per guadagnare poche frazioni di secondo di velocità 
int bubbleSortCorse(Corsa *v[], int n, char cond) {
    Corsa *temp;
    int swapped = 1, swap;
    for (int i = 0; i < n-1 && swapped; i++) {
        swapped = 0;
        for (int j = 0; j < n-1-i; j++) {
            swap = 0;
            switch (cond) {
                case 'd':
                    swap = confrontaDate(*v[j], *v[j+1]);
                    break;
                case 'c':
                    if (strcmp(v[j]->codice, v[j+1]->codice)>0)
                        swap = 1;
                    break;
                case 'p':
                    if (strcmp(v[j]->partenza,v[j+1]->partenza)>0)
                        swap = 1;
                    break;
                case 'a':
                if (strcmp(v[j]->destinazione, v[j+1]->destinazione)>0)
                        swap = 1;
                    break;
                default:
                    return 0;
            }
            if (swap) {
                swapped = 1;
                temp = v[j+1];
                v[j+1] = v[j];
                v[j] = temp;
            }
        }
    }
    return 1;
}


void stampaVettoreCorse(Corsa *c[], int n) {
    for (int i = 0; i < n; i++)
            stampaCorsa(*c[i], stdout);
}


void ordinaVettore(Corsa ***v, Corsa *refCorse[], int n, char cond) {
    if (*v != NULL) free(*v);
    *v = malloc(n*sizeof(**v));
    for (int i = 0; i < n; i++)
        (*v)[i] = refCorse[i];
    if (!bubbleSortCorse(*v, n, cond)) {
        printf("c'è stato un errore");
        return;
    }
    printf("Vettore ordinato con successo.\n");
    stampaVettoreCorse(*v, n);
}


void ricercaPartenza(Corsa *pCorse[], int nCorse, char *x) {
    int count, lenX = strlen(x);
    
    char *current;
    for (int i = 0; i < nCorse; i++) {
        current = pCorse[i]->partenza;
        count = 0;
        for (int j = 0; j < lenX; j++) {
            //toupper completamente superfluo ma già che lo abbiamo nativo in c usiamolo
            if (toupper(*(current + j)) == toupper(x[j]) || (*(current + j) == '_' && x[j] == ' ')) 
                count++;
        }
        if (count == lenX)
            stampaCorsa(*pCorse[i], stdout);
    }
}


//suppongo che 'basta elencare il primo' si intenda il primo trovato dall'algoritmo
int ricercaDicotomicaCodice(Corsa *v[], int l, int r, char *x) {
    int c;
    c = (l+r)/2;
    if (l > r) return 0;
    if (strcmp(v[c]->codice, x) == 0) {
        stampaCorsa(*v[c], stdout);
        return 1;
    }
    if (strcmp(v[c]->codice, x) > 0)
        return ricercaDicotomicaCodice(v, l, c-1, x);
    return ricercaDicotomicaCodice(v, c+1, r, x);
}

void freeArrays(Corsa **v, Corsa ***refV, Ordinato *ord) {
    // dalla documentazione di C, free(NULL) non fa niente, quindi posso anche
    // evitare di controllare che i vettori siano stati allocati (con i comandi di ordinamento)
    // dato che nel main sono inizializzati a NULL
        free(*v); *v = NULL;
        free(*refV); *refV = NULL;
        free(ord->data);     ord->data = NULL;
        free(ord->partenza); ord->partenza = NULL;
        free(ord->arrivo);   ord->arrivo = NULL;
        free(ord->codice);   ord->codice = NULL;   
} 


void eseguiComando(Comando richiesta, Corsa **corse, Corsa ***pCorse, int *pnCorse, Ordinato *ordType) {
    int nCorse = *pnCorse;
    FILE *fp;
    char toFind[30];
    char nomeFile[21] = "\0";
    switch (richiesta) {
    case r_cambiaFile:
        scanf("%s", nomeFile);
        freeArrays(corse, pCorse, ordType);
        *pnCorse = leggiFileCorse(corse, pCorse, nomeFile);
        printf("%d", *pnCorse);
        printf("file letto con successo\n");
        break;
    case r_stampaVideo:
        stampaVettoreCorse(*pCorse, nCorse);
        break;
    case r_stampaFile:
        nomeFile[0] = '\0';
        printf("inserire il nome del file con l'estensione (massimo 20 caratteri, default: corseOut.txt): ");
        scanf("%s", nomeFile);
        fp = fopen(nomeFile, "w");
        for (int i = 0; i < nCorse; i++)
            stampaCorsa((*corse)[i], fp);
        fclose(fp);
        break;
    case r_ordinaData:
        ordinaVettore(&(ordType->data), *pCorse, nCorse, 'd');
        break;
    case r_ordinaCodice:
        ordinaVettore(&(ordType->codice), *pCorse, nCorse, 'c');
        break;
    case r_ordinaStazionePartenza: 
        ordinaVettore(&(ordType->partenza), *pCorse, nCorse, 'p');
        break;
    case r_ordinaStazioneArrivo:
        ordinaVettore(&(ordType->arrivo), *pCorse, nCorse, 'a');
        break;
    case r_ricercaCodice:
        printf("Inserire il codice della corsa da cercare: ");
        scanf("%s", toFind);
        //per una ricerca dicotomica serve il vettore ordinato
        bubbleSortCorse(*pCorse, nCorse, 'c');
        if (!ricercaDicotomicaCodice(*pCorse, 0, nCorse-1, toFind))
            printf("nessuna corsa con quel codice trovata");
        break;
    case r_ricercaStazionePartenza:
        printf("scrivi la partenza: ");
        scanf("%s", toFind);
        ricercaPartenza(*pCorse, nCorse, toFind);
        break;
    default:
        printf("Inserire un'opzione valida");
        break;
    }
}