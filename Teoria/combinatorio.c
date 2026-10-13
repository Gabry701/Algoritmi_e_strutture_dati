#include <stdio.h>




int main() {
    int val[4] = {4, 9, 1, 0};
}



int disp(int pos, int *val, int *sol, int *mark, int n, int k, int cnt) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = 0; i < n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            cnt = disp(pos+1, val, sol, mark, n, k, cnt);
            mark[i] = 0;
        }
    }
    return cnt;
}

int dispRip(int pos, int *val, int *sol, int n, int k, int cnt) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = 0; i < n; i++) {
            sol[pos] = val[i];
            cnt = disp(pos+1, val, sol, n, k, cnt);
    }
    return cnt;
}


int perm(int pos, int *val, int *sol, int *mark, int n, int cnt) {
    int i;
    if (pos >= n) {
        for (i = 0; i < n; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = 0; i < n; i++) {
        if (mark[i] == 0) {
            mark[i] = 1;
            sol[pos] = val[i];
            cnt = perm(pos+1, val, sol, mark, n, cnt);
            mark[i] = 0;
        }
    }
    return cnt;
}

int perm_r(int pos, int *val, int *sol, int *mark, int n, int cnt) {
    int i;
    if (pos >= n) {
        for (i = 0; i < n; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = 0; i < n; i++) {
        if (mark[i] > 0) {
            mark[i] --;
            sol[pos] = val[i];
            cnt = perm_r(pos+1, val, sol, mark, n, cnt);
            mark[i]--;
        }
    }
    return cnt;
}

int comb(int pos, int *val, int *sol, int n, int k, int start, int cnt) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = start; i < n; i++) {
        sol[pos] = val[i];
        cnt = comb(pos+1, val, sol, n, k, i+1, cnt);
    }
    return cnt;
}

int comb_r(int pos, int *val, int *sol, int n, int k, int start, int cnt) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = start; i < n; i++) {
        sol[pos] = val[i];
        cnt = comb(pos+1, val, sol, n, k, start, cnt);
        start++;
    }
    return cnt;
}