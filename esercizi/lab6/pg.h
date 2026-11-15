
#ifndef PG_H
#define PG_H


#include "inv.h"

// dato che 


typedef struct pg_s *Pg;

void PGinit(void);
void PGcreate(char *id, char *name, char *class, int hp, int mp, int atk, int def, int mag, int spr);
void PGinsert(void);
void PGreadFile(char *filename);
void PGprintAll(void);
void PGsearch(char *id);
void PGdelete(char *id);
void PGequip(char *id, char *itemName);
void PGunequip(char *id, char *itemName);
void PGfree(void);
#endif

/*
STAMPA PERSONAGGIO BASE
stampa pg, stampa statistiche base 
STAMPA EQUIPAGGIAMENTO E STATISTICHE AGGIORNATE (in base al codice)
STAMPA TUTTI I PERSONAGGI (for -> stampa pg[i], stampa statNew [pg[i].codice])

*/

/*
AGGIUNGI PERSONAGGIO (ATTENZIONE A CODICI DUPLICATI E DATI NON VALIDI)
*/

/*
ELIMINARE PG TRAMITE CODICE
*/

/*
AGGIUNGERE O RIMUOVERE OGGETTO DALL'EQUIPAGGIAMENTO
*/



// caricamento personaggi
// inserimento e cancellazione personaggi
// ricerca per codice
// stampa 
// gestione equipaggiamento
// aggiornamento statistiche