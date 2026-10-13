#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int **malloc2dR(char *filename, int *nr, int *nc);
void separa(int **mat, int nr, int nc, int **vBianche, int **vNere, int *nNere, int *nBianche);
int main(int argc, char *argv[]) {
    int nr, nc;
    int **mat;
    int *vB, *vN, nNere, nBianche;
    mat = malloc2dR(argv[1], &nr, &nc);
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
    separa(mat, nr, nc, &vB, &vN, &nNere, &nBianche);
    printf("Caselle bianche: ");
    for (int i = 0; i < nBianche; i++)
        printf("%d ", vB[i]);
    printf("\nCaselle Nere: ");
    for (int j = 0; j < nNere; j++)
        printf("%d ", vN[j]);
}


int **malloc2dR(char *filename, int *nr, int *nc) {
    int **mat;
    FILE *fp;
    fp = fopen(filename, "r");
    fscanf(fp, "%d %d\n", nr, nc);
    mat = malloc(sizeof(int*)*(*nr));
    for (int i = 0; i < (*nr); i++) {
        mat[i] = malloc(sizeof(int)*(*nc));
        for (int j = 0; j < (*nc); j++) {
            fscanf(fp, "%d", &mat[i][j]);
        }
    }
    return mat;
}

void separa(int **mat, int nr, int nc, int **vBianche, int **vNere, int *nNere, int *nBianche) {
    int isWhite = 1;
    int b = 0, n = 0;
    *nBianche = *nNere = (nr*nc)/2;
    if ((nr*nc) % 2 != 0)
        (*nBianche)++;
    *vBianche = malloc((*nBianche)*sizeof(int));
    *vNere = malloc((*nNere)*sizeof(int));
    for (int i = 0; i < nr; i++) {
        for (int j = 0; j < nc; j++) {
            if (isWhite) 
                (*vBianche)[b++] = mat[i][j];
            else
                (*vNere)[n++] = mat[i][j];
            isWhite = !isWhite;
        }
    }
}