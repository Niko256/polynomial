#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <stddef.h>
#include <stdlib.h>
#include <complex.h>


typedef struct {
    int coeff_size;
    void* (*add)(void* coeff_1, void* coeff_2);
    void* (*product)(void* coeff_1, void* coeff_2);

    void* (*inverse_elem_add)(void* elem);
    void* (*inverse_elem_prod)(void* elem);
    void* (*neutral_elem_add)();
    void* (*neutral_elem_prod)();
} Field_Info;

typedef struct {
    int degree;
    void* coeffs;
    Field_Info* field;
} polynomial;

#endif // !POLYNOMIAL_H
