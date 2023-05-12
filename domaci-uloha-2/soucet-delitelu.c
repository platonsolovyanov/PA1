#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main () {
    char znak;
    int cislo1, cislo2, sumdel=1, calcCislo1=0, scan;
    printf("Intervaly:\n");
    while((scan = scanf(" %c %d %d", &znak, &cislo1, &cislo2)) 
    !=EOF) {        
        if (scan !=3 || cislo1>cislo2 ||  cislo1<1 || (znak!='#' && znak!='?')) {
            printf("Nespravny vstup.\n");
            return 1;
        }        
        if (znak == '#'){
            while(cislo1 <= cislo2) {
                for(int y = 2; y <= sqrt(cislo1); y++) {
                    if(cislo1%y==0 && sqrt(cislo1)==y) {            
                        sumdel+=y;                
                    } else {
                        if(cislo1%y==0) {
                            sumdel=sumdel+y+cislo1/y;
                        }
                    }
                }
                if (sumdel==2) {
                    sumdel=1;
                    cislo1++;
                    continue;
                }
                for (int i = 2; i <= sqrt(sumdel); i++) {                
                    if(sumdel%i==0) {
                        sumdel=1;
                        break;
                    }
                }
                if (sumdel!=1){                    
                    sumdel=1;
                    calcCislo1++;
                }                            
                cislo1++;
            }
        }
        if (znak == '?') {
            while(cislo1 <= cislo2) {
                for(int y = 2; y <= sqrt(cislo1); y++) {
                    if(cislo1%y==0 && sqrt(cislo1)==y) {            
                        sumdel+=y;                
                    } else {
                        if(cislo1%y==0) {
                            sumdel=sumdel+y+cislo1/y;
                        }
                    }
                }
                if (sumdel==2) {
                    sumdel=1;
                    cislo1++;
                    continue;
                }
                for (int i = 2; i <= sqrt(sumdel); i++) {                
                    if(sumdel%i==0) {
                        sumdel=1;
                        break;
                    }
                }
                if (sumdel!=1){
                    printf("%d\n", cislo1);
                    sumdel=1;
                    calcCislo1++;
                }                            
                cislo1++;
            }
        }
        printf("Celkem: %d\n", calcCislo1);
        calcCislo1 = 0;        
    }
}