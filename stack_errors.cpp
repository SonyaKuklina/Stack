#include <stdio.h>
#include <cassert>
#include <math.h>
#include <stdlib.h>
#include "stack_errors.h"
#include "stack_processing.h"
#include "struct_stack.h"
#include "enum_stack.h"

int StackVerify(Stack_t* stk1) {//возвращает 1, если ошибки не найдены, 0 наоборот

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

        else if ((stk1 -> size_stack) > (stk1 -> capacity)) {

            (stk1 -> err[i]) = ACCEPTABLE_STACK_CAPACITY;
            printf("ERROR: invalid stack capacity\n");

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

    fprintf(stderr, "StackInformation called from %s: %d\n", file, line);
    printf("Stack[%p]\n", stk1);
    printf("{                 \n");
    printf("    size = %zu    \n", (stk1 -> size_stack));
    printf("    capacity = %zu\n", (stk1 -> capacity));
    printf("    data [%p]     \n", (stk1 -> data));
    printf("    {             \n");
    for (size_t index = 0; index < (stk1 -> size_stack); index++) {
        printf("        *[%lld] = %d\n", index, stk1 -> data[index]);
    }
    for (size_t index = (stk1 -> size_stack); index < (stk1 -> capacity); index++) {
        printf("         [%lld] = %d\n", index, stk1 -> data[index]);
    }
    printf("    }             \n");
    printf("}\n");

}

