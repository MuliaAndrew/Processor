#include "text_func.h"

static error_t ERR = {};

error_t Text_Ctor(text_t* code_buf)
{
    Ptr_Ver(code_buf, ERR);

    FILE* code = fopen(code_buf->file_name, "rb");
    if (code == nullptr)
        ERR.value[ERR.amt ++] = NO_FILE_IN_DIR;

    code_buf->len = N_Symb(code);

    code_buf->value = (char*)calloc(code_buf->len + 1, sizeof(char));
    Ptr_Ver(code_buf->value, ERR);

    if (fread(code_buf->value, sizeof(char), code_buf->len, code) != (unsigned int)code_buf->len)
        ERR.value[ERR.amt++] = PTR_ERROR;

    fclose(code);
    return ERR;
}

int N_Symb(FILE* code)
{
    Ptr_Ver(code, ERR);

    fseek(code, 0, SEEK_END);

    int temp = ftell(code);

    fseek(code, 0, SEEK_SET);
    
    return temp;
}

error_t Text_Dtor(text_t* code_buf)
{
    Ptr_Ver(code_buf, ERR);

    free(code_buf->value);
    code_buf = nullptr;

    return ERR;
}

int Log_Error(error_t* err)
{
    Ptr_Ver(err, ERR);
    FILE* log = fopen("ErrorLog.txt", "ab");

    int n_compile_errors = 0;

    int amount = err->amt;
    for (int err_index = 0; err_index < amount; err_index++)
    {
        //printf("%d\n", err->value[err_index]);
        switch (err->value[err_index])
        {
            case NO_ERROR:
                break;

            case PTR_ERROR:
            {
                fprintf(log, "%s", LOG_PTR_ERROR);
                break;
            }
            case LXM_ERROR:
            {
                fprintf(log, "%s", LOG_LXM_ERROR);
                n_compile_errors++;
                break;
            }
        }
    }

    fclose(log);
    err->amt = 0;

    return n_compile_errors;
}

void Obj_Code_Write(double* obj_code, int lxm_amt, char* filename)
{
    Ptr_Ver(obj_code, ERR);
    Ptr_Ver(filename, ERR);

    char dir_file[ARRAY_SIZE] = "ObjCode\\";
    strcpy(dir_file + strlen(dir_file), filename);

    FILE* obj = fopen(dir_file, "wb+");

    fprintf(obj, "%s %s\n", extention, version);

    for(size_t i = 0; i < lxm_amt; i++)
        fprintf(obj, "%lg ", obj_code[i]);

    fclose(obj);
    system(dir_file);
}
