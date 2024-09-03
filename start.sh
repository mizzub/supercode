#!/bin/bash

# Чтение ключа для clang
echo -e "\nФайл .clang-format sдолжен находится в /src"
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
case $VAR2 in
    yes)
        cppcheck --enable=all --suppress=missingIncludeSystem "$1"
        ;;
    no)
        echo
        ;;
    *)
        echo "нет такого варианта в CPPCHECK"
        exit 1
        ;;
    
esac

# Определение типа компиляции
echo -e "Компиляция GCC, с флагами или без...(flags/noflags)? "
read VAR3

case $VAR3 in
    flags)
        gcc -std=c11 -Wall -Werror -Wextra "$1"
        ;;
    noflags)
        gcc "$1"
        ;;
    *)
        echo "Неверный ввод для компиляции."
        exit 1
        ;;
esac
#Если не работает. Сделать по инструкции
#cd /usr/local/lib
#sudo ln -s /Applications/Xcode.app/Contents/Developer/usr/lib/libLeaksAtExit.dylib
#
#
# Проверка LEAKS и запуск програмы
echo -e "Будем делать проверку LEAKS (1/2/no)?"
echo -e "(1) - добавляем 'grep LEAK'\n(2) - не добавляем grep LEAK"
read VAR4
case $VAR4 in
    1)
        leaks -atExit -- ./a.out | grep LEAK:
        ;;
    2)
        leaks -atExit -- ./a.out
        ;;
    no)
        echo
        ;;
    *)
        echo "нет такого варианта для LEAKS"
        exit 1
        ;;
esac
echo -e "Проверки пройдены. Результат выше ..."

