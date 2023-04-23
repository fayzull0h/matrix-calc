// This is a module for a number structure
// The key functionality is that you can store fractions instead of decimals

#include "number.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static int ch_to_d(char c) {
    if (c == '-') {
        return -1;
    }
    if (c < '0' || c > '9') {
        return 10;
    }
    return c - 48;
}

struct Number {
    int num;
    int denom;
};

int gcd(int m, int n) {
  if ((m % n) == 0) { // Base case
    return n;
  } else {
    return gcd(n, m%n);
  }
}

static struct Number DIVIDE_BY_ZERO = {-2147483648, 0};

void simplify(struct Number * num) {
    int factor = gcd(num->num, num->denom);
    num->num /= factor;
    num->denom /= factor;
}

struct Number * num_from_str(char * str) {
    struct Number * new_num = malloc(sizeof(struct Number));
    new_num->num = ch_to_d(str[0]);
    new_num->denom = 1;
    bool fraction = false;

    for (int i = 1; str[i]; ++i) {
        if (str[i] == '/') {
            fraction = true;
            if (str[i + 1] == '0') {
                new_num->num = DIVIDE_BY_ZERO.num;
                new_num->denom = DIVIDE_BY_ZERO.denom;
                return new_num;
            }
            new_num->denom = ch_to_d(str[i + 1]);
            ++i;
        } else if (!fraction) {
            new_num->num = new_num->num * 10 + ch_to_d(str[i]);
        } else {
            new_num->denom = new_num->denom * 10 + ch_to_d(str[i]);
        }
    }
    return new_num;
}

struct Number * multiply(struct Number * num1, struct Number * num2) {
    struct Number * new_num = malloc(sizeof(struct Number));
    new_num->num = num1->num * num2->num;
    new_num->denom = num1->denom * num2->denom;
    simplify(new_num);
    return new_num;
}

void print_number(struct Number * num) {
    if (num->denom == 1) {
        printf("%d", num->num);
        return;
    }
    printf("%d / %d", num->num, num->denom);
}