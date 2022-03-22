// Isto é apenas um protótipo. ~Ian Lavorente

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#define tamanho_da_palavra 6
#define tamanho_real_da_palavra tamanho_da_palavra - 1
#define nome_do_arquivo "words.txt"

/*
Grupo 1

Anderson da Silva
Gustavo Alves
Tiago Gabriel
Gabrielly Cristine
*/

int sortear_numero(int min, int max)
{
  srand(time(NULL));
  return rand() % (max + 1 - min) + min;
}

int contar_quantidade_de_palavra_no_arquivo()
{
  FILE *arquivo = fopen(nome_do_arquivo, "r");
  int numero_de_palavras = 0;
  char palavra[tamanho_da_palavra];
  while (fscanf(arquivo, "%s", palavra) != EOF)
  {
    numero_de_palavras++;
  }
  fclose(arquivo);
  return numero_de_palavras;
}

void gerar_palavra_aleatoria(char *palavraJogo)
{
  int quantidade_de_palavras_no_arquivo = contar_quantidade_de_palavra_no_arquivo();
  printf("%d", quantidade_de_palavras_no_arquivo);
  FILE *arquivo = fopen(nome_do_arquivo, "r");
  int numero_aleatorio = sortear_numero(1, quantidade_de_palavras_no_arquivo);
  rewind(arquivo);
  for (int i = 0; i < numero_aleatorio; i++)
  {
    fscanf(arquivo, "%s", palavraJogo);
  }
  fclose(arquivo);
}

/*
Grupo 2

Karolyne Muniz
Maria Luiza
Luiz Henrique
Alice Akaki
*/

int checar_letra_na_palavra(char *palavra, char letra)
{
  int i = 0;

  while (palavra[i])
  {
    if (palavra[i] == letra)
      return 1;
    i++;
  }

  return 0;
}

void preencher_linha(char matriz[][tamanho_real_da_palavra], char *palavra_do_jogo, char *palavra_do_usuario, int linha)
{
  int i = 0;

  while (palavra_do_jogo[i])
  {
    if (palavra_do_jogo[i] == palavra_do_usuario[i])
    {
      matriz[linha][i] = palavra_do_usuario[i];
    }
    if (palavra_do_jogo[i] != palavra_do_usuario[i])
    {
      matriz[linha][i] = '+';
    }
    if (checar_letra_na_palavra(palavra_do_jogo, palavra_do_usuario[i]) == 0)
    {
      matriz[linha][i] = '#';
    }

    i++;
  }
}

/*
Grupo 4

João Pedro
João Guilherme
Bruno McPherson
Thiago Paiva
*/

void banner()
{
  setlocale(LC_ALL, "Portuguese");
  printf("\n -------------------------------------------------  ");
  printf("\n|         ____ _______  ___   ____  ____  ____    |  ");
  printf("\n|  |     |        |    |   | |     |     |    |   |  ");
  printf("\n|  |     |____    |    |___| |____ |     |    |   |  ");
  printf("\n|  |     |        |    | \\   |     |     |    |   | ");
  printf("\n|  |____ |____    |    |  \\  |____ |____ |____|   | ");
  printf("\n|                                                 |  ");
  printf("\n ------------------------------------------------- ");

  printf("\nBem-vindo ao Letreco, logo abaixo estão as regras do jogo.\n\nOs símbolos representam as letras, como por exemplo:\n");
  printf("# (jogo da velha) representa que a letra não existe na palavra.\n");
  printf("+ (mais) significa que a letra existe na palavra, porém está na posição errada.\n");
  printf("O jogador tem 5 tentativas para tentar acertar a palavra correta. Todas as palavras estão limitadas a 5 letras\n\nBoa sorte e bom jogo!");
}

int checar_tamanho_da_palavra(char *palavra)
{
  int i = 0;

  while (palavra[i] != '\0')
  {
    i++;
  }

  return i;
}

void ver_mascara_da_palavra(char palavra[])
{
  printf("\n ------------------------------------------------\n");
  printf("|");

  for (int i = 0; i < tamanho_real_da_palavra; i++)
  {
    printf("\t%c ", palavra[i]);
  }

  printf("       |");
  printf("\n ------------------------------------------------");
  printf("\n                                                   ");
  printf("\n");
}

/*
Grupo 5

Sandy Campos
Gabriel Sérgio
Deivison Lima
Gustavo Klosinski
*/

int compara_palavra(char *letreco, char *mascara, char *palavra)
{
  int i, cont = 0;

  for (i = 0; i < tamanho_real_da_palavra; i++)
  {
    if (letreco[i] == palavra[i])
    {
      mascara[i] = letreco[i];
      cont++;
    }
  }

  return cont;
}

void preencher_mascara_da_matriz(char matriz[][tamanho_real_da_palavra])
{
  int i, j;

  for (i = 0; i < tamanho_real_da_palavra; i++)
  {
    for (j = 0; j < tamanho_real_da_palavra; j++)
    {
      matriz[i][j] = '_';
    }
  }
}

/*
Extra

William Cardoso
*/

void ver_mascara_da_matriz(char matriz[][tamanho_real_da_palavra])
{
  int i, j;

  for (i = 0; i < tamanho_real_da_palavra; i++)
  {
    printf("\t");
    for (j = 0; j < tamanho_real_da_palavra; j++)
    {
      printf("[ %c ] ", matriz[i][j]);
    }
    printf("\n");
  }
}

/*
Grupo 3

Gabriel Barros
Kauã Reydisson
Guilherme Alves
Ian Lavorente
*/

int main()
{
  char palavra_do_jogo[tamanho_da_palavra] = "";
  char *palavra_do_jogoP = &palavra_do_jogo;
  char mascara[tamanho_da_palavra] = "_____";
  char *mascaraP = &mascara;
  char matriz_de_palavras[tamanho_real_da_palavra][tamanho_real_da_palavra] = {};
  char palavra[tamanho_da_palavra] = "";
  int numero_de_tentativas = 5;
  int tentativas_usadas = 1;

  banner();
  printf("\n ");
  gerar_palavra_aleatoria(palavra_do_jogoP);
  preencher_mascara_da_matriz(matriz_de_palavras);

  while (numero_de_tentativas > 0)
  {
    ver_mascara_da_palavra(mascaraP);
    ver_mascara_da_matriz(matriz_de_palavras);
    printf("\nescreva uma palavra(5 letras): ");
    scanf("%s", palavra);
    if (checar_tamanho_da_palavra(palavra) != 5)
    {
      printf("\nnumero de letras diferente de cinco!\n");
      continue;
    }
    else
    {
      int cont = compara_palavra(palavra_do_jogo, mascara, palavra);

      if (cont == tamanho_real_da_palavra)
      {
        printf("\nParabens, voce acertou! A palavra era: \"%s\".\n", palavra_do_jogo);
        printf("Quantidade de tentativas: %d\n", tentativas_usadas);
        break;
      }
      preencher_linha(matriz_de_palavras, palavra_do_jogoP, palavra, tentativas_usadas - 1);
    }
    system("clear");
    numero_de_tentativas--;
    tentativas_usadas++;
  }

  return 0;
}