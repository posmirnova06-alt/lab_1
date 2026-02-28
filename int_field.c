#include "field_info.h"
#include <stdio.h>
#include <stdlib.h>

static FieldInfo *INT_FIELD_INFO = NULL;

static void int_add(const void* a, const void* b, void* result)
{
    *(int*)result = *(const int*)a + *(const int*)b;
}

static void int_mul(const void* a, const void* b, void* result)
{
    *(int*)result = *(const int*)a * *(const int*)b;
}

static void int_print(const void* a)
{
    printf("%d", *(const int*)a);
}

static void int_zero(void* a)
{
    *(int*)a = 0;
}

FieldInfo* get_int_field_info()
{
    if(!INT_FIELD_INFO)
    {
        INT_FIELD_INFO = malloc(sizeof(FieldInfo));
        INT_FIELD_INFO->size = sizeof(int);
        INT_FIELD_INFO->add = int_add;
        INT_FIELD_INFO->mul = int_mul;
        INT_FIELD_INFO->print = int_print;
        INT_FIELD_INFO->zero =int_zero;
    }
    return INT_FIELD_INFO;
}

