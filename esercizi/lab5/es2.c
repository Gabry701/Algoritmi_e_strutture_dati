#include <stdio.h>
#include <stdlib.h>

#define TILES_FILE "tiles.txt"
#define BOARD_FILE "board.txt"


typedef struct segmento_s
{
    char color;
    int score;
} segmento;

//purtroppo usa padding in più ma penso che 3byte per tile siano sacrificabili per 
// mantenere l'astrazione più ordinata
typedef struct tile_s {
    segmento v, h;
} tile, **board;


tile rot(tile t);
tile nullTile();
tile *getTiles(int *N, char *filename);
board buildBoard(int *r, int *c, char *filename, tile *tiles);
void showBoard(board b, int r, int c);
void showTile(tile t);
int isNullTile(tile t);
int getScore(board b, int r, int c);
int getBestSolution(int pos, board val, board sol, tile *t, int *mark, int maxScore, int r, int c, int n);
int bestBoard(board b, int r, int c, tile *t, int n);

int main() {
    tile *tiles;
    board b;
    int nTiles, r, c;
    tiles = getTiles(&nTiles, TILES_FILE);
    b = buildBoard(&r, &c, BOARD_FILE, tiles);

    bestBoard(b, r, c, tiles, nTiles);
}






int getBestSolution(int pos, board val, board sol, tile *t, int *mark, int maxScore, int r, int c, int n) {
    int i, j, k, currentScore = 0;
    if (pos >= r*c) {
        currentScore = getScore(val, r, c);
        if (currentScore > maxScore) {
            for (i = 0; i < r; i++)
                for (j = 0; j < c; j++)
                    sol[i][j] = val[i][j];
            maxScore = currentScore;
            printf("%d", maxScore);
        }
        return maxScore;
    }
    i = pos / c; 
    j = pos % c;
    if (!isNullTile(val[i][j])) {
        maxScore = getBestSolution(pos+1, val, sol, t, mark, maxScore, r, c, n);
        return maxScore;
    }
    for (k = 0; k < n; k++) {
        if (mark[k] == 0 && !isNullTile(t[k])) {
            mark[k] = 1;
            val[i][j] = t[k];
            maxScore = getBestSolution(pos + 1, val, sol, t, mark, maxScore, r, c, n);
            val[i][j] = rot(t[k]);
            maxScore = getBestSolution(pos + 1, val, sol, t, mark, maxScore, r, c, n);
            mark[k] = 0;
            val[i][j] = nullTile();
        }
    }
    return maxScore;
}

int bestBoard(board b, int r, int c, tile *t, int n) {
    board sol;
    int max = -1, count = 0;
    int *mark;
    mark = calloc(sizeof(int), 2*n);
    sol = malloc(r*sizeof(*sol));
    for (int i = 0; i < r; i++) {
        sol[i] = malloc(c*sizeof(tile));
    }
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            sol[i][j] = b[i][j];
        }
    max = getBestSolution(0, b, sol, t, mark, max, r, c, n);
    printf("Massimo punteggio ottenibile: %d\n", max);
    printf("Ecco una tabella con tale punteggio:\n");
    showBoard(sol, r, c);
}







void showTile(tile t) {
      printf("| %c | ", t.v.color);
        printf("\n");
        printf("|%c %d|  ", t.h.color, t.h.score);
        printf("\n");
        printf("| %d |  ", t.v.score);
}

void showBoard(board b, int r, int c) {
    for (int i = 0; i < r; i++) {
        printf("\n");
        for (int j = 0; j < c; j++) {
            if (isNullTile(b[i][j]))
                    printf("|       |  ");
            else
                printf("|   %c   |  ", b[i][j].v.color);
        }
        printf("\n");
        for (int j = 0; j < c; j++) {
            if (isNullTile(b[i][j]))
                printf("|       |  ");
            else
                printf("| %c   %2d|  ", b[i][j].h.color, b[i][j].h.score);
        }
        printf("\n");
        for (int j = 0; j < c; j++) {
            if (isNullTile(b[i][j]))
                printf("|       |  ");
            else
                printf("|  %2d   |  ", b[i][j].v.score);
        }
        printf("\n");
    }
}


int getScore(board b, int r, int c) {
    int score = 0, partialScore, equalColor = 0;
    for (int i = 0; i < r; i++) {
        partialScore = 0;
        equalColor = 0;
        for (int j = 0; j < c; j++) {
            if (j > 0 && b[i][j].h.color != b[i][j-1].h.color) {
                partialScore = 0;
                break;
            }
            partialScore += b[i][j].h.score;
        }
        score += partialScore;
    }
    for (int j = 0; j < c; j++) {
        partialScore = 0;
        equalColor = 0;
        for (int i = 0; i < r; i++) {
            if (i > 0 && b[i][j].v.color != b[i-1][j].v.color) {
                partialScore = 0;
                break;
            }
            partialScore += b[i][j].v.score;
        }
        score += partialScore;
    }
    return score;
}

tile rot(tile t) {
    segmento s;
    s = t.v;
    t.v = t.h;
    t.h = s;
    return t;
}

int isNullTile(tile t) {
    return t.h.score == -1;
}

tile nullTile() {
    tile t;
    t.v.color = t.h.color = '\0';
    t.v.score = t.h.score = -1;
    return t;
}

tile *getTiles(int *N, char *filename) {
    FILE *fp;
    tile *tiles;
    fp = fopen(filename, "r");
    if (fp == NULL) return NULL;
    fscanf(fp, "%d", N);
    tiles = malloc((*N)*sizeof(tile));
    for (int i = 0; i < *N; i++) {
        fscanf(fp, " %c %d %c %d",
            &(tiles[i].h.color), &(tiles[i].h.score),
            &(tiles[i].v.color), &(tiles[i].v.score) );
    }
    fclose(fp);
    return tiles;
}


board buildBoard(int *r, int *c, char *filename, tile *tiles) {
    FILE *fp;
    board b;
    int id, isRot;
    fp = fopen(filename, "r");
    if (fp == NULL) return NULL;
    fscanf(fp, "%d %d", r, c);
    b = malloc(sizeof(*b)*(*r));
    for (int i = 0; i < *r; i++) {
        b[i] = malloc((*c)*sizeof(tile));
        for (int j = 0; j < *c; j++) {
            fscanf(fp, "%d/%d ", &id, &isRot);
            if (id == -1 && isRot == -1)
                b[i][j] = nullTile();
            else {
                if (isRot == 0)
                    b[i][j] = tiles[id];
                else
                    b[i][j] = rot(tiles[id]);
                tiles[id] = nullTile();
            }
      
        }
    }
    fclose(fp);
    return b; 
}