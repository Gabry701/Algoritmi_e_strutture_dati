#include <stdio.h>
#include <stdlib.h>

typedef int Key;

typedef struct item {
    char nome[20];
    int age;
    Key id;
} item_t;

typedef struct node node_t, *link;
struct node {
    item_t val;
    link next;
};


int isGreater(Key k1, Key k2) {
    if (k1 > k2) return 1;
    return 0;
}

int main() {
    link x,t;
    x = malloc(5*sizeof(node_t));
    x->next = NULL;
    t->next = x->next;
    x->next = t;
}