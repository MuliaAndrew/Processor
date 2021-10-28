#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "structs.h"
#include <string.h>

const int RAM_SIZE = 1000;
const int N_REGS   = 10;

//-----------------------------------------------------------------------------

error_t Processor(code_t* code);

error_t Code_Ctor(code_t* code, char* file_name);


#endif // PROCESSOR_H
