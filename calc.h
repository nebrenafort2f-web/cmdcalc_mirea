#ifndef CALC_H
#define CALC_H

#include <stdbool.h>

bool evaluate_expression(long left, char op, long right, long *result);

char *decode_results(const long *results, int count, long key);

void print_output(const long *results, int count, const char *decoded_str);

#endif
