#include <stdlib.h>


typedef struct{
    int degree; // the biggest degree in polynomial
    void** coeffs;
    coeff_field* field;
} polynomial;


typedef struct {
    polynomial* (*add)(void* poly_1, void* poly_2, void* result);
    polynomial* (*multiply)(void* poly_1, void* poly_2, void* result);
    polynomial* (*multiply_by_scalar)(void* poly, void* scalar, void* result);
    polynomial* (*composition)(void* poly_1, void* poly_2, void* result);
} coeff_field; 

