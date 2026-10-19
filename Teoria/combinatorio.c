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

int powerset_r(int pos, int *val, int *sol, int k, int start, int cnt) {
    int i;
    if (start >= k) {
        for (i = 0; i < pos; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = start; i < k; i++) {
        sol[pos] = val[i];
        cnt = powerset_r(pos+1, val, sol, k, i+1, cnt);
        start++;
    }
    cnt = powerset_r(pos+1, val, sol, k, k, cnt);
    return cnt;
}

int powerset_d(int pos, int *val, int *sol, int k, int cnt)
{
    int j;
    if (pos >= k)
    {
        printf("{\t");
        for (j = 0; j < k; j++)
            if (sol[j] != 0)
                printf("%d \t", val[j]);
        printf("} \n");
        return cnt + 1;
    }
    sol[pos] = 0;
    cnt = powerset_d(pos + 1, val, sol, k, cnt);
    sol[pos] = 1;
    cnt = powerset_d(pos + 1, val, sol, k, cnt);
    return cnt;
}

int powerset_c(int *val, int k, int *sol) {
    int cnt = 0, j;
    printf("{}\n");
    cnt++;
    for (j = 1; j <= k; j++)
        cnt = powerset_impl(val, k, sol, j, 0, 0);
    return cnt;
}

int powerset_impl(int *val, int k, int *sol, int j, int pos,  int start) {
    int cnt = 0, i;
    if (pos >= k)
    {
        printf("{\t");
        for (i = 0; i < j; i++)
            if (sol[i] != 0)
                printf("%d \t", val[i]);
        printf("} \n");
        return 1;
    }
    for (i= start; i < k; i++) {
        sol[pos] = val[i];
        cnt += powerset_impl(val, k, sol, j, pos+1, i+1);
    }
        return cnt;
}