#ifndef STACK_STACK_ERRORS
#define STACK_STACK_ERRORS
#include "struct_stack.h"

int StackVerify(Stack_t* stk1);

void StackInformation(Stack_t* stk1,
                      const char* file, int line);

int AllVerify(Err_t* err);

Stack_parametrs GetStackParametrs(Stack_t* stk1);

int TestStack(Stack_t* stk1, Err_t* err);

int DoCommand(const char* command,
                          Stack_t* stk1, Err_t* err);

int ChangeStack(const char* command, type_stack element,
                                      Stack_t* stk1, Err_t* err);

#endif
