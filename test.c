#include "matrix.h"
#include "field_info.h"
#include <stdio.h>

static int test_add_int()
{
    Matrix* a = create_matrix(2, 3, get_int_field_info());
    Matrix* b = create_matrix(2, 3, get_int_field_info());

    *(int*)matrix_at(a, 0, 0) = 1;
    *(int*)matrix_at(a, 0, 1) = 2;
    *(int*)matrix_at(a, 0, 2) = 3;
    *(int*)matrix_at(a, 1, 0) = 4;
    *(int*)matrix_at(a, 1, 1) = 5;
    *(int*)matrix_at(a, 1, 2) = 6;

    *(int*)matrix_at(b, 0, 0) = 6;
    *(int*)matrix_at(b, 0, 1) = 5;
    *(int*)matrix_at(b, 0, 2) = 4;
    *(int*)matrix_at(b, 1, 0) = 3;
    *(int*)matrix_at(b, 1, 1) = 2;
    *(int*)matrix_at(b, 1, 2) = 1;

    Matrix* c = matrix_add(a, b);

    int result = *(int*)matrix_at(c, 0, 0) == 7 && *(int*)matrix_at(c, 0, 1) == 7 && *(int*)matrix_at(c, 0, 2) == 7 && *(int*)matrix_at(c, 1, 0) == 7 && *(int*)matrix_at(c, 1, 1) == 7 && *(int*)matrix_at(c, 1, 2) == 7;

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);

    return result;
}

static int test_add_double()
{
    Matrix* a = create_matrix(2, 3, get_double_field_info());
    Matrix* b = create_matrix(2, 3, get_double_field_info());

    *(double*)matrix_at(a, 0, 0) = 1.5;
    *(double*)matrix_at(a, 0, 1) = 2.5;
    *(double*)matrix_at(a, 0, 2) = 3.5;
    *(double*)matrix_at(a, 1, 0) = 4.5;
    *(double*)matrix_at(a, 1, 1) = 5.5;
    *(double*)matrix_at(a, 1, 2) = 6.5;

    *(double*)matrix_at(b, 0, 0) = 1.5;
    *(double*)matrix_at(b, 0, 1) = 2.5;
    *(double*)matrix_at(b, 0, 2) = 3.5;
    *(double*)matrix_at(b, 1, 0) = 4.5;
    *(double*)matrix_at(b, 1, 1) = 5.5;
    *(double*)matrix_at(b, 1, 2) = 6.5;

    Matrix* c = matrix_add(a, b);

    int result = *(double*)matrix_at(c, 0, 0) == 3.0 && *(double*)matrix_at(c, 0, 1) == 5.0 && *(double*)matrix_at(c, 0, 2) == 7.0 && *(double*)matrix_at(c, 1, 0) == 9.0 && *(double*)matrix_at(c, 1, 1) == 11.0 && *(double*)matrix_at(c, 1, 2) == 13.0;

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);

    return result;
}

static int test_mul_int()
{
    Matrix* a = create_matrix(2, 3, get_int_field_info());
    Matrix* b = create_matrix(3, 2, get_int_field_info());

    *(int*)matrix_at(a, 0, 0) = 1;
    *(int*)matrix_at(a, 0, 1) = 2;
    *(int*)matrix_at(a, 0, 2) = 3;
    *(int*)matrix_at(a, 1, 0) = 4;
    *(int*)matrix_at(a, 1, 1) = 5;
    *(int*)matrix_at(a, 1, 2) = 6;

    *(int*)matrix_at(b, 0, 0) = 6;
    *(int*)matrix_at(b, 0, 1) = 5;
    *(int*)matrix_at(b, 1, 0) = 4;
    *(int*)matrix_at(b, 1, 1) = 3;
    *(int*)matrix_at(b, 2, 0) = 2;
    *(int*)matrix_at(b, 2, 1) = 1;

    Matrix* c = matrix_mul(a, b);

    int result = *(int*)matrix_at(c, 0, 0) == 20 && *(int*)matrix_at(c, 0, 1) == 14 && *(int*)matrix_at(c, 1, 0) == 56 && *(int*)matrix_at(c, 1, 1) == 41;

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);

    return result;
}

static int test_mul_double()
{
    Matrix* a = create_matrix(2, 2, get_double_field_info());
    Matrix* b = create_matrix(2, 2, get_double_field_info());

    *(double*)matrix_at(a, 0, 0) = 1.5;
    *(double*)matrix_at(a, 0, 1) = 2.5;
    *(double*)matrix_at(a, 1, 0) = 3.5;
    *(double*)matrix_at(a, 1, 1) = 4.5;

    *(double*)matrix_at(b, 0, 0) = 1.5;
    *(double*)matrix_at(b, 0, 1) = 2.5;
    *(double*)matrix_at(b, 1, 0) = 3.5;
    *(double*)matrix_at(b, 1, 1) = 4.5;

    Matrix* c = matrix_mul(a, b);

    int result =
        *(double*)matrix_at(c, 0, 0) == 11.0 && *(double*)matrix_at(c, 0, 1) == 15.0 && *(double*)matrix_at(c, 1, 0) == 21.0 && *(double*)matrix_at(c, 1, 1) == 29.0;

    destroy_matrix(a);
    destroy_matrix(b);
    destroy_matrix(c);

    return result;
}

static int test_transpose()
{
    Matrix* a = create_matrix(2, 3, get_int_field_info());
    *(int*)matrix_at(a, 0, 1) = 5;

    Matrix* t = matrix_transpose(a);

    int result = *(int*)matrix_at(t, 1, 0) == 5;

    destroy_matrix(a);
    destroy_matrix(t);

    return result;
}

static int test_row_combination()
{
    Matrix* m = create_matrix(2, 3, get_double_field_info());

    *(double*)matrix_at(m, 0, 0) = 1.0;
    *(double*)matrix_at(m, 0, 1) = 1.0;
    *(double*)matrix_at(m, 0, 2) = 1.0;

    *(double*)matrix_at(m, 1, 0) = 2.0;
    *(double*)matrix_at(m, 1, 1) = 2.0;
    *(double*)matrix_at(m, 1, 2) = 2.0;

    size_t rows[2] = {0, 1};
    double coeffs[2] = {0.5, 2.0};

    matrix_row_add_combination(m, 1, rows, coeffs, 2);

    int result =
        *(double*)matrix_at(m, 1, 0) == 6.5 && *(double*)matrix_at(m, 1, 1) == 6.5 && *(double*)matrix_at(m, 1, 2) == 6.5;

    destroy_matrix(m);
    return result;
}

int main()
{
    int passed = 0;
    int total = 6;

    if (test_add_int()) passed++; else printf("test_add_int failed\n");
    if (test_add_double()) passed++; else printf("test_add_double failed\n");
    if (test_mul_int()) passed++; else printf("test_mul_int failed\n");
    if (test_mul_double()) passed++; else printf("test_mul_double failed\n");
    if (test_transpose()) passed++; else printf("test_transpose failed\n");
    if (test_row_add_combination()) passed++; else printf("test_row_combination failed\n");

    printf("Tests passed: %d/%d\n", passed, total);

    return (passed == total) ? 0 : 1;
}
