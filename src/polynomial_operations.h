#include "polynomial.h"
#include <complex.h>

void free_polynomial(polynomial* poly);

void free_Field(Field_Info* field);  

void cout_poly(polynomial* poly, Field_Info* field);

polynomial* sum_polynomials(polynomial* p_1, polynomial* p_2);

polynomial* product_polynomials(polynomial* p_1, polynomial* p_2);

polynomial* scalar_multiply(polynomial* poly, void* scalar);

polynomial* create_zero_poly(Field_Info* field);

polynomial* raise_to_power(polynomial* poly, int exp);

// Evaluate 
void* evaluate_poly(polynomial* poly, void* x);

int eval_poly_int(polynomial* poly, int x);
double eval_poly_db(polynomial* poly, double x);
double _Complex eval_poly_cmp(polynomial* poly, double _Complex x);
void* evaluate_poly(polynomial* poly, void* x);
 

// composition
polynomial* composition(polynomial* poly_1, polynomial* poly_2); 
