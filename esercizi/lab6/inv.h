#ifndef INV_H
#define INV_H

// distinguo concettualmente le modifiche degli oggetti
// e le statistiche dei personaggi

typedef struct item_s *Item;

void INVinit(char *filename);
void INVprint(void);
void INVprintItem(Item item);
Item INVgetItem(char *name);
int INVgetHp(Item item);
int INVgetMp(Item item);
int INVgetAtk(Item item);
int INVgetDef(Item item);
int INVgetMag(Item item);
int INVgetSpr(Item item);
int INVhasSameName(char *name, Item item);
void INVfree(void);
#endif


/*
STAMPA OGGETTO INVENTARIO
STAMPA TUTTO L'INVENTARIO
*/

// caricamento catalogo
// ricerca oggetto per nome
// stampa oggetti
// deallocazione 

