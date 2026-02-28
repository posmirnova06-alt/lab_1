#ifndef FIELD_INFO_H
#define FIELD_INFO_H

#include <stddef.h>

typedef struct FieldInfo
{
    size_t size;

    void(*add)(const void* a, const void* b, void* result);
    void(*mul)(const void* a, const void* b, void* result);
    void(*print)(const void* a);
    void(*zero)(void* a);
    void(*copy)(const void*, void*);

} FieldInfo;

FieldInfo* get_int_field_info();
FieldInfo* get_double_field_info();

#endif 

