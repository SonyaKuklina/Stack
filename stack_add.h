#ifndef STACK_STACK_ADD
#define STACK_STACK_ADD

#include "struct_stack.h"

const size_t SIZE_BUFF = 20;
const double SMALL_CONST = 1.e-16;

bool IsNAN(type_stack n);

bool ComparisonWithZero(type_stack n);

bool CompareSuccess(type_stack n1, type_stack n2);

size_t Getline(char** buff ,size_t size_buff);

#endif

