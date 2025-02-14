#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc == 1) {
    exit(EXIT_SUCCESS);
  }

  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      exit(EXIT_FAILURE);
    }

    char buffer[100];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
      printf("%s", buffer);
    }

    fclose(fp);
  }

  exit(EXIT_SUCCESS);
}
