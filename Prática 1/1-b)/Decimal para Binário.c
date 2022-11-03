#include <stdio.h>


void dec2bin(int dec){ 
    
    int resto;

    if(dec/2 == 0){ 
        
        resto = dec%2;
        printf("%i",resto); 
        
    }
    else { 
        resto = dec%2; 
        dec2bin(dec/2); 
        printf("%i",resto);
    }
}

int main(){
    int dec;

    printf("Digite um numero inteiro: ");
    scanf("%i",&dec);

    printf("Resultado: ");
    dec2bin(dec);

    printf("\n");

    return 0;
}
