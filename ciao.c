#include <stdio.h>
#include <stdlib.h>

int main() {
    float *v; 
    int n;
    printf("N? ");
    scanf("%d", &n);
    v = (float *) malloc(n*sizeof(float));
    printf("inserisci gli elementi: ");
    for (int i = 0; i < n; i++) {
        printf("elemento %d: ", i+1);
        scanf("%f", (v+i));
    }
    for (int i = n-1; i >= 0; i--)
        printf("%f ", *(v+i));
    free(v);
    

}