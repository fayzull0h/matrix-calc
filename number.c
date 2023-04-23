// This is a module for a number structure
// The key functionality is that you can store fractions instead of decimals

#include "number.h"
#include <stdlib.h>
#include <stdbool.h>

struct Number {
    int num;
    int denom;
};

struct Number * num_from_str(char * str) {
    struct Number * new_num = malloc(sizeof(struct Number));
    new_num->num = 1;
    new_num->denom = 1;

    bool fraction = false;

    for (int i = 0; str[i]; ++i) {
        if (!fraction) {
            new_num->num *= ch_to_d(str[i]);
        } else {
            new_num->denom *= ch_to_d(str[i]);
        }
    }
}
