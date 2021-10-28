#include "compiler_func.h"

static error_t ERR = {};

error_t Code_Parsing(text_t* code_buf)
{
    Ptr_Ver(code_buf, ERR);

    int buf_pos = 0;

    while (code_buf->value[buf_pos] != '\0')
    {
        if (!isspace(code_buf->value[buf_pos]))
        {
            code_buf->lxm_pos[code_buf->lxm_amt] = buf_pos;
            code_buf->lxm_amt++;
            buf_pos += Code_Divide(code_buf->value + buf_pos);
            printf("%s\n", code_buf->value + code_buf->lxm_pos[code_buf->lxm_amt - 1]);
        }
        buf_pos++;
    }

    return ERR;
}

int Code_Divide(char* str)
{
    Ptr_Ver(str, ERR);

    int symb_index = 0;

    if (str[symb_index] == '[')
        symb_index++;

    while (isalnum(str[symb_index]))
        symb_index++;

    if (str[symb_index] == ']')
        symb_index++;

    str[symb_index] = '\0';

    return symb_index;
}

error_t Compile(text_t* code_buf, double* obj_code)
{
    Ptr_Ver(code_buf, ERR);
    Ptr_Ver(obj_code, ERR);

    int lxm_amt = code_buf->lxm_amt;
      printf("\n%d\n", lxm_amt);
    for (int n_lxm = 0; n_lxm < lxm_amt; n_lxm++) 
    {
        register char* temp_ptr = code_buf->value + code_buf->lxm_pos[n_lxm];
        if (strcmp(temp_ptr, "in") == 0)
        {
            obj_code[n_lxm] = IN;
        }
        else if (strcmp(temp_ptr, "push") == 0)
        {
            if (isalpha(*(code_buf->value + code_buf->lxm_pos[n_lxm + 1])))
            {
                obj_code[n_lxm++] = PUSHREG;
                obj_code[n_lxm] = *(code_buf->value + code_buf->lxm_pos[n_lxm]) - 'a';

               /* if (*(code_buf->value + code_buf->lxm_pos[n_lxm + 1]) == '+')
                {
                    n_lxm++;
                    obj_code[n_lxm] += atof(code_buf->value + code_buf->lxm_pos[n_lxm + 1]);
                    n_lxm++;
                }*/
            }
            else if (*(code_buf->value + code_buf->lxm_pos[n_lxm + 1]) == '[')
            {
                if (isalpha(*(code_buf->value + code_buf->lxm_pos[n_lxm + 1])))
                {    
                    obj_code[n_lxm++] = POPRAMREG;
                    obj_code[n_lxm] = *(code_buf->value + code_buf->lxm_pos[n_lxm] + 1) - 'a';
                }
                else   
                {
                    obj_code[n_lxm++] = PUSHRAMREG;
                    obj_code[n_lxm] = atof(code_buf->value + code_buf->lxm_pos[n_lxm] + 1);
                }
               /* if (*(code_buf->value + code_buf->lxm_pos[n_lxm + 1]) == '+')
                {
                    n_lxm++;
                    obj_code[n_lxm] += atof(code_buf->value + code_buf->lxm_pos[n_lxm + 1]);
                    n_lxm++;
                } */
            }
            else
            {
                obj_code[n_lxm++] = PUSHCONST;
                obj_code[n_lxm] = atof(code_buf->value + code_buf->lxm_pos[n_lxm]);

               /* if (*(code_buf->value + code_buf->lxm_pos[n_lxm + 1]) == '+')
                {
                    n_lxm++;
                    obj_code[n_lxm] += atof(code_buf->value + code_buf->lxm_pos[n_lxm + 1]);
                    n_lxm++;
                }*/
            }
        }
        else if (strcmp(temp_ptr, "pop") == 0)
        {
            if (isalpha(*(code_buf->value + code_buf->lxm_pos[n_lxm + 1])))
            {    
                obj_code[n_lxm++] = POPREG;
                obj_code[n_lxm] = *(code_buf->value + code_buf->lxm_pos[n_lxm]) - 'a';

               /* if (*(code_buf->value + code_buf->lxm_pos[n_lxm + 1]) == '+')
                {
                    n_lxm++;
                    obj_code[n_lxm] += atof(code_buf->value + code_buf->lxm_pos[n_lxm + 2]);
                    n_lxm++;
                }*/
            }
            else if (*(code_buf->value + code_buf->lxm_pos[n_lxm + 1]) == '[')
            {
                if (isalpha(*(code_buf->value + code_buf->lxm_pos[n_lxm + 1] + 1)))
                {
                    obj_code[n_lxm++] = POPRAMREG;
                    obj_code[n_lxm] = *(code_buf->value + code_buf->lxm_pos[n_lxm] + 1) - 'a';
                }
                else
                {
                    obj_code[n_lxm++] = POPRAMCONST;
                    obj_code[n_lxm] = atof(code_buf->value + code_buf->lxm_pos[n_lxm] + 1);
                }
               /* if (*(code_buf->value + code_buf->lxm_pos[n_lxm + 1]) == '+')
                {
                    n_lxm++;
                    obj_code[n_lxm] += atof(code_buf->value + code_buf->lxm_pos[n_lxm + 2]);
                    n_lxm++;
                }*/
            }
        }
        else if (strcmp(temp_ptr, "div") == 0)
            obj_code[n_lxm] = DIV;

        else if (strcmp(temp_ptr, "mul") == 0)
            obj_code[n_lxm] = MUL;

        else if (strcmp(temp_ptr, "add") == 0)
            obj_code[n_lxm] = ADD;

        else if (strcmp(temp_ptr, "sub") == 0)
            obj_code[n_lxm] = SUB;

        else if (strcmp(temp_ptr, "hlt") == 0)
            obj_code[n_lxm] = HLT;

        else if (strcmp(temp_ptr, "in") == 0)
            obj_code[n_lxm] = IN;

        else if (strcmp(temp_ptr, "out") == 0)
            obj_code[n_lxm] = OUT;

        else
            (ERR.value)[(ERR.amt)++] = LXM_ERROR;
    }
    return ERR;
}
