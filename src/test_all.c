#include "polynomial.h"
#include <assert.h>
#include "prot.h"
#include "error_codes.h"
#include "stdio.h"
#include "polynomial_operations.h"
#include "tests.h"


void Test_all() {
    test_create_poly();
    test_addition();
    test_product();
    test_scalar_multiplication();
    test_evaluation();
    test_composition();

    printf("All tests passed successfully!\n");
    printf("\n");
}


void test_create_poly() {
    Field_Info* field = create_int_Field_info();
    polynomial* poly = create_poly(2, field);
    assert(poly != NULL);
    assert(poly->degree == 2);

    for (int i = 0; i <= poly->degree; ++i) {
        assert(((int*)poly->coeffs)[i] == 0);
    }

    free_polynomial(poly);
    printf("Test create_poly passed!\n");
}


void test_addition() {
    Field_Info* int_field = create_int_Field_info();
    polynomial* p_1_int = create_poly(2, int_field);
    polynomial* p_2_int = create_poly(2, int_field);
    
    ((int*)p_1_int->coeffs)[0] = 1;
    ((int*)p_1_int->coeffs)[1] = 2;
    ((int*)p_1_int->coeffs)[2] = 1;

    ((int*)p_2_int->coeffs)[0] = 3;
    ((int*)p_2_int->coeffs)[1] = 2;
    ((int*)p_2_int->coeffs)[2] = 3;

 
    Field_Info* real_field = create_real_Field_info();
    polynomial* p_1_real = create_poly(2, real_field);
    polynomial* p_2_real = create_poly(3, real_field);

    ((double*)p_1_real->coeffs)[0] = 2.0;
    ((double*)p_1_real->coeffs)[1] = 7.0;
    ((double*)p_1_real->coeffs)[2] = 3.0;

    ((double*)p_2_real->coeffs)[0] = 1.0;
    ((double*)p_2_real->coeffs)[1] = 2.0;
    ((double*)p_2_real->coeffs)[2] = 3.0;
    ((double*)p_2_real->coeffs)[3] = 1.0;

    polynomial* result_int = sum_polynomials(p_1_int, p_2_int);
    assert(result_int != NULL);
    assert(((int*)result_int->coeffs)[0] == 4);
    assert(((int*)result_int->coeffs)[1] == 4);
    assert(((int*)result_int->coeffs)[2] == 4);

    polynomial* result_real = sum_polynomials(p_1_real, p_2_real);
    assert(result_real != NULL);
    assert(((double*)result_real->coeffs)[0] == 3.0);
    assert(((double*)result_real->coeffs)[1] == 9.0);
    assert(((double*)result_real->coeffs)[2] == 6.0);
    assert(((double*)result_real->coeffs)[3] == 1.0);
    

    free_polynomial(p_1_int);
    free_polynomial(p_2_int);
    free_polynomial(p_1_real);
    free_polynomial(p_2_real);
    free_polynomial(result_int);
    free_polynomial(result_real);

    printf("Test_addidtion passed!\n");
}

void test_product() {
    Field_Info* field_int = create_int_Field_info();
    Field_Info* field_real = create_real_Field_info();

    polynomial* p_1_int = create_poly(2, field_int);
    polynomial* p_2_int = create_poly(2, field_int);
    polynomial* p_1_real = create_poly(2, field_real);
    polynomial* p_2_real = create_poly(2, field_real);

    ((int*)p_1_int->coeffs)[0] = 1;
    ((int*)p_1_int->coeffs)[1] = 2;
    ((int*)p_1_int->coeffs)[2] = 1;

    ((int*)p_2_int->coeffs)[0] = 3;
    ((int*)p_2_int->coeffs)[1] = 4;
    ((int*)p_2_int->coeffs)[2] = 3;

    ((double*)p_1_real->coeffs)[0] = 1.0;
    ((double*)p_1_real->coeffs)[1] = 2.0;
    ((double*)p_1_real->coeffs)[2] = 3.0;

    ((double*)p_2_real->coeffs)[0] = 1.0;
    ((double*)p_2_real->coeffs)[1] = 2.0;
    ((double*)p_2_real->coeffs)[2] = 3.0;

    polynomial* result_int = product_polynomials(p_1_int, p_2_int);
    polynomial* result_real = product_polynomials(p_1_real, p_2_real);

    assert(result_int != NULL);
    assert(result_real != NULL);
    assert(result_int->degree == 4);
    assert(result_real->degree == 4);

    assert(((int*)result_int->coeffs)[0] == 3);
    assert(((int*)result_int->coeffs)[1] == 10);
    assert(((int*)result_int->coeffs)[2] == 14);
    assert(((int*)result_int->coeffs)[3] == 10);
    assert(((int*)result_int->coeffs)[4] == 3);

    assert(((double*)result_real->coeffs)[0] == 1.0);
    assert(((double*)result_real->coeffs)[1] == 4.0);
    assert(((double*)result_real->coeffs)[2] == 10.0);
    assert(((double*)result_real->coeffs)[3] == 12.0);
    assert(((double*)result_real->coeffs)[4] == 9.0);

    free_polynomial(p_1_int);
    free_polynomial(p_2_int);
    free_polynomial(p_1_real);
    free_polynomial(p_2_real);
    free_polynomial(result_int);
    free_polynomial(result_real);
    printf("Test_product passed!\n");
}


void test_scalar_multiplication() {
    Field_Info* field_int = create_int_Field_info();
    Field_Info* field_real = create_real_Field_info();

    polynomial* int_poly = create_poly(2, field_int);
    polynomial* real_poly = create_poly(2, field_real);

    int int_scalar = 3;
    double real_scalar = 3.0;

    ((int*)int_poly->coeffs)[0] = 1;
    ((int*)int_poly->coeffs)[1] = 2;
    ((int*)int_poly->coeffs)[2] = 1;

    ((double*)real_poly->coeffs)[0] = 1.0;
    ((double*)real_poly->coeffs)[1] = 2.0;
    ((double*)real_poly->coeffs)[2] = 1.0;

    polynomial* int_result = scalar_multiply(int_poly, &int_scalar);
    polynomial* real_result = scalar_multiply(real_poly, &real_scalar);

    assert(int_result != NULL);
    assert(real_result != NULL);

    assert(((int*)int_result->coeffs)[0] == 1 * int_scalar);
    assert(((int*)int_result->coeffs)[1] == 2 * int_scalar);
    assert(((int*)int_result->coeffs)[2] == 1 * int_scalar);

    assert(((double*)real_result->coeffs)[0] == 1.0 * real_scalar);
    assert(((double*)real_result->coeffs)[1] == 2.0 * real_scalar);
    assert(((double*)real_result->coeffs)[2] == 1.0 * real_scalar);

    free_polynomial(int_poly);
    free_polynomial(real_poly);
    free_polynomial(int_result);
    free_polynomial(real_result);

    printf("Test scalar_multiply passed!\n");
}

void test_evaluation() {
    Field_Info* int_field = create_int_Field_info();
    Field_Info* real_field = create_real_Field_info();

    polynomial* poly_int = create_poly(2, int_field);
    polynomial* poly_real = create_poly(2, real_field);

    int int_point = 2;
    double real_point = 2.0;

    ((int*)poly_int->coeffs)[0] = 1;
    ((int*)poly_int->coeffs)[1] = 2;
    ((int*)poly_int->coeffs)[2] = 1;

    ((double*)poly_real->coeffs)[0] = 1.0;
    ((double*)poly_real->coeffs)[1] = 2.0;
    ((double*)poly_real->coeffs)[2] = 1.0;

    void* int_result = evaluate_poly(poly_int, &int_point);
    int rs_int = *(int*)int_result;
    free(int_result);

    void* real_result = evaluate_poly(poly_real, &real_point);
    double rs_db = *(double*)real_result;
    free(real_result);

    assert(rs_int == 1 + 2 * int_point + 1 * int_point * int_point);
    assert(rs_db == 1.0 + 2.0 * real_point + 1.0 * real_point * real_point);

    free_polynomial(poly_int);
    free_polynomial(poly_real);

    printf("Test evaluation passed!\n");
}

void test_composition() {
    Field_Info* int_field = create_int_Field_info();

    polynomial* poly_1 = create_poly(2, int_field);
    polynomial* poly_2 = create_poly(2, int_field);

    ((int*)poly_1->coeffs)[0] = 1;
    ((int*)poly_1->coeffs)[1] = 2;
    ((int*)poly_1->coeffs)[2] = 1;

    ((int*)poly_2->coeffs)[0] = 3;
    ((int*)poly_2->coeffs)[1] = 4;
    ((int*)poly_2->coeffs)[2] = 5;

    polynomial* result_cmp = composition(poly_1, poly_2);
    assert(result_cmp != NULL);
    assert(((int*)result_cmp->coeffs)[0] == 16);
    assert(((int*)result_cmp->coeffs)[1] == 32);
    assert(((int*)result_cmp->coeffs)[2] == 56);
    assert(((int*)result_cmp->coeffs)[3] == 40);

    free_polynomial(poly_1);
    free_polynomial(poly_2);
    free_polynomial(result_cmp);

    printf("Test composition passed!\n");
}
