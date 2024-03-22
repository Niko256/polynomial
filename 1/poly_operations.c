#include "polynomial.h"
#include "prot.h"
#include <stdlib.h>
#include <string.h>

// SUM
polynomial* sum(polynomial* p_1, polynomial* p_2) {
    if (p_1->field != p_2->field){
        fprintf(stderr, "Fields are different (sum)");
        return NULL;
    }
    
    int max_degree = p_1->degree > p_2->degree ? p_1->degree : p_2->degree;

    void* result_cf = calloc(max_degree + 1, p_1->field->coeff_size);
    if (result_cf == NULL) {
        fprintf(stderr, "Memory allocation failed for sum");
        return NULL;
    }

    for (int i = 0; i <= max_degree; ++i) {
        void* cf_1 = i <= p_1->degree ? (p_1->coeffs + i * p_1->field->coeff_size) : p_1->field->neutral_elem_add();
        void* cf_2 = i <= p_2->degree ? (p_2->coeffs + i * p_2->field->coeff_size) : p_2->field->neutral_elem_add();

        void* sum = p_1->field->add(cf_1, cf_2);
        memcpy(result_cf + i * p_1->field->coeff_size, sum, p_1->field->coeff_size);
        free(sum); // because add() allocates a memory
    }

    polynomial* result_poly = malloc(sizeof(polynomial));
    if (result_poly == NULL) {
        fprintf(stderr, "Memory allocation failed for result_poly");
        free(result_cf);
        return NULL;
    }

    result_poly->degree = max_degree;
    result_poly->coeffs = result_cf;
    result_poly->field = p_1->field;

    return result_poly;
}


// PRODUCT
polynomial* product(polynomial* p_1, polynomial* p_2) {
    if (p_1->field != p_2->field) {
        fprintf(stderr, "Fields are different (product)");
        return NULL;
    }   
    
    int res_degree = p_1->degree + p_2->degree;
    
    void* res_cf = calloc(res_degree + 1, p_1->field->coeff_size);
    if (res_cf == NULL) {
        fprintf(stderr, "Memory allocation failed for res_cf (product)");
        return NULL;
    }

    for (int i = 0; i <= p_1->degree, ++i) {
        for (int j = 0; j <= p_2->degree; ++j) {
            void* cf_1 = p_1->coeffs + i * p_1->field->coeff_size;
            void* cf_2 = p_2->coeffs + i * p_2->field->coeff_size;
            void* product = p_1->field->product(cf_1, cf_2);

            void* current = res_cf + (i + j) * p_1->field->coeff_size;
            void* sum = p_1->field->add(current, product);

            memcpy(current, sum, p_1->field->coeff_size);

            free(product);
            free(sum);
        }
    }

    polynomial* res_poly = malloc(sizeof(polynomial));

    if (res_poly == NULL) {
        fprintf(stderr, "Memory allocation failed for res_poly (product)");
        free(res_cf);
        return NULL;
    }
    res_poly->degree = res_degree;
    res_poly->coeffs = res_cf;
    res_poly->field = p_1->field;

    return res_poly;
}


// MULTIPLY BY SCALAR
polynomial* scalar_multiply(polynomial* poly, void* scalar) {
    void* res_cf = malloc((poly->degree + 1) * poly->field->coeff_size);
    if (res_cf == NULL) {
        fprintf(stderr, "Memory allocate failed for res_cf (scalar_multiply)");
        return NULL;
    }

    for (int i = 0; i <= poly->degree; ++i) {
        void* cf = poly->coeffs + i * poly->field->coeff_size;
        void* product = poly->field->product(cf, scalar);
        
        memcpy(res_cf + i * poly->field->coeff_size, product, poly->field->coeff_size);
        free(product);
    }

    polynomial* result_poly = malloc(sizeof(polynomial));
    if (result_poly == NULL) {
        fprintf(stderr, "Memory allocate failed for result_poly (scalar_multiply)");
        free(res_cf);
        return NULL;
    }

    result_poly.degree = poly->degree;
    result_poly->coeffs = res_cf;
    result_poly->field = poly->field;

    return result_poly;
}

