#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN_WORD 50
#define MAX_LEN_CODE 5
#define MAX_FILE_LINE (4*MAX_LEN_WORD + 2*MAX_LEN_CODE + 8 + 7)

typedef enum {r_keyboardIn, r_fileIn, r_searchCode, r_delSingle, r_delInterval, r_exportList} Comando;


typedef struct {
    int giorno;
    int mese;
    int anno;
} Data;

typedef struct {
    char codice[MAX_LEN_CODE + 1];
    char nome[MAX_LEN_WORD + 1];
    char cognome[MAX_LEN_WORD + 1];
    Data dataNascita;
    char via[MAX_LEN_WORD + 1];
    char citta[MAX_LEN_WORD + 1];
    char cap[MAX_LEN_CODE + 1];
} Persona;

typedef struct node Node, *link;
struct node {
    Persona val;
    struct node *next;
};

link newNode(Persona val, link next);
void addNode(link *h, Persona val);
void freeList(link h);
int dataGT(Data a, Data b);
int dataEq(Data a, Data b);
int readPersona(char *s, Persona *p);
Comando getRequest();
void executeRequest(Comando req, link *h);
void printList(link h);
void keyboardIn_exe(link *h);
void fileIn_exe(link *h);
void printPersona(Persona p);
link searchCode_exe(link *h);
Persona delSingle_exe(link *h);
Persona delRecord(link *h, char *k);
Persona *delInterval_exe(link *h);
void exportList_exe(link *h);
void executeRequest(Comando req, link *h);



int main() {
    link head = NULL;
    Comando request;
    do {
        request = getRequest();
        executeRequest(request, &head);
        printList(head);
    } while (request < 6 && request >= 0);
    freeList(head);
}

// program flow
Comando getRequest() {
    Comando comando;
    printf("==================== SCEGLI IL COMANDO DA ESEGUIRE ====================\n");
    printf("\t 1. Inserisci un record da tastiera\n");
    printf("\t 2. Leggi e inserisci tutti i record di un file\n");
    printf("\t 3. Cerca un record tramite il codice\n");
    printf("\t 4. Cancella un record\n");
    printf("\t 5. Cancella tutti i record compresi tra due date\n");
    printf("\t 6. stampa la lista in un file\n");
    printf("\nDigita il comando: ");
    scanf("%d", &comando);
    return comando-1;
}

void executeRequest(Comando req, link *h) {
    Persona *deleted = NULL;
    switch (req) {
    case r_keyboardIn:
        keyboardIn_exe(h);
        break;
    case r_fileIn:
        fileIn_exe(h);
        break;
    case r_searchCode:
        //la funzione returna il nodo, se si vuole fare qualcosa
        //con il nodo dichiarare la variabile adeguata e salvarlo
        searchCode_exe(h);
        break;
    case r_delSingle:
        //assegnazioni a scopo dimostrativo, in realtà
        // sarebbe meglio separare il vettore dei dati eliminati
        // dal dato eliminato singolo o aggiungere il dato singolo 
        // a un unico vettore mallocato (ed eventualmente reallocato)
        // che contiene tutti gli elementi eliminati
        deleted = malloc(sizeof(Persona));
        *deleted = delSingle_exe(h);
        break;
    case r_delInterval:
        deleted = delInterval_exe(h);
        // qui si possono inserire le funzioni che operano sui
        // record eliminati
        break;
    case r_exportList:
        exportList_exe(h);
        break;
    default:
        printf("Programma terminato");
        break;
    }
    // se non si devono fare operazioni con deleted
    // fuori dalla funzione
    free(deleted);
}

//execute command functions 
// ho provato a usare implementazioni _exe per ogni singolo comando
// lasciando la funzione request senza codice aggiuntivo a parte quello necessario
// per il return

void keyboardIn_exe(link *h) {
    Persona person;
    //potrei usare l'altra funzione ma per permettere all'utente di avere un'esperienza 
    //migliore (vengono stampati i nomi dei campi da inserire) e non usare nell'altra 
    //fscanf separati e if (fp == stdout) per ogni fscanf penso che separarle sia la 
    //soluzione corretta 
    printf("Inserire i seguenti dati per il record:\n");
    printf("- Codice: "); scanf("%5s", person.codice);
    printf("- Nome: "); scanf("%50s", person.nome);
    printf("- Cognome: "); scanf("%50s", person.cognome);
    printf("- Data di nascita (separata da '/'): "); scanf("%d/%d/%d", &person.dataNascita.giorno, &person.dataNascita.mese, &person.dataNascita.anno);
    printf("- Via: "); scanf("%50s", person.via);
    printf("- Citta': "); scanf("%50s", person.citta);
    printf("- Cap': "); scanf("%5s", person.cap);
    addNode(h, person);
}

void fileIn_exe(link *h) {
    Persona current;
    FILE *fp;
    char filename[31];
    char line[MAX_FILE_LINE + 1];
    printf("\nInserire il nome del file da cui prendere i dati: "); 
    scanf("%30s", filename);
    printf("\n\n");
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("|ERRORE: File non aperto correttamente|\n");
        return;
    }
    while (fgets(line, MAX_FILE_LINE +1, fp) != NULL) {
        if(readPersona(line, &current)) {
            addNode(h, current);
        }
    }
    fclose(fp);
}

link searchCode_exe(link *h) {
    char toFind[MAX_LEN_CODE + 1];
    link x;
    printf("Inserire il codice del record da trovare: ");
    scanf("%s", toFind);
    for (x = *h; x != NULL; x = x->next) 
        if (strcmp(x->val.codice, toFind) == 0) {
            printf("\n\nNODO CON CODICE %s:\n", toFind);
            printPersona(x->val);
            return x;
        }
    printf("\nNon esiste un nodo con quel codice\n");
    return NULL;
}

Persona delSingle_exe(link *h) {
    char code[6];
    Persona deleted;
    printf("Inserire il codice da eliminare: ");
    scanf("%5s", code);
    deleted = delRecord(h, code);
    // qui si possono aggiungere condizioni o passare 
    // per reference un flag nonTrovato così da evitare
    // messaggi nell'uso della deleted returnata se è vuota
    // es: if(strlen(deleted.codice)==0) nonTrovato = 0;
    return deleted;
}

Persona *delInterval_exe(link *h) {
    Persona *deletedArray;
    Data data1, data2;
    link *x, *y, tmp, *start = h;
    int first = 1, c = 0, i;
    printf("Inserisci la prima data: "); 
    scanf("%d/%d/%d", &data1.giorno, &data1.mese, &data1.anno);
    printf("\nInserisci la seconda data: ");
    scanf("%d/%d/%d", &data2.giorno, &data2.mese, &data2.anno);
    printf("\n");
    if (*h == NULL)
        return NULL;
    for (x = h; (*x)->next != NULL; x = &((*x)->next), c++) {
        if (first && (dataGT(data1, (*x)->val.dataNascita) || dataEq(data1, (*x)->val.dataNascita))) {
            start = x;
            first = 0;
            c = 0;
        }
        if (dataGT(((*x)->next)->val.dataNascita, data2)) break;
    }
    deletedArray = malloc(c*sizeof(Persona));
    for (i = 0; i < c; i++) {
        // potevo creare una nuova funzione delNode ma tanto partendo da start
        // elimina il nodo con in valore codice di start ossia fa un ciclo di 1
        // non aumentando la complessità se non per il controllo di un if
        deletedArray[i] = delRecord(start, (*start)->val.codice);
    }
    return deletedArray;
}

void exportList_exe(link *h) {
    FILE *fp;
    link x;
    char filename[31] = "\0";
    printf("Inserire il nome dei file su cui salvare i dati: ");
    scanf("%30s", filename);
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Errore nell'apertura del file");
        return;
    }
    for (x = *h; x != NULL; x = x->next) {
        fprintf(fp, "%s ", x->val.codice);
        fprintf(fp, "%s ", x->val.nome);
        fprintf(fp, "%d/%d/%d ", x->val.dataNascita.giorno, x->val.dataNascita.mese, x->val.dataNascita.anno);
        fprintf(fp, "%s\n", x->val.citta);
    }
    fclose(fp);
    printf("\nDati salvati con successo\n\n");
}


//list functions

link newNode(Persona val, link next) {
    link x = malloc(sizeof(*x));
    if (x == NULL)
        return NULL;
    x->val = val;
    x->next = next;
    return x;
}

void addNode(link *h, Persona val) {
    link p, x;
    for (x = *h; x != NULL; x = x->next)
        if (strcmp(x->val.codice, val.codice) == 0) 
            return;
    if (*h == NULL || dataGT((*h)->val.dataNascita, val.dataNascita)) {
        *h = newNode(val, *h);
        return;
    }
    for (x = (*h)->next, p = *h; x != NULL && dataGT(val.dataNascita, x->val.dataNascita); p = x, x = x->next);
        p->next = newNode(val, x);
}

void printList(link h) {
    link x;
    int c = 1;
    for (x = h; x != NULL; x = x->next, c++) {
        printf("===== Nodo %d =====\n", c);
        printf("Codice: %s\n", x->val.codice);
        printf("Nome: %s\n", x->val.nome);
        printf("Cognome: %s\n", x->val.cognome);
        printf("Data di nascita: %02d/%02d/%d\n", x->val.dataNascita.giorno, x->val.dataNascita.mese, x->val.dataNascita.anno);
        printf("Via: %s\n", x->val.via);
        printf("Citta': %s\n", x->val.citta);
        printf("Cap': %s\n", x->val.cap);
        printf("\n");
    }
}

// leggermente superflua dato che la lista è presente in tutto il programma 
// e la lista viene deallocata automaticamente alla chiusura
void freeList(link h) {
    link x, p;
    for (x = h; x != NULL; x = p) {
        p = x->next;
        free(x);
    }
}


//helpers


void printPersona(Persona p) {
    printf("Codice: %s\n", p.codice);
    printf("Nome: %s\n", p.nome);
    printf("Cognome: %s\n", p.cognome);
    printf("Data di nascita: %02d/%02d/%d\n", p.dataNascita.giorno, p.dataNascita.mese, p.dataNascita.anno);
    printf("Via: %s\n", p.via);
    printf("Citta': %s\n", p.citta);
    printf("Cap': %s\n", p.cap);
    printf("\n");
}


int dataGT(Data a, Data b) {
    if (a.anno > b.anno)
        return 1;
    if (a.anno == b.anno) {
        if (a.mese > b.mese)
            return 1;
        if (a.mese == b.mese && a.giorno > b.giorno)
            return 1;
    }
    return 0;
}

int dataEq(Data a, Data b) {
    return a.anno == b.anno && a.mese == b.mese && a.giorno == b.giorno;
}

// uso void passando il puntatore per risparmiare memoria (copia solo il puntatore, non l'intera struct)
int readPersona(char *s, Persona *p) {
    //specifichiamo i caratteri massimi che possiamo avere nella stringa per evitare buffer overflow
    return sscanf(s, "%5s %50s %50s %d/%d/%d %50s %50s %5s",
        p->codice,
        p->nome, p->cognome,
        &(p->dataNascita.giorno), &(p->dataNascita.mese), &(p->dataNascita.anno),
        p->via, p->citta, p->cap
    ) == 9;
}


Persona delRecord(link *h, char *k) {
    link *x, t;
    Persona deleted = {0};
    for (x = h; *x != NULL; x = &((*x)->next)) {
        if (strcmp((*x)->val.codice, k) == 0) {
            t = *x;
            *x = (*x)->next;
            deleted = t->val;
            free(t);
            return deleted;
        }
    }
    printf("Non esiste un elemento con quel codice\n");
    return deleted;
}

