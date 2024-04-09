#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "error_codes.h"
#include "prot.h"
#include "polynomial.h"
#include "dialog.h"


#define MAX_POLYNOMIALS 5
var* polynomials[MAX_POLYNOMIALS];
int polys_count = 0;


var* create_var() {
    var* vb = malloc(sizeof(var));
    if (vb == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        return NULL;
    }

    char name[256];
    printf("enter name of the polynomial: \n");
    scanf("%s", name);

    vb->name = strdup(name);

    int choice;
    printf("select the type of coefficients:\n");

    printf("1. Integer\n");
    printf("2. Real\n");
    printf("3. Complex\n");

    printf("choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1: 
            vb->field = create_int_Field_info();
            break;
        case 2:
            vb->field = create_real_Field_info();
            break;
        case 3:
            vb->field = create_complex_Field_info();
            break;
        default:
            fprintf(stderr, "Invalid choice\n");
            free(vb);
            return NULL;
    }

    int degree;
    printf("Enter the highest degree of your polynomial: \n");
    scanf("%d", &degree);

    vb->poly_ptr = malloc(sizeof(polynomial));
    if (vb->poly_ptr == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        free(vb->name);
        return NULL;
    }

    vb->poly_ptr->degree = degree;
    vb->poly_ptr->field = vb->field;
    vb->poly_ptr->coeffs = calloc(degree + 1, vb->field->coeff_size);

    if (vb->poly_ptr->coeffs == NULL) {
        handle_err_code(ERR_MEMORY_ALLOCATION);
        free(vb->poly_ptr);
        free(vb->name);
        free(vb);
        return NULL;
    }

    printf("Enter the coefficients for the polynomial: \n");
    for (int i = 0; i <= degree; ++i) {
        if (choice == 1) {
            printf("coefficient for x^%d: \n", i);
            scanf("%d", (int*)(vb->poly_ptr->coeffs + i * sizeof(int)));
        }
        else if (choice == 2) {
            printf("coefficients for x^%d: \n", i);
            scanf("%lf", (double*)(vb->poly_ptr->coeffs + i * sizeof(double)));
        }
        else if (choice == 3) {
            double Re, Im;
            printf("Real part of x^%d: \n", i);
            scanf("%lf", &Re);
            printf("Imaginary part of x^%d: \n", i);
            scanf("%lf", &Im);

            *((complex double*)(vb->poly_ptr->coeffs + i * sizeof(complex double))) = Re + Im * I;
        }
    }
    return vb;
}

int select_poly(const char* option) {
    // return a choosen index of the option
    if (polys_count == 0) {
        handle_err_code(ERR_INVALID_POINT);
        return -1;
    }

    printf("Select a polynomial %s (1 to %d)\n", option, polys_count);
    int index;
    scanf("%d", &index);

    index--; // bc indexes starts from 0

    if (index < 0 || index >= polys_count) {
        handle_err_code(ERR_INVALID_SELECTION);
        return -1;
    }

    return index;
}



void poly_menu() {
    int flag = 1;
    
    while (flag) {

        printf("Polynomial operations Menu:\n");
        printf("1. Create a new polynomial\n");
        printf("2. Add polynomials\n");
        printf("3. Multiply polynomials\n");
        printf("4. Evaluate polynomial at a point\n");
        printf("5. Composition of polynomials\n");
        printf("6. Multiply by scalar\n");
        printf("7. Display all polynomials\n");
        printf("8. Exit\n");

        printf("Enter your choice.\n");


        int choice, index_1, index_2;
        int result = scanf("%d", &choice);

        if (result != 1) {
            fprintf(stderr,"Invalid input. Try again!\n");
            int cnt = 0;
            while (getchar() != 'n'){
                cnt++;
                if (cnt == 4) {
                    printf("That's your last try!\n");
                }
                if (cnt == 5) {
                    fprintf(stderr, "Bye!\n");
                    exit(EXIT_FAILURE);
                }

            }
            continue;
        }

        
        
        if (choice == 1 && polys_count >= MAX_POLYNOMIALS) {
            printf("You've reached the maximum possible count of polynomials (%d)\n", MAX_POLYNOMIALS);
            continue;
        }

        switch (choice) {
            case 1: {
                var* new_poly = create_var();
                if (new_poly) {
                    polynomials[polys_count++] = new_poly; // save new User's polynomial
                }
                break;
            }
            case 2: {
                if (polys_count < 2) {
                    handle_err_code(ERR_MIN_POLYS);
                    break;
                }

                index_1 = select_poly("add");
                index_2 = select_poly("add to");
                if (index_1 != -1 && index_2 != -1) {
                   polynomial* result_poly = sum_polynomials(polynomials[index_1]->poly_ptr, polynomials[index_2]->poly_ptr);
                    if (result_poly) {
                        printf("Sum of polynomials: \n");
                        cout_poly(result_poly, polynomials[index_1]->field);
                        printf("\n");
                        free_polynomial(result_poly);
                    }
                    else {
                        handle_err_code(TRY_AGAIN);
                    }
                }
                break;
            }
            case 3 : {
                if (polys_count < 2) {
                    handle_err_code(ERR_MIN_POLYS);
                    break;
                }

                index_1 = select_poly("multiply");
                index_2 = select_poly("multiply with");
                if (index_1 != -1 && index_2 != -1) {
                    polynomial* result_poly = product_polynomials(polynomials[index_1]->poly_ptr, polynomials[index_2]->poly_ptr);
                    if (result_poly) {
                        printf("Product of polynomials: \n");
                        cout_poly(result_poly, polynomials[index_1]->field);
                        printf("\n");
                        free_polynomial(result_poly);
                    }
                    else {
                        handle_err_code(TRY_AGAIN);
                    }
                }
                break;
            }
            case 4: {
                if (polys_count < 2) {
                    handle_err_code(ERR_MIN_POLYS);
                    break;
                }

                index_1 = select_poly("evaluate");
                if (index_1 != -1) {
                    int point;
                    printf("Enter the value of x for the polynomial: \n");
                    scanf("%d", &point);

                    void* result = evaluate_poly(polynomials[index_1]->poly_ptr, &point);
                    if (result) {
                        if (polynomials[index_1]->field->coeff_size == sizeof(int)) {
                            printf("The value of the polynomial at %d : %d\n", point, *(int*)result);
                        }
                        else if (polynomials[index_1]->poly_ptr->field->coeff_size == sizeof(double)) {
                            printf("The value of the polynomial at %d: %f\n", point, *(double*)result);
                        }
                        else if (polynomials[index_1]->field->coeff_size == sizeof(complex double)) {
                            printf("The value of the polynomial at %d: %f + %fin \n", point, creal(*(complex double*)result), cimag(*(complex double*)result));
                        }
                        free(result);
                    }
                    else {
                        handle_err_code(TRY_AGAIN);
                    }
                }
                break;
            }
            case 5: {
                if (polys_count < 2) {
                    handle_err_code(ERR_MIN_POLYS);
                    break;
                }

                printf("Choose the polynomial to be composed: \n");
                index_1 = select_poly("compose");
                
                if (index_1 == -1)
                    break;
                
                printf("Choose the polynomial to compose into the base polynomial: \n");
                index_2 = select_poly("compose into");
                
                if (index_2 == -1)
                    break;

                var* base_poly = polynomials[index_1];
                var* inner_poly = polynomials[index_2];

                polynomial* cmp_result = composition(base_poly->poly_ptr, inner_poly->poly_ptr);

                if (cmp_result) {
                    printf("Composition result: \n");
                    cout_poly(cmp_result, base_poly->field);
                    printf("\n");
                    free_polynomial(cmp_result);
                }
                else {
                    handle_err_code(TRY_AGAIN);                }
            }
            break;
            case 6: {
                index_1 = select_poly("for scalar multiplication;");
                if (index_1 != -1) {
                    printf("Enter scalar value for multiplying\n");
                    void* scalar = malloc(polynomials[index_1]->field->coeff_size);

                    if (polynomials[index_1]->field->coeff_size == sizeof(int)) {
                        int temp_int;
                        scanf("%d", &temp_int);
                        memcpy(scalar, &temp_int, sizeof(int));
                    }
                    else if (polynomials[index_1]->field->coeff_size == sizeof(double)) {
                        double temp_db;
                        scanf("%lf", &temp_db);
                        memcpy(scalar, &temp_db, sizeof(double));
                    }
                    else if (polynomials[index_1]->field->coeff_size == sizeof(complex double)) {
                        double Re, Im;
                        printf("Enter real part of scalar: \n");
                        scanf("%lf", &Re);
                        printf("Enter Imaginary part of scalar: \n");
                        scanf("%lf", &Im);
                        complex double temp_cmp = Re + Im * I;
                        memcpy(scalar, &temp_cmp, sizeof(complex double));
                    }
                    polynomial* sc_poly = scalar_multiply(polynomials[index_1]->poly_ptr, scalar);
                    if (sc_poly) {
                        printf("Result of scalar multiplication: \n");
                        cout_poly(sc_poly, polynomials[index_1]->field);
                        printf("\n");
                        free_polynomial(sc_poly);
                    }
                    else {
                        handle_err_code(TRY_AGAIN);
                    }
                    free(scalar);
                }
                break;
            }
            case 7: {
                if (polys_count == 0) {
                    handle_err_code(ERR_MIN_POLYS);
                }
                else {
                    printf("List of all polynomials: \n");
                    for (int i = 0; i < polys_count; ++i) {
                        printf("Polynomial %s: \n", polynomials[i]->name);
                        cout_poly(polynomials[i]->poly_ptr, polynomials[i]->field);
                        printf("\n");
                    }
                }
                break;
            }
            case 8: {
                printf("Exiting the program.\n");
                flag = 0;
                break;
            }
            default:
                handle_err_code(TRY_AGAIN);
        }
    }

    // deallocating the memory 
    for (int i = 0; i < polys_count; ++i) {
        free_polynomial(polynomials[i]->poly_ptr);
        free(polynomials[i]->name);
        free(polynomials[i]);
    }
}
