#ifndef PROBING_METHODS
#define PROBING_METHODS

#include "hashing_methods.h"

int linear_probing(long long user_id, int capacity, int i)
{
    return (mult(user_id, capacity) + i) % capacity;
}

int quadratic_probing(long long user_id, int capacity, int i)
{
    return (mult(user_id, capacity) + i*i + i) % capacity;
}

int double_probing(long long user_id, int capacity, int i)
{
    return (mult(user_id, capacity) + i*div(user_id, capacity)) % capacity;
}

#endif
