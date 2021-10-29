#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h>
#include <assert.h>

const size_t ARRAY_SIZE = 100;
const char LOG_LXM_ERROR[] = "syntax error\n"; 
const char LOG_PTR_ERROR[] = "pointer error\n";

struct error_t
{
    int amt               = 0;
    int value[ARRAY_SIZE] = {0};
};

enum prog_errors
{
    NO_ERROR       = 0,
    PTR_ERROR      = 1,
    NO_FILE_IN_DIR = 2,

    LXM_ERROR      = 10,
    LABEL_ERROR	   = -1
};

#endif // ERRORS_H
