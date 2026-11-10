/*
COME UTILIZZARE IL PROGRAMMA:
    Durante lo sviluppo, notando i tempi ingenti di esecuzione della versione con pruning
    limitato, ho pensato a come ottimizzare la soluzione.
    Tuttavia, un'intuizione mi ha portato a sviluppare un algoritmo che non usa i principi
    del calcolo combinatorio. L'esercizio non specifica di "implementare" un modello combinatorio
    ma dice di identificarlo, perciò, dato che la prima stesura del programma implementava un modello
    di calcolo combinatorio (permutazioni con ripetizione), lo lascio come opzione per l'utente.
    Dati i tempi di calcolo molto superiori della versione ottimizzata (che sfrutta, tra le altre
    cose, l'indicazione di trovare una SINGOLA soluzione) ho deciso di lasciarla nel programma.
    Pertanto, l'esecuzione del programma farà uso di flag passati in argv[]:
    Esecuzione: E03 <file.txt> -c oppure E03 <file.txt> -o
    -c sta per combinatorio, ossia il programma userà la funzione combinatoria implementata.
    -o sta per ottimizzato, perciò il programma userà la funzione ottimale ma non combinatoria.
*/



#include <stdio.h>
#include <stdlib.h>

/*
    z -> z || r
    r -> s || t
    t -> z || r
    s -> s || t
*/

#define NUM_TIPI 4
#define MAX_LINE 256

typedef struct pietra_s {
  char type;
  int quantity;
} Pietra;

int permRipPietre(int pos, Pietra* val, char* sol, char* currentMax, int n, char last, int len, int maxLen);
int collana(Pietra* val, int N);
int isValidPietra(char prev, char current);
void swap(Pietra *a, Pietra *b);
int test(Pietra v[], int N, char *filename, char exeType);
int collanaOpt(Pietra* val, int N);

int main(int argc, char *argv[]) {
    Pietra pietre[NUM_TIPI];
    test(pietre, NUM_TIPI, argv[1], argv[2][1]);
     
}


int test(Pietra v[], int N, char *filename, char exeType) {
    FILE *fp;
    int testNum, len;
    Pietra temp;
    fp = fopen(filename, "r");
    fscanf(fp, "%d", &testNum);
    for (int i = 1; i <= testNum; i++) {
            printf("Test #%d\n", i);
            fscanf(fp, "%d %d %d %d", 
                &v[3].quantity, &v[0].quantity, &v[1].quantity, &v[2].quantity);
            // per la versione ottimizzata viene più comodo avere la configurazione in cui
            // z ed s sono gli ultimi
            v[3].type = 'z'; v[0].type = 'r'; v[1].type = 't'; v[2].type = 's';
            for (int i = 0; i < N; i++)
                printf("%c %d  ", v[i].type, v[i].quantity);
            printf("\n");
            if (exeType == 'c')
                len = collana(v, N);
            else
                len = collanaOpt(v, N);
    }    
    fclose(fp);
    return 1;
}

void swap(Pietra *a, Pietra *b) {
    Pietra temp;
    temp = *a;
    *a = *b;
    *b = temp;    
}


int collana(Pietra* val, int N) {
  char *sol, *cMax;
  int totPietre = 0;
  int len = 0, pos = 0;
  for (int i = 0; i < N; i++) totPietre += val[i].quantity;
  if (totPietre == 0) {
    printf("collana di lunghezza massima: [ ]\n");
    return len;
  }
  sol = malloc(totPietre);
  cMax = malloc(totPietre);
  len = permRipPietre(pos, val, sol, cMax, N, 0, len, totPietre);
  printf("lunghezza: %d \n", len);
  for (int i = 0; i < len; i++) {
        printf("%c ", sol[i]);
  }
  printf("\n\n");
  free(sol);
  return len+1;
}

int permRipPietre(int pos, Pietra* val, char* sol, char* currentMax, int n, char last, int len, int maxLen) {
  int i, continua = 0;
  for (i = 0; i < n; i++)
        if(isValidPietra(last, val[i].type) && val[i].quantity > 0)
            continua = 1;
  if (pos > len && !continua) {

        for (i = 0; i < pos; i++)
            sol[i] = currentMax[i];
        return pos;
  }
  if (!continua)
    return len;
  for (i = 0; i < n; i++) {
    if (val[i].quantity > 0 && isValidPietra(last, val[i].type)) {
      val[i].quantity--;
      currentMax[pos] = val[i].type;
      len = permRipPietre(pos + 1, val, sol, currentMax, n, currentMax[pos], len, maxLen);
      if (len == maxLen) return len;
      val[i].quantity++;
    }
  }
  return len;
}

// suppongo che (per ora è un ragionamento intuitivo, dovrei verificarlo 
// con più rigore) se ho una collana di forma z-z-...-z-z-r-s-s-s-s-...
// dove ho già esaurito s e z, (posta l'esistenza di un rubino, se no si inizia dal
// vettore al contrario con t al posto di r), crei l'inizio della collana massima.
// se non ci sono t e non ci sono r, invece la collana massima sarà il massimo tra s e z
// dato che queste due catene non potranno mai essere collegate.
// Importante è, infine, se sono disponibili sia r che t, mettere quello disponibile in maggior
// quantità al centro della catena di smeraldi e zaffiri
// Da questa deduzione (che suppongo vera) si può riscrivere un algoritmo molto più efficiente:


int collanaOpt(Pietra* val, int N) {
    // ricordiamo la corrispondenza indici-pietra:
    // [0]: r , [1]: t , [2]: s, [3]: z
    char *sol;
    int totPietre = 0;
    int pos = 0, currentPos = 0;
    int first, middle, last, end;
    int insertMiddle = 0, max;
    for (int i = 0; i < N; i++) totPietre += val[i].quantity;
    if (totPietre == 0) {
        printf("collana di lunghezza massima: [ ]\n");
        return 0;
    }
    //caso |r| == 0 && |t| == 0
    if (val[1].quantity == 0 && val[0].quantity == 0) {
        if (val[2].quantity > val[3].quantity) 
            max = 2;
        else 
            max = 3;
        for (int i = 0; i < val[max].quantity; i++) 
            printf("%c ", val[max].type);
        printf("\n");
        return val[max].quantity;
    }
    // caso |r| != 0 && |t| == 0
    if (val[0].quantity > 0 && val[1].quantity > 0) {
        if (val[0].quantity > val[1].quantity) 
            max = 0;
        else max = 1;
        if (max) {
            first = 2; //smeraldo
            middle = 1; //topazio
            last = 3; //zaffiro
            end = 0; //rubino
        } else {
            first = 3; //zaffiro
            middle = 0; //rubino
            last = 2; //smeraldo
            end = 1; // topazio  
        }
      
    }
    else if (val[0].quantity > 0) {
        first = 3; //zaffiro
        middle = 0; //rubino
        last = 2; //smeraldo
        end = 1; // topazio  
    }
    else {
        first = 2; //smeraldo
        middle = 1; //topazio
        last = 3; //zaffiro
        end = 0; //rubino
    }

    sol = malloc(totPietre);
 
    // inserisci zaffiri/smeraldi
    for (pos = 0; pos < val[first].quantity; pos++) 
        sol[pos] = val[first].type;
    // inserisci un rubino/topazio
    sol[pos++] = val[middle].type;
    val[middle].quantity--;
    // inserisci gli smeraldi/zaffiri
    currentPos = pos;
    for (; pos < currentPos + val[last].quantity; pos++) {
        sol[pos] = val[last].type; 
    }

    //inserisci un topazio/rubino se si può
    if (val[end].quantity > 0) {
        // ora basta alternare r e t finchè uno dei 2 non finisce
        for (pos; pos < totPietre; pos++, insertMiddle = !insertMiddle) {
            if (val[middle].quantity == 0 && insertMiddle)
                break;
            if (val[end].quantity == 0 && !insertMiddle)
                break;
            if (insertMiddle) {
                sol[pos] = val[middle].type;
                val[middle].quantity--; 
            }
            else {
                sol[pos] = val[end].type;
                val[end].quantity--; 
            }
            
        }
    }
    
    printf("lunghezza: %d \n", pos);
    for (int i = 0; i < pos; i++) {
            printf("%c ", sol[i]);
    }
    printf("\n\n");
    free(sol);
    return pos;
}



int isValidPietra(char prev, char current) {
  switch (prev) {
    case 0:
      return 1;
    case 'z':
    case 't':
      return (current == 'z' || current == 'r');
    case 's':
    case 'r':
      return (current == 's' || current == 't');
    default:
      printf("tipo di pietra non valido");
      return -1;  // considererò, tuttavia, il vettore con i tipi corretti
  }
}