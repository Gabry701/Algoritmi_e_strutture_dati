#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 4

/*
REGEXP:
prendiamo le stringhe valide ['Moto', 'moto', 'voto', 'noto']
'.' = trova ogni carattere -> .oto => 'voto', 'moto', 'noto', 'Moto'
'[x]' = trova i caratteri tra parentesi -> [mn]oto => 'moto', 'noto'.
'[^x]' = trova tutti i caratteri tranne quelli da parentesi -> [^mn]oto = 'voto'
'\a' = trova un carattere minuscolo -> \aoto => 'voto', 'moto', 'noto'
'\A' = trova un carattere maiuscolo -> \Aoto => 'Moto'
*/

/*
APPROCCIO: creo una lista che contiene in ogni nodo una espressione regex (del tipo token) tra quelle scritte prima, ossia:
    - '.' -> val = NULL, type = ALL
    - '[x]' -> val = x, type = INCLUDE
    - '[^x]' -> val = x, type = EXCLUDE
    - '\a' -> val = NULL, type = LOWERCASE
    - '\A' -> val = NULL, type = UPPERCASE
    - qualunque altro carattere -> val = il carattere,   
*/


typedef enum {ALL, INCLUDE, EXCLUDE, LOWERCASE, UPPERCASE, DEFAULT} Type;
typedef enum {IN_BRACKET, EX_BRACKET} BracketType;

//def tipo token
typedef struct tokenType {
    char *val;
    Type type;
} token_t;

typedef struct nodeType node_t, *link;
struct nodeType {
    token_t tk;
    link next;
};


link newNode(token_t val, link next);
void insNewNode(link *h, link *t, token_t val);
void freeListOfTokens(link h);
link tokenizeRegexp(char *rgxp, int* nodeCount);
int compareRegChar(link node, char c);
char *cercaRegexp(char *src, char *regexp);



int main(int argc, char *argv[]) {
    char *src, *regexp, *found;
    src = argv[1];    
    regexp = argv[2];
    found = cercaRegexp(src, regexp);
    
    printf("%s", found);
}






//funzioni per la gestione della lista
link newNode(token_t val, link next) {
    link x = malloc(sizeof(*x));
    if (x == NULL) return NULL;
    x->tk = val;
    x->next = next;
    return x;
}

void insNewNode(link *h, link *t, token_t val) {
    if (*h == NULL)
        *h = *t = newNode(val, NULL);
    else {
        (*t)->next = newNode(val, NULL);
        *t = (*t)->next;
    }
}

void freeListOfTokens(link h) {
    if (h == NULL) return;
    freeListOfTokens(h->next);
    free(h->tk.val);
    free(h);
}


link tokenizeRegexp(char *rgxp, int* nodeCount) {
    link head = NULL, tail = NULL;
    char *p;
    int dimValue;
    BracketType currentBracketType;
    token_t token;
    for (p = rgxp; *p != '\0'; p++) {
        switch (*p) {
        // se il carattere della regexp è '.' crea un nodo con all'interno type ALL;
        case '.':
            token.val = NULL;
            token.type = ALL;
            break;
        //se è la [ controlla i due casi
        case '[':
            dimValue = 0;
            if (*(++p) == '^') {
                currentBracketType = EX_BRACKET;
            }
            else
                currentBracketType = IN_BRACKET;
            p += currentBracketType;
            for (char *pp = p; (*pp)!=']'; dimValue++, pp++);
            token.val = malloc(dimValue+1);
            for (int i = 0; i < dimValue; i++) {
                token.val[i] = *(p+i);
            }
            token.val[dimValue] = '\0';
            p += dimValue;

            if (currentBracketType == IN_BRACKET) 
                token.type = INCLUDE;
            else 
                token.type = EXCLUDE;
            
            break;
        case '\\':
            token.val = NULL;
            if (*(++p) == 'a')
                token.type = LOWERCASE;
            else 
                token.type = UPPERCASE;
            break;
        default:
            token.val = malloc(2);
            token.val[0] = *p;
            token.val[1] = '\0';
            token.type = DEFAULT;
            break;
        }
        insNewNode(&head, &tail, token);
        (*nodeCount)++;
    }
    return head;
}

int compareRegChar(link node, char c) {
    switch (node->tk.type) {
        case ALL:
            return 1;
        case INCLUDE:
            for (char *p = node->tk.val; *p != '\0'; p++)
                if (*p == c) return 1;
            return 0;
        case EXCLUDE:
            for (char *p = node->tk.val; *p != '\0'; p++)
                if (*p == c) return 0;
            return 1;
        case UPPERCASE:
            if (c >= 'A' && c <= 'Z') return 1;
            return 0;
        case LOWERCASE:
            if (c >= 'a' && c <= 'z') return 1;
            return 0;
        case DEFAULT:
            if (c == node->tk.val[0]) return 1;
            return 0;
    }
}



char *cercaRegexp(char *src, char *regexp) {
    int len, matchCount = 0;
    link list, head;
    char *solution;
    head = tokenizeRegexp(regexp, &len);
    list = head;
    solution = malloc(len+1);
    for (char *p = src; *p != '\0' && matchCount < len; p++) {
        if (compareRegChar(list, *p)) {
            list = list->next;
            solution[matchCount++] = *p;
        } else {
            list = head;
            matchCount = 0;
        }
    }
    freeListOfTokens(head);

    if (matchCount >= len) {
        solution[len] = '\0';
        return solution;
    }
    free(solution);
    return NULL;
}

