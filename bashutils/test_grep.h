#!/bin/bash

run_diff() {
    echo "Сравнение с помощью: $1"
    result=$(eval "$1")

    if [ -z "$result" ]; then
        echo "Все хорошо."
    else
        echo "Есть проблемы:"
        echo "$result"
    fi
    echo "-------------------------------"
}

run_diff "diff <(./s21_grep asd grep.txt) <(grep asd grep.txt)"
run_diff "diff <(./s21_grep -e asd grep.txt) <(grep -e asd grep.txt)"
run_diff "diff <(./s21_grep -i asd grep.txt) <(grep -i asd grep.txt)"
run_diff "diff <(./s21_grep -v asd grep.txt) <(grep -v asd grep.txt)"
run_diff "diff <(./s21_grep -c asd grep.txt) <(grep -c asd grep.txt)"
run_diff "diff <(./s21_grep -l asd grep.txt) <(grep -l asd grep.txt)"
run_diff "diff <(./s21_grep -n asd grep.txt) <(grep -n asd grep.txt)"
run_diff "diff <(./s21_grep -h asd grep.txt) <(grep -h asd grep.txt)"
run_diff "diff <(./s21_grep -s asd grep.xt) <(grep -s asd grep.xt)"
run_diff "diff <(./s21_grep -n "[1-5]" grep.txt) <(grep -n "[1-5]" grep.txt)"
run_diff "diff <(./s21_grep asd grep.txt grep_2.txt) <(grep asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -e asd grep.txt grep_2.txt) <(grep -e asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -i asd grep.txt grep_2.txt) <(grep -i asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -v asd grep.txt grep_2.txt) <(grep -v asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -c asd grep.txt grep_2.txt) <(grep -c asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -l asd grep.txt grep_2.txt) <(grep -l asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -n asd grep.txt grep_2.txt) <(grep -n asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -h asd grep.txt grep_2.txt) <(grep -h asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -s asd grep.txt rep_2.txt) <(grep -s asd grep.txt rep_2.txt)"
run_diff "diff <(./s21_grep -d asd grep.txt rep_2.txt) <(grep -d asd grep.txt rep_2.txt)"
run_diff "diff <(./s21_grep -in asd grep.txt grep_2.txt) <(grep -in asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -ie asd grep.txt grep_2.txt) <(grep -ie asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -iv asd grep.txt grep_2.txt) <(grep -iv asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -ic asd grep.txt grep_2.txt) <(grep -ic asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -il asd grep.txt grep_2.txt) <(grep -il asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -in asd grep.txt) <(grep -in asd grep.txt)"
run_diff "diff <(./s21_grep -ie asd grep.txt) <(grep -ie asd grep.txt)"
run_diff "diff <(./s21_grep -iv asd grep.txt) <(grep -iv asd grep.txt)"
run_diff "diff <(./s21_grep -ic asd grep.txt) <(grep -ic asd grep.txt)"
run_diff "diff <(./s21_grep -il asd grep.txt) <(grep -il asd grep.txt)"


# Проверка комбинаций двойных флагов
run_diff "diff <(./s21_grep -ie asd grep.txt grep_2.txt) <(grep -ie asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -iv asd grep.txt grep_2.txt) <(grep -iv asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -ic asd grep.txt grep_2.txt) <(grep -ic asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -il asd grep.txt grep_2.txt) <(grep -il asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -in asd grep.txt grep_2.txt) <(grep -in asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -is asd grep.txt grep_2.txt) <(grep -is asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -id asd grep.txt grep_2.txt) <(grep -id asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -lc asd grep.txt grep_2.txt) <(grep -lc asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -lv asd grep.txt grep_2.txt) <(grep -lv asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -ll asd grep.txt grep_2.txt) <(grep -ll asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -ln asd grep.txt grep_2.txt) <(grep -ln asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -ls asd grep.txt grep_2.txt) <(grep -ls asd grep.txt grep_2.txt)"
run_diff "diff <(./s21_grep -ld asd grep.txt grep_2.txt) <(grep -ld asd grep.txt grep_2.txt)"

# Проверка комбинаций с инверсией
run_diff "diff <(./s21_grep -v -i asd grep.txt) <(grep -v -i asd grep.txt)"
run_diff "diff <(./s21_grep -v -e asd grep.txt) <(grep -v -e asd grep.txt)"
run_diff "diff <(./s21_grep -v -c asd grep.txt) <(grep -v -c asd grep.txt)"
run_diff "diff <(./s21_grep -v -l asd grep.txt) <(grep -v -l asd grep.txt)"
