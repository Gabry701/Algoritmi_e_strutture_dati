#ifndef STACKQADT_H
#define STACKQADT_H

#include "..\item.h"

void STACKinit(int maxN);
int STACKempty();
void STACKpush(Item val);
Item STACKpop();

#endif