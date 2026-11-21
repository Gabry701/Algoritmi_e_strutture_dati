#include <stdio.h>
#include <stdlib.h>

typedef struct att_s
{
    int s, f;
} att;


/*
OPT(i): 
    opt(0) = durata(0);
    max(opt(i-1), opt(q[i]) + dur(val[i]))
*/



int readAtt(att **v, char *filename);
void swap(att *v, int i, int j);
int partition(att *v, int l, int r);
void quickSort(att *v, int l, int r);
int *compatibleActivities(att *v, int N);
int dur(att a);
int *maxDurata(att *v, int *q, int n);
void displayBestSol(att *v, int n);

int main (int argc, char *argv[]) {
    int N; 
    att *activities;

    N = readAtt(&activities, argv[1]);
    if (N == -1) return 1;
    displayBestSol(activities, N);
    free(activities);
}


void displayBestSol(att *v, int n) {
    int *sommeDurate, *q;
    int i;
    quickSort(v, 1, n);
    q = compatibleActivities(v, n);
    sommeDurate = maxDurata(v, q, n);
    i = n;
    // volendo si può usare un vettore sol per stamparale in ordine
    // crescente
    while (i >= 1) {
        if (sommeDurate[i-1] != sommeDurate[i]) {
            printf("(%d %d) ", v[i].s, v[i].f);
            i = q[i];
        } else i--;
    }
    free(q);
    free(sommeDurate);
}


int *maxDurata(att *v, int *q, int n) {
    int i, *opt;
    opt = calloc(n+1, sizeof(int));
    opt[0] = dur(v[0]); // anche = 0 andava bene
    for (i = 1; i <= n; i++) {
        if (opt[i-1] >= opt[q[i]] + dur(v[i]))
            opt[i] = opt[i-1];
        else
            opt[i] = opt[q[i]] + dur(v[i]);
    }
    printf("Durata massima: %d\n", opt[n]);
    return opt;
}


int *compatibleActivities(att *v, int N) {
    int *q;
    q = calloc(N+1, sizeof(int));
    for (int i = 1; i <= N; i++) {
        for (int j = i-1; j >= 0; j--)
            if (v[j].f <= v[i].s) {
                q[i] = j;
                break;
            }
    }
    return q;
}



int dur(att a) {
    return a.f - a.s;
}


void quickSort(att *v, int l, int r) {
    int q;
    if (l >= r)
        return;
    q = partition(v, l, r);
    quickSort(v, l, q-1);
    quickSort(v, q+1, r);
}

int partition(att *v, int l, int r) {
    int i = l-1, j = r;
    att x = v[r];
    for (;;) {
        while(v[++i].f < x.f);
        while(j > l && v[--j].f > x.f);
        if (i >= j)
            break;
        swap(v, i, j);
    }
    swap(v, i, r);
    return i;
}

void swap(att *v, int i, int j) {
    att tmp;
    tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
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
    // farle iniziare da 1 è più comodo
    // lascio in v[0] un elemento con s = 0, f = 0 => dur = 0
    *v = calloc(nAtt+1, sizeof(att));
    for (int i = 1; i <= nAtt; i++) 
        fscanf(fp, "%d %d\n", &((*v)[i].s), &((*v)[i].f));
    fclose(fp);
    return nAtt;
}
