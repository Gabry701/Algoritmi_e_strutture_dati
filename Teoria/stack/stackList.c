#include <stdlib.h>
#include "stackList.h"

typedef struct STACKnode *link;
struct STACKnode {Item val; link next;};

struct stack {link head;};

static link NEW (Item val, link next) {
    link x = malloc(sizeof(*x));
    x->val = val; x->next = next;
    return x;
}

//maxN passato per uniformità, la lista è illimitata ma all'utente non importa sapere se lo
// stack è una lista o un vettore
void STACKinit (int maxN) {
    STACK s = malloc(sizeof(*s));
    s->head = NULL;
    return s;
}

int STACKempty (STACK s) {
    s->head == NULL;
}


void STACKpush (STACK s, Item val) {
    s->head = NEW(val, s->head);
}

Item STACKpop(STACK s) {
    Item tmp;
    link t; 
    
    tmp = s->head->val;
    t = s->head->next;

    free(s->head);
    s->head = t;
    return tmp;
}
