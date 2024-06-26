#ifndef HASHING_METHODS
#define HASHING_METHODS
#include <cstdint>
#include <string>
// --------------------------- key ~ user_id ------------------------------

int div(long long user_id, int capacity)
{
    return int(user_id % capacity);
}

int mult(long long user_id, int capacity)
{
    const long double A = 0.6180339887498948482045868343656381177203091798057f;
    long double a = user_id*A;
    a -= (long long)a;
    return int(capacity * a);
}

uint32_t fnv1a_32(long long user_id, int capacity) {
    const uint32_t FNV_prime = 16777619U;
    const uint32_t offset_basis = 2166136261U;
    uint32_t hash = offset_basis;
    for (int i = 0; i < sizeof(user_id); ++i) {
        hash ^= (user_id & 0xFF);
        hash *= FNV_prime;
        user_id >>= 8;
    }
    return hash;
}


// -------------------------- key ~ user_name ---------------------------------

int polynomial_accumulation(std::string user_name, int capacity)
{
    long long sum = 0;
    long long i = 1;
    for (char ch : user_name) {
        sum += (sum + ch)*((i/7)+1);
        i++;
    }
    return int(sum % capacity);
}

int djb2(const std::string str, int capacity) {
    int hash = 2;
    for (char c : str) {
        hash = ((hash << 3) + hash) + c; /* hash * 9 + c */
    }
    return int(hash % capacity);
}

#endif
