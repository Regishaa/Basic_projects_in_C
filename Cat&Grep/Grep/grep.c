#include "grep.h"

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// -e- Шаблон
// -i- Игнорирует различия регистра.
// -v- Инвертирует смысл поиска соответствий.
// -c- Выводит только количество совпадающих строк.
// -l- Выводит только совпадающие файлы.
// -n- Предваряет каждую строку вывода номером строки из файла ввода.
// -h- Выводит совпадающие строки, не предваряя их именами файлов.
// -s- Подавляет сообщения об ошибках о несуществующих или нечитаемых файлах.
// -f file- Получает регулярные выражения из файла.
// -o- Печатает только совпадающие (непустые) части совпавшей строки.

void input(int argc, char *argv[], option_type *op);
void output(char *argv[], option_type *op);
void fflag(option_type *op);

int main(int argc, char *argv[]) {  //количество аргументов, массив строк
  option_type op = {0};
  input(argc, argv, &op);
  while (optind < argc) {
    output(argv, &op);
    optind++;  //элемент после флага
  }
  return 0;
}

void input(int argc, char *argv[], option_type *op) {
  int option;
  while ((option = getopt_long(argc, argv, "e:ivclnhsf:o", NULL, 0)) != -1) {
    switch (option) {
      case 'e':
        op->e = 1;
        strcat(op->str_buf, optarg);  //записывает после флага
        strcat(op->str_buf, "|");
        break;
      case 'i':
        op->i = 1;
        break;
      case 'v':
        op->v = 1;
        break;
      case 'c':
        op->c = 1;
        break;
      case 'l':
        op->l = 1;
        break;
      case 'n':
        op->n = 1;
        break;
      case 'h':
        op->h = 1;
        break;
      case 's':
        op->s = 1;
        break;
      case 'o':
        op->o = 1;
        break;
      case 'f':
        op->f = 1;
        strcpy(op->filename, optarg);
        fflag(op);
        break;
      default:
        exit(1);
    }
    if (op->v && op->o) {
      op->o = 0;
    }
  }
  if (!op->e && !op->f) {
    if (argc > optind) {
      strcat(op->str_buf,
             argv[optind]);  //добавляем аргумент в строку выражений
    }
    optind++;
  }
  if (op->e || op->f) {
    op->str_buf[strlen(op->str_buf) - 1] = '\0';  //удаляем последний пайп
  }
  if (argc - optind > 1) op->c_flag = 1;
}

void output(char *argv[], option_type *op) {
  FILE *file;
  regex_t reg;       // регулярное выражение
  regmatch_t start;  //струкура для хранения совпадений
  int counter = 0;
  int str_number = 0;
  int flag_i = REG_EXTENDED;  // компиляция в расширенном формате
  if (op->i) {
    flag_i = REG_EXTENDED | REG_ICASE;  //игнор регистра
  }
  regcomp(&reg, op->str_buf,
          flag_i);  //компилятор регулярных выражений в виде строки
  file = fopen(argv[optind], "r");
  if (file != NULL) {
    while (fgets(op->str, BUFFER, file) != NULL) {  //записываем строки из файла
      int match = regexec(&reg, op->str, 1, &start, 0);  //сравниваем
      str_number++;
      if (op->o) strcpy(op->str_o, op->str);
      if ((!match || op->v) && op->c_flag && !op->l && !op->h && !op->c &&
          !op->f)
        printf("%s:", argv[optind]);                         // filename
      if (!match) counter++;                                 // -c
      if (op->v) match = !match;                             //-v
      if (!match && !op->c && !op->l && !op->n && !op->o) {  // grep сам по себе
        printf("%s", op->str);
        if (op->str[strlen(op->str) - 1] != '\n') printf("\n");
      }
      if (!match && op->n && !op->c && !op->l) {
        if (op->o) {
          printf("%d:", str_number);
        } else
          printf("%d:%s", str_number, op->str);
        if (op->str[strlen(op->str) - 1] != '\n') printf("\n");  // -n
      }
      if (!match && op->o && !op->l && !op->c) {  //-o
        char *pointer = op->str_o;
        while ((regexec(&reg, pointer, 1, &start, 0) == 0)) {
          printf("%.*s\n", (int)(start.rm_eo - start.rm_so),
                 pointer + start.rm_so);  // End Offset & Start Offset
          pointer += start.rm_eo;
        }
      }
    }
    regfree(&reg);
    if (op->l && counter < 1 && op->v) {
      printf("%s\n", argv[optind]);
    }
    if (op->l && counter > 0 && !op->c) printf("%s\n", argv[optind]);  // -l
    if (op->c && op->c_flag && !op->h) printf("%s:", argv[optind]);    // -c
    if (op->c && !op->l && !op->v) printf("%d\n", counter);
    if (op->c && !op->l && op->v) printf("%d\n", str_number - counter);
    if (op->c && op->l) {
      if (counter > 0) {
        counter = 1;
        printf("%d\n%s\n", counter, argv[optind]);  // -cl
      } else
        printf("%d\n", counter);
    }
    fclose(file);
  } else {
    regfree(&reg);
    if (!op->s) {
      fprintf(stderr, "grep: %s: No such file or directory\n", argv[optind]);
    }
  }
}

void fflag(option_type *op) {
  FILE *f;
  f = fopen(op->filename, "r");
  if (f != NULL) {
    while (!feof(f)) {
      if (fgets(op->str, 1000, f) != NULL) {
        if (op->str[strlen(op->str) - 1] == '\n' && strlen(op->str) - 1 != 0)
          op->str[strlen(op->str) - 1] = '\0';
        strcat(op->str_buf, op->str);
        strcat(op->str_buf, "|");
      }
    }
    fclose(f);
  }
}