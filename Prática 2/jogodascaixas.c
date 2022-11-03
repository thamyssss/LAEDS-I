#include <stdio.h>
#include <stdlib.h>

int main(){

    char nomeDoArquivo[30]; //declara o nome de um arquivo de ate 30 caracteres

    printf("Digite o nome do arquivo de entrada: ");
    scanf("%s", nomeDoArquivo);

    FILE *f = fopen(nomeDoArquivo, "r");

    int N; //numero de linhas das caixas
    int i, j; 

    fscanf(f,"%i",&N);

    int pilhaDeCaixas[N][N]; //monta a matriz caixas

    //para salvar os valores do arquivo na matriz caixas:
    for (int i = 0; i < N; i++)
    {
        int a = i;

        for (int j = 0; j < N; j++)
        {
            if(i == a && j > a){ //atribui valor 0 onde ha espacos vazios no arquivo das caixas
                pilhaDeCaixas[i][j] = 0;
            }

            else {
                fscanf(f,"%d", &pilhaDeCaixas[i][j]);
            }
        }   
    }

    int soma; //soma da fileira
    int somaTotal = 0; //soma das fileiras anteriores
    int premio; //valor do premio a receber de acordo com a caixa escolhida
    int maiorValor = 0; //guarda o maior premio possivel
    
    int fileiraVencedora, caixaVencedora;

    for (i = 0; i < N; i++){

        soma = 0;
        premio = 0;

        for (j = 0; j < N; j++) {
            
            soma += pilhaDeCaixas[i][j];

            if(pilhaDeCaixas[i][j] != 0){
                premio = somaTotal + pilhaDeCaixas[i][j];

                if(maiorValor < premio){
                    maiorValor = premio;

                    fileiraVencedora = i+1;
                    caixaVencedora = j+1;
                }
            }
        }

        somaTotal += soma;    
    }

    printf("Resposta: fileira %d, caixa %d.\n", fileiraVencedora, caixaVencedora);

    fclose(f);
    return 0;
}