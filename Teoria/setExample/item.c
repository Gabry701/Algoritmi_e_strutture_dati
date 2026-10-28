#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "item.h"

#define MAXC 50

struct item {
    char name[MAXC]; //Key
    int num;
};


Key KEYget(Item val) {
    return val->name;
}

int KEYcompare(Key k1, Key k2) {
    return stcmp(k1, k2);
}

void ITEMshow(Item val) {
    printf("%s %d", val->name, val->num);
}

int ITEMless(Item val1, Item val2) {
    return (strcmp(KEYget(val1),KEYget(val2))<0);
}

int ITEMgreater(Item val1, Item val2) {
    return (strcmp(KEYget(val1),KEYget(val2))>0);
}

int ITEMgreater(Item val1, Item val2) {
    return (strcmp(KEYget(val1),KEYget(val2))==0);
}

Item ITEMsetvoid() {
    printf("Non è stato possibile creare l'item\n");
    return NULL;
}

int ITEMcheckvoid(Item val) {
    return val == NULL;
}

Item ITEMnew(void) {
    Item val;
    val = (Item) malloc(sizeof(*val));
    if (val == NULL)
        return ITEMsetvoid();
    val->name[0] = '\0';
    val->num = 0;
    return val;
}


void ITEMfree(Item val) {
    free(val);
}

Item ITEMscan() {
    Item val = ITEMnew();
    if (val != NULL)
        scanf("%s %d", val->name, &val->num);
    return val;
}