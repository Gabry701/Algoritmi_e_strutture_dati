#ifndef ITEM_H
#define ITEM_H

#include <stdio.h>

#define maxKey 100

typedef int Item;

Item ITEMscan(void);
int ITEMeq(Item A, Item B);
int ITEMneq(Item A, Item B);
int ITEMlt(Item A, Item B);
int ITEMgt(Item A, Item B);
void ITEMshow(Item A);
Item ITEMrand(void);

#endif