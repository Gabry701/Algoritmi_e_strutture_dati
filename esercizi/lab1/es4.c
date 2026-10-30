#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#define FILENAME "corse.txt"



typedef enum {r_stampaVideo, r_stampaFile, r_ordinaData, r_ordinaCodice, r_ordinaStazionePartenza, 
                r_ordinaStazioneArrivo, r_ricercaCodice, r_ricercaStazionePartenza, r_ordinaTutto} Comando;

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



Comando registraComando();
int leggiFileCorse(Corsa v[]);
int bubbleSortCorse(Corsa *v[], int n, char cond, Corsa *out[]);
int confrontaDate(Corsa a, Corsa b);
int ricercaDicotomicaCodice(Corsa *v[], int l, int r, char *x);
void stampaCorsa(Corsa c, FILE *fp);
void eseguiComando(Comando richiesta, Corsa *pCorse[], int nCorse, Corsa *corseOrdData[], Corsa *corseOrdCodice[], Corsa *corseOrdPartenza[], Corsa *corseOrdArrivo[]);
void stampaVettoreCorse(Corsa *c[], int n);
void ordinaVettore(Corsa *v[], int n, char cond, Corsa *out[]);
void ricercaPartenza(Corsa *pCorse[], int nCorse, char *x);




int main() {
    //il vettore potrebbe essere creato con malloc ma, avendo il numero
    //massimo di corse possibili lo ritengo superfluo
    Corsa corse[1000];
    Corsa *refCorse[1000];
    //probabilmente è meglio creare un vettore di vettori o una struct e passare ogni volta quello, magari facendo un for 
    //nella funzione eseguiComando nel caso l'utente scelga l'opzione 9 (ordina tutto), tuttavia per 4 opzioni di ordinamento
    //credo vada bene pure crearli singolarmente, è leggermente meno leggibile a causa dei vari parametri delle funzioni ma 
    //forse facendo una struct o un vettore diventerebbe comunque confusionario l'accesso alle variabili interne della struct Corsa
    Corsa *corseOrdData[1000], *corseOrdCodice[1000], *corseOrdPartenza[1000], *corseOrdArrivo[1000]; 
    int numeroCorse;
    Comando richiestaUtente;
    
    numeroCorse = leggiFileCorse(corse);

    for (int i = 0; i < numeroCorse; i++) 
        refCorse[i] = &corse[i];
    
    richiestaUtente = registraComando();
    eseguiComando(richiestaUtente, refCorse, numeroCorse, corseOrdData, corseOrdCodice, corseOrdPartenza, corseOrdArrivo);
}



int leggiFileCorse(Corsa v[]) {
    int numCorse;
    FILE *fp = fopen(FILENAME, "r");
    fscanf(fp, "%d", &numCorse);
    for (int i = 0; i < numCorse; i++) {
        //fscanf separati per leggibilità
        fscanf(fp, "%s %s %s", v[i].codice, v[i].partenza, v[i].destinazione);
        fscanf(fp, "%d/%d/%d", &v[i].data.anno, &v[i].data.mese, &v[i].data.giorno);
        fscanf(fp, "%d:%d:%d", &v[i].oraPartenza.ora, &v[i].oraPartenza.minuti, &v[i].oraPartenza.secondi);
        fscanf(fp, "%d:%d:%d", &v[i].oraArrivo.ora, &v[i].oraArrivo.minuti, &v[i].oraArrivo.secondi);
        fscanf(fp, "%d", &v[i].ritardo);
    }
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
    //dato che nel 3 non è specificato il metodo in cui l'utente deve specificare 
    //l'operazione da attuare, scelgo di implementare un elenco puntato che, a livello di
    //ux per una applicazione del genere mi sembra più chiaro e fruibile all'utente 
    printf("======================== SCEGLIERE IL COMANDO DA ESEGUIRE ========================\n");
    printf("    1. Stampa a video dei contenuti\n");
    printf("    2. Stampa su file dei contenuti\n");
    printf("    3. Ordina il vettore di corse per data\n");
    printf("    4. Ordina il vettore di corse per codice di tratta\n");
    printf("    5. Ordina il vettore di corse per stazione di partenza\n");
    printf("    6. Ordina il vettore di corse per stazione di arrivo\n");
    printf("    7. Trova la prima corsa registrata nel vettore tramite il codice di tratta\n");
    printf("    8. Trova tutte le corse che partono da una fermata specifica\n");
    printf("    9. Ordina e salva il vettore in base a ogni condizione sopra indicata\n");
    printf("\nINSERIRE IL COMANDO DA ESEGUIRE: ");
    scanf("%d", &usrPrompt);
    printf("\n");
    //returno il numero scelto -1 in quanto gli indici degli enum iniziano da 0 mentre il mio elenco da 1
    return usrPrompt-1;
}


//nel testo non è specificato ma penso si intenda l'orario di partenza nel confronto
// quindi userò quello.
int confrontaDate(Corsa a, Corsa b) {
    //returna 1 se data a > data b
   int dataA, dataB;
   int orarioA, orarioB;
   dataA = a.data.anno*10000 + a.data.mese*100 + a.data.giorno;
   dataB = b.data.anno*10000 + b.data.mese*100 + b.data.giorno;
   if (dataA > dataB)  return 1;
   if (dataA == dataB) {
        orarioA = a.oraPartenza.ora*10000 + a.oraPartenza.minuti*100 + a.oraPartenza.secondi;
        orarioB = b.oraPartenza.ora*10000 + b.oraPartenza.minuti*100 + b.oraPartenza.secondi;
        if (orarioA > orarioB) return 1;
   }
   return 0;
}


//dato che ci sono solo 1000 dati da ordinare userò algoritmi quadratici di ordinamento.
//Nel caso in cui la velocità sia prioritaria si potrebbe usare un algoritmo linearitmico 
//come il bottom up merge sort di TDP ma, in questo caso, non vedo i benefici di sacrificare
//memoria usando un algoritmo non in loco per guadagnare poche frazioni di secondo di velocità 
int bubbleSortCorse(Corsa *v[], int n, char cond, Corsa *out[]) {
    Corsa *temp;
    int swapped = 1, swap;
    if (v != out)
        for (int k = 0; k < n; k++)
            out[k] = v[k];
    for (int i = 0; i < n-1 && swapped; i++) {
        swapped = 0;
        for (int j = 0; j < n-1-i; j++) {
            swap = 0;
            switch (cond) {
                case 'd':
                    swap = confrontaDate(*out[j], *out[j+1]);
                    break;
                case 'c':
                    if (strcmp(out[j]->codice, out[j+1]->codice)>0)
                    swap = 1;
                    break;
                case 'p':
                    if (strcmp(out[j]->partenza,out[j+1]->partenza)>0)
                    swap = 1;
                    break;

                case 'a':
                if (strcmp(out[j]->destinazione, out[j+1]->destinazione)>0)
                    swap = 1;
                    break;
                default:
                    return 0;
            }
            if (swap) {
                swapped = 1;
                temp = out[j+1];
                out[j+1] = out[j];
                out[j] = temp;
            }
        }
    }
    return 1;
}


void stampaVettoreCorse(Corsa *c[], int n) {
    for (int i = 0; i < n; i++)
            stampaCorsa(*c[i], stdout);
}


void ordinaVettore(Corsa *v[], int n, char cond, Corsa *out[]) {
    if (!bubbleSortCorse(v, n, cond, out)) {
        printf("c'è stato un errore");
        return;
    }
    switch (cond) {
        case 'd':
            printf("vettore ordinato per data:\n");
            break;
        case 'c':
            printf("vettore ordinato per codice:\n");
            break;
        case 'p':
            printf("vettore ordinato per partenza:\n");
            break;
        case 'a':
            printf("vettore ordinato per arrivo:\n");
            break;
        default:
            return;
    }
    stampaVettoreCorse(out, n);
    printf("\n");
}


void ricercaPartenza(Corsa *pCorse[], int nCorse, char *x) {
    int count, lenX = strlen(x);
    
    char *current;
    for (int i = 0; i < nCorse; i++) {
        current = pCorse[i]->partenza;
        count = 0;
        for (int j = 0; j < lenX && *(current+j) != '\0'; j++) {
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


void eseguiComando(Comando richiesta, Corsa *pCorse[], int nCorse, Corsa *corseOrdData[], Corsa *corseOrdCodice[], Corsa *corseOrdPartenza[], Corsa *corseOrdArrivo[]) {
    FILE *fp;
    char toFind[30];
    char nomeFile[21] = "\0";
    switch (richiesta) {
    case r_stampaVideo:
        stampaVettoreCorse(pCorse, nCorse);
        break;
    case r_stampaFile:
        printf("inserire il nome del file con l'estensione (massimo 20 caratteri, default: corseOut.txt): ");
        scanf("%s", nomeFile);
        fp = fopen(nomeFile, "w");
        for (int i = 0; i < nCorse; i++)
            stampaCorsa(*pCorse[i], fp);
        fclose(fp);
        break;
    case r_ordinaData:
        ordinaVettore(pCorse, nCorse, 'd', corseOrdData);
        break;
    case r_ordinaCodice:
        ordinaVettore(pCorse, nCorse, 'c', corseOrdCodice);
        break;
    case r_ordinaStazionePartenza: 
        ordinaVettore(pCorse, nCorse, 'p', corseOrdPartenza);
        break;
    case r_ordinaStazioneArrivo:
        ordinaVettore(pCorse, nCorse, 'a', corseOrdArrivo);
        break;
    case r_ricercaCodice:
        printf("Inserire il codice della corsa da cercare: ");
        scanf("%s", toFind);
        //per una ricerca dicotomica serve il vettore ordinato
        bubbleSortCorse(pCorse, nCorse, 'c', pCorse);
        if (!ricercaDicotomicaCodice(pCorse, 0, nCorse-1, toFind))
            printf("nessuna corsa con quel codice trovata");
        break;
    case r_ricercaStazionePartenza:
        printf("scrivi la partenza: ");
        scanf("%s", toFind);
        ricercaPartenza(pCorse, nCorse, toFind);
        break;
    case r_ordinaTutto:
        ordinaVettore(pCorse, nCorse, 'd', corseOrdData);
        ordinaVettore(pCorse, nCorse, 'c', corseOrdCodice);
        ordinaVettore(pCorse, nCorse, 'p', corseOrdPartenza);
        ordinaVettore(pCorse, nCorse, 'a', corseOrdArrivo);
        break;
    default:
        printf("Inserire un'opzione valida");
        break;
    }
}