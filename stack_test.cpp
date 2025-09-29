#include <stdio.h>
#include <cassert>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "stack_test.h"
#include "stack_processing.h"
#include "struct_stack.h"
#include "enum_stack.h"
#include "stack_add.h"

int StackVerify(Stack_t* stk1) {

    for (int i = 0; i < count_err_stack; i++) {

        if (stk1 == NULL) {

            (stk1 -> err[i]) = NULL_POINTER_STACK;
            printf("ERROR: null pointer to stk1\n");

        }

        else if ((stk1 -> data) == NULL) {

            (stk1 -> err[i]) = NULL_POINTER_DATA;
            printf("ERROR: null pointer to data in stk1\n");

        }

        else if ((stk1 -> size_stack) < 0) {

            (stk1 -> err[i]) = ACCEPTABLE_STACK_SIZE;
            printf("ERROR: invalid stack size\n");

        }

        else if (!CompareSuccess((stk1 -> data[0]), 0xFACE)) {

            (stk1 -> err[i]) = CANARY_LEFT;
            printf("ERROR: the stack is damaged\n");

        }

        else if (!CompareSuccess((stk1 -> data[(stk1 -> capacity) + 1]), 0xFEED)) {

            (stk1 -> err[i]) = CANARY_RIGHT;
            printf("ERROR: the stack is damaged\n");

        }

        else {

            (stk1 -> err[i]) = SUCCESS;

        }

        if ((stk1 -> err[0]) == SUCCESS)
            return 1;

    }

    return 0;

}

void StackInformation(Stack_t* stk1, const char* file, int line) {

    Stack_parametrs stack_info = GetStackParametrs(stk1);
    Stack_parametrs* stack_info_p = &stack_info;

    fprintf(stderr, "StackInformation called from %s: %d\n", file, line);
    printf("Stack[%p]\n", (stack_info_p -> stack_adr_p));
    printf("{                   \n");
    printf("    size = %zu      \n", (stack_info_p -> size_stack_p));
    printf("    capacity = %zu  \n", (stack_info_p -> capacity_p));
    printf("    data [%p]       \n", (stack_info_p -> data_adr_p));
    printf("    {               \n");
    printf("         [%d] = %g\n", 0, (stack_info_p -> data_adr_p[0]));
    for (size_t index = 1; index < (stack_info_p -> size_stack_p) + 1; index++) {
        printf("        *[%lld] = %g\n", index, stack_info_p -> data_adr_p[index]);
    }
    for (size_t index = (stack_info_p -> size_stack_p) + 1;
                    index < (stack_info_p -> capacity_p) + TWO_CANARY; index++) {
        printf("         [%lld] = %g\n", index, stack_info_p -> data_adr_p[index]);
    }
    printf("    }             \n");
    printf("}\n");

}


int AllVerify(Err_t* err) {

    switch(*err) {
        case NULL_POINTER:     printf("ERROR: null pointer on element\n");
                               return 1;

        case ERR_FILE_OPEN:    printf("ERROR: file open incorrect\n");
                               return 1;

        case INVALID_VALUES:   printf("ERROR: values incorrect\n");
                               return 1;

        case ERR_MEMORY_ALLOC: printf("ERROR: memory allocation failure\n");
                               return 1;

        case SUCCESS_OP:       return 0;

        default:               assert(0);
    }

}

Stack_parametrs GetStackParametrs(Stack_t* stk1) {

     Stack_parametrs stack_info  = {

                    stack_info.stack_adr_p  = stk1,
                    stack_info.size_stack_p = (stk1 -> size_stack),
                    stack_info.capacity_p   = (stk1 -> capacity),
                    stack_info.data_adr_p   = (stk1 -> data)

                    };

     return stack_info;
}

int TestStack(Stack_t* stk1, Err_t* err) {

      char* buff = 0;
      size_t size_buff = SIZE_BUFF;

      char command[SIZE_BUFF];
      const char* str = 0;
      type_stack element = 0;

      while (Getline(&buff, size_buff) > 0) {

            assert(buff != NULL);

            if (sscanf(buff, "%s %lg", command, &element) == 2) {

                str = command;

                if (ChangeStack(str, element, stk1, err) == -1)

                    return -1;

            }

            else if (sscanf(buff, "%s", command) == 1) {

                str = command;
                int result = DoCommand(str, stk1, err);

                if (result == -1)

                    return -1;

                else if (result == 1)

                    break;
            }

      }

      return 0;
}

int ChangeStack(const char* str, type_stack element,
                                      Stack_t* stk1, Err_t* err) {

      if (strcmp(str, "PUSH") == 0) {

            if (StackPush(stk1, element, err) == 1)
                return -1;

            return 0;

      }

      return -1;

}

int DoCommand(const char* str,
                          Stack_t* stk1, Err_t* err) {

     if (strcmp(str, "ADD") == 0) {

        type_stack last_el1 = StackPop(stk1);
        type_stack last_el2 = StackPop(stk1);

        if (StackPush(stk1, last_el1 + last_el2, err) == 1)
            return -1;

        return 0;

     }

     else if (strcmp(str, "SUB") == 0) {

        type_stack last_el1 = StackPop(stk1);
        type_stack last_el2 = StackPop(stk1);

        if (StackPush(stk1, last_el2 - last_el1, err) == 1)
            return -1;

        return 0;

     }
     else if (strcmp(str, "MUL") == 0) {

        type_stack last_el1 = StackPop(stk1);
        type_stack last_el2 = StackPop(stk1);

        if (StackPush(stk1, last_el1 * last_el2, err) == 1)
            return -1;

        return 0;

     }
     else if (strcmp(str, "SQRT") == 0) {

        type_stack last_el      = StackPop(stk1);
        type_stack sqrt_last_el = sqrt(last_el * 1e6) / 1e3;

        if (StackPush(stk1, sqrt_last_el, err) == 1)
            return -1;

        return 0;


     }
     else if (strcmp(str, "DIV") == 0) {

        type_stack last_el1 = StackPop(stk1);
        type_stack last_el2 = StackPop(stk1);

        if ((last_el2 != 0) && (StackPush(stk1, last_el1 / last_el2, err) == 1))
            return -1;

        return 0;

     }
     else if (strcmp(str, "OUT") == 0) {

        printf("%f\n", StackPop(stk1));
        return 0;

     }
     if (strcmp(str, "HLT") == 0) {

        if (StackDestroy(stk1) == 1)
            return -1;
        return 1;

     }

     return -1;

}

