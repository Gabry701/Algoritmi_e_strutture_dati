#include <stdio.h>



/*
IDEA:
se hai un vettore di un elemento, il maggioritario di quel vettore è l'elemento stesso.
Se hai un maggioritario allora esisterà almeno una coppia nella quale ci sono 2 elementi del maggioritario vicini.
Perciò se lo dividi in coppie ed esiste un maggioritario, avrai sempre una coppia del maggioritario.
ossia, dividendo in sx e dx, se sx == dx := x allora x sarà un possibile maggioritario.
ECCEZIONE: l'unica eccezione è se il vettore è della forma v[m] = {a, n1, a, n2, a, ..., a} con m dispari, a maggioritario e
    n1, n2, nm naturali eventualmente distinti, in questo caso non si hanno coppie di maggioritari, perciò si pone *excess = sx,
    il quale metterà sempre a tra i 2 maj da controllare (andava bene anche *excess = dx perchè a è simmetrico in v)
se invece sono diversi possiamo tranquillamente scartare quei numeri (maj = -1) perchè, se esiste un maggioritario tanto 
    si verifica la condizione precedente (e quindi l'informazione del maggioritario la abbiamo da quella).
L'unico caso scomodo è se alla fine si hanno 2 papabili maggioritari, ossia quando, ritornando alla dimensione n si ha
    sx != dx != -1. In questo caso il modo più facile per vedere in un colpo solo quale dei due è il possibile maggioritario
    è applicare la condizione dalla definizione, ossia se il possibile maggioritario è presente per più di N/2 volte nel vettore,
    a entrambi i valori trovati.
Si introduce quindi una variabile excess (maggioritario in eccesso), passata by pointer così che la funzione 
    possa returnare 2 variabili (i 2 maj) nella quale verrà messo uno dei 2 valori nel caso sx != dx != -1
Alla fine si scorre il vettore una sola volta, incrementando le occorrenze dei due possibili maggioritari (se excess = -1 penso
    si possa pure evitare di controllare la condizione ma essendo solo un if che returna falso penso sia trascurabile) finchè 
    occ1 || occ2 > N/2. In tal il maj di quella occ è il maggioritario cercato.
Nel caso nessuno dei 2 maggioritari abbia occorrenze > N/2 non esiste il maggioritario.
Data la natura di questa ricorsione non serve adattarla per N != 2^k perchè, nel caso, la ricorsione semplicemente
    continuerà in rami successivi finchè non raggiunge la condizione di terminazione (l==r).
L'algoritmo ha una complessità O(n) in quanto si ha 
- divide = calcolo del nuovo centro O(1)
- ricorsione con legge T(n) = 2T(n/2) -> O(n)
- ricombinazione = comparazioni di variabili O(1)
- ciclo del vettore una volta per vedere il numero delle occorrenze O(n)
sommando tutto (trascurando gli O(1)) si ha O(n) + O(n) = O(n), rendendolo un algoritmo lineare.

*/

void majority(int *a, int N);
int majority_impl(int *a, int l, int r, int *excess);


int main() {
    //vettore di esempio, testato su vari vettori
    int v[7] = {5, 1, 5, 2, 5, 3, 5};

    majority(v, 7);
}

void majority(int *a, int N) {
    int l = 0, r = N-1, maj_candidate1, maj_candidate2 = -1, occ1 = 0, occ2 = 0;
    maj_candidate1 = majority_impl(a, l, r, &maj_candidate2);
    for (int i = 0; i < N; i++) {
        if (a[i] == maj_candidate1) occ1++;
        if (a[i] == maj_candidate2) occ2++;
    }
    if (occ1 > N/2) printf("Maggioritario: %d", maj_candidate1);
    else if (occ2 > N/2) printf("Maggioritario: %d", maj_candidate2);
    else printf("Non esiste maggioritario");
}

int majority_impl(int *a, int l, int r, int *excess) {
    int c, maj, sx = -1, dx = -1;
    c = (l+r)/2;
    if (l == r) {
        return a[l]; 
    }
    sx = majority_impl(a, l, c, excess);
    dx = majority_impl(a, c+1, r, excess);
    if (sx == dx)
        return sx;
    if (sx == -1)
        return dx;
    if (dx == -1)
        return sx;
    *excess = sx;
    return dx;
}
