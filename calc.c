#include "calc.h"
#include <stdio.h>
#include <stdlib.h>

bool evaluate_expression(long left, char op, long right, long *result) {
    switch (op) {
        case '+':
            *result = left + right;
            return true;
        case '-':
            *result = left - right;
            return true;
        case '*':
            *result = left * right;
            return true;
        case '%':
            *result = left % right;
            return true;
        default:
            return false;
    }
}

char *decode_results(const long *results, int count, long key) {
    char *decoded = (char *)malloc(((unsigned int)count + 1) * sizeof(char));

    for (int i = 0; i < count; ++i) {
        decoded[i] = (char)(results[i] - key);
    }
    decoded[count] = '\0';

    return decoded;
}

void print_output(const long *results, int count, const char *decoded_str) {
    for (int i = 0; i < count; ++i) {
        printf("Ответ №%d: %ld\n", i + 1, results[i]);
    }
    printf("Результирующая строка: %s\n", decoded_str);
}
