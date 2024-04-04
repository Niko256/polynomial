#include <stdio.h>
#include "polynomial.h"
#include "prot.h"
#include "polynomial_operations.h"
#include <complex.h>


int main() {
    Field_Info* int_field_info = create_int_Field_info();

    polynomial p_1 = {
        .degree = 2,
        .coeffs = (int []) {1, 2, 3},
        .field = int_field_info
    };

    polynomial p_2 = {
        .degree = 2,
        .coeffs = (int []) {3, 2, 1},
        .field = int_field_info
    };
    
    int x_value = 3;
   
    int sc_int = 3;
    void* scalar = &sc_int;

    int exp = 2;

    // sum
    polynomial* sum_result = sum_polynomials(&p_1, &p_2);
    if (sum_result != NULL) {
        printf("sum polys: ");
        cout_poly(sum_result, int_field_info);
        printf("\n");
        free_polynomial(sum_result);
    }
    

    // product
    polynomial* prod_result = product_polynomials(&p_1, &p_2);
    if (prod_result != NULL) {
        printf("product polys: ");
        cout_poly(prod_result, int_field_info);
        printf("\n");
        free_polynomial(prod_result);
    }
    
    // multiply by scalar
    polynomial* sc = scalar_multiply(&p_1, scalar);
    if (sc != NULL) {
        printf("multiply by scalar: ");
        cout_poly(sc, int_field_info);
        printf("\n");
        free(sc);
    }
    
    
    // raise to power
    
    polynomial* rs_pow = raise_to_power(&p_1, exp);
    if (rs_pow != NULL) {
        printf("raise to power: ");
        cout_poly(rs_pow, int_field_info);
        printf("\n");
        free(rs_pow);
    }
   
    // evaluate

    int* poly_value = (int*)evaluate_poly(&p_1, &x_value);
    if (poly_value != NULL) {
        printf("The polynomial value at x = %d is %d\n", x_value, *poly_value);
        free(poly_value);
    }


    // composition
    
    polynomial* compose = composition(&p_1, &p_2);
    
    if (compose != NULL) {
        printf("Composition of polynomails is : ");

        for (int i = 0; i <= compose->degree; ++i) {
            printf("%dx^%d ", ((int*)compose->coeffs)[i], i);
        }
        printf("\n");
        free_polynomial(compose);
    }
    else {
        fprintf(stderr, "Error computing the composition of polynomials");
    }

    free(int_field_info);
    return 0;
}



