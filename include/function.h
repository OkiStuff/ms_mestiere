#ifndef MESTIERE_FUNCTION_H
#define MESTIERE_FUNCTION_H

#include "types.h"
#include <stdint.h>

// TODO: Consumers
#define CONSUMER(T) consumer_##T##_func_t
#define DEFINE_CONSUMER(T) typedef void (*CONSUMER(T))(T)

DEFINE_CONSUMER(int);
DEFINE_CONSUMER(char);
DEFINE_CONSUMER(pointer_t);

// Biconsumers
#define BICONSUMER(T,U) biconsumer_##T##_##U##_func_t
#define DEFINE_BICONSUMER(T,U) typedef void (*BICONSUMER(T,U))(T, U)

DEFINE_BICONSUMER(int, pointer_t);
DEFINE_BICONSUMER(int, int);
DEFINE_BICONSUMER(char, char);

#endif // MESTIERE_FUNCTION_H
