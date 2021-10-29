#ifndef COMPILER_FUNC_H
#define COMPILER_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "errors.h"
#include "commands.h"

#define Ptr_Ver(ptr, err)                                   \
    do                                                      \
    {   													\
    	if ((ptr) == nullptr)                               \
        	(err).value[(err).amt++] = PTR_ERROR;           \
    } while(0)                                              \

//----------------------------------------------------------------------------

const int LABELS_AMOUNT  	= 100;
const int LABEL_NAME_SIZE 	= 20;

struct text_t
{
    int   len                   = 0;
    int   lxm_amt               = 0;
    char* value                 = nullptr;
    char  file_name[ARRAY_SIZE] = {0};
    int   lxm_pos[MAX_LXM_AMT]  = {0};
};

struct label_t
{
	int ip 					= 0;
	char name[LABEL_NAME_SIZE] 	= {};
};

//-----------------------------------------------------------------------------

error_t Code_Parsing(text_t * buf);

int Code_Divide(char* str);

int Search_Label(char* str, label_t* label);

error_t Compile(text_t* buf, double* obj_code);

#endif // COMPILER_FUNC_H
