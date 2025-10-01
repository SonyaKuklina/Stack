#ifndef STACK_ENUM_STACK
#define STACK_ENUM_STACK
#define CANARY_USE 1
const int count_err_stack = 5;
const int count_er = 5;

enum StackErr_t {

      SUCCESS = 0,
      NULL_POINTER_STACK,
      NULL_POINTER_DATA,

      #if CANARY_USE

      NULL_POINTER_LEFT_CANARY,
      NULL_POINTER_RIGHT_CANARY,
      CANARY_LEFT,
      CANARY_RIGHT,

      #endif

      ACCEPTABLE_STACK_SIZE,

} ;


#endif
