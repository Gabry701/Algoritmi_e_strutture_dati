#include "inv.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_STR 51

typedef struct modifier_s Mod;
typedef struct inventory_s Inv;


struct modifier_s {
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
};

struct item_s {
    char name[MAX_STR];
    char type[MAX_STR];
    Mod mod;
};

struct inventory_s {
    Item *items;
    int numItems;
};

// anche qui ritengo che l'approccio quasi ADT sia meglio

static Inv inventory;


int isValidItem(Item item, int currentItems);

int isValidItem(Item item, int currentItems) {
    for (int i = 0; i < currentItems; i++) 
        if (strcmp(item->name, inventory.items[i]->name) == 0) 
            return 0;
    return 1;
}


// in questo caso l'inizializzazione coincide con il caricamento da 
// file perchè non si possono creare da tastiera oggetti dell'inventory 
void INVinit(char *filename) {
    FILE *fp;
    fp = fopen(filename, "r");
    Item tmp;
    if (fp == NULL) {
        printf("INV: Errore nell'apertura del file");
        return;
    }
    fscanf(fp, "%d", &inventory.numItems);
    inventory.items = malloc(inventory.numItems*sizeof(Item));
    tmp = malloc(sizeof(*tmp));
    for (int i = 0; i < inventory.numItems; i++)
    {
        fscanf(fp,"%s %s %d %d %d %d %d %d", 
            tmp->name, tmp->type,
            &(tmp->mod.hp), &(tmp->mod.mp), &(tmp->mod.atk),
            &(tmp->mod.def), &(tmp->mod.mag), &(tmp->mod.spr));
        if (isValidItem(tmp, i)) {
            inventory.items[i] = malloc(sizeof(struct item_s));
            *(inventory.items[i]) = *tmp;    
        }
        else {i--; inventory.numItems--;}

    }
    free(tmp);
    fclose(fp);
}


Item INVgetItem (char *name) {
    for (int i = 0; i < inventory.numItems; i++)
        if (strcmp(name, inventory.items[i]->name) == 0)
            return inventory.items[i];
    return NULL;
}


void INVprintItem(Item item) {
    printf("Nome: %s\n", item->name);
    printf("Classe: %s\n", item->type);
    printf("Modificatori: \n");
    printf("- HP: %d\n", item->mod.hp);
    printf("- MP: %d\n", item->mod.mp);
    printf("- ATK: %d\n", item->mod.atk);
    printf("- DEF: %d\n", item->mod.def);
    printf("- MAG: %d\n", item->mod.mag);
    printf("- SPR: %d\n", item->mod.spr);
}

void INVprint() {
    for (int i = 0; i < inventory.numItems; i++) 
        INVprintItem(inventory.items[i]);
    printf("\n\n\n");
}

int INVgetHp(Item item) {
    return item->mod.hp;
}
int INVgetMp(Item item) {
    return item->mod.mp;
}
int INVgetAtk(Item item) {
    return item->mod.atk;
}
int INVgetDef(Item item) {
    return item->mod.def;
}
int INVgetMag(Item item) {
    return item->mod.mag;
}
int INVgetSpr(Item item) {
    return item->mod.spr;
}

int INVhasSameName(char *name, Item item) {
    return strcmp(item->name, name) == 0;
}

void INVfree() {
    for (int i = 0; i < inventory.numItems; i++)
        free(inventory.items[i]);
    free(inventory.items);
}