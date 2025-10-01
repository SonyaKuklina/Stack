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
#define CANARY_USE 1

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
        #if CANARY_USE

        else if ((stk1 -> left_canary) == NULL) {

            (stk1 -> err[i]) = NULL_POINTER_LEFT_CANARY;
            printf("ERROR: null pointer to left_canary in stk1\n");

        }
        else if ((stk1 -> right_canary) == NULL) {

            (stk1 -> err[i]) = NULL_POINTER_RIGHT_CANARY;
            printf("ERROR: null pointer to right_canary in stk1\n");

        }

        else if (!CompareSuccess(*(stk1 -> left_canary), 0xFACE)) {

            (stk1 -> err[i]) = CANARY_LEFT;
            printf("ERROR: the left canary is destroyed\n");

        }

        else if (!CompareSuccess(*(stk1 -> right_canary), 0xFEED)) {

            (stk1 -> err[i]) = CANARY_RIGHT;
            printf("ERROR: the right canary is destroyed\n");

        }

        #endif

        else if ((stk1 -> size_stack) < 0) {

            (stk1 -> err[i]) = ACCEPTABLE_STACK_SIZE;
            printf("ERROR: invalid stack size\n");

        }

        else {

            (stk1 -> err[i]) = SUCCESS;

        }

        if ((stk1 -> err[0]) == SUCCESS)
            return 1;

    }

    return 0;

}

int StackInformation(Stack_t* stk1, const char* file, int line) {

    Stack_parametrs stack_info = {};

    if (GetStackParametrs(stk1, &stack_info) == 1)
        return 1;

    fprintf(stderr, "StackInformation called from %s: %d\n", file, line);
    printf("Stack[%p]\n", (stack_info.stack_adr_p));
    printf("{                   \n");
    printf("    size = %zu      \n", (stack_info.size_stack_p));
    printf("    capacity = %zu  \n", (stack_info.capacity_p));
    printf("    data [%p]       \n", (stack_info.data_adr_p));
    printf("    {               \n");
    for (size_t index = 0; index < (stack_info.size_stack_p); index++) {
        printf("        *[%lld] = %g\n", index, stack_info.data_adr_p[index]);
    }
    for (size_t index = (stack_info.size_stack_p);
                    index < (stack_info.capacity_p); index++) {
        printf("         [%lld] = %g\n", index, stack_info.data_adr_p[index]);
    }
    printf("    }             \n");
    printf("}\n");

    return 0;

}


int GetStackParametrs(Stack_t* stk1, Stack_parametrs* stack_info) {

    assert(stack_info != NULL);

    if (!StackVerify(stk1))
        return 1;

     (stack_info -> stack_adr_p)  = stk1;
     (stack_info -> size_stack_p) = (stk1 -> size_stack);
     (stack_info -> capacity_p)   = (stk1 -> capacity);
     (stack_info -> data_adr_p)   = (stk1 -> data);

     return 0;

}

int TestStack(Stack_t* stk1) {

      if (!StackVerify(stk1))
        return 1;

      char* buff = 0;
      size_t size_buff = SIZE_BUFF;

      char command[SIZE_BUFF];
      const char* str = 0;
      type_stack element = 0;

      while (Getline(&buff, size_buff) > 0) {

            assert(buff != NULL);

            if (sscanf(buff, "%s %lg", command, &element) == 2) {

                str = command;

                if (ChangeStack(str, element, stk1) == -1)

                    return -1;

            }

            else if (sscanf(buff, "%s", command) == 1) {

                str = command;
                int result = DoCommand(str, stk1);

                if (result == -1)

                    return -1;

                else if (result == 1)

                    break;
            }

      }

      return 0;
}

int ChangeStack(const char* str, type_stack element,
                            Stack_t* stk1) {

      assert(str != NULL);

      if (!StackVerify(stk1))
        return 1;

      if (strcmp(str, "PUSH") == 0) {

            if (StackPush(stk1, element) == 1)
                return -1;

            return 0;

      }

      return -1;

}

int DoCommand(const char* str, Stack_t* stk1) {

     assert(str != NULL);

     if (!StackVerify(stk1))
        return 1;

     type_stack last_el1 = 0;
     type_stack last_el2 = 0;

     if (strcmp(str, "ADD") == 0) {

        if (StackPop(stk1, &last_el1) == 1)
            return -1;

        if (StackPop(stk1, &last_el2) == 1)
            return -1;

        if (StackPush(stk1, last_el1 + last_el2) == 1)
            return -1;

        return 0;

     }

     else if (strcmp(str, "SUB") == 0) {

        if (StackPop(stk1, &last_el1) == 1)
            return -1;

        if (StackPop(stk1, &last_el2) == 1)
            return -1;

        if (StackPush(stk1, last_el2 - last_el1) == 1)
            return -1;

        return 0;

     }

     else if (strcmp(str, "MUL") == 0) {

        if (StackPop(stk1, &last_el1) == 1)
            return -1;

        if (StackPop(stk1, &last_el2) == 1)
            return -1;

        if (StackPush(stk1, last_el1 * last_el2) == 1)
            return -1;

        return 0;

     }

     else if (strcmp(str, "SQRT") == 0) {

        if (StackPop(stk1, &last_el1) == 1)
            return -1;

        type_stack sqrt_last_el = sqrt(last_el1 * 1e6) / 1e3;

        if (StackPush(stk1, sqrt_last_el) == 1)
            return -1;

        return 0;


     }

     else if (strcmp(str, "DIV") == 0) {

        if (StackPop(stk1, &last_el1) == 1)
            return -1;

        if (StackPop(stk1, &last_el2) == 1)
            return -1;

        if ((last_el2 != 0) && (StackPush(stk1, last_el1 / last_el2) == 1))
            return -1;

        return 0;

     }

     else if (strcmp(str, "OUT") == 0) {

        if (StackPop(stk1, &last_el1) == 1)
            return -1;

        printf("%f\n", last_el1);
        return 0;

     }

     if (strcmp(str, "HLT") == 0) {

        if (StackDestroy(stk1) == 1)
            return -1;

        return 1;

     }

     return -1;

}

