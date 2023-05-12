#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
int main () {
    int lastDay = -2, firstDay = 0;
    double kredit, debit, ucet = 0, castka;
    printf("Zadejte kreditni urok [%%]:\n");
    if(scanf("%lf", &kredit) !=1) {
        printf("Nespravny vstup.\n");
        return 1;
    };
    printf("Zadejte debetni urok [%%]:\n");
    if (scanf("%lf", &debit) !=1) {
        printf("Nespravny vstup.\n");
        return 1;
    };
    printf("Zadejte transakce:\n"); 
    if (scanf("%d, %lf", &firstDay, &castka) !=2) {
            printf("Nespravny vstup.\n");
            return 1;
    };
    do {        
        if(lastDay == -2) {
            lastDay = -1;
            ucet = castka;                    
        } else {
            lastDay = firstDay;
            if (scanf("%d, %lf", &firstDay, &castka) != 2 ||  firstDay < lastDay) {
                printf("Nespravny vstup.\n");
                return 0;
            }     
            for(int i = 0; i < firstDay - lastDay; i++) {                
                if(ucet >= 0) {                    
                    ucet = trunc((ucet + ucet*(kredit/100))*100)/100;
                } else {
                    ucet = trunc((ucet + ucet*(debit/100))*100)/100;
                }                
            }
            ucet += castka;
            if (castka == 0) {        
                printf("Zustatek: %.2lf\n", ucet);
                return 0;
            }             
        }                                   
    } while(firstDay>lastDay);
    return 0;
}