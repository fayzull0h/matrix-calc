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

void simplify(struct Number * n) {
    int factor = gcd(n->num, n->denom);
    n->num /= factor;
    n->denom /= factor;

    if (n->num < 0 && n->denom < 0) {
        n->num *= -1;
        n->denom *= -1;
    } else if (n->num > 0 && n->denom < 0) {
        n->num *= -1;
        n->denom *= -1;
    }
}

struct Number * create_number(int num, int denom) {
    struct Number * newnum = malloc(sizeof(struct Number));
    newnum->num = num;
    newnum->denom = denom;
    simplify(newnum);
    return newnum;
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
                new_num = create_number(DIVIDE_BY_ZERO.num, DIVIDE_BY_ZERO.denom);
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
    simplify(new_num);
    return new_num;
}

struct Number * multiply(struct Number * n1, struct Number * n2) {
    struct Number * new_num = malloc(sizeof(struct Number));
    new_num->num = n1->num * n2->num;
    new_num->denom = n1->denom * n2->denom;
    simplify(new_num);
    return new_num;
}

struct Number * divide(struct Number * n1, struct Number * n2) {
    struct Number * newn2 = create_number(n2->denom, n2->num);
    struct Number * product = multiply(n1, newn2);
    free(newn2);
    return product;
}

struct Number * add(struct Number * n1, struct Number * n2) {
    struct Number * sum = malloc(sizeof(struct Number));
    sum->num = n1->num * n2->denom + n2->num * n1->denom;
    sum->denom = n1->denom * n2->denom;
    simplify(sum);
    return sum;
}

struct Number * subtract(struct Number * n1, struct Number * n2) {
    struct Number * difference = malloc(sizeof(struct Number));
    struct Number * newn2 = create_number(-1 * n2->num, n2->denom);
    difference = add(n1, newn2);
    free(newn2);
    return difference;
}

void print_number(struct Number * num) {
    if (num->denom == 1) {
        printf("%d", num->num);
        return;
    }
    printf("%d / %d", num->num, num->denom);
}

bool num_equal(struct Number * n1, struct Number * n2) {
    return n1->num == n2->num && n1->denom == n2->denom;
}

char * str_from_num(struct Number * n) {
    
}