Em grego, cryptos significa secreto, oculto. A criptografia estuda os métodos para codificar uma mensagem de modo que somente seu destinatário legítimo consiga interpretá-la. É a arte dos “códigos secretos” (Coutinho, 2015).

Uma das técnicas de criptografia mais simples e conhecida consiste em substituir cada letra da mensagem por outra, que se apresenta no alfabeto abaixo dela um número fixo de vezes. Conta a história que Júlio César (100-44 a.C.) utilizava este código nas mensagens enviadas a seus generais.

A transformação pode ser representada alinhando-se dois alfabetos: o alfabeto cifrado e o alfabeto normal rotacionado à direita ou esquerda por um número de posições. Por exemplo, a seguir está uma cifra de César usando uma rotação à esquerda de três posições:

Normal:  ABCDEFGHIJKLMNOPQRSTUVWXYZ
Cifrado: DEFGHIJKLMNOPQRSTUVWXYZABC
Embora cifra de César seja facilmente decifrada e na prática não ofereça essencialmente nenhuma segurança na comunicação, é frequentemente incorporada como parte de esquemas mais complexos de criptografia (Wikipedia, 2019).

Este exercício consiste em ler uma mensagem criptografada de um arquivo texto e imprimir a mensagem descriptografada na saída padrão. A técnica de criptografia será a de códigos em bloco, que consiste em subdividir a mensagem em blocos de várias letras e embaralhar esses blocos. Antes, porém, será utilizada a cifra de César com rotação à esquerda de cinco posições. Após a codificação da mensagem, será realizada a adição de 5 bits no inicio da string da mensagem contendo o número binário que corresponde à posiçã da string em que será adicionado um caracter extra que deverá ser descartado na decodificação.

Por exemplo, considere a mensagem AMO LIVROS. Para codificá-la seguiremos os seguintes passos:

• Substituir os espaços pelo símbolo # e completar a mensagem com este mesmo símbolo no final, caso tenha uma quantidade ímpar de letras;

• Substituir cada letra por outra, utilizando a cifra de César com uma rotação à esquerda de cinco posições;

• Subdividir a mensagem em blocos de n letras (neste caso n=2);

• Refletir cada bloco;

• Permutar os blocos trocando o primeiro com o último, o terceiro com a antepenúltimo, e assim por diante, mas deixando os outros como estão.

• Adicionar 5 dígitos no inicio da string da mensagem contendo o número binário que corresponde à posição da string em que será adicionado um caracter extra (a posição e o caracter são escolhidos aleatoriamente).
Aplicando isto, passo a passo, à mensagem acima, obtemos primeiro:

AMO#LIVROS

Depois usamos a cifra de César:

FRT#QNAWTX

Separamos em blocos de 2 letras (observação: os traços não fazem parte da mensagem):

FR-T#-QN-AW-TX

em seguida refletimos cada bloco

RF-#T-NQ-WA-XT

depois permutamos os blocos

XT-#T-NQ-WA-RF

e, finalmente, adicionamos o caracter extra e a sua posição em binário, o que nos dá como mensagem codificada:

00110XT#TNAQWARF

Use o método explicado para poder decodificar a mensagem contida em um arquivo texto cujo nome será lido da entrada padrão. Para simplificar, foram eliminados acentos e pontuação. As letras maiúsculas e minúsculas do texto deverão ser mantidas.

A saída do programa deverá seguir o padrão abaixo, mas lembre-se que o seu programa será testado com arquivos distintos:

Digite o nome do arquivo: mensagem.txt

--------------------
Mensagem codificada:
--------------------
01111tinhkn#ftyH#y#Xwfxfitufjxmsfk#jrqjzjytrhjr#fwfiknxji#v#sjx#nhjy#w#f#jsju#t#xjcjjih#wkfw#F

----------------------
Mensagem decodificada:
----------------------
A cifra de Cesar pode ser facilmente decifrada mesmo que se tenha apenas o texto cifrado