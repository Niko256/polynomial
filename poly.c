#include <field.c>
#include <iostream>
#include <iterator>
#include <prot.h>
#include <header.h>
#include <stdio.h>
#include <stdlib.h>

// all functions
// 1) sum polys - +
// 2) product polys
// 3) composition polys
// 

void zero_coefficients(void* coeffs, int count, Field_Info* fi){
    for (int i = 0; i < count; ++i){ 
        void* curr_coeff = (char*)coeffs + i * fi->coeff_size;
        // getting ptr to (i)-coeff in arr of coeffs
        if (fi->coeff_size == sizeof(int))
            *((int*)curr_coeff) = 0;
        else if (fi->coeff_size == sizeof(double))
            *((double*)curr_coeff) = 0.0;
        else if (fi->coeff_size == sizeof(complex double))
            *((complex double*)curr_coeff) = 0.0 + 0.0 * I;
        else 
            fprintf(stderr, "unknown coeff size");
        exit(EXIT_FAILURE);
        
    }
}
    


polynomial* sum(polynomial p_1, polynomial p_2){
    if (p_1.field != p_2.field)
        return NULL;

    int max_degree = (p_1->degree > p_2->degree) ? p_1->degree : p_2->degree;
    
    void* coeffs = malloc((max_degree + 1) * p_1.field->coeff_size);
    if (!coeffs)
        return NULL;
        // memory error

    zero_coefficients(void* coeffs , int max_degree + 1, p_1.field);
    
    for (int i = 0; i < p_1.degree; ++i){
        p_1.field->add(coeffs + i * p_1.field->coeff_size,
            // ptr to i-coefficient of res polynomial
        p_1.coeffs + i * p_1.field->coeff_size,
            // ptr to (i) coefficient of p_1
        coeffs + i * p_1.field->coeff_size);
    }

    for (int i = 0; i < p_2.degree; ++i){
        p_1.field->add(coeffs + i * p_2.field->coeff_size,
        p_2.coeffs + i * p_2.field->coeff_size,
        coeffs + i * p_1.field->coeff_size);
    }

    polynomial* result_poly = malloc(sizeof(polynomial));
    if (!result_poly) {
        free(coeffs);
        return NULL;
    }
    
    result_poly->degree = max_degree;
    result_poly->coeffs = coeffs;
    result_poly->field = p_1.field;

    return result_poly;
}




