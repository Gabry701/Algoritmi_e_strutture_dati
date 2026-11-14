#include <stdio.h>
#include <stdlib.h>

// se la condizione di incompatibità è: 
// s[i] < f[j] && s[j] < f[i] <=> L'insieme non è compatibile, 
// con De Morgan (-(a && b) = -a && -b):
// s[i] >= f[j] || s[j] >= f[i] <=> L'insieme è compatibile


typedef struct att_s
{
    int s, f;
} att;
int powerset(att *val, int n, att *current, att *maxSol, int maxDurata, int j, int pos, int start, int *len);
int readAtt(att **v, char *filename);
void attSel(int N, att *V);




int main (int argc, char *argv[]) {
    int N; 
    att *activities;
    N = readAtt(&activities, argv[1]);
    attSel(N, activities);
    // for (int i = 0; i < N; i++) {
    //     printf("%d %d\n", activities[i].s, activities[i].f);
    // }
}
int readAtt(att **v, char *filename) {
    FILE *fp;
    int nAtt;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("errore nell'apertura del file");
        return -1;
    }
    fscanf(fp, "%d\n", &nAtt);
    *v = malloc(nAtt*sizeof(att));
    for (int i = 0; i < nAtt; i++) 
        fscanf(fp, "%d %d\n", &((*v)[i].s), &((*v)[i].f));
    fclose(fp);
    return nAtt;
}

void attSel(int N, att *V) {
    att *sol, *temp;
    int max = 0, len = 0;
    sol = malloc(N*sizeof(att));
    temp = malloc(N*sizeof(att));
    for (int j = 0; j <= N; j++)
        max = powerset(V, N, temp, sol, max, j, 0, 0, &len);
    free(temp);
    for (int i = 0; i < len; i++)
        printf("(%d %d)  ", sol[i].s, sol[i].f);
    printf("\nDurata totale massima: %d", max);
    free(sol);
}


// si può implementare un semplice pruning dato dalla condizione che la durata massima è vincolata
// dall'upper bound max(f) - min(s) ma non credo che sia particolarmente impattante
int powerset(att *val, int n, att *current, att *maxSol, int maxDurata, int j, int pos, int start, int *len) {
    int i, durata = 0, skip;
    if (pos >= j) {
        for (i = 0; i < j; i++) durata += current[i].f - current[i].s;
        if (durata > maxDurata) {
            maxDurata = durata;
            *len = j;
            for (i = 0; i < j; i++)
                maxSol[i] = current[i];
        }
        return maxDurata;
    }
    for (i = start; i < n ; i++) {
        skip = 0;
        for (int k = 0; k < pos && !skip; k++) 
            if (current[k].s < val[i].f && val[i].s < current[k].f)
                skip = 1;
        if (!skip) {
            current[pos] = val[i];
            maxDurata = powerset(val, n, current, maxSol, maxDurata, j, pos+1, i+1, len);
        }
    }
    return maxDurata;
}