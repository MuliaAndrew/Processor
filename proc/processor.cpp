#include <stdlib.h>
#include "processor.h"
#include "commands.h"

static 		 int MINSIZE   = 32;
static const int SIZE_COEF = 32;

error_t Code_Ctor(code_t* code, char* file_name)
{
	ptr_ver(code);
	ptr_ver(file_name);

	char* version_assert = (char*)calloc(sizeof(version), sizeof(char));
	char* extention_assert = (char*)calloc(sizeof(extention), sizeof(char));

	FILE* code_file = fopen(file_name, "rb");
	ptr_ver(code_file);

	fscanf(code_file, "%s %s", extention_assert, version_assert);
	// printf("%s\n%s\n", extention_assert, version_assert);

	if (strcmp(extention_assert, extention))
	{
		return EXTENTION_ERROR;
	}

	if(strcmp(version_assert, version))
	{
		return VERSION_ERROR;
	}

	code->val = (data_t*)calloc(MINSIZE, sizeof(data_t));

	/* fseek(code_file, 1, SEEK_CUR); 
	int AA = ftell(code_file); 
	printf("%d", AA); */

	while(fscanf(code_file, "%lg", code->val + code->size_) != EOF)
	{
		if (code->size_ >= MINSIZE)
		{
			MINSIZE += SIZE_COEF;
			code->val = (data_t*)realloc(code->val, MINSIZE);
		}
        code->size_++;
	}

	fclose(code_file);
	return NO_ERROR;
}

error_t Processor(code_t* code)
{
	stack_t stack = {};
	Stack_Ctor(&stack);

    reg_t reg[N_REGS] = {0};
    
    ram_t ram[RAM_SIZE] = {0};
    
    int ip = 0;

    while (true)
    {
        switch ((int)code->val[ip])
    	{
            case PUSHREG:
    		{
                Stack_Push(&stack, reg[(int)code->val[++ip]]);
   				break;
    		}
    		case PUSHRAMREG:
    		{
    			Stack_Push(&stack, ram[(int)reg[(int)code->val[++ip]]]);
    			break;
    		}
    		case PUSHRAMCONST:
    		{
    			Stack_Push(&stack, ram[(int)code->val[++ip]]);
    			break;
    		}
    		case PUSHCONST:
    		{
    			Stack_Push(&stack, code->val[++ip]);
    			break;
    		}
    		case POPREG:
    		{
    			reg[(int)code->val[++ip]] = Stack_Pop(&stack);
    			break;
    		}
    		case POPRAMCONST:
    		{
    			ram[(int)code->val[++ip]] = Stack_Pop(&stack);
    			break;
    		}
    		case POPRAMREG:
    		{
    			ram[(int)reg[(int)code->val[++ip]]] = Stack_Pop(&stack);
    			break;
    		}
    		case ADD:
    		{
    			double arg1 = Stack_Pop(&stack);
    			double arg2 = Stack_Pop(&stack);
    			Stack_Push(&stack, arg1 + arg2);
    			break;
    		}
    		case SUB:
    		{
    			double arg1 = Stack_Pop(&stack);
    			double arg2 = Stack_Pop(&stack);
    			Stack_Push(&stack, arg1 - arg2);
    			break;
    		}
    		case MUL:
    		{
    			double arg1 = Stack_Pop(&stack);
    			double arg2 = Stack_Pop(&stack);
    			Stack_Push(&stack, arg1 * arg2);
    			break;
    		}
    		case DIV:
    		{
    			double arg1 = Stack_Pop(&stack);
    			double arg2 = Stack_Pop(&stack);
    			Stack_Push(&stack, arg1 / arg2);
    			break;
    		}
    		case IN:
    		{
    			double arg;
    			scanf("%lg", &arg);
    			Stack_Push(&stack, arg);
    			break;
    		}
    		case OUT:
    		{
    			double arg = Stack_Pop(&stack);
    			printf("%lg\n", arg);
    			break;
    		}
            case JMP:
            {
                ip = (int)code->val[++ip];
                break;
            }
            case JA:
            {
                if (Stack_Pop(&stack) > Stack_Pop(&stack))
                    ip = (int)code->val[++ip];

                break;
            }
            case JAE:
            {
                 if (Stack_Pop(&stack) >= Stack_Pop(&stack))
                    ip = (int)code->val[++ip];

                break;
            }
            case JB:
            {
                 if (Stack_Pop(&stack) < Stack_Pop(&stack))
                    ip = (int)code->val[++ip];

                break;
            }
            case JBE:
            {
                 if (Stack_Pop(&stack) <= Stack_Pop(&stack))
                    ip = (int)code->val[++ip];

                break;
            }
            case JNE:
            {
                 if (Stack_Pop(&stack) != Stack_Pop(&stack))
                    ip = (int)code->val[++ip];

                break;
            }
            case JE:
            {
                 if (Stack_Pop(&stack) == Stack_Pop(&stack))
                    ip = (int)code->val[++ip];

                break;
            }
    		case HLT:
    			return NO_ERROR;
    	}
    	ip++;
    }

	return UNDEF_ERROR;
}