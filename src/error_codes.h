#ifndef ERROR_CODES_H
#define ERROR_CODES_H

typedef enum {
    SUCCESS,
    ERR_MEMORY_ALLOCATION,
    ERR_NULLPTR,
    ERR_DIVISION_BY_ZERO,
    ERR_DIFFERENT_FIELDS,
    ERR_INVALID_POINT,
    ERR_INVALID_SELECTION,
    ERR_MIN_POLYS,
    TRY_AGAIN
} Error_type;

void handle_err_code(Error_type error); 

#endif /* ifndef ERROR_CODES_H */
