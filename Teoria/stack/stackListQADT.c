#include <stdlib.h>
#include "stackListQADT.h"

typedef struct STACKnode *link;
struct STACKnode {Item val; link next;};

static link head;

static link NEW (Item val, link next) {
    link x = malloc(sizeof(*x));
    x->val = val; x->next = next;
    return x;
}

//maxN passato per uniformità, la lista è illimitata ma all'utente non importa sapere se lo
// stack è una lista o un vettore
void STACKinit (int maxN) {
    head = NULL;
}

int STACKempty () {
    return head == NULL;
}


void STACKpush (Item val) {
    head = NEW(val, head);
}

Item STACKpop() {
    Item tmp;
    link t; 
    
    tmp = head->val;
    t = head->next;

    free(head);
    head = t;
    return tmp;
}