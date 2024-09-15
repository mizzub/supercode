#include "graph.h"

int main() {
    char **graph = malloc_matrix(HEIGHT, WIDTH + 1);
    struct stack *operations = NULL;
    char input_formula[100], polish_formula[100];
    do {
        system("clear");
        printf("Введите формулу: ");
        for (int i = 0; i < 100; i++) {
            char symbol = getchar();
            if (symbol == '\n') {
                input_formula[i] = '\0';
                break;
            }
            if (symbol != ' ')
                input_formula[i] = symbol;
            else
                i--;  // читаем формулу игнор пробелов
        }
    } while (!check_input(input_formula));
    polish_notation(operations, input_formula, polish_formula);
    printf("Формула в польской нотации: %s\n", polish_formula);

    init_graph(graph, HEIGHT, WIDTH);
    add_func_for_graph(graph, HEIGHT, WIDTH, polish_formula);  // размещаем звездочки в матрицу graph
    draw_graph(graph, HEIGHT);                                 // рисуем график
    free_matrix(graph, HEIGHT);                                // чистим память матрицы
    return 0;
}