#include <stdio.h>

int disp(int pos, int *val, int *sol, int *mark, int n, int k, int cnt);
int dispRip(int pos, int *val, int *sol, int n, int k, int cnt);
int perm(int pos, int *val, int *sol, int *mark, int n, int cnt);
int permRip(int pos, int *val, int *sol, int *mark, int n, int cnt);
int comb(int pos, int *val, int *sol, int n, int k, int start, int cnt);
int combRip(int pos, int *val, int *sol, int n, int k, int start, int cnt);
int powerset_r(int pos, int *val, int *sol, int k, int start, int cnt);
int powerset_d(int pos, int *val, int *sol, int k, int cnt);
int powerset_c(int *val, int k, int *sol);
int powerset_impl(int *val, int k, int *sol, int j, int pos, int start);
void SP_rec(int n,int m,int pos,int *sol,int *val);
void SP_rec_all(int n, int k, int m, int pos, int *sol, int *val);


int main() {
    int val[4] = {4, 9, 1, 0};
    int sol[4];
    int mark[4];
    
}


//DISPOSIZIONI SEMPLICI
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

//DISPOSIZIONI RIPETUTE
int dispRip(int pos, int *val, int *sol, int n, int k, int cnt) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = 0; i < n; i++) {
            sol[pos] = val[i];
            cnt = dispRip(pos+1, val, sol, n, k, cnt);
    }
    return cnt;
}

//PERMUTAZIONI SEMPLICI
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

//PERMUTAZIONI RIPETUTE
int permRip(int pos, int *val, int *sol, int *mark, int n, int cnt) {
    int i;
    if (pos >= n) {
        for (i = 0; i < n; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = 0; i < n; i++) {
        if (mark[i] > 0) {
            mark[i]--;
            sol[pos] = val[i];
            cnt = permRip(pos+1, val, sol, mark, n, cnt);
            mark[i]--;
        }
    }
    return cnt;
}

//COMBINAZIONI SEMPLICI
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

//COMBINAZIONI RIPETUTE
int combRip(int pos, int *val, int *sol, int n, int k, int start, int cnt) {
    int i;
    if (pos >= k) {
        for (i = 0; i < k; i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for (i = start; i < n; i++) {
        sol[pos] = val[i];
        cnt = combRip(pos+1, val, sol, n, k, start, cnt);
        start++;
    }
    return cnt;
}

//POWERSET RICORSIVO
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

//POWERSET CON DISPOSIZIONI RIPETUTE
int powerset_d(int pos, int *val, int *sol, int k, int cnt)
{
    int j;
    if (pos >= k) {
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

//POWERSET CON COMBINAZIONI SEMPLICI (WRAPPER)
int powerset_c(int *val, int k, int *sol) {
    int cnt = 0, j;
    printf("{}\n");
    cnt++;
    for (j = 1; j <= k; j++)
        cnt = powerset_impl(val, k, sol, j, 0, 0);
    return cnt;
}
    //POWERSET CON COMBINAZIONI SEMPLICI (IMPLEMENTATION)
    int powerset_impl(int *val, int k, int *sol, int j, int pos,  int start) {
        int cnt = 0, i;
        if (pos >= k) {
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

//ALGORITMO DI ER TRA IN (1,n)
void SP_rec(int n,int m,int pos,int *sol,int *val) {
    int i, j;
    if (pos >= n) {
        printf("partizione in %d blocchi: ", m);
        for (i=0; i<m; i++) {
            printf("{ ");
            for (j=0; j<n; j++)
                if (sol[j]==i)
                    printf("%d ", val[j]);
            printf("} ");
        }
        printf("\n");
        return;
    }
    for (i=0; i<m; i++) {
        sol[pos] = i;
        SP_rec(n, m, pos+1, sol, val);
    }
    sol[pos] = m;
    SP_rec(n, m+1, pos+1, sol, val);
}

//ALGORITMO DI ER PER TUTTE LE PARTIZIONI
void SP_rec_all(int n, int k, int m, int pos, int *sol, int *val) {
    int i, j;
    if (pos >= n) {
        if (m == k) {
            for (i=0; i<m; i++)
                for (j=0; j<n; j++)
                    if (sol[j]==i)
                        printf("%d ", val[j]);
        printf("\n");
        }
    return;
    }
    for (i=0; i < m; i++) {
        sol[pos] = i;
        SP_rec_all(n, k, m, pos+1, sol, val);
    }
    sol[pos] = m;
    SP_rec_all(n, k, m+1, pos+1, sol, val);
} 