#include <stdio.h>
#include <cassert>
#include <math.h>
#include <stdlib.h>
#include "stack_processing.h"
#include "struct_stack.h"
#include "enum_stack.h"
#include "stack_test.h"
#include "stack_add.h"
#define STACK_INFORMATION(x) StackInformation((x), __FILE__, __LINE__)

int StackInit(Stack_t* stk1, size_t capacity) {

    type_stack* new_memory = (type_stack*)calloc(capacity + TWO_CANARY, sizeof(type_stack));

    assert(new_memory != NULL);

    (stk1 -> data)         = new_memory + 1;
    (stk1 -> left_canary)  = new_memory;
    (stk1 -> right_canary) = new_memory + capacity + 1;
   *(stk1 -> left_canary)  = 0xFACE;
   *(stk1 -> right_canary) = 0xFEED;

    (stk1 -> capacity) = capacity;
    (stk1 -> size_stack) = 0;

    for (int i = 0; i < count_err_stack; i++)
        (stk1 -> err[i]) = SUCCESS;

    if (!StackVerify(stk1))
        return 1;

    return 0;

}

int StackPush(Stack_t* stk1, type_stack value) {

    if (!StackVerify(stk1))
        return 1;

    if ((stk1 -> size_stack) >= (stk1 -> capacity)) {

        if (StackExpansion(stk1))
            return 1;
    }

    if (StackVerify(stk1)) {

        if (STACK_INFORMATION(stk1))
            return -1;

    }

    (stk1 -> data[(stk1 -> size_stack++)]) = value;

    if (StackVerify(stk1)) {

        if (STACK_INFORMATION(stk1))
            return -1;

    }

    return 0;

}

int StackDestroy(Stack_t* stk1) {

    if (!StackVerify(stk1))
        return 1;

    free((stk1 -> data));

    for (size_t i = 0; i < (stk1 -> capacity); i++) {
        (stk1 -> data[i]) = NAN;
    }

    (stk1 -> size_stack)   = NAN;
    (stk1 -> capacity)     = NAN;
    (stk1 -> left_canary)  = NULL;
    (stk1 -> right_canary) = NULL;

    return 0;

}

int StackPop(Stack_t* stk1, type_stack* last_element) {

    assert(last_element != NULL);

    if (!StackVerify(stk1))
        return 1;

    *last_element = stk1 -> data[(stk1 -> size_stack) - 1];
    (stk1 -> data[(stk1 -> size_stack) - 1]) = 0;
    (stk1 -> size_stack)--;

    if (!StackVerify(stk1))
        return 1;

    return 0;

}

int StackExpansion(Stack_t* stk1) {

     if (!StackVerify(stk1))
        return 1;

     size_t capacity_t        = stk1 -> capacity;
     size_t size_stack_t      = stk1 -> size_stack;
     type_stack* old_data_ptr = stk1 -> left_canary;

     assert(old_data_ptr != NULL);

     type_stack* new_data_ptr = (type_stack*)realloc(old_data_ptr,
                                (capacity_t * 2 + TWO_CANARY) * sizeof(type_stack));

     if (new_data_ptr == NULL) {

        free(old_data_ptr);
        return 1;

     }

     old_data_ptr = new_data_ptr;

     for (size_t index = capacity_t + 1; index < capacity_t * 2 + 1; index++)
         *(old_data_ptr + index) = 0;

     capacity_t *= 2;
     (stk1 -> right_canary) = old_data_ptr;
     (stk1 -> left_canary)  = old_data_ptr + capacity_t + 1;
    *(stk1 -> right_canary) = 0xFEED;
    *(stk1 -> left_canary)  = 0xFACE;
     (stk1 -> data)         = old_data_ptr + 1;
     (stk1 -> capacity) = capacity_t;

     if (!StackVerify(stk1))
        return 1;

     return 0;

}

