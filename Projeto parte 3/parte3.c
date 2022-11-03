/****************

LAED1 - Projeto (Parte III) - Estimativa do formato da pista

Aluno(as): Thamiris Souza e Hugo Barbosa

Data: 28/01/2022

****************/

#include <stdio.h>
#include <stdlib.h>

//array struct com L posicoes
struct vetores
{
    int N;
    int inteiro[1000];
    int seg[20];
    int salvaNumero[1000];

    int elementos[20];
    int segmentos[20];

    int contSeg; //indicador de quantidade de segmentos
    int guardaPosicao; //guarda a posicao do segmento 2 - cor vermelha, para buscar o valor do ponto medio desse segmento no vetor pmedio[]

    int ultima[1000];
    int posicao[1000];
    int pmedio[20];
};

//LISTA
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

//procura pelo padrao da pista - PROJETO PARTE I
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

//procura por obstaculo na pista - PROJETO PARTE II
void obstaculo(TipoLista *Lista, int *padrao, int *contSeg, int L)
{
    TipoApontador Aux;
    Aux = Lista->Primeiro->Prox;
    int i = 0, cont = 0, guarda, achou = 0;
    
    int linha = 0; //contador de linhas
    int  p2[3] = {2,3,1};
    int contador = 0, f = 0, guarda2 = 0;

    while (linha != L)
    {
        cont = 0, guarda = 0;
        contador = 0, achou = 0, guarda2 = 0;
        
        for (int a = 0; a < contSeg[linha]; a++) //analisa linha por linha
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
                    Aux = Aux->Prox;
                    break;            
                }

                if(cont == 3)
                    achou = 1; //achou a primeira parte da pista {1,3,2}
            }      
              
            else
            {
                if (cont == 5)
                {
                    Aux = Aux->Prox;
                    break;
                }
            
                else
                {
                    cont = 0;
                    i = 0;
                }          
            }

            if (achou == 1)
            {
                if (Aux->Item.Tipo == p2[0] && guarda2 == p2[f])
                {
                    contador = 1;
                    f = 1;
                }
                
                else if (Aux->Item.Tipo == p2[f])
                {
                    guarda2 = p2[f+1];
                    contador++;
                    f++;

                    if (contador == 3)
                    {
                        achou = 2;
                        printf("Resultado: Pista com impedimento.\n");
                        exit(0); //a partir do momento que acha um obstaculo ja pode declarar que a pista tem impedimento         
                    }
                }

                else
                {
                    if (contador == 3)
                    {
                        achou = 2;
                        printf("Resultado: Pista com impedimento.\n");
                        exit(0);  
                    }
                    
                    else
                    {
                        contador = 0;
                        f = 0;
                    } 
                }        
            }
        
            Aux = Aux -> Prox; 
        }
        
        if (linha == L-1)
             printf("Resultado: Pista sem impedimento.\n"); //se rodou ate aqui e nao achou impedimento, pista sem obstaculo

        i = 0;
        f = 0;
        linha++;
    } 
}

//projeto parte III - formato da pista
int *formato(TipoLista *Lista, int *padrao, int *contSeg, int L)
{
    TipoApontador Aux;
    Aux = Lista->Primeiro->Prox;
    int i = 0;
    int cont, guarda, iguais; //se iguais = 1 achou o padrao 
    
    int *guardaPosicao = malloc(L * sizeof(int));
    int linha = 0; //contador de linhas

    while (linha != L)
    {
        int X; //auxiliar
        cont = 0;
        guarda = 0;
        iguais = 0;

        for (int a = 0; a < contSeg[linha]; a++)
        {
            if (Aux->Item.Tipo == padrao[0] && guarda == padrao[i] && cont != 4)
            {
                cont = 1;
                i = 1;
                
                if (iguais == 1)
                        guardaPosicao[linha] = X;
                    
                    else
                       guardaPosicao[linha] = 0;
            }
        
            else if(Aux->Item.Tipo == padrao[i])
            {
                guarda = padrao[i+1];
                cont++;
                i++;

                if (Aux->Item.Tipo == 2 && a != contSeg[linha]-2){
                    guardaPosicao[linha] = a;
                }
                
                if (cont == 5)
                    iguais = 1;
            }  

            else
            {
                if (cont == 5)
                {
                    X = guardaPosicao[linha];
                    iguais = 1;
                }
                               
                else
                {
                    cont = 0;
                    i = 0;
                    
                    if (iguais == 1)
                        guardaPosicao[linha] = X;
                    
                    else
                       guardaPosicao[linha] = 0;
                }          
            }
        
            Aux = Aux -> Prox;
        }
        
        linha++;
        i = 0;
    }

    return guardaPosicao; //retorna um vetor com a posicao do segmento vermelho em cada linha
}

int main(){

    char nomeDoArquivo[30];

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    FILE *f = fopen(nomeDoArquivo,"r");

    //NUMERO DE LINHAS
    int L;
    fscanf(f,"%d",&L);
    
    //inicializando o struct
    struct vetores v[L];

    //NUMERO DE ELEMENTOS
    int N;

    //transformando em numeros inteiros
    for (int i = 0; i < L; i++)
    {
        fscanf(f,"%d",&N);
        v[i].N = N;

        for (int a = 0; a < N; a++)
        {
            fscanf(f,"%d ",&v[i].inteiro[a]);
        }  
    }

    //colocando em ordem crescente
    int guarda;

    for (int i = 0; i < L; i++)
    {
        for (int a = 0; a < N; a++)
        {
            for (int m = a+1; m < N; m++)
            {
                if(v[i].inteiro[a] > v[i].inteiro[m])
                {
                    guarda =  v[i].inteiro[a];
                    v[i].inteiro[a] = v[i].inteiro[m];
                    v[i].inteiro[m] = guarda;
                }
            }
        }
    }    

    //definindo os segmentos pela ordem crescente
    int k; 
    
    for (int i = 0; i < L; i++)
    {
        k = 0;

        for (int a = 0; a < N; a++) 
        {
            if(v[i].inteiro[a] == v[i].inteiro[a+1])
            {
                v[i].seg[k] = k+1;
                v[i].salvaNumero[k] = v[i].inteiro[a];
            }
        
            else if(v[i].inteiro[a] != v[i].inteiro[a-1] && v[i].inteiro[a] != v[i].inteiro[a+1]) //no caso de ser um numero isolado, contara como um segmento de apenas um numero
            { 
                v[i].seg[k] = k+1;
                v[i].salvaNumero[k] = v[i].inteiro[a];
                k++;
            }   
        
            else
                k++;
        }
    }

    fclose(f);

    fopen(nomeDoArquivo,"r");

    fscanf(f,"%d",&L);

    for (int i = 0; i < L; i++)
    {
        fscanf(f,"%d",&N);

        for (int a = 0; a < N; a++)
        {
            fscanf(f,"%d ",&v[i].inteiro[a]);
        }
    }

    //contando a quantidade de elementos em cada segmento
    int cont; 
    int j; //vai indicar a quantidade de segmentos
    int t;

    for (int i = 0; i < L; i++)
    {
        cont = 1;
        j = 0;
        t = 0;

        for (int a = 0; a < N; a++)
        {
            if(v[i].inteiro[a] == v[i].inteiro[a+1] && a != N-1)
            {     
                cont++;
                v[i].elementos[j] = cont;

                if (t == 0)
                {
                    v[i].posicao[j] = a;
                    t++;
                }     
            }
       
            else if(v[i].inteiro[a] != v[i].inteiro[a-1] && v[i].inteiro[a] != v[i].inteiro[a+1])
            {
                cont = 1;
                v[i].elementos[j] = cont;
                v[i].posicao[j] = a;
                v[i].ultima[j] = a;
                j++;
            }

            else 
            {
                cont = 1;
                v[i].ultima[j] = a;
                j++;
                t = 0;
            }
        }
        v[i].contSeg = j;
    }

    //para criar o ponto medio
    for (int i = 0; i < L; i++)
    {
        for (int a = 0; a < v[i].contSeg; a++)
        {
            v[i].pmedio[a] = (v[i].posicao[a] + v[i].ultima[a]) / 2;
        }
    }

    //definindo os segmentos
    int b;

    for (int i = 0; i < L; i++)
    {
        b = 0;

        for (int a = 0; a < N; a++)
        {
            for (int m = 0; m < k+1; m++)
            {
                if(v[i].inteiro[a] == v[i].salvaNumero[m])
                {
                    v[i].segmentos[b] = v[i].seg[m];               
                    break;
                }
            }

            if (v[i].inteiro[a] != v[i].inteiro[a+1] || (v[i].inteiro[a] != v[i].inteiro[a-1] && v[i].inteiro[a] != v[i].inteiro[a+1]))
                b++;
        }
    }
    
    //IMPLEMENTANDO - PROJETO I
    //LISTA
    int padrao[5] = {1,3,2,3,1}; //SUBSEQUENCIA A SER BUSCADA

    TipoLista sequencias; //nome da(s) lista(s)
    TipoItem X; //ponteiro para o tipo lista
    int *guardaPosicao = malloc(L * sizeof(int));

    FLVazia(&sequencias);

    //para atribuir valor e inserir os itens na lista
    cont = 1;

    for (int i = 0; i < L; i++)
    {
        for (int a = 0; a < v[i].contSeg; a++)
        {
            X.Chave = cont;
            X.Tipo = v[i].segmentos[a];
            X.NumElementos = v[i].elementos[a];
            X.PontoMedio = v[i].pmedio[a];
        
            Insere(X,&sequencias);
            cont++;
        }
    }
    
    int contSeg[L]; //vetor contador de segmentos de cada linha
    
    for (int a = 0; a < L; a++)
    {
        contSeg[a] = v[a].contSeg;
    }
    
    guardaPosicao = formato(&sequencias,padrao,contSeg,L);

    int primeiro = 0, ultimo; //guarda o valor do ponto medio da primeira e da ultima linha
    cont = 0;

    for (int a = 0; a < L; a++)
    {
        v[a].guardaPosicao = guardaPosicao[a];

        if(v[a].guardaPosicao != 0)
        {
            if (primeiro == 0)
                primeiro = v[a].pmedio[guardaPosicao[a]];
            
            ultimo = v[a].pmedio[guardaPosicao[a]];

            cont++;
        }  
    }

    //para o formato da pista ser estimado e necessario ter no minimo 70% do total de linhas
    if (cont >= (0.7 * L))
    {
        //para descobrir o formato da pista, se houver uma diferença > 25 entre o primeiro e o ultimo ponto a pista e considerada curva
        if (primeiro < ultimo && ultimo - primeiro > 25)
            printf("Resultado: Curva a esquerda.\n");

        else if (primeiro > ultimo && primeiro - ultimo > 25)
            printf("Resultado: Curva a direita.\n");

        else if (primeiro == ultimo || (primeiro > ultimo && primeiro - ultimo < 25) || (primeiro < ultimo && ultimo - primeiro < 25))
            printf("Resultado: Pista em linha reta.\n");
    }

    else
        printf("Resultado: Formato da pista nao estimado.\n");

    fclose(f);

    return 0;
}