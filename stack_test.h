#ifndef STACK_STACK_ERRORS
#define STACK_STACK_ERRORS
#include "struct_stack.h"

int StackVerify(Stack_t* stk1);

int StackInformation(Stack_t* stk1,
                      const char* file, int line);

int GetStackParametrs(Stack_t* stk1, Stack_parametrs* stack_info);

int TestStack(Stack_t* stk1);

int DoCommand(const char* command, Stack_t* stk1);

int ChangeStack(const char* command, type_stack element,
                                Stack_t* stk1);

#endif
