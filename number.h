// The header file for a Numbers module
// The key functionality of this module is to allow the storing
// of numbers as fractions instead of decimals
// 
// Developed by Fayzulloh Ergashev

#include <stdbool.h>

struct Number;

struct Number * num_from_str(char * str);

struct Number * create_number(int num, int denom);

void print_number(struct Number * n);

struct Number * multiply(struct Number * n1, struct Number * n2);

struct Number * divide(struct Number * n1, struct Number * n2);

struct Number * add(struct Number * n1, struct Number * n2);

struct Number * subtract(struct Number * n1, struct Number * n2);

bool num_equal(struct Number * n1, struct Number * n2);

char * str_from_num(struct Number * n);