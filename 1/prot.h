#ifndef PROT_H
#define PROT_H

#include "polynomial.h"

Field_Info* create_Field_info(
    int coeff_size, 
    void* (*add)(void* coeff_1, void* coeff_2),
    void* (*product)(void* coeff_1, void* coeff_2), 
    void* (*inverse_elem_add)(void* elem),
    void* (*inverse_elem_prod)(void* elem),
    void* (*neutral_elem_add)(),
    void* (*neutral_elem_prod)());

void free_Field(void* field);

// Integer field operations
Field_Info* create_int_Field_info();
void* int_add(void* coeff_1, void* coeff_2);
void* int_product(void* coeff_1, void* coeff_2);
void* int_inverse_add(void* coeff);
void* int_neutral_add();
void* int_inverse_prod(void* coeff);
void* int_neutral_prod();

// Real field operations
Field_Info* create_real_Field_info();
void* real_add(void* coeff_1, void* coeff_2);
void* real_product(void* coeff_1, void* coeff_2);
void* real_inverse_add(void* coeff);
void* real_neutral_add();
void* real_inverse_prod(void* coeff);
void* real_neutral_prod();

// Complex field operations
Field_Info* create_complex_Field_info();
void* complex_add(void* coeff_1, void* coeff_2);
void* complex_product(void* coeff_1, void* coeff_2);
void* complex_inverse_add(void* coeff);
void* complex_neutral_add();
void* complex_inverse_prod(void* coeff);
void* complex_neutral_prod();

// Polynomial operations
polynomial* sum(polynomial p_1, polynomial p_2);
void zero_coefficients(void* coeffs, int count, Field_Info* fi);

#endif // !PROT_H
#define PROT_H

#include "polynomial.h"





