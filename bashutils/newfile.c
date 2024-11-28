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

arguments Scan_Options(int argc, char *argv[], int *illigal_opt);
void printData(arguments *arg, FILE *f);

int main(int argc, char *argv[]) {
  int illigal_opt = 0;
  int exit_flag = 0;
  arguments arg = Scan_Options(argc, argv, &illigal_opt);
  if (illigal_opt == 0) {
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
          printData(&arg, file);  // Вызов функции printData с указателем на arg
                                  // и открытым файлом
          fclose(file);  // Закрываем файл после обработки
        }
      }
    }
  }
  return exit_flag;
}

arguments Scan_Options(int argc, char *argv[], int *illigal_opt) {
  arguments arg = {0};  // Инициализируем все флаги в 0
  int opt;

  while ((opt = getopt_long(argc, argv, "bnsEeTtv", long_options, NULL)) !=
             -1 &&
         *(illigal_opt) == 0) {
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
        *(illigal_opt) = 1;

        break;
      default:
        *(illigal_opt) = 1;
        //
        break;
    }
  }

  return arg;  // Возвращаем структуру аргументов
}

void printData(arguments *arg, FILE *f) {
  char pr_ch = 0, ch = 0;  // Предыдущий символ // Текущий символ
  int tab = 0, s = 0, line_number = 0, noEmpty = 1, pr_pr_ch = 0;
  while ((ch = fgetc(f)) != EOF) {
    s = 0;
    if (arg->s) {  // Обработка сжатия пустых строк
      if (pr_ch == '\n' && ch == '\n' && pr_pr_ch == '\n') s = 1;
      if (s == 0) pr_pr_ch = pr_ch;
      pr_ch = ch;
    }
    if ((arg->n) && (s == 0)) {  // Нумерация всех строк
      if (noEmpty) {
        printf("%6d\t", ++line_number);
        noEmpty = 0;
      }
      if (ch == '\n') noEmpty = 1;
    }
    if ((arg->b) && (s == 0)) {
      arg->n = 0;  // Нумерация только непустых строк
      if (noEmpty && ch != '\n') {
        printf("%6d\t", ++line_number);
        noEmpty = 0;
      }
      if (ch == '\n') noEmpty = 1;
    }
    if ((arg->E && ch == '\n') &&
        (s == 0)) {  // Выводим $ в конце строки, если включен флаг -E
      printf("$");
    }
    if ((arg->T && ch == '\t') && (s == 0)) {  // Визуализация табуляций
      tab = 0;  // Пропускаем вывод символа табуляции
    } else {
      tab = 1;
    }
    if ((arg->v) && (s == 0)) {  // Визуализация управляющих символов
      if (ch <= 31 && ch != '\n' && ch != '\t') {
        putchar('^');
        ch += 'A' - 1;  // Преобразование для визуализации
      } else if (ch == 127) {
        putchar('^');
        ch = '?';  // Визуализация символа DEL
      }
    }
    if ((tab) && (s == 0)) {
      putchar(ch);
    } else if (!tab)
      printf("^I");  // Печатаем текущий символ
  }
}
