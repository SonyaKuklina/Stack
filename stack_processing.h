#ifndef STACK_STACK_PROCESSING
#define STACK_STACK_PROCESSING

#include "struct_stack.h"
const size_t TWO_CANARY = 2;

int StackInit(Stack_t* stk1, size_t capacity);

int StackPush(Stack_t* stk1, type_stack value);

int StackDestroy(Stack_t* stk1);

int StackPop(Stack_t* stk1, type_stack* last_element);

int StackExpansion(Stack_t* stk1);

#endif
