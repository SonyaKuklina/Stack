#ifndef STACK_ENUM_STACK
#define STACK_ENUM_STACK
const int count_err_stack = 5;
const int count_er = 5;

enum Err_t {

      SUCCESS_OP = 0,
      NULL_POINTER,
      ERR_FILE_OPEN,
      INVALID_VALUES,
      ERR_MEMORY_ALLOC,

} ;

enum StackErr_t {

      SUCCESS = 0,
      NULL_POINTER_STACK,
      NULL_POINTER_DATA,
      ACCEPTABLE_STACK_SIZE,
      CANARY_LEFT,
      CANARY_RIGHT,
} ;


#endif
