// This is a module for implementing vectors
// 
// Developed by Fayzulloh
#include "number.h"
#include "vector.h"

struct vector {
    int n;
    struct Number ** vec;
};

struct vector * create_vector(int n) {
    struct vector * v = malloc(sizeof(struct vector));
    v->n = n;
    v->vec = malloc(sizeof(struct Number **));
    for (int i = 0; i < n; ++i) {
        v->vec[i] = malloc(sizeof(struct Number *));
    }
    return v;
}

int get_vector_n(struct vector * v) {
    return v->n;
}

struct Number * ith_element(struct vector * v, int i) {
    return v->vec[i];
}