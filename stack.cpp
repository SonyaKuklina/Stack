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
#include "stack_errors.h"

int main(void) {

    Stack_t stk1 = {};
    StackInit(&stk1, 5);

    if (StackPush(&stk1, 10) == 1)
        return 1;

    if (StackPush(&stk1, 20) == 1)
        return 1;

    int tech_element = StackPop(&stk1);

    if (StackDestroy(&stk1) == 1)
        return 1;

    printf("%d", tech_element);

    return 0;

}
