#include "stack.h"


struct stack {Item *s; int N};


STACK STACKinit (int maxN) {
    STACK sp = malloc(sizeof(*sp));
    sp->s = malloc(maxN*sizeof(Item));
    sp->N = 0;
    return sp;
}

int STACKempty(STACK sp) {
    return sp->N == 0;
}

void STACKpush(STACK sp, Item val) {
    sp->s[sp->N++] = val;
}

Item STACKpop(STACK sp) {
    return sp->s[--(sp->N)];
}
