#include <stdio.h>
#include <cassert>
#include <math.h>
#include <stdlib.h>
#include "stack_processing.h"
#include "struct_stack.h"
#include "enum_stack.h"
#include "stack_test.h"
#include "stack_add.h"
#define STACK_INFORMATION(x) StackInformation((x), __FILE__, __LINE__);

int StackInit(Stack_t* stk1, size_t capacity, Err_t* err) {

    (stk1 -> data) = (type_stack*)calloc(capacity + TWO_CANARY, sizeof(type_stack));
    (stk1 -> data[0]) = 0xFACE;
    (stk1 -> data[capacity + 1]) = 0xFEED;

    if ((stk1 -> data) == NULL) {

         *err = ERR_MEMORY_ALLOC;
         return AllVerify(err);

    }

    (stk1 -> capacity) = capacity;
    (stk1 -> size_stack) = 0;

    for (int i = 0; i < count_err_stack; i++)
        (stk1 -> err[i]) = SUCCESS;

    return 0;

}

int StackPush(Stack_t* stk1, type_stack value, Err_t* err) {

    if (IsNAN(value)) {

        *err = INVALID_VALUES;
        return AllVerify(err);

    }

    if ((stk1 -> size_stack) >= (stk1 -> capacity)) {

        if (StackExpansion(stk1, err))
            return 1;
    }

    if (StackVerify(stk1))
        STACK_INFORMATION(stk1);

    (stk1 -> data[(stk1 -> size_stack++) + 1]) = value;

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

type_stack StackPop(Stack_t* stk1) {

    if (!StackVerify(stk1))
        return 1;

    type_stack last_element = stk1 -> data[(stk1 -> size_stack)];
    (stk1 -> data[(stk1 -> size_stack)]) = 0;
    (stk1 -> size_stack)--;

    if (!StackVerify(stk1))
        return 1;

    return last_element;

}

int StackExpansion(Stack_t* stk1, Err_t* err) {

     size_t capacity_t = stk1 -> capacity;
     size_t size_stack_t = stk1 -> size_stack;
     type_stack* old_data_ptr = stk1 -> data;

     type_stack* new_data_ptr = (type_stack*)realloc(old_data_ptr,
                                (capacity_t * 2 + 1) * sizeof(type_stack));

     if (new_data_ptr == NULL) {

        *err = ERR_MEMORY_ALLOC;
        free(old_data_ptr);
        return AllVerify(err);

     }

     old_data_ptr = new_data_ptr;

     for (size_t index = capacity_t + 1; index < capacity_t * 2 + 1; index++)
         *(old_data_ptr + index) = 0;

     capacity_t *= 2;
     *(old_data_ptr + capacity_t + 1)   = 0xFEED;
     (stk1 -> capacity) = capacity_t;

     (stk1 -> data) = old_data_ptr;

     return 0;

}

