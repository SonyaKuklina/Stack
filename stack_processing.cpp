#include <stdio.h>
#include <cassert>
#include <math.h>
#include <stdlib.h>
#include "stack_processing.h"
#include "struct_stack.h"
#include "enum_stack.h"
#include "stack_errors.h"
#define STACK_INFORMATION(x) StackInformation((x), __FILE__, __LINE__);
void StackInit(Stack_t* stk1, size_t capacity) {

    (stk1 -> data) = (int*)calloc(capacity, sizeof(int));
    (stk1 -> capacity) = capacity;
    (stk1 -> size_stack) = 0;
    for (int i = 0; i < count_err_stack; i++)
        (stk1 -> err[i]) = SUCCESS;

}

int StackPush(Stack_t* stk1, int value) {

    if (StackVerify(stk1))
        STACK_INFORMATION(stk1);

    (stk1 -> data[stk1 -> size_stack++]) = value;

    if (StackVerify(stk1))
        STACK_INFORMATION(stk1);

    return 0;

}

int StackDestroy(Stack_t* stk1) {

    if (!StackVerify(stk1))
        return 1;

    free((stk1 -> data));

    for (size_t i = 0; i < (stk1 -> capacity); i++) {
        (stk1 -> data[i]) = NAN;
    }

    (stk1 -> size_stack) = NAN;
    (stk1 -> capacity) = NAN;


    return 0;

}

int StackPop(Stack_t* stk1) {

    if (!StackVerify(stk1))
        return 1;

    int last_element = stk1 -> data[(stk1 -> size_stack) - 1];
    (stk1 -> size_stack)--;
    return (last_element);

    if (!StackVerify(stk1))
        return 1;

}

