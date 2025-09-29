#ifndef STACK_STACK_PROCESSING
#define STACK_STACK_PROCESSING

#include "struct_stack.h"
const size_t TWO_CANARY = 2;

int StackInit(Stack_t* stk1, size_t capacity, Err_t* err);

int StackPush(Stack_t* stk1, type_stack value, Err_t* err);

int StackDestroy(Stack_t* stk1);

type_stack StackPop(Stack_t* stk1);

int StackExpansion(Stack_t* stk1, Err_t* err);

#endif
