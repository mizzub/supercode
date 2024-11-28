#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct arguments {
  int b;  // Нумеровать только непустые строки
  int n;  // Нумеровать все строки
  int s;  // Сжимать пустые строки
  int E;  // Выводить символ $ в конце строк
  int T;  // Выводить ^I вместо табуляций
  int v;
  int e;
  int t;  // Визуализировать управляющие символы
} arguments;

struct option long_options[] = {
    {"squeeze-blank", no_argument, NULL, 's'},
    {"number", no_argument, NULL, 'n'},
    {"number-nonblank", no_argument, NULL, 'b'},
    {0, 0, 0, 0}  // Конец массива опций
};

arguments Scan_Options(int argc, char *argv[]);
void printData(arguments *arg, FILE *f);

int main(int argc, char *argv[]) {
  arguments arg = Scan_Options(argc, argv);
  int exit_flag = 0;

  if (optind >= argc) {
    fprintf(stderr, "Error: No input files provided.\n");
    exit_flag = 1;
  } else {
    for (int i = optind; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (!file) {
        perror("Error opening file");
        exit_flag = 1;
      } else {
        printData(&arg, file);  // Вызов функции printData с указателем на arg и
                                // открытым файлом
        fclose(file);  // Закрываем файл после обработки
      }
    }
  }

  return exit_flag;
}

arguments Scan_Options(int argc, char *argv[]) {
  arguments arg = {0};  // Инициализируем все флаги в 0
  int opt;

  while ((opt = getopt_long(argc, argv, "bnsEeTtv", long_options, NULL)) !=
         -1) {
    switch (opt) {
      case 'b':
        arg.b = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'E':
        arg.E = 1;
        break;
      case 'e':
        arg.E = 1;
        arg.v = 1;
        break;
      case 't':
        arg.T = 1;
        arg.v = 1;
        break;
      case 'T':
        arg.T = 1;
        break;
      case 'v':
        arg.v = 1;
        break;
      case '?':
        exit(1);
    }
  }

  return arg;  // Возвращаем структуру аргументов
}

void printData(arguments *arg, FILE *f) {
  int line_number = 0;  // Счетчик строк
  int noEmpty = 1;  // Флаг для отслеживания непустых строк
  int empty = 0;  // Флаг для отслеживания пустых строк
  char pr_ch = 0;  // Предыдущий символ
  char ch = 0;     // Текущий символ
  int tab = 0;

  while ((ch = fgetc(f)) != EOF) {
    if (arg->s) {  // Обработка сжатия пустых строк
      if (pr_ch == '\n' && ch == '\n') {
        if (empty) continue;  // Пропускаем если уже была пустая строка
        empty = 1;
      } else {
        empty = 0;
      }
      pr_ch = ch;
    }
    if (arg->n) {  // Нумерация всех строк
      if (noEmpty) {
        printf("%6d\t", ++line_number);
        noEmpty = 0;
      }
      if (ch == '\n') noEmpty = 1;
    }
    if (arg->b) {
      arg->n = 0;  // Нумерация только непустых строк
      if (noEmpty && ch != '\n') {
        printf("%6d\t", ++line_number);
        noEmpty = 0;
      }
      if (ch == '\n') noEmpty = 1;
    }
    if (arg->E &&
        ch == '\n') {  // Выводим $ в конце строки, если включен флаг -E
      printf("$");
    }
    if (arg->T && ch == '\t') {  // Визуализация табуляций
      tab = 0;  // Пропускаем вывод символа табуляции
    } else {
      tab = 1;
    }

    if (arg->v) {  // Визуализация управляющих символов
      if (ch <= 31 && ch != '\n' && ch != '\t') {
        putchar('^');
        ch += 'A' - 1;  // Преобразование для визуализации
      } else if (ch == 127) {
        putchar('^');
        ch = '?';  // Визуализация символа DEL
      }
    }
    if (tab) {
      putchar(ch);
    } else if (!tab)
      printf("^I");  // Печатаем текущий символ
  }
}
