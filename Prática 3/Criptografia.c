#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(){

    char nomeDoArquivo[30];

    printf("Digite o nome do arquivo: ");
    scanf("%s", nomeDoArquivo);

    printf("\n--------------------\n");

    FILE *f = fopen(nomeDoArquivo,"r");

    //PASSO 1 - CALCULAR A POSICAO DO CARACTERE EXTRA, BINARIO P/ DECIMAL
    char numero = '0';
    int cont = 0;

    char str[2]; //variavel usada apenas para fazer a conversão
    int binario[cont];
    int posicaoDecimal = 0; //posicao em decimal

    for (int i = 0; i < 30; i++)
    {
        numero = fgetc(f);

        if(numero == '0' || numero == '1'){

            cont += 1; //conta quantas posicoes estao com o valor do numero binario

            str[0] = numero;
            binario[i] = atoi(str);
        }
        else {
            break;
        }
    }

    fclose(f);

    fopen(nomeDoArquivo,"r");
    //calcula a quantidade de caracteres do arquivo
    fseek(f,0,SEEK_END);
    int tamanho = ftell(f);
    fclose(f);

    fopen(nomeDoArquivo,"r");
    char texto[tamanho]; //cria um vetor char com a mesma quantidade de caracteres do arquivo
    fgets(texto,tamanho,f);

    printf("Mensagem codificada:\n--------------------\n");
    printf("%s\n",texto);
    fclose(f);

    //ACHANDO A POSICAO DO CARACTERE EXTRA
    fopen(nomeDoArquivo,"r");

    for (int i = cont-1; i >= 0; i--)
    {
        numero = fgetc(f);
        posicaoDecimal += binario[i] * pow(2,cont-1-i);
    }

    posicaoDecimal -= 1;

    char mensagem[tamanho-cont];
    fgets(mensagem,tamanho-cont,f);

    //PARA APAGAR O CARACTERE EXTRA
    for(int i = posicaoDecimal; i < tamanho; i++){ //int i = posicaoDecimal
        mensagem[i] = mensagem[i+1];
    }

    //PASSO 2 - DIVIDINDO EM BLOCOS DE 2 LETRAS
    int linhas = (tamanho-1-cont)/2; //numero de linhas da matriz, tamanho-cont pois tira as posicoes onde esta o numero em binario
    char blocos[linhas][2];
    int x = 0;

    for (int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < 2; j++){
            blocos[i][j] = mensagem[x];
            x += 1;
        }
    }

    //PASSO 3 - DESPERMUTAR OS BLOCOS
    char permuta[linhas][2];

    if(linhas%2 != 0){
        
        for(int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < 2; j++)
            {
                if(i%2==0) {
                    permuta[i][j] = blocos[linhas-i-1][j];
                }

                else{
                    permuta[i][j] = blocos[i][j];
                }
            }
        }
    }
    
    else{

    for (int i = 0; i < linhas; i++)
    {
        if(i >= linhas/2+1){
            break;
        }
        
        for (int j = 0; j < 2; j++)
        {
            if(i != linhas/2 && i+2 < linhas/2){
                permuta[i][j] = blocos[linhas-i-1][j];
                permuta[linhas-i-1][j] = blocos[i][j];

                permuta[i+1][j] = blocos[i+1][j];
                permuta[linhas-i-2][j] = blocos[linhas-i-2][j];
            }

            else{
                permuta[i][j] = blocos[linhas-i-1][j];
                permuta[linhas-i-1][j] = blocos[i][j];
            }
        }
            i++;
        }
    }

    //PASSO 4 - REFLETIR OS BLOCOS
    char guarda;
    int z = 0;

    for (int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < 2; j++){

            if(j < 1) {
                guarda = permuta[i][j];
                permuta[i][j] = permuta[i][j+1];

                mensagem[z] = permuta[i][j];
            }

            else {
                permuta[i][j] = guarda;
                mensagem[z] = permuta[i][j];
            }
            
            z++;
        }
    }

    //PASSO 5 - DECIFRAR O CODIGO
    char alfNormal[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char alfNormalm[] = "abcdefghijklmnopqrstuvwxyz";

    char alfCifrado[] = "FGHIJKLMNOPQRSTUVWXYZABCDE";
    char alfCifradom[] = "fghijklmnopqrstuvwxyzabcde";

    for(int i = 0; i < tamanho-cont; i++){

        for (int j = 0; j < 26; j++)
        {
            if(alfCifrado[j] == mensagem[i] || alfCifradom[j] == mensagem[i]){

                if(alfCifrado[j] == mensagem[i]){
                    mensagem[i] = alfNormal[j];
                    break;
                }
                else{
                    mensagem[i] = alfNormalm[j];
                    break;
                }              
            }

            else if(mensagem[i] == '#'){
                mensagem[i] = ' ';
            }
        }
    }

    printf("\n----------------------\n");
    printf("Mensagem decodificada:\n----------------------\n%s\n",mensagem);

    fclose(f);
    return 0;
}
