#include "matrix.h"
#include "field_info.h"
#include <stdio.h>
#include <stdlib.h>

static void fill_matrix(Matrix* m)
{
    if (!m) return;

    printf("ВВЕДИТЕ ЭЛЕМЕНТЫ (%zu x %zu):\n", m -> rows, m -> cols);

    for (size_t i = 0; i < m -> rows; i++)
    {
        for (size_t j = 0; j < m -> cols; j++)
        {
            if (m -> type -> size == sizeof(int))
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

    printf("ТИП МАТРИЦЫ (1 - int, 2 - double): ");
    if (scanf("%d", &type_choice) != 1) return NULL;

    printf("ВВЕДИТЕ КОЛИЧЕСТВО СТРОК И СТОЛБЦОВ: ");
    if (scanf("%zu %zu", &rows, &cols) != 2) return NULL;

    FieldInfo* type = NULL;

    if (type_choice == 1) type = get_int_field_info();
    else if (type_choice == 2) type = get_double_field_info();
    else
    {
        printf("ВЫБРАН НЕВЕРНЫЙ ТИП\n");
        return NULL;
    }

    Matrix* m = create_matrix(rows, cols, type);
    if (!m)
    {
        printf("Ошибка при создании матрицы\n");
        return NULL;
    }
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
        printf("____МЕНЮ____\n");
        printf("1. СОЗДАТЬ МАТРИЦУ A\n");
        printf("2. СОЗДАТЬ МАТРИЦУ B\n");
        printf("3. A + B\n");
        printf("4. A * B\n");
        printf("5. ТРАНСПОНИРОВАТЬ МАТРИЦУ A\n");
        printf("6. НАЙТИ ЛИНЕЙНУЮ КОМБИНАЦИЮ ДВУХ СТРОК (A)\n");
        printf("7. ВЫВЕСТИ МАТРИЦУ A\n");
        printf("8. ЗАКОНЧИТЬ\n");
        printf("ВАШ ВЫБОР:\n");

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
                if (!A || !B)
                {
                    printf("МАТРИЦЫ НЕ СОЗДАНЫ\n");
                    break;
                }

                if (A -> type != B -> type)
                {
                    printf("ТИПЫ МАТРИЦ НЕ СОВПАДАЮТ\n");
                    break;
                }
            
                if (C) destroy_matrix(C);
                C = matrix_add(A,B);

                if(!C) printf("НЕЛЬЗЯ ВЫПОЛНИТЬ СЛОЖЕНИЕ\n");
                else
                {
                    printf("RESULT: \n");
                    matrix_print(C);
                }
                break;

            case 4:
                if (!A || !B)
                {
                    printf("МАТРИЦЫ НЕ СОЗДАНЫ\n");
                    break;
                }

                if (A -> type != B -> type)
                {
                    printf("ТИПЫ МАТРИЦ НЕ СОВПАДАЮТ\n");
                    break;
                }
            
                if (C) destroy_matrix(C);
                C = matrix_mul(A,B);

                if(!C) printf("НЕЛЬЗЯ ВЫПОЛНИТЬ УМНОЖЕНИЕ\n");
                else
                {
                    printf("RESULT: \n");
                    matrix_print(C);
                }
                break;

            case 5:
                if (!A)
                {
                    printf("МАТРИЦА А НЕ СОЗДАНА\n");
                    break;
                }

                {
                    Matrix* T = matrix_transpose(A);
                    destroy_matrix(A);
                    A = T;

                    printf("ТРАНСПОНИРОВАННАЯ МАТРИЦА А: \n");
                    matrix_print(A);
                }
                break;

            case 6:
                if(!A)
                {
                    printf("МАТРИЦА А НЕ СОЗДАНА\n");
                    break;
                }

                {
                    size_t target, r1, r2;
                    double k1, k2;

                    printf("ВВЕДИТЕ СТРОКУ:\n");
                    scanf("%zu %zu %lf %zu %lf", &target, &r1, &k1, &r2, &k2);

                    printf("РЕЗУЛЬТАТ: \n");
                    matrix_row_combination(A, target, r1, k1, r2, k2);
                    matrix_print(A);
                }
                break;

            case 7:
                    if (A) matrix_print(A);
                    else printf("МАТРИЦА А НЕ СОЗДАНА\n");
                    break;

                case 8:
                    running = 0;
                    break;

                default:
                    printf("Неверно выбран номер\n");        
        }
    }

    if (A) destroy_matrix(A);
    if (B) destroy_matrix(B);
    if (C) destroy_matrix(C);

    return 0;
}


*cd "/Users/p-smirnova06/Desktop/МИФИ/project /лаб 1"  gcc -std=c99 -Wall -Wextra Main.c Matrix.c Int_field.c double_field.c -o app*
./app *

