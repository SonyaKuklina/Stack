#ifndef STACK_STRUCT_STACK
#define STACK_STRUCT_STACK
#include "enum_stack.h"

struct Stack_t {

    int* data;
    size_t size_stack;
    size_t capacity;
    StackErr_t err[count_err_stack];

    };

/*struct Stack_par {

    Stack_t* stack_adr;
    size_t size_stack;
    size_t capacity;
    int* data_adr;

    };*/

#endif
