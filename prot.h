#include <complex.h>

// INTEGER
void* int_add(void* c1, void* c2, void* result);
void* int_product(void* c1, void* c2, void* result);
void* multiply_by_int_scalar(void* coeff, int scalar, void* result);

void* int_inverse_add(void* elem, void* result);
void* int_inverse_prod(void* elem, void* result);
void* int_neutral_add(void* elem, void* result);
void* int_neutral_prod(void* elem, void* result);

// REAL
void* real_inverse_add(void* elem, void* result);
void* real_inverse_prod(void* elem, void* result);
void* real_neutral_add(void* elem, void* result);
void* real_neutral_prod(void* elem, void* result);

void* real_add(void* c1, void* c2, void* result);
void* real_product(void* c1, void* c2, void* result);
void* multiply_by_real_scalar(void* coeff, double scalar);

// COMPLEX
void* complex_inverse_add(void* elem, void* result);
void* complex_inverse_prod(void* elem, void* result);
void* complex_neutral_add(void* result);
void* complex_neutral_prod(void* elem, void* result);

void* complex_conj(void* elem, void* result);
void* complex_add(void* c1, void* c2, void* result);
void* complex_product(void* c1, void* c2, void* result);
void* multiply_by_complex_scalar(void* coeff, complex scalar);


