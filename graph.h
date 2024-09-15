#ifndef MAIN_H_
#define MAIN_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define _USE_MATH_DEFINES
#define WIDTH 80
#define HEIGHT 25
#define POINT '.'
#define STAR '*'

struct stack {
    char ch;
    struct stack *next;
};

// POLISH
int check_input(char *input_string);
struct stack *push(struct stack *, char);  // помещаем в стек
char delete (struct stack **head);         // удаляем из стека
int priority(char);
void polish_notation(struct stack *operations, char *input_str, char *output_str);

// CALCULATOR
double counter(char *output_str, double x);
void add_func_for_graph(char **graph, int height, int width, char *polish);

// DRAW
char **malloc_matrix(int height, int width);
void init_graph(char **graph, int height, int width);
void draw_graph(char **graph, int height);
void free_matrix(char **graph, int height);

#endif