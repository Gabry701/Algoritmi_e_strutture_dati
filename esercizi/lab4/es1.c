#include <stdio.h>
#include <stdlib.h>


typedef struct vertici_s {
    int *vAssociati;
    int numAssociati;
} Vertice;



int leggiGrafo(Vertice **v, char *filename, int *numArchi) {
    FILE *fp;
    int nVertici, nArchi;
    int v1, v2;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("errore nell'apertura del file");
        return EXIT_FAILURE;
    }
    fscanf(fp, "%d %d", &nVertici, &nArchi);
    *v = malloc(nVertici*sizeof(Vertice));
    for (int i = 0; i < nVertici; i++) {
        (*v)->vAssociati = malloc(nArchi*sizeof(int));
        (*v)->numAssociati = 0;
    }
    for (int i = 0; i < nArchi; i++) {
        if (fscanf(fp, "%d %d", &v1, &v2) == 2) {
            (*v)[v1].vAssociati[(*v)[v1].numAssociati++] = v2;
            (*v)[v2].vAssociati[(*v)[v2].numAssociati++] = v1;
        }
    }
    fclose(fp);
    return nVertici;
}


int elementNotInArray(int el, int *v, int k) {
    int count = 0;
    for (int i = 0; i < k; i++)
        if (el != v[k]) count++;
    if (count == k)
        return 1;
    return 0;
}


int isCompletedSet(Vertice *val, int *sol, int lenSol, int N) {
    int i;
    int seen[N];
    int completed = 0, count = 0;
    for (int i = 0; i < lenSol; i++) {
        for (int j = 0; j < val[sol[i]].numAssociati; j++)
            for (int k = 0; k < count; k++)
                if (val[sol[i]].vAssociati[j] == seen[k]) {
                    seen[count++] = val[sol[i]].vAssociati[j];
                    if (count == N) return 1;
                }
    }
    return 0;
}


int powersetFiltered(Vertice *val, int k, int *sol, int j, int pos, int start) {
    int cnt = 0, i;
    if (pos >= k) {
        if (isCompletedSet(val, sol, pos, k)) {
            printf("{");
            for (i = 0; i < j; i++)
                    printf("%d\t", i);
            printf("}\n");
        }
        return 1;
    }
    for (i = start; i < k; i++) {
        sol[pos] = i;
        cnt += powersetFiltered(val, k, sol, j, pos+1, i+1);
    }
    return cnt;
}



int vertexCover(Vertice *val, int k, int *sol) {
    int cnt = 0;
    sol = malloc(k*sizeof(int));
    for (int j = 0; j <= k; j++)
        cnt += powersetFiltered(val, k, sol, j, 0, 0);
    return cnt;
}



int main(int argc, char *argv[]) {
    Vertice *grafo;
    char *filename = argv[1];
    int *sol;
    int N;
    if ((N = leggiGrafo(&grafo, filename, sol)) == 0)
        return EXIT_FAILURE;
    vertexCover(grafo, N, sol);

    
}