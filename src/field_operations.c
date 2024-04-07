#include "polynomial.h"
#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include "error_codes.h"


Field_Info* create_Field_info(
    int coeff_size, 
    void* (*add)(void* coeff_1, void* coeff_2),
    void* (*product)(void* coeff_1, void* coeff_2), 
    void* (*inverse_elem_add)(void* elem),
    void* (*inverse_elem_prod)(void* elem),
    void* (*neutral_elem_add)(),
    void* (*neutral_elem_prod)()) {  
    Field_Info* fi = (Field_Info*) malloc(sizeof(Field_Info));

    if (fi == NULL) {
        return NULL;
    }

    fi->coeff_size = coeff_size;
    fi->add = add;
    fi->product = product;
    fi->inverse_elem_add = inverse_elem_add;
    fi->inverse_elem_prod = inverse_elem_prod;
    fi->neutral_elem_add = neutral_elem_add;
    fi->neutral_elem_prod = neutral_elem_prod;

    return fi;
}

void free_Field(Field_Info* field) {
    if (field != NULL) {
        free(field);
        field = NULL;
    }
}


// INTEGER FIELD FUNCTIONS

Field_Info* create_int_Field_info(){
    return create_Field_info(
        sizeof(int),
        &int_add,
        &int_product,
        &int_inverse_add,
        &int_inverse_prod,
        &int_neutral_add,
        &int_neutral_prod);
}


void* int_add(void* coeff_1, void* coeff_2){
    if (coeff_1 == NULL || coeff_2 == NULL){
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    int* result = malloc(sizeof(int));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL; 
    }

    *result = *(int*)coeff_1 + *(int*)coeff_2;
    return result;
}

void* int_product(void* coeff_1, void* coeff_2) {
    if (coeff_1 == NULL || coeff_2 == NULL) {
        handle_err_code(ERR_NULLPTR);
        return NULL;
    }

    int* result = malloc(sizeof(int));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = *(int*)coeff_1 * *(int*)coeff_2;
    return result;
}


void* int_inverse_add(void* coeff) {
    
    if (coeff == NULL) {
        handle_err_code(ERR_NULLPTR);
        return NULL;
    }

    int* result = malloc(sizeof(int));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = -(*(int*)coeff);
    return result;
}


void* int_inverse_prod(void* coeff) {
    
    if (coeff == NULL) {
        handle_err_code(ERR_NULLPTR);
        return NULL;
    }

    
    if (*(int*)coeff == 0) {
        handle_err_code(ERR_DIVISION_BY_ZERO);
        return NULL;
    }

    int* result = malloc(sizeof(int));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

   
    *result = (*(int*)coeff == 1 || *(int*)coeff == -1) ? *(int*)coeff : 0;
    return result;
}



void* int_neutral_add(){
    int* result = malloc(sizeof(int));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        exit(EXIT_FAILURE);
    }

    *result = 0;
    return result;
}


void* int_neutral_prod(){
    int* result = malloc(sizeof(int));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = 1;
    return result;
}


// REAL FIELD FUNCTIONS
//

Field_Info* create_real_Field_info(){
    return create_Field_info(
        sizeof(double),
        &real_add,
        &real_product,
        &real_inverse_add,
        &real_inverse_prod,
        &real_neutral_add,
        &real_neutral_prod);
}

void* real_add(void* coeff_1, void* coeff_2){
    double* result = malloc(sizeof(double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = *(double*)coeff_1 + *(double*)coeff_2;
    return result;
}


void* real_product(void* coeff_1, void* coeff_2){
    double* result = malloc(sizeof(double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = *(double*)coeff_1 * *(double*)coeff_2;
    return result;
}


void* real_inverse_add(void* coeff) {

    double* result = malloc(sizeof(double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = (1 / (*(double*)coeff));
    return result;
}


void* real_inverse_prod(void* coeff){
    double* real_coeff = (double*)coeff;

    if (*real_coeff == 0.0) {
        handle_err_code(ERR_DIVISION_BY_ZERO);
    }

    double* result = malloc(sizeof(double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = (1.0 / *real_coeff);
    return result;
}


void* real_neutral_add(){
    double* result = malloc(sizeof(double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = 0.0;
    return result;
}

void* real_neutral_prod(){
    double* result = malloc(sizeof(double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = 1.0;
    return result;
}


// COMPLEX FIELD FUNCTIONS
//

Field_Info* create_complex_Field_info(){
    return create_Field_info(
        sizeof(complex double),
        &complex_add,
        &complex_product,
        &complex_inverse_add,
        &complex_inverse_prod,
        &complex_neutral_add,
        &complex_neutral_prod);
}


void* complex_add(void* coeff_1, void* coeff_2){
    complex double* result = malloc(sizeof(complex double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = (*(complex double*)coeff_1 + *(complex double*)coeff_2);
    return result;
}


void* complex_product(void* coeff_1, void* coeff_2){
    complex double* result = malloc(sizeof(complex double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = (*(complex double*)coeff_1 * *(complex double*)coeff_2);
    return result;
}


void* complex_inverse_add(void* coeff) {
    complex double* result = malloc(sizeof(complex double));

    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = -(*(complex double*)coeff);
    return result;
}


void* complex_inverse_prod(void* coeff) {

    complex double* complex_coeff = (complex double*)coeff;
    complex double zero = 0.0 + 0.0 * I;

    // if complex root == 0.0
    if (cabs(*complex_coeff) == 0.0) {
        handle_err_code(ERR_DIVISION_BY_ZERO);
        return NULL;
    }

    complex double* result = malloc(sizeof(complex double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = (1.0 / *complex_coeff);
    return result;
}


void* complex_neutral_add() {

    complex double* result = malloc(sizeof(complex double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = 0.0 + 0.0 * I;
    return result;
}


void* complex_neutral_prod() {
    complex double* result = malloc(sizeof(complex double));
    if (result == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    *result = 1.0 + 0.0 * I;
    return result;
}


