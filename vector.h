// This is the interface for a module that implements vector functionality
//
// Developed by Fayzulloh Ergashev

struct vector;

struct vector * create_vector(int n);

int get_vector_n(struct vector * v);

struct Number * ith_element(struct vector * v, int i);