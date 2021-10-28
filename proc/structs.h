#ifndef STRUCTS_H
#define STRUCTS_H

#include "stack.h"

typedef double reg_t;
typedef double ram_t;

struct code_t
{
    int size_   = 0;
    double* val = nullptr;
};

#endif // STRUCTS_H
