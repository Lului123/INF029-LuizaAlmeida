// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: luiza almeida
//  email: luiza.allmeida2006@gmailcom
//  Matrícula: 20261160009
//  Semestre: 2

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    int i, barras = 0;
    DataQuebrada dq;

    for (i = 0; data[i] != '\0'; i++) {
        if (data[i] == '/')
            barras++;
        else if (data[i] < '0' || data[i] > '9')
            return 0;
    }

    if (barras != 2)
        return 0;

    dq = quebraData(data);
    if (dq.valido == 0)
        return 0;

    if (dq.iMes < 1 || dq.iMes > 12)
        return 0;

    if (dq.iDia < 1)
        return 0;

    if (dq.iMes == 2) {
        if ((dq.iAno % 4 == 0 && dq.iAno % 100 != 0) || dq.iAno % 400 == 0) {
            if (dq.iDia > 29) return 0;
        } else {
            if (dq.iDia > 28) return 0;
        }
    } else if (dq.iMes == 4 || dq.iMes == 6 || dq.iMes == 9 || dq.iMes == 11) {
        if (dq.iDia > 30) return 0;
    } else {
        if (dq.iDia > 31) return 0;
    }

    return 1;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DataQuebrada inicio, fim;
    DiasMesesAnos dma;
    int diasMes, anoInicio, anoFim;

    if (q1(datainicial) == 0) {
        dma.retorno = 2;
        return dma;
    }
    if (q1(datafinal) == 0) {
        dma.retorno = 3;
        return dma;
    }

    inicio = quebraData(datainicial);
    fim = quebraData(datafinal);

    anoInicio = inicio.iAno;
    anoFim = fim.iAno;

    if (anoInicio > anoFim ||
        (anoInicio == anoFim && inicio.iMes > fim.iMes) ||
        (anoInicio == anoFim && inicio.iMes == fim.iMes && inicio.iDia > fim.iDia)) {
        dma.retorno = 4;
        return dma;
    }

    dma.qtdAnos = fim.iAno - inicio.iAno;
    dma.qtdMeses = fim.iMes - inicio.iMes;
    dma.qtdDias = fim.iDia - inicio.iDia;

    if (dma.qtdDias < 0) {
        int mesAnterior = fim.iMes - 1;
        int anoAnterior = fim.iAno;

        if (mesAnterior == 0) {
            mesAnterior = 12;
            anoAnterior--;
        }

        if (mesAnterior == 2) {
            if ((anoAnterior % 4 == 0 && anoAnterior % 100 != 0) || anoAnterior % 400 == 0)
                diasMes = 29;
            else
                diasMes = 28;
        } else if (mesAnterior == 4 || mesAnterior == 6 || mesAnterior == 9 || mesAnterior == 11) {
            diasMes = 30;
        } else {
            diasMes = 31;
        }

        dma.qtdDias += diasMes;
        dma.qtdMeses--;
    }

    if (dma.qtdMeses < 0) {
        dma.qtdMeses += 12;
        dma.qtdAnos--;
    }

    dma.retorno = 1;
    return dma;
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int i, qtdOcorrencias = 0;
    char atual, procurado = c;

    if (isCaseSensitive != 1 && procurado >= 'A' && procurado <= 'Z')
        procurado = procurado + ('a' - 'A');

    for (i = 0; texto[i] != '\0'; i++) {
        atual = texto[i];

        if (isCaseSensitive != 1 && atual >= 'A' && atual <= 'Z')
            atual = atual + ('a' - 'A');

        if (atual == procurado)
            qtdOcorrencias++;
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int i, j, tamanhoBusca = 0, qtdOcorrencias = 0, igual;

    while (strBusca[tamanhoBusca] != '\0')
        tamanhoBusca++;

    if (tamanhoBusca == 0)
        return 0;

    for (i = 0; strTexto[i] != '\0'; i++) {
        igual = 1;

        for (j = 0; j < tamanhoBusca; j++) {
            if (strTexto[i + j] == '\0' || strTexto[i + j] != strBusca[j]) {
                igual = 0;
                break;
            }
        }

        if (igual == 1 && qtdOcorrencias < 15) {
            posicoes[qtdOcorrencias * 2] = i + 1;
            posicoes[qtdOcorrencias * 2 + 1] = i + tamanhoBusca;
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{
    int invertido = 0, digito;

    while (num != 0) {
        digito = num % 10;
        invertido = invertido * 10 + digito;
        num = num / 10;
    }

    return invertido;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int divisor = 1, temp;

    if (numerobase < 0)
        numerobase = -numerobase;
    if (numerobusca < 0)
        numerobusca = -numerobusca;

    temp = numerobusca;
    while (temp >= 10) {
        temp = temp / 10;
        divisor = divisor * 10;
    }

    while (numerobase >= divisor) {
        if (numerobase % (divisor * 10) == numerobusca)
            qtdOcorrencias++;
        numerobase = numerobase / 10;
    }

    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
{
    int achou = 0, tam = 5;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 10; j++){

            if(matriz[i][j] == palavra[0]){

                // Direita
                if(j + tam < 10){
                    achou = 1;
                    for(int direita = 1; direita < tam; direita++){
                        if(matriz[i][j + direita] != palavra[direita]){
                            achou = 0;
                            break;
                        }
                    }
                    if(achou == 1)
                        return 1;
                }

                // Esquerda
                if(j - tam + 1 >= 0){
                    achou = 1;
                    for(int esquerda = 1; esquerda < tam; esquerda++){
                        if(matriz[i][j - esquerda] != palavra[esquerda]){
                            achou = 0;
                            break;
                        }
                    }
                    if(achou == 1)
                        return 1;
                }

                // Baixo
                if(i + tam < 8){
                    achou = 1;
                    for(int baixo = 1; baixo < tam; baixo++){
                        if(matriz[i + baixo][j] != palavra[baixo]){
                            achou = 0;
                            break;
                        }
                    }
                    if(achou == 1)
                        return 1;
                }

                // Cima
                if(i - tam + 1 >= 0){
                    achou = 1;
                    for(int cima = 1; cima < tam; cima++){
                        if(matriz[i - cima][j] != palavra[cima]){
                            achou = 0;
                            break;
                        }
                    }
                    if(achou == 1)
                        return 1;
                }

                // Diagonal para baixo e direita
                if(i + tam < 8 && j + tam < 10){
                    achou = 1;
                    for(int diagonal1 = 1; diagonal1 < tam; diagonal1++){
                        if(matriz[i + diagonal1][j + diagonal1] != palavra[diagonal1]){
                            achou = 0;
                            break;
                        }
                    }
                    if(achou == 1)
                        return 1;
                }

                // Diagonal para baixo e esquerda
                if(i + tam < 8 && j - tam + 1 >= 0){
                    achou = 1;
                    for(int diagonal2 = 1; diagonal2 < tam; diagonal2++){
                        if(matriz[i + diagonal2][j - diagonal2] != palavra[diagonal2]){
                            achou = 0;
                            break;
                        }
                    }
                    if(achou == 1)
                        return 1;
                }

                // Diagonal para cima e direita
                if(i - tam + 1 >= 0 && j + tam < 10){
                    achou = 1;
                    for(int diagonal3 = 1; diagonal3 < tam; diagonal3++){
                        if(matriz[i - diagonal3][j + diagonal3] != palavra[diagonal3]){
                            achou = 0;
                            break;
                        }
                    }
                    if(achou == 1)
                        return 1;
                }

                // Diagonal para cima e esquerda
                if(i - tam + 1 >= 0 && j - tam + 1 >= 0){
                    achou = 1;
                    for(int diagonal4 = 1; diagonal4 < tam; diagonal4++){
                        if(matriz[i - diagonal4][j - diagonal4] != palavra[diagonal4]){
                            achou = 0;
                            break;
                        }
                    }
                    if(achou == 1)
                        return 1;
                }
            }
        }
    }

    return 0;
}



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
