#include <stdlib.h>
#include "stackQADT.h"


// globali per semlicità, in questo caso si ha un solo item
static Item *s;
static int N;

void STACKinit(int maxN) {
    s = malloc(maxN*sizeof(Item));
    N = 0;
}

int STACKempty() {
    return N == 0;
}

void STACKpush(Item val) {
    s[N++] = val;
}

Item STACKpop() {
    return s[--N];
}

