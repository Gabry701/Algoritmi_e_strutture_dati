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
int ageGreaterThan(Data a, Data b);
int readPersona(char *s, Persona *p);
Comando getRequest();
void executeRequest(Comando req, link *h);
void printList(link h);
void keyboardIn_exe(link *h);
void fileIn_exe(link *h);
//FINITO PUNTO 1, FARE PUNTO 2, FUNZIONE PER INPUT DA FILE GIÀ PRONTA

void search_


void executeRequest(Comando req, link *h) {
    switch (req) {
    case r_keyboardIn:
        keyboardIn_exe(h);
        break;
    case r_fileIn:
        fileIn_exe(h);
        break;
    case r_searchCode:
        //keyboardIn_exe();
        break;
    case r_delSingle:
        break;
    case r_delInterval:
        break;
    case r_exportList:
        break;
    default:
        printf("Programma terminato");
        break;
    }
}

int main() {
    link head = NULL;
    Comando request;
    do {
        request = getRequest();
        executeRequest(request, &head);
        printList(head);
    } while (request < 6 && request >= 0);
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
    if (*h == NULL || ageGreaterThan((*h)->val.dataNascita, val.dataNascita)) {
        *h = newNode(val, *h);
        return;
    }
    for (x = (*h)->next, p = *h; x != NULL && ageGreaterThan(val.dataNascita, x->val.dataNascita); p = x, x = x->next);
        p->next = newNode(val, x);
}

//helpers

int ageGreaterThan(Data a, Data b) {
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

//execute command functions 

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