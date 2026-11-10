#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "..\item.h"

typedef struct symbtab *ST;
ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, Item val);
Item STsearch(ST st, Key k);
void STdelete(ST st, Key k);
Item STselect(ST st, int r);
void STdisplay(ST st);



#endif