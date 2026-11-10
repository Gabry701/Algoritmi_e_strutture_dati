#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "..\item.h"


typedef struct pqueue *PQ;
PQ PQinit(int maxN);
int PQempty(PQ pq);
void PQinsert(PQ pq, Item data);
Item PQextractMax(PQ pq);
Item PQshowMax(PQ pq);
void PQdisplay(PQ pq);
void PQchange(PQ pq, Item data);

#endif