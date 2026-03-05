#include "matrix.h"
#include "field_info.h"
#include <stdio.h>
#include <stdlib.h>

static void fill_matrix(Matrix* m)
{
    if (!m) return;

    printf("ВВЕДИТЕ ЭЛЕМЕНТЫ (%zu x %zu):\n", m->rows, m->cols);

    for (size_t i = 0; i < m->rows; i++) {
        for (size_t j = 0; j < m->cols; j++) 
        {
            if (m->type->size == sizeof(int)) 
            {
                int value;
                scanf("%d", &value);
                *(int*)matrix_at(m, i, j) = value;
            } 
            else 
            {
                double value;
                scanf("%lf", &value);
                *(double*)matrix_at(m, i, j) = value;
            }
        }
    }
}

static Matrix* create_and_fill()
{
    int type_choice;
    size_t rows, cols;

    printf("ТИП (1-int, 2-double): ");
    if (scanf("%d", &type_choice) != 1) return NULL;

    printf("СТРОКИ И СТОЛБЦЫ: ");
    if (scanf("%zu %zu", &rows, &cols) != 2) return NULL;

    FieldInfo* type = NULL;

    if (type_choice == 1) type = get_int_field_info();
    else if (type_choice == 2) type = get_double_field_info();
    else return NULL;

    Matrix* m = create_matrix(rows, cols, type);
    if (!m) return NULL;

    fill_matrix(m);
    return m;
}

int main()
{
    Matrix* A = NULL;
    Matrix* B = NULL;
    Matrix* C = NULL;

    int running = 1;

    while (running)
    {
        printf("\n1. Создать A\n");
        printf("2. Создать B\n");
        printf("3. A + B\n");
        printf("4. A * B\n");
        printf("5. Транспонировать A\n");
        printf("6. Прибавление линейной комбинации к строке A\n");
        printf("7. Вывести A\n");
        printf("8. Выход\n");
        printf("Ваш выбор: ");

        int choice;
        if (scanf("%d", &choice) != 1) break;

        switch (choice)
        {
            case 1:
                if (A) destroy_matrix(A);
                A = create_and_fill();
                break;

            case 2:
                if (B) destroy_matrix(B);
                B = create_and_fill();
                break;

            case 3:
                if (A && B)
                {
                    if (C) destroy_matrix(C);
                    C = matrix_add(A, B);
                    if (C) matrix_print(C);
                }
                break;

            case 4:
                if (A && B)
                {
                    if (C) destroy_matrix(C);
                    C = matrix_mul(A, B);
                    if (C) matrix_print(C);
                }
                break;

            case 5:
                if (A)
                {
                    Matrix* T = matrix_transpose(A);
                    destroy_matrix(A);
                    A = T;
                    matrix_print(A);
                }
                break;

            case 6:
                if (A)
                {
                    size_t target;
                    size_t count;

                    printf("Целевая строка (начиная с нуля): ");
                    scanf("%zu", &target);

                    printf("Сколько строк в линейной комбинации? ");
                    scanf("%zu", &count);

                    size_t rows[count];
                    double coeffs[count];

                    for (size_t i = 0; i < count; i++)
                    {
                        printf("Строка[%zu], Коэффициент[%zu]: ", i, i);
                        scanf("%zu %lf", &rows[i], &coeffs[i]);
                    }
    
                    matrix_row_add_combination(A, target, rows, coeffs, count);
                    matrix_print(A);
                }
                break;

            case 7:
                if (A) matrix_print(A);
                break;

            case 8:
                running = 0;
                break;
        }
    }

    if (A) destroy_matrix(A);
    if (B) destroy_matrix(B);
    if (C) destroy_matrix(C);

    return 0;
}

