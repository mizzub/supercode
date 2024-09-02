#!/bin/bash

# Чтение ключа для clang
echo -e "Введите ключ для clang (-i/-n/-in):"
read VAR1
case $VAR1 in
    -i)
        clang-format -i "$1"
        ;;
    -n)
        clang-format -n "$1"
        ;;
    -in)
        clang-format -i "$1"
        clang-format -n "$1"
        ;;
    *)
        echo "Неверный ключ для clang."
        exit 1
        ;;
esac

# Проверка CPPCHECK
echo -e "Будем делать проверку CPPCHECK (yes/no)?"
read VAR2

if [[ $VAR2 == "yes" ]]; then
    cppcheck --enable=all --suppress=missingIncludeSystem "$1"
fi
if [[ $VAR2 != "no" ]]; then
    echo "Неверный ввод для CPPCHECK."
    exit 1
fi

# Определение типа компиляции
echo -e "Компиляция GCC, простая или сложная (easy/hard)? "
read VAR3

case $VAR3 in
    hard)
        gcc -std=c11 -Wall -Werror -Wextra -fsanitize=address "$1"
        ;;
    easy)
        gcc "$1"
        ;;
    *)
        echo "Неверный ввод для компиляции."
        exit 1
        ;;
esac


