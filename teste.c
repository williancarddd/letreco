
#include <stdio.h>;
#include <stdlib.h>;

void getLineFile(char *filename, int numberLine, char *wordGamer)
{
  // get line File
  FILE *file = fopen(filename, "r");
  int count = 1;
  char c;
  while ((c = fgetc(file)) != EOF)
  {
    if (c == '\n') // cada \n é uma linha
    {
      count++;
    }
    if (count == numberLine)
    {
      fscanf(file, "%s", wordGamer);
      break;
    }
  }
  fclose(file);
}

int main()
{
  char word[6] = "";
  getLineFile("words.txt",  5, word);
  printf("%s", word);

  return 0;
}