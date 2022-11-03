#include <stdio.h>

int mult(int base, int exp){

    int resultado = base;

    if (exp > 0)
    {
        resultado = resultado * mult(base, exp-1);
        return resultado;
    }

    else {
        resultado = 1;
        return resultado;
    }
}

int main(){
    int base, exp, resultado;

    printf("Digite a base e o expoente inteiros: ");
    scanf("%i %i", &base, &exp);

    resultado = mult(base,exp);

    printf("Resultado: %i\n",resultado);

    return 0;
}