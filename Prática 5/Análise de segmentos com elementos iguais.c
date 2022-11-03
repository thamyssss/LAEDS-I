/****************

LAED1

Aluna: Thamiris Souza

Data: 07/01/2021

****************/

#include <stdio.h>
#include <stdlib.h>

int main(){

    char nomeDoArquivo[30];

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    FILE *f = fopen(nomeDoArquivo,"r");

    //NUMERO DE ELEMENTOS
    int N;
    fscanf(f,"%d",&N);

    //transformando em numeros inteiros
    int inteiro[N];
    
    for (int i = 0; i < N; i++)
    {
       fscanf(f,"%d ",&inteiro[i]);
    }

    //colocando em ordem crescente
    int guarda;

    for (int i = 0; i < N; i++)
    {
        for (int m = i+1; m < N; m++)
        {
            if(inteiro[i] > inteiro[m])
            {
                guarda =  inteiro[i];
                inteiro[i] = inteiro[m];
                inteiro[m] = guarda;
            }
        }
    }

    //definindo os segmentos pela ordem crescente
    int *seg;
    seg = (int*) calloc(10,sizeof(int));

    int *salvaNumero; //salva os numeros diferentes existentes
    salvaNumero = (int*) malloc(N*sizeof(int));
    
    int k = 0;
    
    for (int i = 0; i < N; i++) 
    {
        if(inteiro[i] == inteiro[i+1]){
            seg[k] = k+1;
            salvaNumero[k] = inteiro[i];
        }
        
        else if(inteiro[i] != inteiro[i-1] && inteiro[i] != inteiro[i+1]){ //no caso de ser um numero isolado, contara como um segmento de apenas um numero
           seg[k] = k+1;
           salvaNumero[k] = inteiro[i];
           k++;
        }
        
        else{
            k++;
        }
    }  
    
    fclose(f);

    fopen(nomeDoArquivo,"r");

    fscanf(f,"%d",&N);
    
    for (int i = 0; i < N; i++)
    {
       fscanf(f,"%d ",&inteiro[i]);
    }

    //contando a quantidade de elementos em cada segmento
    int *elementos; 
    elementos = (int*) malloc(10*sizeof(int));
    
    int cont = 1; //contador
    int j = 0; //vai indicar a quantidade de segmentos

    for (int i = 0; i < N; i++)
    {
       if(inteiro[i] == inteiro[i+1]){     
           cont++;
           elementos[j] = cont;
       }

       else if(inteiro[i] != inteiro[i-1] && inteiro[i] != inteiro[i+1]){
           cont = 1;
           elementos[j] = cont;
           j++;
       }

       else {
           cont = 1;
           j++;
       }
    }

    //definindo os segmentos
    int segmentos[10];
    
    int b = 0;

    for (int i = 0; i < N; i++)
    {
       for (int m = 0; m < k+1; m++)
       {
           if(inteiro[i] == salvaNumero[m])
           {
               segmentos[b] = seg[m];               
               break;
           }
       }

       if (inteiro[i] != inteiro[i+1] || (inteiro[i] != inteiro[i-1] && inteiro[i] != inteiro[i+1]))
       {
           b++;
       }
    }

    printf("Matriz:\n");

    //imprimindo os segmentos
    for (int i = 0; i < j; i++)
    {
        printf("%d ",segmentos[i]);
    }

    printf("\n");

    //imprimindo os elementos em cada segmento
    for (int i = 0; i < j; i++)
    {
        printf("%d ",elementos[i]);
    }

    printf("\n");

    fclose(f);
    free(seg);

    return 0;
}