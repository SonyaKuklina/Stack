#ifndef STACK_STACK_ERRORS
#define STACK_STACK_ERRORS
#include "struct_stack.h"

int StackVerify(Stack_t* stk1);

void StackInformation(Stack_t* stk1,
                      const char* file, int line);

#endif
