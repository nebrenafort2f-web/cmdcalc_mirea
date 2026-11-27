#include "calc.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool parse_long(const char *str, long *out_val) {

    char *endsim = NULL;
    long val = strtol(str, &endsim, 10);

    if (*endsim != '\0') {
        return false;
    }

    *out_val = val;
    return true;
}

bool parse_operator(const char *str, char *out_op) {
    if (strlen(str) != 1) {
        return false;
    }

    char c = str[0];
    if (c == '+' || c == '-' || c == '*' || c == '%') {
        *out_op = c;
        return true;
    }

    return false;
}

int main(int argc, char *argv[]) {
    if (argc < 6) {
        printf("Ошибка: недостаточно аргументов.\n");
        printf("Использование: %s <число> <оп> <число> ... -k <ключ>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[argc - 2], "-k") != 0) {
        printf("Ошибка: ожидался флаг '-k' перед ключом, получено '%s'.\n", argv[argc - 2]);
        return 1;
    }

    int expr_args_count = argc - 3;
    if (expr_args_count % 3 != 0) {
        printf("Ошибка: некорректное количество аргументов для арифметических выражений.\n");
        return 1;
    }

    long key = strtol(argv[argc - 1], NULL, 10);

    int expr_count = expr_args_count / 3;

    long *results = (long *)calloc((unsigned int)expr_count, sizeof(long));

    for (int i = 0; i < expr_count; ++i) {
        int base_idx = 1 + i * 3;
        long left = 0;
        long right = 0;
        char op = '\0';

        if (!parse_long(argv[base_idx], &left)) {
            printf("Ошибка: некорректный левый операнд '%s' в выражении №%d.\n",
                   argv[base_idx], i + 1);
            free(results);
            return 1;
        }

        if (!parse_operator(argv[base_idx + 1], &op)) {
            printf("Ошибка: некорректный оператор '%s' в выражении №%d.\n",
                   argv[base_idx + 1], i + 1);
            free(results);
            return 1;
        }

        if (!parse_long(argv[base_idx + 2], &right)) {
            printf("Ошибка: некорректный правый операнд '%s' в выражении №%d.\n",
                   argv[base_idx + 2], i + 1);
            free(results);
            return 1;
        }

        if (!evaluate_expression(left, op, right, &results[i])) {
            free(results);
            return 1;
        }
    }

    char *decoded_str = decode_results(results, expr_count, key);
    if (decoded_str == NULL) {
        free(results);
        return 1;
    }

    print_output(results, expr_count, decoded_str);

    free(decoded_str);
    free(results);

    return 0;
}
