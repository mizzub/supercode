#include "graph.h"

void polish_notation(struct stack *operations, char *input_str, char *output_str) {
    int point = 0;
    ;  // элемент выходной строки
    for (int i = 0; input_str[i] != '\0'; i++) {
        if (input_str[i] == ')') {  // выпихиваем в стек предыдущие операции
            while ((operations->ch) != '(')
                output_str[point++] = delete (&operations);  // вынос операции в польскую нотацию
            delete (&operations);                            // удаляем скобку
        }
        if ((input_str[i] >= '0' && input_str[i] <= '9') || input_str[i] == 'x')
            output_str[point++] = input_str[i];  // вынос цифр и х в польскую нотацию

        if (input_str[i] == 's' && input_str[i + 1] == 'i' && input_str[i + 2] == 'n') {
            if (operations == NULL) {
                operations = push(operations, 's');
            } else if (priority(operations->ch) < priority('s'))
                operations = push(operations, 's');
            else {
                while ((operations != NULL) && (priority(operations->ch) >= priority('s')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 's');
            }
            i += 3;
        }
        if (input_str[i] == 'c' && input_str[i + 1] == 'o' && input_str[i + 2] == 's') {
            if (operations == NULL)
                operations = push(operations, 'c');
            else if (priority(operations->ch) < priority('c'))
                operations = push(operations, 'c');
            else {
                while ((operations != NULL) && (priority(operations->ch) >= priority('c')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 'c');
            }
            i += 3;
        }
        if (input_str[i] == 't' && input_str[i + 1] == 'a' && input_str[i + 2] == 'n') {
            if (operations == NULL)
                operations = push(operations, 't');
            else if (priority(operations->ch) < priority('t'))
                operations = push(operations, 't');
            else {
                while ((operations != NULL) && (priority(operations->ch) >= priority('t')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 't');
            }
            i += 3;
        }
        if (input_str[i] == 'c' && input_str[i + 1] == 't' && input_str[i + 2] == 'g') {
            if (operations == NULL)
                operations = push(operations, 'g');
            else if (priority(operations->ch) < priority('g'))
                operations = push(operations, 'g');
            else {
                while ((operations != NULL) && (priority(operations->ch) >= priority('g')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 'g');
            }
            i += 3;
        }
        if (input_str[i] == 's' && input_str[i + 1] == 'q' && input_str[i + 2] == 'r' &&
            input_str[i + 3] == 't') {
            if (operations == NULL)
                operations = push(operations, 'q');
            else if (priority(operations->ch) < priority('q'))
                operations = push(operations, 'q');
            else {
                while ((operations != NULL) && (priority(operations->ch) >= priority('q')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 'q');
            }
            i += 4;
        }
        if (input_str[i] == 'l' && input_str[i + 1] == 'n') {
            if (operations == NULL)
                operations = push(operations, 'l');
            else if (priority(operations->ch) < priority('l'))
                operations = push(operations, 'l');
            else {
                while ((operations != NULL) && (priority(operations->ch) >= priority('l')))
                    output_str[point++] = delete (&operations);
                operations = push(operations, 'l');
            }
            i += 2;
        }
        if (input_str[i] == '(') operations = push(operations, '(');
        if (input_str[i] == '+' || input_str[i] == '-' || input_str[i] == '/' || input_str[i] == '*') {
            if (operations == NULL)
                operations = push(operations, input_str[i]);
            else if (priority(operations->ch) < priority(input_str[i]))
                operations = push(operations, input_str[i]);
            else {
                while ((operations != NULL) && (priority(operations->ch) >= priority(input_str[i])))
                    output_str[point++] = delete (&operations);  // проверка на приоритетность
                operations = push(operations, input_str[i]);
            }
        }
    }

    while (operations != NULL) output_str[point++] = delete (&operations);  // весь выход формирем тут
    output_str[point] = '\0';
}

char delete (struct stack **head) {
    struct stack *upper;  // создаем левый указатель структурного типа
    char symbol;
    if (*head == NULL) return '\0';  // проверка стека на пустоту
    upper = *head;                   // присваем указатель на начало стека
    symbol = upper->ch;              // записываем операцию в переменную
    *head = upper->next;             // переключение конца стека
    free(upper);                     // удаление предыдущего элемента стека
    return symbol;                   // возврат операции
}

struct stack *push(struct stack *head, char symbol) {
    struct stack *pt;
    if ((pt = malloc(sizeof(struct stack))) == NULL) {
        puts("Невозможно выделить память");
        exit(-1);  // РАЗОБРАТЬ
    }
    pt->ch = symbol;
    pt->next = head;
    return pt;
}

int priority(char symbol) {
    switch (symbol) {
        case 'c':
        case 's':
        case 't':
        case 'g':
        case 'q':
        case 'l':
            return 4;
        case '*':
        case '/':
            return 3;

        case '-':
        case '+':
            return 2;

        case '(':
            return 1;
    }
    return 0;
}

int check_input(char *input_string) {
    char *p = input_string;
    int i = 0;
    while (p[i]) {
        char oper;
        int count;

        if (p[i] == '(') {
            oper = '(';
            count = 1;
        } else if (p[i] == ')') {
            oper = ')';
            count = 1;
        } else if (p[i] == 's' && p[i + 1] == 'i' && p[i + 2] == 'n') {
            oper = 'S';
            count = 3;
        } else if (p[i] == 'c' && p[i + 1] == 'o' && p[i + 2] == 's') {
            oper = 'C';
            count = 3;
        } else if (p[i] == 't' && p[i + 1] == 'a' && p[i + 2] == 'n') {
            oper = 'T';
            count = 3;
        } else if (p[i] == 'c' && p[i + 1] == 't' && p[i + 2] == 'g') {
            oper = 'Z';
            count = 3;
        } else if (p[i] == 's' && p[i + 1] == 'q' && p[i + 2] == 'r' && p[i + 3] == 't') {
            oper = 'Q';
            count = 4;
        } else if (p[i] == 'l' && p[i + 1] == 'n') {
            oper = 'L';
            count = 2;
        } else if (p[i] == '*') {
            oper = '*';
            count = 1;
        } else if (p[i] == '/') {
            oper = '/';
            count = 1;
        } else if (p[i] == '+') {
            oper = '+';
            count = 1;
        } else if (p[i] == '-') {
            oper = '-';
            count = 1;
        } else if (p[i] == 'x') {
            oper = 'x';
            count = 1;
        } else {
            oper = '0';
        }

        if (oper != '0') {
            i += count;
        } else {
            if (p[i] < '0' || p[i] > '9') return 0;
            i++;
        }
    }
    return 1;
}