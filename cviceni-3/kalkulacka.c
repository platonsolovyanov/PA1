#include <stdio.h>
#include <stdlib.h> 
#include <math.h>
int main () {
    double a, b;
    char c, r;    
    printf("Zadejte vzorec:\n");
    if (scanf("%lf %c %lf %c", &a, &c, &b, &r) !=4 || (c != '+' && c != '-' && c != '/' && c != '*') || r != '=') {
        printf("Nespravny vstup.\n");

        return 1;
    }
    switch (c) {
        case '+':
            printf("%ld\n", lround(a + b));
            break;
        case '-':
            printf("%ld\n", lround(a - b));            
            break;
        case '/':
            if(b != 0) {
                printf("%ld\n", lround(a / b));
            } else {
                printf("Nespravny vstup.\n");
            }                    
            break;
        case '*':
            printf("%g\n", a * b);
            break; 
    }      
}