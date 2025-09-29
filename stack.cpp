#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "stack_processing.h"
#include "struct_stack.h"
#include "enum_stack.h"
#include "stack_test.h"
#include "stack_add.h"

int main(void) {

    Stack_t stk1 = {};
    Err_t err = SUCCESS_OP;

    if (StackInit(&stk1, 5, &err) == 1)
        return -1;

    if (TestStack(&stk1, &err) == -1)
        return -1;

    return 0;

}
