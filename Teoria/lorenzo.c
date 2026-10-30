#include <stdio.h>
#include <ctype.h>

#define MAXS 50

char *cercaRegexp(char *src, char *regexp);

int main(){
    char * out;
    char src[MAXS],reg[MAXS];
    printf("Inserisci la stringa sorgente: "); scanf("%s",src);
    printf("Inserisci l\'espressione regolare: "); scanf("%s",reg);
    out = cercaRegexp(src,reg);
    if(out) printf("%s\n",out);
    else printf("Non trovato!\n");
    return 0; 
}

char *cercaRegexp(char *src, char *regexp){
    int indexSrc = 0, found = 0, i=0;
    int indexReg = 0, stay = 1, flagChParentesi;

    while(src[i] != '\0' && !found){

        found = 0;
        stay = 1;
        indexReg = 0;
        indexSrc = i;

        while(stay && regexp[indexReg] != '\0' && src[indexSrc] != '\0'){
            if(isalpha(regexp[indexReg])){ 
                if(src[indexSrc] != regexp[indexReg]) stay = 0;
                indexReg++;
            }
            else{//se non è un alfa allora c'è un metacarattere
                if(regexp[indexReg] == '.') indexReg++;//va bene qualsiasi carattere
                else if(regexp[indexReg] == '[' && regexp[indexReg+1] == '^'){
                    indexReg+=2;
                    flagChParentesi = 0;
                    while(regexp[indexReg] != ']'){
                        if(regexp[indexReg++] == src[indexSrc]) flagChParentesi = 1;
                    }
                    if(flagChParentesi) stay = 0;
                    indexReg++;
                }
                else if(regexp[indexReg] == '['){ 
                    indexReg++; 
                    flagChParentesi = 0;
                    while(regexp[indexReg] != ']'){
                        if(regexp[indexReg++] == src[indexSrc]) flagChParentesi = 1;
                    }
                    if(!flagChParentesi) stay = 0;
                    indexReg++;
                }
                else if(regexp[indexReg] == '\\' && regexp[indexReg+1] == 'a'){
                    if(isupper(src[indexSrc])) stay = 0;
                    indexReg+=2;
                }
                else if(regexp[indexReg] == '\\' && regexp[indexReg+1] == 'A'){
                    if(!isupper(src[indexSrc])) stay = 0;
                    indexReg+=2;
                }
            }
            if(stay) indexSrc++;
        }

        if(stay && regexp[indexReg] == '\0') found = 1; //se non ho mismatch e la regexp è stata consumata allora ho trovato l'occorrenza
        else i++;
    }

    if(found) return &src[i];
    return NULL;
}