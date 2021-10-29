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
        }
        buf_pos++;
    }

    return ERR;
}

int Code_Divide(char* str)
{
    Ptr_Ver(str, ERR);

    int symb_index = 0;

    if (str[symb_index] == '[' || str[symb_index] == ':')
        symb_index++;

    while (isalnum(str[symb_index]))
        symb_index++;

    if (str[symb_index] == ']' || str[symb_index] == ':')
        symb_index++;

    str[symb_index] = '\0';

    return symb_index;
}

error_t Compile(text_t* code_buf, double* obj_code)
{
    Ptr_Ver(code_buf, ERR);
    Ptr_Ver(obj_code, ERR);

    label_t* label = (label_t*)calloc(LABELS_AMOUNT, sizeof(label_t));

    int lxm_amt = code_buf->lxm_amt;

    int new_code_len = 0;
    
    // printf("\n%d\n", lxm_amt);
        
    for (int i = 0; i <= 1; i++)
    {
        for (int n_lxm = 0, n_code = 0; n_lxm < lxm_amt; n_lxm++, n_code++) 
        {
            char* temp_ptr = code_buf->value + code_buf->lxm_pos[n_lxm];
            int n_label = 0;
            
            if (strcmp(temp_ptr, "in") == 0)
                obj_code[n_code] = IN;
            
            else if (strcmp(temp_ptr, "push") == 0)
            {
                if (isalpha(*(code_buf->value + code_buf->lxm_pos[n_lxm + 1])))
                {
                    obj_code[n_code++] = PUSHREG;
                    n_lxm++;
                    obj_code[n_code] = *(code_buf->value + code_buf->lxm_pos[n_lxm]) - 'a';

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
                        obj_code[n_code++] = POPRAMREG;
                        n_lxm++;
                        obj_code[n_code] = *(code_buf->value + code_buf->lxm_pos[n_lxm] + 1) - 'a';
                    }
                    else   
                    {
                        obj_code[n_code++] = PUSHRAMREG;
                        n_lxm++;
                        obj_code[n_code] = atof(code_buf->value + code_buf->lxm_pos[n_lxm] + 1);
                    }
                }
                else
                {
                    obj_code[n_code++] = PUSHCONST;
                    n_lxm++;
                    obj_code[n_code] = atof(code_buf->value + code_buf->lxm_pos[n_lxm]);
                }
            }
            else if (strcmp(temp_ptr, "pop") == 0)
            {
                if (isalpha(*(code_buf->value + code_buf->lxm_pos[n_lxm + 1])))
                {    
                    obj_code[n_code++] = POPREG;
                    n_lxm++;
                    obj_code[n_code] = *(code_buf->value + code_buf->lxm_pos[n_lxm]) - 'a';
                }
                else if (*(code_buf->value + code_buf->lxm_pos[n_lxm + 1]) == '[')
                {
                    if (isalpha(*(code_buf->value + code_buf->lxm_pos[n_lxm + 1] + 1)))
                    {
                        obj_code[n_code++] = POPRAMREG;
                        n_lxm++;
                        obj_code[n_code] = *(code_buf->value + code_buf->lxm_pos[n_lxm] + 1) - 'a';
                    }
                    else
                    {
                        obj_code[n_code++] = POPRAMCONST;
                        n_lxm++;
                        obj_code[n_code] = atof(code_buf->value + code_buf->lxm_pos[n_lxm] + 1);
                    }
                }
            }
            else if (strcmp(temp_ptr, "div") == 0)
                obj_code[n_code] = DIV;

            else if (strcmp(temp_ptr, "mul") == 0)
                obj_code[n_code] = MUL;

            else if (strcmp(temp_ptr, "add") == 0)
                obj_code[n_code] = ADD;

            else if (strcmp(temp_ptr, "sub") == 0)
                obj_code[n_code] = SUB;

            else if (strcmp(temp_ptr, "hlt") == 0)
                obj_code[n_code] = HLT;

            else if (strcmp(temp_ptr, "out") == 0)
                obj_code[n_code] = OUT;


            else if (strchr(temp_ptr, ':'))
            {
                if (temp_ptr[0] == ':')
                {
                    label[n_label].ip = n_code;
                    strcpy(label[n_label++].name, temp_ptr + 1);
                }
                else 
                {
                    label[n_label].ip = n_code;
                    int label_len = strcspn(temp_ptr, ":");
                    strncpy(label[n_label++].name, temp_ptr, label_len);
                }
                printf("%d\n", label[n_label - 1].ip);
                n_code--;
            }

            else if (temp_ptr[0] == 'j')
            {
                if (strcmp(temp_ptr + 1, "mp") == 0)
                    obj_code[n_code++] = JMP;

                else if (strcmp(temp_ptr + 1, "a") == 0)
                    obj_code[n_code++] = JA;

                else if (strcmp(temp_ptr + 1, "ae") == 0)
                    obj_code[n_code++] = JAE;

                else if (strcmp(temp_ptr + 1, "b") == 0)
                    obj_code[n_code++] = JB;

                else if (strcmp(temp_ptr + 1, "be") == 0)
                    obj_code[n_code++] = JBE;

                else if (strcmp(temp_ptr + 1, "ne") == 0)
                    obj_code[n_code++] = JBE;

                else if (strcmp(temp_ptr + 1, "e") == 0)
                    obj_code[n_code++] = JE;

                else
                    (ERR.value)[(ERR.amt)++] = LXM_ERROR;

                n_lxm++;
                obj_code[n_code] = Search_Label(code_buf->value + code_buf->lxm_pos[n_lxm], label);
            }
            
            else
                (ERR.value)[(ERR.amt)++] = LXM_ERROR;

            new_code_len = code_buf->lxm_amt - (code_buf->lxm_amt - n_code) / 2;
        }
    }
    code_buf->lxm_amt = new_code_len;

    return ERR;
}

int Search_Label(char* str, label_t* label)
{
    Ptr_Ver(str, ERR);
    Ptr_Ver(label, ERR);

    int n_label = 0;
    while(label[n_label].name[0] != 0)
    {
        if(strcmp(str + 1, label[n_label].name) == 0)
            return label[n_label].ip;

        n_label++;
    }

    return LABEL_ERROR;
}