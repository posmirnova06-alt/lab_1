#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>

Matrix* create_matrix(size_t rows, size_t cols, FieldInfo* type)
{
    if (!type || rows == 0 || cols == 0)
    return NULL;

    Matrix* m = malloc(sizeof(Matrix));
    if (!m) return NULL;

    m -> rows = rows;
    m -> cols = cols;
    m -> type = type;

    m -> data = malloc(rows * cols * type->size);
    if (!m -> data)
    {
        free(m);
        return NULL;
    }

    for (size_t i=0; i < rows * cols; i++)
    {
        type -> zero((char*)m->data + i * type->size);
    }
    return m;
}

void destroy_matrix(Matrix* m)
{
    if (!m) return;
    free(m -> data);
    free(m);
}

void* matrix_at(Matrix* m, size_t row, size_t col)
{
    if (!m) return NULL;
    if (row >= m -> rows || col >= m -> cols) return NULL;

    size_t index = row * m -> cols + col;
    return (char*)m -> data + index * m -> type -> size;
}

const void* matrix_at_const(const Matrix* m, size_t row, size_t col)
{
    if (!m) return NULL;
    if (row >= m -> rows || col >= m -> cols) return NULL;

    size_t index = row * m -> cols + col;

    return (const char*)m -> data + index * m -> type -> size;
}

void matrix_print(const Matrix* m)
{
    if (!m) return;

    for (size_t i = 0; i < m -> rows; i++)
    {
        for (size_t j = 0; j < m -> cols; j++)
        {
            const void* element = matrix_at_const(m, i, j);
            m->type->print(element);
            printf(" ");
        }
        printf("\n");
    }
}

Matrix* matrix_add(const Matrix* a, const Matrix* b)
{
    if (!a || !b) return NULL;
    if (a -> rows != b -> rows || a -> cols != b -> cols) return NULL;
    if (a -> type != b -> type) return NULL;

    Matrix* c = create_matrix(a -> rows, a -> cols, a -> type);
    if (!c) return NULL;

    for (size_t i = 0; i < a -> rows * a-> cols; i++)
    {
        a->type->add((char*)a->data + i * a->type->size, (char*)b->data + i * a->type->size, (char*)c->data + i * a->type->size);
    }
    return c;
}

Matrix* matrix_mul(const Matrix* a, const Matrix* b)
{
    if (!a || !b) return NULL;
    if (a -> cols != b -> rows) return NULL;
    if (a -> type != b -> type) return NULL;

    Matrix* r = create_matrix(a -> rows, b -> cols, a -> type);
    if (!r) return NULL;

    for (size_t i = 0; i < a -> rows; i++)
    {
        for (size_t j = 0; j < b -> cols; j++)
        {
            void* result_cell = matrix_at(r, i, j);
            a->type->zero(result_cell);

            for (size_t k = 0; k < a -> cols; k++)
            {
                char temp[a -> type -> size];
                a -> type -> mul(matrix_at_const(a, i, k), matrix_at_const(b, k, j), temp);
                a -> type -> add(result_cell, temp, result_cell);
            }
        }
    }
    return r;
}

Matrix* matrix_transpose(const Matrix* m)
{
    if (!m) return NULL;

    Matrix* r = create_matrix(m -> cols, m -> rows, m -> type);
    if (!r) return NULL;

    for (size_t i = 0; i < m -> rows; i++)
    {
        for (size_t j = 0; j < m -> cols; j++)
        {
            m -> type -> copy(matrix_at_const(m, i, j), matrix_at(r, j, i));
        }
    }
    return r;
}

void matrix_row_add_combination(Matrix* m, size_t target, const size_t* rows , const double* coeffs, size_t count)
{
    if (!m || !rows || !coeffs) return;
    if (target >= m->rows) return;

    FieldInfo* t = m->type;
    if (!t) return;

    for (size_t j = 0; j < m->cols; j++)
    {
        void* destination = matrix_at(m, target, j);

        for (size_t i = 0; i < count; i++)
        {
            if (rows[i] >= m->rows) continue;
            if (rows[i]==target) continue;

            const void* source = matrix_at_const(m, rows[i], j);

            char coeff_buf[t->size];
            char temp[t->size];

            if (t->size == sizeof(int)) 
                *(int*)coeff_buf = (int)coeffs[i];
            else    
                *(double*)coeff_buf = (double)coeffs[i];
            
            t->mul(source, coeff_buf,temp);
            t->add(destination, temp, destination);
        }
    }
}
