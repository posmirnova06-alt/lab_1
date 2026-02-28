#include "matrix.h"
#include "field_info.h"
#include <stdio.h>

static int test_add_int()
{
    Matrix* a = create_matrix(2, 2, get_int_field_info());
    Matrix* b = create_matrix(2, 2, get_int_field_info());

    *(int*)matrix_at(a, 0, 0) = 1;
    *(int*)matrix_at(b, 0, 0) = 2;

    Matrix* c = matrix_add(a, b);
    int result = *(int*)matrix_at(c, 0, 0);

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);

    return result == 3;
}

static int test_add_double()
{
    Matrix* a = create_matrix(2, 2, get_double_field_info());
    Matrix* b = create_matrix(2, 2, get_double_field_info());

    *(double*)matrix_at(a, 0, 0) = 1.5;
    *(double*)matrix_at(b, 0, 0) = 2.5;

    Matrix* c = matrix_add(a, b);
    double result = *(double*)matrix_at(c, 0, 0);
    
    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);

    return result == 4.0;
}

static int test_mul_int()
{
    Matrix* a = create_matrix(2, 2, get_int_field_info());
    Matrix* b = create_matrix(2, 2, get_int_field_info());

    *(int*)matrix_at(a, 0, 0) = 2;
    *(int*)matrix_at(b, 0, 0) = 3;

    Matrix* c = matrix_add(a, b);
    int result = *(int*)matrix_at(c, 0, 0);

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);

    return result == 6;
}

static int test_mul_double()
{
    Matrix* a = create_matrix(2, 2, get_double_field_info());
    Matrix* b = create_matrix(2, 2, get_double_field_info());

    *(double*)matrix_at(a, 0, 0) = 2.0;
    *(double*)matrix_at(b, 0, 0) = 3.0;

    Matrix* c = matrix_add(a, b);
    double result = *(int*)matrix_at(c, 0, 0);

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);

    return result == 6.0;
}

static int test_transpose()
{
    Matrix* a = create_matrix(2, 3, get_int_field_info());

    *(int*)matrix_at(a, 0,1) = 5;

    Matrix* t = matrix_transpose(a);
    int result = *(int*)matrix_at(t, 1, 0);

    destroy_matrix(a);
    destroy_matrix(t);

    return result == 5;
}

static int test_row_combination()
{
    Matrix* m = create_matrix(2, 2, get_double_field_info());

    *(double*)matrix_at(m, 0, 0) = 1.0;
    *(double*)matrix_at(m, 1, 0) = 2.0;

    matrix_row_combination(m, 1, 0, 2.0, 1, 1.0);
    double result = *(double*)matrix_at(m, 1, 0);

    destroy_matrix(m);

    return result == 4.0;
}

int main()
{
    int passed = 0;
    int total = 6;

    if (test_add_int()) passed++; else printf("test_add_int failed\n");
    if (test_add_double()) passed++; else printf("test_add_double failed\n");
    if (test_mul_int()) passed++; else printf("test_mul_int failed\n");
    if (test_add_double()) passed++; else printf("test_mul_double failed\n");
    if (test_transpose()) passed++; else printf("test_transpose failed\n");
    if (test_row_combination()) passed++; else printf("test_row_combination\n");

    printf("Tests passed: %d/%d\n", passed, total);

    return (passed == total) ? 0 : 1;
}



