#define SET_DEF_LEVEL 2
#define DEFAULT_CAPACITY 32

//-----------------------------------------------------------------------------

#include "processor.h"

//-----------------------------------------------------------------------------

int main(int argc, char* argv[])
{
    error_t err = NO_ERROR;

    code_t code = {};

    if (argc >= 2)
        Code_Ctor(&code, argv[1]);
    else
    {
        char file_name[100] = {};
        scanf("%s", file_name);
        Code_Ctor(&code, file_name);
    }

    err = Processor(&code);
    Error_Log(err);

    return 0;
}
