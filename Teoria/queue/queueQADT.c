#include <stdlib.h>
#include "queueQADT.h"

static Item *q;
static int N, head, tail;

// si usa un versore circolare 
// si allocano N+1 elementi così tail sarà sempre al massimo
// head-1 (e viceversa)

//si usa %N per ritornare all'inizio (o fine) del vettore circolare

void QUEUEinit(int maxN) {
    q = malloc((maxN+1)*sizeof(Item));
    N = maxN+1;
    head = N; tail = 0;
}

int QUEUEempty() {
    return head%N == tail;
}

void QUEUEput(Item val) {
    q[tail++] = val;
    tail = tail%N; 
}

Item QUEUEget() {
    head = head%N;
    return q[head++];
}
