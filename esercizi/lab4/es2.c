#include <stdio.h>
#include <stdlib.h>

#define MAX_CANZONI 5
#define MAX_CHAR_TITOLO 256
#define filename "brani.txt"

typedef struct amico_s {
    char canzoni[MAX_CANZONI][MAX_CHAR_TITOLO];
    int numCanzoni;
} Amico;


void printAmici(Amico *amici, int nAmici);
Amico *leggiAmici (int *nAmici);


int main() {
    Amico *amici;
    int nAmici;
    amici = leggiAmici(&nAmici);
    printAmici(amici, nAmici);
}




void printAmici(Amico *amici, int nAmici) {
    for (int i = 0; i < nAmici; i++) {
        printf("%d\n", amici[i].numCanzoni);
        for (int j = 0; j < amici[i].numCanzoni; j++) 
            printf("%s\n", amici[i].canzoni[j]);
        printf("\n");
    }
    
}


Amico *leggiAmici (int *nAmici) {
    Amico *amici;
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("errore nell'apertura del file");
        return NULL;
    }
    fscanf(fp, "%d", nAmici);
    amici = malloc((*nAmici) * sizeof(Amico));
    for (int i = 0; i < *nAmici; i++) {
        fscanf(fp, "%d", &(amici[i].numCanzoni));
        for (int j = 0; j < amici[i].numCanzoni; j++)
            fscanf(fp, "%255s", amici[i].canzoni[j]);
    }
    return amici;
}