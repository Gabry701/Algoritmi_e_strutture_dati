#include <stdio.h>
#include <stdlib.h>

#define MAX_CANZONI 5
#define MAX_CHAR_TITOLO 256
#define filename "brani.txt"

typedef struct amico_s {
    char canzoni[MAX_CANZONI][MAX_CHAR_TITOLO];
    int numCanzoni;
} Amico;


Amico *leggiAmici (int *nAmici);
int moltPlaylist(int pos, Amico *val, int *sol, int dimPlaylist, int cnt);
int generatePlaylist(Amico *val, int nCanzoni, int dimPlaylist);


int main() {
    Amico *amici;
    int nAmici;
    amici = leggiAmici(&nAmici);
    generatePlaylist(amici, nAmici*5, nAmici);
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


int generatePlaylist(Amico *val, int nCanzoni, int dimPlaylist) {
    int pos = 0, cnt = 0;
    int *sol;
    sol = malloc(dimPlaylist*sizeof(int));
    moltPlaylist(pos, val, sol, dimPlaylist, cnt);
    free(sol);
    return cnt;
}

int moltPlaylist(int pos, Amico *val, int *sol, int dimPlaylist, int cnt) {
    int i;
    if (pos >= dimPlaylist) {
        printf("Playlist %d: ", cnt+1);
        for (i = 0; i < dimPlaylist; i++)
            printf("%s, ", val[i].canzoni[sol[i]]);
        printf("\n"); 
        return cnt+1;
    }
    for (i = 0; i < val[pos].numCanzoni; i++) {
        sol[pos] = i;
        cnt = moltPlaylist(pos+1, val, sol, dimPlaylist, cnt);
    }
    return cnt;
}