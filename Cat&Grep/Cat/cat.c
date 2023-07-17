#include "cat.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

// -b (GNU: --number-nonblank)- нумерует только непустые строки
// -e предполагает и -v (GNU only: -E то же самое, но без применения -v)- также
// отображает символы конца строки как $ -n (GNU: --number)- нумерует все
// выходные строки -s (GNU: --squeeze-blank)- сжимает несколько смежных пустых
// строк -t предполагает и -v (GNU: -T то же самое, но без применения -v)- также
// отображает табы как ^I

void input(int argc, char *argv[], option_type *op);
void output(option_type *op, FILE *fp);

int main(int argc, char *argv[]) {  //количество аргументов, массив строк
  option_type op = {0};
  input(argc, argv, &op);

  if (optind == argc) {
    output(&op, stdin);
  } else {
    for (int i = optind; i < argc; i++) {
      FILE *fp = fopen(argv[i], "r");
      if (fp == NULL) {
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                argv[i]);
        continue;
      }
      output(&op, fp);
      fclose(fp);
    }
  }

  return 0;
}

void input(int argc, char *argv[], option_type *op) {
  int option;
  int argument_option_index;
  const char *short_options = "beEnstvT";
  const struct option long_options[] = {
      {"number-nonblank", no_argument, NULL, 'b'},
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {NULL, 0, NULL, 0}};
  while ((option = getopt_long(argc, argv, short_options, long_options,
                               &argument_option_index)) != -1) {
    switch (option) {
      case 'b':
        op->b = 1;
        break;
      case 'e':
        op->e = 1;
        op->v = 1;
        break;
      case 'n':
        op->n = 1;
        break;
      case 's':
        op->s = 1;
        break;
      case 't':
        op->t = 1;
        op->v = 1;
        break;
      case 'v':
        op->v = 1;
        break;
      default:
        exit(1);
    }
  }
}

void output(option_type *op, FILE *fp) {
  int line_number = 1;  //счетчик строк
  int ch;               //хранение символов из файла
  int end = 1;

  while ((ch = fgetc(fp)) != EOF) {
    if (!(op->s && ch == '\n' && end > 1)) {
      if (op->b && ch != '\n' && end != 0) {
        printf("%6d\t", line_number++);
      } else if (op->n && end != 0 && !op->b) {
        printf("%6d\t", line_number++);
      }
      if (ch == '\n') {
        end++;
      } else
        end = 0;
      if (op->e && ch == '\n') {
        printf("$\n");
      } else if (op->t && ch == '\t') {
        printf("^I");
      } else if (op->v && ch < 32 && ch != 10 && ch != 9) {
        printf("^%c", ch + 64);
      } else if (op->v && ch == 127) {
        printf("^?");
      } else {
        printf("%c", ch);
      }
    }
  }
}