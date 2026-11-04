#include <stdio.h>
#include <stdlib.h>

#define filename "grafo.txt"

typedef struct arco_s {
    int v1, v2;
} Arco;



Arco *leggiGrafo(int *N, int *E);
int vertexCover(Arco *archi, int N, int E);
int vertexCover_impl(Arco *archi, int N, int E, int *sol, int j, int pos, int start);

int main() {
    int nArchi, nVertici;
    Arco *archi;
    archi = leggiGrafo(&nVertici, &nArchi);
    vertexCover(archi, nVertici, nArchi);
}

Arco *leggiGrafo (int *N, int *E) {
    FILE *fp;
    Arco *archi;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("errore nell'apertura del file");
        return NULL;
    }
    fscanf(fp, "%d %d", N, E);
    archi = malloc((*E)*sizeof(Arco));
    for (int i = 0; i < *E; i++) 
        fscanf(fp, "%d %d", &archi[i].v1, &archi[i].v2);
    fclose(fp);
    return archi;
}


int vertexCover(Arco *archi, int N, int E) {
    int cnt = 0, j;
    int *sol;
    sol = malloc(E*sizeof(int));
    for (j = 0; j <= E; j++) {
        cnt += vertexCover_impl(archi, N, E, sol, j, 0, 0);
    }
    free(sol);
    return cnt;
}

int vertexCover_impl(Arco *archi, int N, int E, int *sol, int j, int pos, int start) {
    int cnt = 0, i, included = 0;
    if (pos >= j) {
        for (i = 0; i < E; i++) {
            for (int k = 0; k < j; k++) {
                if (archi[i].v1 == sol[k] || archi[i].v2 == sol[k]) {
                    included += 1;
                    break;
                }
            }
        }
        if (included == E) {
            printf("{ ");
            for (i = 0; i < j; i++)
                    printf("%d ", sol[i]);
            printf("} \n");
            return 1;
        }
        return 0;
    }
    for (i = start; i < N; i++) {
        sol[pos] = i;
        cnt += vertexCover_impl(archi, N, E, sol, j, pos+1, i+1);
    }
    return cnt;
}
