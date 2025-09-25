#ifndef STACK_STACK_PROCESSING
#define STACK_STACK_PROCESSING

#include "struct_stack.h"

void StackInit(Stack_t* stk1, size_t capacity);

int StackPush(Stack_t* stk1, int value);

int StackDestroy(Stack_t* stk1);

int StackPop(Stack_t* stk1);

#endif
