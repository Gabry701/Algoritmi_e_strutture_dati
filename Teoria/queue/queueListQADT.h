#ifndef QUEUE_H
#define QUEUE_H

#include "..\item.h"


void QUEUEinit(int maxN);
int QUEUEempty();
void QUEUEput(Item val);
Item QUEUEget();

#endif