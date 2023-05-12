#include <stdio.h>
#include <stdlib.h> 
#define MAX_WIDTH_ARR 2000
int compare(const void* x, const void* y) {
    int el1 = *(const int*)x;
    int el2 = *(const int*)y;
    if (el1 < el2) return -1;
    if (el1 > el2) return 1;
    return 0;
}
int main() {
    int prvek, indexPrvku = 0, sumPrvku = 0, indexSum = 0, scan;    
    int *arrPrvku = (int *) malloc(MAX_WIDTH_ARR * sizeof(int));        
    printf("Posloupnost:\n");
    while((scan = scanf("%d", &prvek)) != EOF) {        
        if (indexPrvku+1 > MAX_WIDTH_ARR ){
            printf("Nespravny vstup.\n");
            exit(1);
        }
        arrPrvku[indexPrvku] = prvek;
        indexPrvku++;        
    }
    if(indexPrvku == 0) {
            printf("Nespravny vstup.\n");
            exit(1);
    }
    int kombinacePrvku = indexPrvku*(indexPrvku-1)/2;
    //filling arraySum 
    int *arrSum = (int *) malloc(kombinacePrvku * sizeof(int));
    for ( int i = 0; i < indexPrvku; i++ ) {           
        for (int j = i; j < indexPrvku; j++) {  
            sumPrvku += arrPrvku[j];
            if (sumPrvku != arrPrvku[j] ){                                
                arrSum[indexSum] = sumPrvku;
                indexSum++;
            }
        }
        sumPrvku = 0;              
    }
    free(arrPrvku); 
    int pocetDvojic = 0;
    qsort(arrSum, kombinacePrvku, sizeof(int), compare);
    int scetcik = 1;
    for (int i = 0; i < kombinacePrvku - 1; i++) {
        if(arrSum[i] == arrSum[i + 1]) {
            scetcik++;
        }
        else {
            pocetDvojic += scetcik * (scetcik - 1) / 2;
            scetcik = 1;
        }
    }
    free(arrSum); 
    printf("Pocet dvojic: %d\n", pocetDvojic);
    return 0;
}
