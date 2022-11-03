#include <stdio.h>

//calculando pelo algoritmo de euclides
int mdc(int a, int b){ 

    int resto;
    int resultado;

    //primeiro divide-se o maior valor pelo menor para descobrir o resto, em seguida divide-se o menor pelo resto encontrado
    if(a > b) {

        resultado = b;
        resto = a%b;

        if(resto == 0){ //quando os dois numeros sao divisiveis entre si, o menor numero eh o MDC, e o menor numero = b
            return resultado;
        }

        resultado = mdc(b, resto); //divide-se o menor valor pelo resto até chegar a 0, e o penultimo resto encontrado eh o MDC

        return resultado;
    }
    
    else if(b > a) {
        
        resto = b%a;
        resultado = a;

        if(resto == 0){
            return resultado;
        }

        resultado = mdc(a, resto); //divide-se o menor valor pelo resto até chegar a 0, e o penultimo resto encontrado eh o MDC

        return resultado;    
    }

    else {
        
        resultado = a;
        return resultado;
    }
}    

int main(){

    int a, b, resultado;

    printf("Digite dois numeros inteiros: ");
    scanf("%i %i", &a, &b);

    resultado = mdc(a,b);

    printf("Resultado: %i\n", resultado);

    return 0;
}
