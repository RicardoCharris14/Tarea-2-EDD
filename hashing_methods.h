#ifndef HASHING_METHODS
#define HASHING_METHODS

#include <string>
// --------------------------- key ~ user_id ------------------------------

int div(long long user_id, int capacity)
{
    return int(user_id) % capacity;
}

int mult(long long user_id, int capacity)
{
    const long double A = 0.6180339887498948482045868343656381177203091798057f;
    long double a = user_id*A;
    a -= (int)a;

    return capacity * a;
}


// -------------------------- key ~ user_name ---------------------------------

int polynomial_accumulation(const std::string &user_name, int capacity)
{
    int sum = 0, i = 1;
    for (char ch : user_name) {
        sum += (sum + ch)*i;
        i++;
    }
    return sum % capacity;
}

#endif
