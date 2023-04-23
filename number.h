// The header file for a Numbers module
// The key functionality of this module is to allow the storing
// of numbers as fractions instead of decimals
// 
// Developed by Fayzulloh Ergashev

struct Number;

struct Number * num_from_str(char * str);

void print_number(struct Number * n);

struct Number * multiply(struct Number * n1, struct Number * n2);

struct Number * divide(struct Number * n1, struct Number * n2);

struct Number * add(struct Number * n1, struct Number * n2);

struct Number * subtract(struct Number * n1, struct Number * n2);