// e - принимает рег выражения
// v - путь до файла
// optarg укажет на ту строку после флага -e
// optind
// REG_ICASE - флаг игнорир регистра
// Функция regexec выполняет поиск по строке с использованием скомпилированного
// регулярного выражения. Функция regcomp компилирует регулярное выражение,
// указанное в строке, и сохраняет его в структуре regex_t, чтобы его можно было
// использовать позже для поиска. regmatch_t match - структура ещё из библиотеки
// match.rm_so - хранит номер символ в котором есть совпадения на номер начала
// match.rm_eo - на конец

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct arguments {
  int e, i, c, l, n, v, h, s, f, o;
  int exit;
  char* pattern;
} arguments;

arguments scan_options(int argc, char** argv) {
  arguments arg = {0};
  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        arg.pattern = optarg;
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'f':
        arg.f = 1;
        break;
      case 'o':
        arg.o = 1;
        break;
      case '?':
        arg.exit = 1;
        break;
    }
  }
  // Получение шаблона
  if (arg.pattern == NULL) {
    arg.pattern =
        argv[optind];  // Устанавливаем последний аргумент как шаблон для поиска
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void output_line(char* line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') putchar('\n');
}

int processFile(arguments arg, char* path, regex_t* reg) {
  char
      line[10024];  // Буфер для строки (можно изменить размер по необходимости)
  int line_count = 1;
  int c_count = 0;
  int exit_flag = 0;

  FILE* f = fopen(path, "r");
  if (f == NULL) {
    if (!arg.s) perror(path);
    exit_flag = 1;
  } else {
    // Читаем строки из файла
    while (fgets(line, sizeof(line), f) != 0) {
      int result = regexec(reg, line, 0, NULL, 0);
      if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
        if (!arg.c && !arg.l) {
          if (!arg.h) printf("%s:", path);
          if (arg.n) printf("%d:", line_count);
          output_line(
              line,
              strlen(line));  // Используем strlen для передачи длины строки
        }
        c_count++;
      }
      line_count++;
    }

    if (arg.c && !arg.l) {
      if (!arg.h) printf("%s:", path);
      printf("%d\n", c_count);
    }
    if (arg.l && c_count > 0) printf("%s\n", path);

    fclose(f);
  }
  return exit_flag;
}

void output(arguments arg, int argc, char** argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, arg.i);
  if (error) perror("error");
  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &re);
  }
  regfree(&re);
}

int main(int argc, char** argv) {
  int exit_out = 0;
  arguments arg = scan_options(argc, argv);
  if (arg.exit == 0) {
    output(arg, argc, argv);
  } else {
    exit_out = 1;
  }
  return exit_out;
}

// починить main вначало
