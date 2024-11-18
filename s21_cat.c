#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct arguments {
  int b, n, s, E, T, v;
} arguments;

arguments argument_parser(int argc, char** argv) {
  arguments arg = {0};  // zapolnena nulami
  int opt;
  struct option long_options[] = {
      {"number", no_argument, NULL, 'n'},
      {"squeeze-blank", no_argument, NULL, 's'},
      {"number-nonblank", no_argument, NULL, 'b'},
      {0, 0, 0, 0}  //
  };
  opt = getopt_long(argc, argv, "bnEeTt", long_options, 0); //v

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
    case 'e':
      arg.E = 1;
      arg.v = 1;
      break;
    case 'E':
      arg.E = 1;
      break;
    case 'T':
      arg.T = 1;
      break;
    case 't':
      arg.T = 1;
      arg.v = 1;
      break;
    case '?':
      perror("ERROR");
      exit(1);
      break;
    default:
      // perror("ERROR");
      // exit(1);
      break;
  }
}
char v_output(char ch) {
  if (ch == '\n' || ch == '\t') return ch;

  if (ch <= 31) {
    putchar('^');
    ch == 64;
  } else if (ch == 127) {
    putchar('^');
    ch = '?';
  }
  return ch;
}
void outline(arguments* arg, char* line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg->E && line[i] == '\n') {
      putchar('$');
    }
    if (arg->v) {
      line[i] = v_output(line[i]);
    }
    putchar(line[i]);
  }
}

void readfile() {}

int main(int argc, char* argv[]) {
  arguments arg = argument_parser(argc, argv);
  // printf("argc is %d, argv is %s", argc, argv[0]);
  FILE* f = fopen(argv[optind], "r");
  char* line = NULL;
  size_t memline = 0;
  int read = 0;
  read = getline(&line, &memline, f);

  while (read != -1) {
    outline(&arg, line, read);
    read = getline(&line, &memline, f);
  }
  fclose(f);
  return 0;
}

