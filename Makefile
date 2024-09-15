CC=gcc
FLAGS=-Wall -Werror -Wextra -std=c11
BUILD=../build/

all: graph

graph: graph.c polish.c matrix.c calc_matrix.c
	$(CC) $(FLAGS) graph.c polish.c matrix.c calc_matrix.c -o $(BUILD)graph

rebuild: clean graph

clean:
	rm -rf $(BUILD)graph
