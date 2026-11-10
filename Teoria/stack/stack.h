#ifndef STACK_H
#define STACK_H

#include "..\item.h"

typedef struct stack *STACK;

void STACKinit(int maxN);
int STACKempty();
void STACKpush(Item val);
Item STACKpop();

#endif