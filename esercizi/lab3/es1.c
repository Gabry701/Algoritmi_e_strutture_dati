#include <stdio.h>



/*
IDEA:
    Se hai un vettore di un elemento, il maggioritario di quel vettore è l'elemento stesso.
    Si fanno quindi due ricorsioni (a destra e a sinistra) per trovare dei "candidati all'essere maggioritari".
    Alla fine di ogni ricorsione si controlla se uno dei 2 elementi dei vettori finali della ricorsione (quelli 
    dove N = 1, maggioritari per definizione), è maggioritario del sottovettore della ricorsione successiva. 
    Se non lo è, o lo è l'altro elemento trovato, o non esiste maggioritario (per cui si passa dx senza controlli).
    Alla fine la funzione restituisce il maggioritario trovato, il quale, però, è solo un candidato, in quanto
    la funzione non gestisce il return nel caso non ci sia maggioritario. Perciò nel wrapper si inserisce
    un ultimo ciclo for che controlla che il valore trovato sia effettivamente un maggioritario per il vettore.
    La complessità totale dell'algoritmo è O(NlogN).
*/

void majority(int *a, int N);
int majority_impl(int *a, int l, int r);


int main() {
    //testato su vari vettori
}

void majority(int *a, int N) {
    int l = 0, r = N-1, maj_candidate, occ = 0;
    maj_candidate = majority_impl(a, l, r);
    for (int j = 0; j < N; j++)
        if (maj_candidate == a[j]) occ++;
    if (occ > N/2)
        printf("Maggioritario: %d\n", maj_candidate);
    else
        printf("Non esiste maggioritario\n");
}

int majority_impl(int *a, int l, int r) {
    int c, maj, sx = -1, dx = -1, occ = 0;
    c = (l+r)/2;
    if (l == r) {
        return a[l]; 
    }
    sx = majority_impl(a, l, c);
    dx = majority_impl(a, c+1, r);
    for (int i = l; i <= r; i++) {
        if (sx == a[i]) occ++;
    }
    if (occ > (r-l+1)/2) 
        return sx;
    return dx;
}
