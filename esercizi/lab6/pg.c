#include "pg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// contengono già lo spazio per il '\0'
#define ID_SIZE 7
#define MAX_STR 51
#define MAX_EQUIP 8
#define MAX_LINE 256

// preferisco un approccio quasi ADT dato che i personaggi
// non sono divisi in gruppi ma esiste una singola lista
// che li contiene

typedef struct stats_s Stats;
typedef struct PGnode_s *link;
typedef struct PGlist_s PGlist;
typedef struct equip_s Equip;

struct PGlist_s {
    link head;
    link tail;
    int numPG;
};

struct PGnode_s {
    Pg pg;
    link next;
};



struct stats_s {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
};

struct equip_s {
    Item items[MAX_EQUIP];
    int numEquip;
};

struct pg_s {
    Stats baseStats;
    Stats currentStats;
    char id[ID_SIZE];
    char name[MAX_STR];
    char class[MAX_STR];
    Equip equip;
}; 


static PGlist list;
static link PGsearchNode(char *id);
static void freeNode(link x);


// prima funzione da chiamare nel main
// inizializza la lista
void PGinit() {
    list.head = list.tail = NULL;
    list.numPG = 0;
}


// aggiungi personaggio alla lista
static void addPG (Pg val) {
    link x;
    x = malloc(sizeof(struct PGnode_s));
    x->pg = val;
    x->next = NULL;
    list.numPG++;
    if (list.head == NULL) {
        list.head = list.tail = x;
        return;
    }
    list.tail->next = x;
    list.tail = x;
    list.tail->next = NULL;
}



static int isValidPG (Pg pg) {
    link x;
    int valid = 1;
    // correttezza codice
    if (strlen(pg->id) != ID_SIZE - 1)
        valid = 0;
    for (int i = 0; pg->id[i] != '\0' && valid; i++) {
        if ((i == 0 && pg->id[i] != 'P') ||
            (i == 1 && pg->id[i] != 'G') ||
            (i > 1 && !isdigit(pg->id[i])))
            valid = 0;
    }
    if (!valid) {
        printf("codice non valido\n");
        return 0;
    }
    // correttezza nome 
    for (char *s = pg->name; *s != '\0'; s++)
        if (!isalpha(*s)) {
            printf("nome non valido\n");
            return 0;
        }
    // correttezza classe
    for (char *s = pg->class; *s != '\0'; s++)
        if (!isalpha(*s)) {
            printf("classe non valida\n");
            return 0;
        }
    // correttezza statistiche
    if (pg->baseStats.hp < 0 ||
        pg->baseStats.mp < 0 ||
        pg->baseStats.atk < 0 ||
        pg->baseStats.def < 0 ||
        pg->baseStats.mag < 0 ||
        pg->baseStats.spr < 0 ) {
            printf("le statistiche devono essere maggiori o uguali a 0\n");
            return 0;
        }
    // controllo duplicati id
    for (x = list.head; x != NULL; x = x->next) {
        if (strcmp(x->pg->id, pg->id) == 0) {
            printf("codice già presente nella lista\n");
            return 0;
        }
    }
    return 1;
}

// per provare un approccio in cui i dati del file vengono completamente oscurati al main
// e per permettere al main di creare comunque un personaggio direttamente tramite gli argomenti
// della funzione inserisco i dati come int, lasciando la definizione di stats nel .c
void PGcreate (char *id, char *name, char *class, int hp, int mp, int atk, int def, int mag, int spr) {
    Pg pg;
    Stats stats = {hp, mp, atk, def, mag, spr};
    pg = malloc(sizeof(*pg));
    strcpy(pg->id, id);
    strcpy(pg->name, name);
    strcpy(pg->class, class);
    pg->equip.numEquip = 0;
    pg->baseStats = stats;
    pg->currentStats = stats;
    if (!isValidPG(pg)) {
        printf("Personaggio non inserito\n");
        free(pg);
        return;
    }
    addPG(pg);
}

// lo metterei in un'altra libreria tipo help.h
// dato che lo devo usare anche nel main ma non voglio
// uscire dalle specifiche del problema
static int readInt(int *x) {
    int c; 
    if (scanf("%d", x) != 1) {
        do {
            c = getchar();
        } while (c != '\n' && c != EOF);
        printf("Inserire statisitiche valide\n");
        return 0;
    }
    do {
            c = getchar();
        } while (c != '\n' && c != EOF);
    return 1;
}



// inserimento da tastiera
void PGinsert () {
    char id[ID_SIZE], name[MAX_STR], class[MAX_STR];
    Stats stats;
    printf("============= INSERIRE I DATI DEL PERSONAGGIO =============\n");
    printf("Codice: "); scanf("%s", id);
    printf("Nome: "); scanf("%s", name);
    printf("Classe: "); scanf("%s", class);
    printf("Statistiche: \n"); 
    printf("- HP: ");  if (readInt(&stats.hp) == 0)  return;
    printf("- MP: ");  if (readInt(&stats.mp) == 0)  return;
    printf("- ATK: "); if (readInt(&stats.atk) == 0) return;
    printf("- DEF: "); if (readInt(&stats.def) == 0) return;
    printf("- MAG: "); if (readInt(&stats.mag) == 0) return;
    printf("- SPR: "); if (readInt(&stats.spr) == 0) return;
    printf("\n");
    PGcreate(id, name, class, stats.hp, stats.mp, stats.atk, stats.def, stats.mag, stats.spr);
}


static int max(int a, int b) {
    return (a > b)? a : b;
}

void PGreadFile(char *filename) {
    FILE *fp;
    char id[ID_SIZE], name[MAX_STR], class[MAX_STR];
    Stats stats;
    char buffer[MAX_LINE];
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("PG: Errore nell'apertura del file");
        return;
    }
    while (fgets(buffer, MAX_LINE, fp) != NULL) {
        sscanf(buffer, "%s %s %s %d %d %d %d %d %d", 
            id, name, class,
            &stats.hp, &stats.mp, &stats.atk,
            &stats.def, &stats.mag, &stats.spr);
        PGcreate(id, name, class, stats.hp, stats.mp, stats.atk, stats.def, stats.mag, stats.spr);
    }
    fclose(fp);
}

static void PGprint(Pg pg) {
        printf("Codice: %s\n", pg->id);
        printf("Nome: %s\n", pg->name);
        printf("Classe: %s\n", pg->class);
        printf("Statistiche base: \n");
        printf("- HP: %d\n", max(pg->baseStats.hp, 0));
        printf("- MP: %d\n", max(pg->baseStats.mp, 0));
        printf("- ATK: %d\n", max(pg->baseStats.atk, 0));
        printf("- DEF: %d\n", max(pg->baseStats.def, 0));
        printf("- MAG: %d\n", max(pg->baseStats.mag, 0));
        printf("- SPR: %d\n", max(pg->baseStats.spr, 0));
        printf("Equipaggiamento: \n");
        if (pg->equip.numEquip == 0)
            printf("Il personaggio non ha oggetti equipaggiati\n");
        else {
            for (int i = 0; i < pg->equip.numEquip; i++) {
                printf("Oggetto %d", i+1);
                printf("\n"); 
                INVprintItem(pg->equip.items[i]);
            }
            printf("Statistiche attuali: \n");
            printf("- HP: %d\n", max(pg->currentStats.hp, 0));
            printf("- MP: %d\n", max(pg->currentStats.mp, 0));
            printf("- ATK: %d\n", max(pg->currentStats.atk, 0));
            printf("- DEF: %d\n", max(pg->currentStats.def, 0));
            printf("- MAG: %d\n", max(pg->currentStats.mag, 0));
            printf("- SPR: %d\n", max(pg->currentStats.spr, 0));
        }
        
}

void PGprintAll() {
    link x;
    int c = 1;
    for (x = list.head; x != NULL; x = x->next) {
        printf("==== PERSONAGGIO %d ====\n", c++);
        PGprint(x->pg);
        printf("\n\n");
    }
    printf("\n\n\n");
}

static link PGsearchNode(char *id) {
    link x;
    for (x = list.head; x != NULL; x = x->next) 
        if (strcmp(id, x->pg->id) == 0) {
            return x;
        }
    return NULL;
}

void PGsearch(char *id) {
    link x;
    x = PGsearchNode(id);
    if (x != NULL) {
        printf("Personaggio trovato: \n");
        PGprint(x->pg);
        printf("\n\n");
    }
    else
        printf("Non esiste un personaggio con quel codice\n\n\n");
}

void PGdelete(char *id) {
    link x, prev = list.head;
    if (list.head == NULL) {
        printf("Non esiste un personaggio con quel codice\n");
        return;
    }
    if (strcmp(list.head->pg->id, id) == 0) {
        list.head = list.head->next;
        if (list.head == NULL)
            list.tail = NULL;
        free(prev->pg);
        free(prev);
        list.numPG--;
        return;
    }
    for (x = list.head->next; x != NULL && strcmp(id, x->pg->id) != 0;prev = x, x = x->next);
    if (x == NULL) {
        printf("Non esiste un personaggio con quel codice\n");
        return;
    }
    prev->next = x->next;
    if (x->next == NULL)
        list.tail = prev;
    free(x->pg);
    free(x);
    list.numPG--;
}

void PGequip(char *id, char *itemName) {
    link x;
    Item toEquip;
    toEquip = INVgetItem(itemName);
    x = PGsearchNode(id);
    if (toEquip == NULL) {
        printf("Oggetto non presente nell'inventario\n");
        return;
    }
    if (x == NULL) {
        printf("Non esiste un personaggio con quel codice\n");
        return;
    }
    if (x->pg->equip.numEquip == MAX_EQUIP) {
        printf("Il personaggio non può equipaggiare altri oggetti\n");
        return;
    }
    x->pg->equip.items[x->pg->equip.numEquip] = toEquip;
    x->pg->equip.numEquip++;
    x->pg->currentStats.hp += INVgetHp(toEquip);
    x->pg->currentStats.mp  += INVgetMp(toEquip);
    x->pg->currentStats.atk += INVgetAtk(toEquip);
    x->pg->currentStats.def += INVgetDef(toEquip);
    x->pg->currentStats.mag += INVgetMag(toEquip);
    x->pg->currentStats.spr += INVgetSpr(toEquip);
    printf("Oggetto equipaggiato\n");
}

void PGunequip(char *id, char *itemName) {
    link x;
    Item toEquip = NULL;
    int i;
    x = PGsearchNode(id);
    if (x == NULL) {
            printf("Non esiste un personaggio con quel codice\n");
            return;
        }
    for (i = 0; i < x->pg->equip.numEquip; i++) 
        if (INVhasSameName(itemName, x->pg->equip.items[i])) {
            toEquip = x->pg->equip.items[i];
            break;
        }
    if (toEquip == NULL) {
        printf("Oggetto non equipaggiato\n");
        return;
    }
    
    
    for (int j = i; j < x->pg->equip.numEquip -1; j++) 
        x->pg->equip.items[j] = x->pg->equip.items[j+1];
    x->pg->equip.items[--(x->pg->equip.numEquip)] = NULL; 

    x->pg->currentStats.hp -= INVgetHp(toEquip);
    x->pg->currentStats.mp  -= INVgetMp(toEquip);
    x->pg->currentStats.atk -= INVgetAtk(toEquip);
    x->pg->currentStats.def -= INVgetDef(toEquip);
    x->pg->currentStats.mag -= INVgetMag(toEquip);
    x->pg->currentStats.spr -= INVgetSpr(toEquip);
    printf("Oggetto rimosso\n");
}

static void freeNode(link x) {
    if (x == NULL) return;
    freeNode(x->next);
    free(x->pg);
    free(x);
}

// wrapper da poter chiamare nel main senza argomenti
// ho voluto implementare la versione ricorsiva
void PGfree() {
    freeNode(list.head);
}