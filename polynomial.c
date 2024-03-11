#include <stdio.h>
#include <header.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

polynomial* init_poly(coeff_field* field, int degree){
    polynomial* poly = malloc(sizeof(polynomial));
    poly->degree = degree;
    poly->coeffs = malloc((degree + 1) * sizeof(void*));
    poly->field = field;
    return poly;
}

void free_poly(polynomial* poly) {
    if (poly == NULL){
        return;
    }

    free(poly->coeffs);
    free(poly);
}

int max(int a, int b){
  return (a > b) ? a:b;
}

// sum of polynomials
polynomial* sum_polys(polynomial* poly_1, polynomial* poly_2){
    if (poly_1 == NULL || poly_2 == NULL)
        exit(EXIT_FAILURE);


  if (poly_1->field != poly_2->field)
        // different types of coeffs in polynomyals
        exit(EXIT_FAILURE);

    polynomial* result = init_poly(poly_1->field, max(poly_1->degree, poly_2->degree));

    for (int i = 0; i < result->degree; ++i){
        poly_1->field.add(poly_1->coeffs[i], poly_2->coeffs[i], result->coeffs[i]);
    }
    return result;
}

polynomial* multiply(void* poly_1, void* poly_2, void* result){
    polynomial* p_1 = (polynomial*)poly_1;
    polynomial* p_2 = (polynomial*)poly_2;
    polynomial* result_poly = (polynomial*)result;

    if (p_1->field != p_2->field)
        exit(EXIT_FAILURE);
    
    result_poly->degree = p_1->degree + p_2->degree;

    for (int i = 0; i < result_poly->degree; ++i){
        result_poly->coeffs[i] = 0;
        for (int j = 0; j <= p_1->degree; ++j){
            for (int k = 0;k <= p_2->degree; ++k){
                if (i == j + k){
                    result_poly->coeffs[i] += (p_1->coeffs[j] * p_2->coeffs[k]);
                }
            }
        }
    }
    return result_poly;
}


polynomial* multiply_by_scalar(void* poly, void* scalar, void* result){
    polynomial* p = (polynomial*)poly;
    polynomial* res = (polynomial*)result;

    res->degree = p->degree;
    for (int i = 0; i <= res->degree; ++i){
        res->coeffs[i] = p->field->multiply_scalar(p->coeffs[i], scalar);
    }
    return res;
}


polynomial* composition(void* poly_1, void* poly_2, void* result){
    polynomial* p_1 = (polynomial*)poly_1;
    polynomial* p_2 = (polynomial*)poly_2;
    polynomial* res = (polynomial*)result;

    res->degree = p_1->degree * p_2->degree;
    for (int i = 0; i <= res->degree; ++i){
        res->coeffs[i] = 0;
        for (int j = 0; j <= p_1->degree; ++j){
            for (int k = 0; k <= p_2->degree; ++k){
                if (i == j * k){
                    res->coeffs[i] += p_1->coeffs[j] * p_2->coeffs[k];
                } 
            }
        }
    }
    return res;
}
