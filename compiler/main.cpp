#include "compiler_func.h"
#include "text_func.h"

int main(int argc, char* argv[])
{
    text_t code_buf = {};
    error_t err = {};

    if (argc >= 2)
    {
        strcpy(code_buf.file_name, argv[1]);
        err = Text_Ctor(&code_buf);
    }
    else
    {
        scanf("%s", code_buf.file_name);
        err = Text_Ctor(&code_buf);
    }

    err = Code_Parsing(&code_buf);

    double* obj_code = (double*)calloc(code_buf.lxm_amt, sizeof(double));

    err = Compile(&code_buf, obj_code);

    if (!Log_Error(&err))
        if (argc >= 3)
            Obj_Code_Write(obj_code, code_buf.lxm_amt, argv[2]);
        else
        {
            char obj_filename[ARRAY_SIZE] = {0};
            scanf("%s", obj_filename);
            Obj_Code_Write(obj_code, code_buf.lxm_amt, obj_filename);
        }
    else
        printf("Compile error. Please, read ErrorLog file for more information\n");

    Text_Dtor(&code_buf);

    free(obj_code);
    obj_code = nullptr;
}
