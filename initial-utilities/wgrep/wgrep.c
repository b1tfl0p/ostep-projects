#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_matching_lines(char *searchterm, FILE *stream) {
  char *lineptr = NULL;
  unsigned long term_size = strlen(searchterm);

  size_t n = 0;
  ssize_t nread;

  while ((nread = getline(&lineptr, &n, stream)) != -1) {
    if (nread - 1 < term_size) {
      continue;
    }

    for (size_t cursor = 0, head = 0; head + term_size < nread;
         cursor = 0, ++head) {
      while (searchterm[cursor] == lineptr[head + cursor]) {
        ++cursor;
      }

      if (cursor == term_size) {
        printf("%s", lineptr);
        break;
      }
    }
  }

  if (lineptr != NULL) {
    free(lineptr);
  }
}

int main(int argc, char *argv[]) {
  // Error out if no search term is provided:
  if (argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }

  // Set the search term:
  char *searchterm = argv[1];
  FILE *fp;

  // If no filenames were provided...
  if (argc == 2) {
    // ...read from stdin:
    print_matching_lines(searchterm, stdin);
  } else {
    // ...read from each file:
    for (int i = 2; i < argc; i++) {
      fp = fopen(argv[i], "r");
      if (!fp) {
        printf("wgrep: cannot open file\n");
        exit(1);
      }

      print_matching_lines(searchterm, fp);
      fclose(fp);
    }
  }

  exit(0);
}
