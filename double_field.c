#include "field_info.h"
#include <stdio.h>
#include <stdlib.h>

static FieldInfo *DOUBLE_FIELD_INFO = NULL;

static void double_add(const void* a, const void* b, void* result)
{
    *(double*)result = *(const double*)a + *(const double*)b;
}

static void double_mul(const void* a, const void* b, void* result)
{
    *(double*)result = *(const double*)a * *(const double*)b;
}

static void double_print(const void* a)
{
    printf("%lf", *(const double*)a);
}

static void double_zero(void* a)
{
    *(double*)a = 0.0;
}

FieldInfo* get_double_field_info() 
{
    if(!DOUBLE_FIELD_INFO)
    {
        DOUBLE_FIELD_INFO = malloc(sizeof(FieldInfo));
        DOUBLE_FIELD_INFO->size = sizeof(double);
        DOUBLE_FIELD_INFO->add = double_add;
        DOUBLE_FIELD_INFO->mul = double_mul;
        DOUBLE_FIELD_INFO->print = double_print;
        DOUBLE_FIELD_INFO->zero = double_zero;
    }
    return DOUBLE_FIELD_INFO;
}

