#include "error_codes.h"
#include <stdio.h>

void handle_err_code(Error_type error){
    if (error != SUCCESS) {
        switch (error) {
            case ERR_MEMORY_ALLOCATION:
                printf("MEMORY_ALLOCATION_ERROR\n");
                break;
            case ERR_NULLPTR:
                printf("NULL_PTR_ERROR\n");
                break;
            case ERR_DIVISION_BY_ZERO:
                printf("DIVISION_BY_ZERO_ERROR\n");
                break;
            case ERR_DIFFERENT_FIELDS:
                printf("FIELDS_ARE_DIFFERENT\n");
                break;
            case ERR_INVALID_POINT:
                printf("INDEX_IS_INVALID\n");
                break;
            case ERR_INVALID_SELECTION:
                printf("INVALID_POLYNOMIAL_SELECTION\n");
                break;
            case ERR_MIN_POLYS:
                printf("ADD_ANOTHER POLYNOMIAL\n");
                break;
            case TRY_AGAIN:
                printf("Error! Try again!\n");
                break;
            
            default:
                printf("Unknown error code\n");
                break;
            
        }
    }
}
