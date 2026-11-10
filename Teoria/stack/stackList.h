#ifndef STACKLIST_H
#define STACKLIST_H

#include "..\item.h"

typedef struct stack *STACK;

void STACKinit(int maxN);
int STACKempty();
void STACKpush(Item val);
Item STACKpop();

#endif