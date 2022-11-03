/****************

LAED1 - Projeto (Parte I) - Busca por padrão em sequência

Aluno(as): Thamiris Souza e Hugo Barbosa

Data: 14/01/2022

****************/

#include <stdio.h>
#include <stdlib.h>

typedef int TipoChave;
typedef struct
{
    TipoChave Chave;
    int NumElementos;
    int PontoMedio;
    int Tipo;

} TipoItem; 

typedef struct TipoCelula *TipoApontador;
typedef struct TipoCelula {

    TipoItem Item;
    TipoApontador Prox; //aponta para a proxima celula da lista

} TipoCelula;

typedef struct {

    TipoApontador Primeiro, Ultimo;

} TipoLista; 

void FLVazia(TipoLista *Lista) //FLVazia -> cria a lista vazia
{ 
    Lista -> Primeiro = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Primeiro; 
    Lista -> Primeiro -> Prox = NULL;
}

int Vazia(TipoLista Lista)
{ 
    return (Lista.Primeiro == Lista.Ultimo); 
}

void Insere(TipoItem x, TipoLista *Lista)
{
    Lista -> Ultimo -> Prox = (TipoApontador) malloc(sizeof(TipoCelula));
    Lista -> Ultimo = Lista -> Ultimo -> Prox; 
    Lista -> Ultimo -> Item = x;
    Lista -> Ultimo -> Prox = NULL;
}

void Retira(TipoApontador p, TipoLista *Lista, TipoItem *Item) /* retira o item seguinte ao apontado por p*/
{ 
    TipoApontador q;

    if(Vazia(*Lista) || p == NULL || p->Prox == NULL)
    {   
        printf("Erro: Lista vazia ou posicao nao existe\n");
        return;
    }

    q = p -> Prox; //guarda o endereco da celula a ser retirada
    *Item = q -> Item; //copia o endereco da memoria apontada por Tipo
    p -> Prox = q -> Prox;
    
    if(p -> Prox == NULL) {
        Lista -> Ultimo = p;
    }  
    
    free(q);   
}

void Imprime(TipoLista Lista)
{ 
    TipoApontador Aux;
    Aux = Lista.Primeiro->Prox; //imprime a partir da segunda celula, pois a primeira = celula cabeca

    while (Aux != NULL)
    { 
        printf("Chave: %d\n", Aux->Item.Chave); 
        printf("Tipo de segmento: %d\n", Aux->Item.Tipo); 
        printf("N de elementos: %d\n", Aux->Item.NumElementos); 
        printf("Ponto medio: %d\n", Aux->Item.PontoMedio); 
        Aux = Aux->Prox;
    }
}

void busca(TipoLista *Lista, int *padrao)
{
    TipoApontador Aux;
    Aux = Lista->Primeiro->Prox;
    int i = 0, cont = 0, iguais = 0, guarda = 0;

    while (Aux != NULL)
    {
        if (Aux->Item.Tipo == padrao[0] && guarda == padrao[i] && cont != 4)
        {
            cont = 1;
            i = 1;
        }
        
        else if(Aux->Item.Tipo == padrao[i])
        {
            guarda = padrao[i+1];
            cont++;
            i++;

            if (cont == 5)
            {
                iguais = 1;
                break;              
            } 
        }  

        else
        {
            if (cont == 5)
            {
                iguais = 1;
                break;
            }
            
            else
            {
                cont = 0;
                i = 0;
            }          
        }
        
        Aux = Aux -> Prox;
    }

    if (iguais == 1)
    {
        printf("Resultado: Padrao encontrado.\n");
    }

    else
        printf("Resultado: Padrao nao encontrado.\n");
}

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
    seg = (int*) calloc(20,sizeof(int));

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
    elementos = (int*) malloc(20*sizeof(int));

    int *posicao; 
    posicao = (int*) malloc(N*sizeof(int));
    int *ultima; 
    ultima = (int*) malloc(N*sizeof(int));
    
    int cont = 1; //contador
    int j = 0; //vai indicar a quantidade de segmentos
    int t = 0;

    for (int i = 0; i < N; i++)
    {
       if(inteiro[i] == inteiro[i+1]){     
           cont++;
           elementos[j] = cont;

           if (t == 0)
           {
               posicao[j] = i;
               t++;
           }     
       }

       else if(inteiro[i] != inteiro[i-1] && inteiro[i] != inteiro[i+1]){
           cont = 1;
           elementos[j] = cont;
           posicao[j] = i;
           ultima[j] = i;
           j++;
       }

       else {
            cont = 1;
            ultima[j] = i;
            j++;
            t = 0;
       }
    }

    //para criar o ponto medio
    int pmedio[j];

    for (int i = 0; i < j; i++)
    {
        pmedio[i] = (posicao[i]+ultima[i])/2;
    }
    

    //definindo os segmentos
    int segmentos[20];
    
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

    //IMPLEMENTANDO - PROJETO I
    //LISTA
    int padrao[5] = {1,3,2,3,1}; //SUBSEQUENCIA A SER BUSCADA

    TipoLista sequencias; //nome da(s) lista(s)
    TipoItem X; //ponteiro para o tipo lista

    FLVazia(&sequencias);

    //para atribuir valor e inserir os itens na lista
    for (int i = 0; i < j; i++)
    {
        X.Chave = i+1;
        X.Tipo = segmentos[i];
        X.NumElementos = elementos[i];
        X.PontoMedio = pmedio[i];
        
        Insere(X,&sequencias);
    }

    busca(&sequencias,padrao);

    fclose(f);
    free(seg);

    return 0;
}