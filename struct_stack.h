#ifndef STACK_STRUCT_STACK
#define STACK_STRUCT_STACK
#include "enum_stack.h"

typedef double type_stack;

struct Stack_t {

    type_stack* data;
    size_t size_stack;
    size_t capacity;
    StackErr_t err[count_err_stack];

    };

struct Stack_parametrs {

    Stack_t* stack_adr_p;
    size_t size_stack_p;
    size_t capacity_p;
    type_stack* data_adr_p;

    };

#endif
