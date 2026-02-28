#ifndef MATRIX_H
#define MATRIX_H

#include "field_info.h"
#include <stddef.h>

typedef struct 
{
    void *data;
    size_t rows;
    size_t cols;
    FieldInfo *type;
} Matrix;

Matrix* create_matrix(size_t rows, size_t cols, FieldInfo* type);
void destroy_matrix(Matrix* m);

void* matrix_at(Matrix* m, size_t row, size_t col);
const void* matrix_at_const(const Matrix* m, size_t row, size_t col);

void matrix_print(const Matrix* m);

Matrix* matrix_add(const Matrix* a, const Matrix* b);
Matrix* matrix_mul(const Matrix* a, const Matrix* b);
Matrix* matrix_transpose(const Matrix* m);
void matrix_row_combination(Matrix* m, size_t target, size_t row1, double k1, size_t row2, double k2);

#endif 


