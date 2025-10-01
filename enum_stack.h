#ifndef STACK_ENUM_STACK
#define STACK_ENUM_STACK
const int count_err_stack = 5;
const int count_er = 5;

enum StackErr_t {

      SUCCESS = 0,
      NULL_POINTER_STACK,
      NULL_POINTER_DATA,
      NULL_POINTER_LEFT_CANARY,
      NULL_POINTER_RIGHT_CANARY,
      ACCEPTABLE_STACK_SIZE,
      CANARY_LEFT,
      CANARY_RIGHT,

} ;


#endif
