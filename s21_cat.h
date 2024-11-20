#ifndef MY_PROGRAM_H
#define MY_PROGRAM_H

#include <getopt.h>

typedef struct arguments {
    int b; // Number non-blank lines
    int n; // Number all lines
    int s; // Squeeze blank lines
    int E; // Show $ at end of lines
    int T; // Show ^I for tabs
    int v; // Visualize control characters
} arguments;

arguments Scan_Options(int argc, char* argv[]);
char v_using(char ch);
void outline(arguments* arg, char* line);
int output_nums(arguments* arg, char** argv);

#endif // MY_PROGRAM_H
