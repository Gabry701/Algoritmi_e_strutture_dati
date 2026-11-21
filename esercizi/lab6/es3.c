#include <stdio.h>
#include <stdlib.h>
#include "pg.h"
#include "inv.h"
#include <ctype.h>

#define PG_FILE "pg.txt"
#define INV_FILE "inventario.txt"
#define OPTIONS_NUM 8
#define MAX_STR 51

typedef enum {r_printPGs, r_printINV, r_printSpecificPG, r_addPG, r_delPG, r_equipPG, r_uneqipPG, r_exit} req;


void gameLoop();
void showMenu();
int executeRequest(req request);
int readInt(int *x);

int main() {
    
    gameLoop();

}

int readInt(int *x) {
    int c; 
    if (scanf("%d", x) != 1) {
        do {
            c = getchar();
        } while (c != '\n' && c != EOF);
        printf("Inserire richiesta valida\n");
        return 0;
    }
    do {
            c = getchar();
        } while (c != '\n' && c != EOF);
    return 1;
}


void gameLoop() {
    int request = -1;
    int exit = 0;
    PGinit();
    PGreadFile(PG_FILE);
    INVinit(INV_FILE);
    do {
        showMenu();
        if(readInt(&request) == 0) continue;
        exit = executeRequest((req) (request-1));
    } while (!exit);
}


void showMenu() {
    printf("======================== SCEGLI UN'OPZIONE ========================\n");
    printf("\t1) Stampa la lista dei personaggi\n");
    printf("\t2) Stampa l'inventario\n");
    printf("\t3) Stampa un personaggio specifico\n");
    printf("\t4) Aggiungi un nuovo personaggio\n");
    printf("\t5) Elmina un personaggio\n");
    printf("\t6) Aggiungi un oggetto all'equipaggiamento di un personaggio\n");
    printf("\t7) Rimuovi un oggetto all'equipaggiamento di un personaggio\n");
    printf("\t8) Esci\n");
    printf("->");
}

// non so se sia meglio mettere return 1 a ogni case o lasciare i break 
// e lasciare un singolo return alla fine, ma non penso che sia così importante
int executeRequest(req request) {
    char id[MAX_STR], name[MAX_STR];

    switch (request)
    {
    case r_printPGs:
        PGprintAll();
        return 0;
    case r_printINV:
        INVprint();
        return 0;
    case r_printSpecificPG:
        printf("Inserire il codice del personaggio: ");
        scanf("%s", id);
        PGsearch(id);
        return 0;
    case r_addPG:
        PGinsert();
        return 0;
    case r_delPG:
        printf("Inserire il codice del personaggio: ");
        scanf("%s", id);
        PGdelete(id);
        return 0;
    case r_equipPG:
        printf("Inserire il codice del personaggio: ");
        scanf("%s", id);
        printf("Inserire il nome dell'arma");
        scanf("%s", name);
        PGequip(id, name);
        return 0;
    case r_uneqipPG:
        printf("Inserire il codice del personaggio: ");
        scanf("%s", id);
        printf("Inserire il nome dell'arma");
        scanf("%s", name);
        PGunequip(id, name);
        return 0;
    case r_exit:
        printf("Programma terminato\n");
        PGfree();
        INVfree();
        return 1;
    default:
        printf("Inserire un comando valido\n");
        return 0;
    }
}