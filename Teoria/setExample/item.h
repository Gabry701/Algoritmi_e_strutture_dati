#ifndef ITEM_H
#define ITEM_H

typedef struct item *Item;
typedef char *Key;

Key KEYget(Item val);
Key KEYscan();
int KEYcompare(Key k1, Key k2);
Item ITEMnew();
void ITEMfree(Item val);
Item ITEMscan();
void ITEMshow(Item val);
int ITEMless(Item val1, Item val2);
int ITEMgreater(Item val1, Item val2);
int ITEMeq(Item val1, Item val2);
int ITEMcheckvoid(Item val);
Item ITEMsetvoid();

#endif