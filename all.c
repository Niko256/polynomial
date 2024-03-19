#include <stdio.h>
#include <header.h>
#include <stdlib.h>
#include <complex.h>
#include <prot.h>

#include <cstddef>
#include <stdlib.h>
#include <complex.h>


typedef struct {
    int coeff_size;
    void* (*add)(void* poly_1, void* poly_2, void* result);
    void* (*product)(void* poly_1, void* poly_2, void* result);
    void* (*multiply_by_scalar)(void* poly, void* scalar, void* result);
    void* (*composition)(void* poly_1, void* poly_2, void* result);
} Field_Info;



typedef struct{
    int degree; // the biggest degree in polynomial 
    void* coeffs;
    Field_Info* field;
} polynomial;





Field_Info* create_Field_info(
    int coeff_size, 
    void* (*add)(void* poly_1, void* poly_2, void* result),
    void* (*product)(void* poly_1, void* poly_2, void* result),
    void* (*multiply_by_scalar)(void* poly, void* scalar, void* result)) 
    
{  
    Field_Info* fi = (Field_Info*) malloc(sizeof(Field_Info));
    
    if (fi == NULL) {
        return NULL;
    }
    
    fi->coeff_size = coeff_size;
    fi->add = add;
    fi->product = product;
    fi->multiply_by_scalar = multiply_by_scalar;

    return fi;
}

void free_Field(void* field) {
    free(field);
}

Field_Info* create_int_Field_info() {
    return create_Field_info(sizeof(int),
    &int_add,
    &int_product,
    &multiply_by_int_scalar);
}

Field_Info* create_real_Field_info() {
    return create_Field_info(sizeof(double),
    &real_add,
    &real_product,
    &multiply_by_real_scalar);
}


Field_Info* create_complex_Field_info(){
    return create_Field_info(sizeof(complex double),
    &complex_add,
    &complex_product,
    &multiply_by_complex_scalar);
}


void* int_additive_inverse(void* elem, void* int_inverse) {
    *(int*)result = -(*(int*)elem);
    return result;
}

void* int_zero(void* result) {
    *(int*)result = 0;
    return result;
}


void* real_additive_inverse(void* elem, void* result) {
    *(double*)result = -(*(double*)elem);
    return result;
}

void* real_zero(void* result) {
    *(double*)result = 0.0;
    return result;
}

void* complex_additive_inverse(void* elem, void* result) {
    *(complex double*)result = -(*(complex double*)elem);
    return result;
}

void* complex_zero(void* result) {
    *(complex double*)result = 0.0 + 0.0 * I;
    return result;
}

void* complex_conj(void* elem, void* result) {
    *(complex double*)result = conj(*(complex double*)elem);
    return result;
}


void* int_add(void* c1, void* c2, void* result){
    *(int*)result = *(int*)c1 + *(int*)c2;
    return result;
}

void* int_product(void* c1, void* c2, void* result){
    *(int*)result = *(int*)c1 * *(int*)c2;
}

void* multiply_by_int_scalar(void* coeff, int scalar){
    *(int*)coeff *= scalar;
    return coeff;
}


void* real_add(void* c1, void* c2, void* result) {
    *(double*)result = *(double*)c1 + *(double*)c2;
    return result;
}

void* real_product(void* c1, void* c2, void* result) {
    *(double*)result = *(double*)c1 * *(double*)c2;
    return result;
}

void* multiply_by_real_scalar(void* coeff, double scalar) {
    *(double*)coeff *= scalar;
    return coeff;
}


void* complex_add(void* c1, void* c2, void* result) {
    *(complex double*)result = *(complex double*)c1 + *(complex double*)c2;
    return result;
}

void* complex_product(void* c1, void* c2, void* result) {
    *(complex double*)result = *(complex double*)c1 * *(complex double*)c2;
    return result;
}

void* multiply_by_complex_scalar(void* coeff, complex scalar) {
    *(complex*)coeff *= scalar;
    return coeff;
}
