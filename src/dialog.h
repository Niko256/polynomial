#include <stdio.h>
#include <complex.h>
#include "polynomial.h"
#include "polynomial_operations.h"
#include "prot.h"

#ifndef DIALOG_H
#define DIALOG .H


typedef struct {
    char* name;
    Field_Info* field;
    polynomial* poly_ptr;
} var;

var* create_var();
void poly_menu();

#endif //  !DIALOG_H
#define DIALOG .H
