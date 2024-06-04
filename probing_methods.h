#ifndef PROBING_METHODS
#define PROBING_METHODS

#include "hashing_methods.h"
#include "cstdlib"

int id_linear_probing(long long user_id, int capacity, int i)
{
    return (mult(user_id, capacity) + i) % capacity;
}

int id_quadratic_probing(long long user_id, int capacity, int i)
{
    return (mult(user_id, capacity) + i*i + i) % capacity;
}

int id_double_probing(long long user_id, int capacity, int i)
{
    return std::abs(mult(user_id, capacity) + i*div(user_id, capacity)) % capacity;
}

int name_linear_probing(std::string user_name, int capacity, int i)
{
    return (polynomial_accumulation(user_name, capacity) + i) % capacity;
}

int name_quadratic_probing(std::string user_name, int capacity, int i)
{
    return (polynomial_accumulation(user_name, capacity) + i*i + i) % capacity;
}

int name_double_probing(std::string user_name, int capacity, int i)
{
    return std::abs(polynomial_accumulation(user_name, capacity) + i*djb2(user_name, capacity)) % capacity;
}
#endif
