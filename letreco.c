// trabalho de programação 1
// Criar jogo letreco
#include <stdio.h>;
#include <stdlib.h>;
#include <time.h>;
#include <string.h>;
#define LENGTH_WORD 6
#define MAX_WORDS 100
#define LENGTH_REAL_WORD LENGTH_WORD - 1

void bannerGamer()
{
  printf("\t-----------------------------------------------------\n");
  printf("\t-------------------------LETRECO---------------------\n");
  printf("\t-----------------------------------------------------\n");
  printf("\t * -> Letra nao existe na palavra\n");
  printf("\t + -> Letra existe na palavra, mas fora de posicao.\n");
  printf("\n");
}

void fillMatrizMask(char matriz[][LENGTH_REAL_WORD])
{
  int i, j;
  for (i = 0; i < LENGTH_REAL_WORD; i++)
  {
    for (j = 0; j < LENGTH_REAL_WORD; j++)
    {
      matriz[i][j] = '_';
    }
  }
}

void viewMatrizMask(char matriz[][LENGTH_REAL_WORD])
{
  int i, j;
  for (i = 0; i < LENGTH_REAL_WORD; i++)
  {
    printf("\t");
    for (j = 0; j < LENGTH_REAL_WORD; j++)
    {
      printf("\t[ %c ] ", matriz[i][j]);
    }
    printf("\n");
  }
}

void viewMaskWord(char word[])
{
  printf("\t---------------------------------------------\n");
  printf("\t");
  for (int i = 0; i < LENGTH_WORD; i++)
  {
    printf("\t%c ", word[i]);
  }
  printf("\n\t---------------------------------------------\n");
  printf("\n");
}

void fillLineMatriz(char matriz[][LENGTH_REAL_WORD], char word[], int position, char *wordGame)
{
  for (int i = 0; i < LENGTH_REAL_WORD; i++)
  {
    int teste = checkLetterInWord(wordGame, word[i]);
    if (teste)
    {
      if (wordGame[i] == word[i])
      {
        matriz[position][i] = word[i];
      }
      else
      {
        matriz[position][i] = '+';
      }
    }
    else
    {
      matriz[position][i] = '*';
    }
    // matriz[position][i] = word[i];
  }
}

void readFileWordsAndFillArrayWords(char *filename, char words[][MAX_WORDS], int *length)
{
  FILE *file = fopen(filename, "r");
  int i = 0;
  if (file == NULL)
  {
    printf("Erro ao abrir o arquivo\n");
    exit(1);
  }
  while (!feof(file))
  {
    fscanf(file, "%s", words[i]);
    i++;
  }
  *length = i; // quantidade de palavras no banco de dados
  fclose(file);
}

int randomNumber(int min, int max)
{
  srand(time(NULL));
  return rand() % (max - min + 1) + min;
}

void generateRandomWord(char *wordGamer)
{
  char words[LENGTH_WORD][MAX_WORDS];
  int lengthDbWords;
  int *lengthDbWordsP = &lengthDbWords;
  readFileWordsAndFillArrayWords("words.txt", words, lengthDbWordsP);
  int randomNumberForWord = randomNumber(0, lengthDbWords - 1);
  strcpy(wordGamer, words[randomNumberForWord]);
}

int compareWord(char *wordGamer, char *word, char *maskFill)
{
  int i = 0;
  int count = 0; // quantidade de letras iguais
  while (wordGamer[i] != '\0')
  {
    if (wordGamer[i] == word[i])
    {
      maskFill[i] = wordGamer[i];
      count++;
    }
    i++;
  }
  return count;
}

int checkLengthWordUser(char *word)
{
  int i = 0;
  while (word[i] != '\0')
  {
    i++;
  }
  return i;
}

int checkLetterInWord(char *word, char *letter)
{
  int i = 0;
  while (word[i] != '\0')
  {
    if (word[i] == letter)
    {
      return 1;
    }
    i++;
  }
  return 0;
}

void main()
{
  // inicializando variaveis char
  char wordGamer[LENGTH_WORD] = ""; // palavra da vez no jogo
  char *wordGamerP = &wordGamer;
  char maskWord[LENGTH_WORD] = "_____"; // mascara para a palavra
  char *maskWordP = &maskWord;
  char word[LENGTH_WORD] = "";                               // palavra do usuário
  char matrizWords[LENGTH_REAL_WORD][LENGTH_REAL_WORD] = {}; // matriz para armazenar as palavras

  // inicializando variaveis inteiras
  int amountOfTries = 5; // número de tentativas restantes
  int tries = 1;         // número de tentativas feitas

  // configurações iniciais, iniciando funções.
  generateRandomWord(wordGamerP); // gera uma palavra aleatória
  fillMatrizMask(matrizWords);    // preenche a matriz com '_'
  printf("%s\n", wordGamer);
  bannerGamer(); // imprime o banner do jogo

  while (amountOfTries >= 0)
  {
    viewMaskWord(maskWordP);
    viewMatrizMask(matrizWords);
    printf("Digite uma palavra: ");
    scanf("%s", word);
    if (checkLengthWordUser(word) > LENGTH_REAL_WORD)
    {
      printf("palavra muito grande, tente algo com %d letras.\n\n", LENGTH_REAL_WORD);
      break;
    }
    else
    {
      int count = compareWord(wordGamer, word, maskWordP); // quantidade de letras corretas em uma tentativa
      if (count == LENGTH_REAL_WORD)
      {
        printf("Parabens voce acertou a palavra era \"%s.\" \n", wordGamer);
        printf("Tentativas feitas: %d", tries - 1);
        break;
      }
      else
      {
        fillLineMatriz(matrizWords, word, tries - 1, wordGamer); // preenche a linha da matriz com a palavra do usuário
      }
      amountOfTries--;
      tries++;
      system("clear");
    }
  }
}