#ifndef STACK_STRUCT_STACK
#define STACK_STRUCT_STACK
#include "enum_stack.h"
#define CANARY_USE 1
typedef double type_stack;

struct Stack_t {

    type_stack* data;
    size_t size_stack;
    size_t capacity;
    StackErr_t err[count_err_stack];

    #if CANARY_USE

    type_stack* left_canary;//адрес левой канарейки
    type_stack* right_canary; //адрес правой канарейки

    #endif

    };

struct Stack_parametrs {

    Stack_t* stack_adr_p;
    size_t size_stack_p;
    size_t capacity_p;
    type_stack* data_adr_p;

    };

#endif
