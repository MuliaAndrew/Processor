#ifndef TEXT_FUNC_H
#define TEXT_FUNC_H

#include "compiler_func.h"

error_t Text_Ctor(text_t* code_buf);

error_t Text_Dtor(text_t* code_buf);

int N_Symb(FILE* code);

int Log_Error(error_t* err);

void Obj_Code_Write(double* obj_code, int lxm_amt, char* file_name);

#endif // TEXT_FUNC_H
