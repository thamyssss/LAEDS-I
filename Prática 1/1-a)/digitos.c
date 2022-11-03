#include <stdio.h>

int Digitos(int N){
    int cont = 0;
    cont++;

    if(N >= 10){
        
        cont = cont + Digitos(N/10);
        return cont;
    }
    else {
        return cont;
    }
    
}

int main(){

    int N, numeros;
    
    printf("Digite um numero inteiro: ");
    scanf("%i",&N);

    numeros = Digitos(N);

    printf("Resultado: %i\n",numeros);

    return 0;
}

