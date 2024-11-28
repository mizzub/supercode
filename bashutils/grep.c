
#include "grep.h"
#include <getopt.h>
#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <stdlib.h>

void pattern_add(arguments* arg, char* pattern) {
    //?
}
void add_reg_from_file(arguments* arg, char* filepath) {
    FILE* f = fopen(filepath,"r");
    if (f == NULL) {
        if (!arg->s) perror(filepath);
        perror(filepath);
        exit(1);
    }
    
}

arguments Scan_Options(int argc, char* argv[]) {
    arguments arg = {0}; // Инициализируем все флаги в 0
    int opt;
    while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
        switch (opt) {
            case 'e':
                arg.e = 1;
                arg.pattern = optarg; 
                break;
            case 'i':
                //;
                arg.i = REG_ICASE; // для учёта регистра независимого поиска
                break;
            case 'v':
                arg.v = 1;
                break;
            case 'c':
                arg.c = 1;
                break;
            case 'l':
                arg.c = 1;
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
            case 'f':
                arg.f = 1;
                break;
            case 'o':
                arg.o = 1;
                break;
            case '?':
                exit(1);
        }
    }
    if (arg.pattern == NULL) {
        arg.pattern == argv[optind];
        optind++;
    }
    if (argc - optind == 1) {
        arg.h = 1; // когда сделаем вызов на одном файл
    }
    return arg; // Возвращаем структуру аргументов
}
//
void output_line(char* line, int n) {
    for (int i=0; i<n ; i++) {
        putchar(line[i]);
    }
}

void output(arguments arg, int argc, char** argv) {
    regex_t re;
    int error = regcomp(&re, arg.pattern, arg.i); // принимает ссылку, паттерн. То самое число
    if (error) perror("Error");
    for(int i = optind; i < argc; i++) {
        processFile(arg, argv[i], &re);

    }
}


void processFile(arguments arg, char* path, regex_t* reg) {
    // -s не выводим сообщения об ошибках
    FILE* f = fopen(path,"r");
    if (f == NULL) {
        if (!arg.s) perror(path);
        exit(1);
    }
    char* line = NULL;
    size_t memlen = 0;
    int read = 0;
    int line_count = 1;
    int c = 0; //
    read = getline(&line, &memlen, f);
    //?
    while (read != -1) {
        int result = regexec(reg, line, 0, NULL, 0);
        
    if ((result == 0 && !arg.v)||(arg.v && result != 0)) {
        if (!arg.c && !arg.l) {
            if (!arg.h) printf("%s:", path);
            if (arg.n) printf("%d:", line_count); //только в случ совпадения
         output_line(line, read);
        }
         c++;//
        }
        read = getline(&line,&memlen, f);
        line_count++;
    }
    free(line);
    if (arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        printf("%d\n",c); //конец строки
    } 
    if (arg.l && c > 0) printf("%s\n", path);
    fclose(f);
}

int main(int argc, char** argv) {
    arguments arg = Scan_Options(argc, argv);
    output(arg, argc,argv);
    return 0;
}
