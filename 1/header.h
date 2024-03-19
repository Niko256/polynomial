#include <cstddef>
#include <stdlib.h>
#include <complex.h>
#include <field.c>
#include <poly.c>
#include <prot.h>

typedef struct {
    int coeff_size;
    void* (*add)(void* poly_1, void* poly_2, void* result);
    void* (*product)(void* poly_1, void* poly_2, void* result);
    void* (*multiply_by_scalar)(void* poly, void* scalar, void* result);
    void* (*composition)(void* poly_1, void* poly_2, void* result);

    void* (*inverse_elem_sum)(void* elem, void* result);
    void* (*inverse_elem_product)(void* elem, void* result);
    void* (*neutral_elem_sum)(void* result);
    void* (*neutral_elem_prod)(void* result);
    void* (*zero)(void* coeff);
    
} Field_Info;


typedef struct{
    int degree; // the biggest degree in polynomial 
    void* coeffs;
    Field_Info* field;
} polynomial;


