#include "polynomial.h"
#include "prot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <complex.h>


void free_polynomial(polynomial* poly){
    if (poly != NULL) {
        if (poly->coeffs != NULL) {
            free(poly->coeffs);
        }

        free(poly);
        poly = NULL;
    }
}

void cout_poly(polynomial *poly, Field_Info* field) {
   for (int i = 0; i <= poly->degree; ++i) {
        if (field->coeff_size == sizeof(int)) {
            printf("%d", *((int*)(poly->coeffs + i * field->coeff_size)));
        }

        else if (field->coeff_size == sizeof(double)) {
            printf("%f", *((double*)(poly->coeffs + i * field->coeff_size)));
        }

        else if (field->coeff_size == sizeof(complex double)) {
            complex double compl_cf = *((complex double*)(poly->coeffs + i * field->coeff_size));
            printf("(%f, %f)", creal(compl_cf), cimag(compl_cf));
        }

        if (i > 0)
            printf("x");
            if (i > 1)
                printf("^%d", i);
            if (i != poly->degree)
                printf(" + ");
    }
}


// SUM
polynomial* sum_polynomials(polynomial* p_1, polynomial* p_2) {
    if (p_1->field != p_2->field){
        fprintf(stderr, "Fields are different (sum_polynomials)");
        return NULL;
    }

    int max_degree = p_1->degree > p_2->degree ? p_1->degree : p_2->degree;

    void* result_cf = calloc(max_degree + 1, p_1->field->coeff_size);
    if (result_cf == NULL) {
        fprintf(stderr, "Memory allocation failed for sum_polynomials");
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
polynomial* product_polynomials(polynomial* p_1, polynomial* p_2) {
    if (p_1->field != p_2->field) {
        fprintf(stderr, "Fields are different (product_polynomials)");
        return NULL;
    }   

    int res_degree = p_1->degree + p_2->degree;

    void* res_cf = calloc(res_degree + 1, p_1->field->coeff_size);
    if (res_cf == NULL) {
        fprintf(stderr, "Memory allocation failed for res_cf (product_polynomials)");
        return NULL;
    }

    for (int i = 0; i <= p_1->degree; ++i) {
        for (int j = 0; j <= p_2->degree; ++j) {
            void* cf_1 = p_1->coeffs + i * p_1->field->coeff_size;
            void* cf_2 = p_2->coeffs + j * p_2->field->coeff_size;
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
        fprintf(stderr, "Memory allocation failed for res_poly (product_polynomials)");
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

    result_poly->degree = poly->degree;
    result_poly->coeffs = res_cf;
    result_poly->field = poly->field;

    return result_poly;
}


polynomial* create_zero_poly(Field_Info* field) {
    polynomial* zero_poly = malloc(sizeof(polynomial));
    if (!zero_poly) {
        fprintf(stderr, "Memory allocation failed for zero_poly");
        return NULL;
    }

    zero_poly->degree = 0;
    zero_poly->coeffs = calloc(1, field->coeff_size);
    if (!zero_poly->coeffs) {
        fprintf(stderr, "Memory allocation failed for zero_poly coeffs");
        free(zero_poly);
        return NULL;
    }

    void* neutral_add = field->neutral_elem_add();

    memcpy(zero_poly->coeffs, neutral_add, field->coeff_size);
    free(neutral_add); // because neutral_elem_add allocated a memory

    zero_poly->field = field;
    return zero_poly;
}

// Raise to power

polynomial* raise_to_power(polynomial* poly, int exp) {
    if (exp == 0) {
        return create_zero_poly(poly->field); // degree 1
    } else if (exp == 1) {
        return poly;
    }

    polynomial* result = poly;
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed for result (raise_to_power)\n");
    }

    for (int i = 1; i < exp; ++i) {
        polynomial* temp = product_polynomials(result, poly);
        if (temp == NULL) {
            fprintf(stderr, "Memory allocation failed for temp (raise_to_power)\n");
            return NULL;
        }

        if (i > 1)
            free_polynomial(result);
        result = temp;
    }

    return result;
}

// EVALUATE 


int eval_poly_int(polynomial* poly, int x) {
    int result = 0;
    int x_power = 1;

    for (int i = 0; i <= poly->degree; ++i) {

        result += ((int*)poly->coeffs)[i] * x_power;

        x_power *= x;
    }

    return result;
}

double eval_poly_db(polynomial* poly, double x) {
    double result = 0.0;
    double x_power = 1.0;

    for (int i = 0; i <= poly->degree; ++i) {
        result += ((double*)poly->coeffs)[i] * x_power;

        x_power *= x;
    }
    return result;
}


complex double eval_poly_cmp(polynomial* poly, complex double x) {
    complex double result = 0.0 + 0.0 + I;
    complex double x_power = 1.0 + 0.0 + I; // from x^0.0
    

    for (int i = 0; i < poly->degree; ++i) {
        result += ((complex double*)poly->coeffs)[i] * x_power;

        x_power *= x;
    }

    return result;
}


void* evaluate_poly(polynomial* poly, void* x) {
    if (poly->field->coeff_size == sizeof(int)) {
        int* result = malloc(sizeof(int));
        if (result != NULL) {
            *result = eval_poly_int(poly, *(int*)x);
        }
        return result;
    }
    else if (poly->field->coeff_size == sizeof(double)) {
        double* result = malloc(sizeof(double));
        if (result != NULL) {
            *result = eval_poly_db(poly, *(double*)x);
        }
        return result;
    }
    else if (poly->field->coeff_size == sizeof(complex double)) {
        complex double* result = malloc(sizeof(complex double));
        if (result != NULL) {
            *result = eval_poly_cmp(poly, *(complex double*)x);
        }
        return result;
    }
    else {
        return NULL;
    }
}

// composition


polynomial* composition(polynomial* poly_1, polynomial* poly_2) {
    if (poly_1->field != poly_2->field) {
        fprintf(stderr, "Fields are different (composition)");
        return NULL;
    }

    Field_Info* field = poly_1->field;

    polynomial* result = create_zero_poly(field);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed for result (composition)");
        return NULL;
    }

    polynomial* temp_poly;
    polynomial* new_result;
    polynomial* new_q_x;

    // Initialize q_x to the neutral element of the field (typically one for multiplication)
    polynomial* q_x = create_zero_poly(field);
    if (q_x == NULL) {
        fprintf(stderr, "Memory allocation failed for q_x (composition)");
        free_polynomial(result);
        return NULL;
    }

    void* neutral_elem_prod = field->neutral_elem_prod();
    if (neutral_elem_prod == NULL) {
        fprintf(stderr, "Failed to get neutral element (composition)");
        free_polynomial(result);
        free_polynomial(q_x);
        return NULL;
    }
    memcpy(q_x->coeffs, neutral_elem_prod, field->coeff_size);
    free(neutral_elem_prod);
    q_x->degree = 0; 

    // Iterate over the coefficients of poly_1
    for (int i = 0; i <= poly_1->degree; ++i) {
        // Multiply temp coeff of poly_1 with q_x
        temp_poly = scalar_multiply(q_x, poly_1->coeffs + i * field->coeff_size);
        if (temp_poly == NULL) {
            fprintf(stderr, "Scalar multiplication failed (composition)");
            free_polynomial(result);
            free_polynomial(q_x);
            return NULL;
        }
        
        new_result = sum_polynomials(result, temp_poly);
        if (new_result == NULL) {
            fprintf(stderr, "Polynomials sum failed (composition)");
            free_polynomial(temp_poly);
            free_polynomial(result);
            free_polynomial(q_x);
            return NULL;
        }
        free_polynomial(result);
        free_polynomial(temp_poly);
        result = new_result;

        // Multiply q_x by poly_2
        new_q_x = product_polynomials(q_x, poly_2);
        if (new_q_x == NULL) {
            fprintf(stderr, "Polynomials product failed (composition)");
            free_polynomial(result);
            free_polynomial(q_x);
            return NULL;
        }
        free_polynomial(q_x);
        q_x = new_q_x;
    }

    free_polynomial(q_x);
    return result;
}
