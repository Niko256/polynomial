#include <stdio.h>
#include <header.h>
#include <stdlib.h>
#include <complex.h>
#include <prot.h>


Field_Info* create_Field_info(
    int coeff_size, 
    void* (*add)(void* poly_1, void* poly_2, void* result),
    void* (*product)(void* poly_1, void* poly_2, void* result), 
    void* (*zero)(void* coeff)) {  
    Field_Info* fi = (Field_Info*) malloc(sizeof(Field_Info));
    
    if (fi == NULL) {
        return NULL;
    }
    
    fi->coeff_size = coeff_size;
    fi->add = add;
    fi->product = product;
    fi->zero = zero;

    return fi;
}

void free_Field(void* field) {
    free(field);
}


// INTEGER_FIELD

Field_Info* create_int_Field_info() {
    return create_Field_info(sizeof(int),
    &int_add,
    &int_product,
    &int_zero);
}

void* int_add(void* c1, void* c2, void* result){
    *(int*)result = *(int*)c1 + *(int*)c2;
    return result;
}

void* int_product(void* c1, void* c2, void* result){
    *(int*)result = *(int*)c1 * *(int*)c2;
}

void* multiply_by_int_scalar(void* coeff, int scalar, void* result){
    *(int*)coeff *= scalar;
    return coeff;
}

void* int_additive_inverse(void* elem, void* int_inverse) {
    *(int*)int_inverse = -(*(int*)elem);
    return int_inverse;
}

void* int_zero(void* coeff) {
    *((int*)coeff) = 0;
    return coeff;
}



// REAL_FIELD

Field_Info* create_real_Field_info() {
    return create_Field_info(sizeof(double),
    &real_add,
    &real_product,
    &real_zero);
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

void* real_additive_inverse(void* elem, void* real_inverse) {
    *(double*)real_inverse = -(*(double*)elem);
    return real_inverse;
}

void* real_zero(void* coeff) {
    *((double*)coeff) = 0.0;
    return coeff;
}



// COMPLEX_FIELD

Field_Info* create_complex_Field_info(){
    return create_Field_info(sizeof(complex double),
    &complex_add,
    &complex_product,
    &complex_zero);
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

void* complex_additive_inverse(void* elem, void* complex_inverse) {
    *(complex double*)complex_inverse = -(*(complex double*)elem);
    return complex_inverse;
}

void* complex_zero(void* coeff) {
    *((complex double*)coeff) = 0.0 + 0.0 * I;
    return coeff;
}

void* complex_conj(void* elem, void* result) {
    *(complex double*)result = conj(*(complex double*)elem);
    return result;
}

