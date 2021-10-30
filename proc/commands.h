#ifndef COMMANDS_H
#define COMMANDS_H

const char version[]   = "2";
const char extention[] = "aboba";

enum cmd
{
    HLT             = 0,
    PUSHREG         = 1,
    PUSHCONST       = 2,
    PUSHRAMREG      = 3,
    PUSHRAMCONST    = 4,
    POPREG          = 5,
    POPRAMCONST     = 6,
    POPRAMREG       = 7,
    ADD             = 8,
    SUB             = 9,
    MUL             = 10,
    DIV             = 11,
    IN              = 12,
    OUT             = 13,
    JMP             = 14,
    JA              = 15,
    JAE             = 16,
    JB              = 17,
    JBE             = 18,
    JNE             = 19,
    JE              = 20
};

#endif // COMMANDS_H
