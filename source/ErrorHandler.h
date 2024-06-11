// ErrorHandler.h

#define _ERROR_HANDLER_H

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _STDARG_H
    #include <stdarg.h>
#endif

typedef struct
{
    char *error;
    unsigned int line;
} Error;

Error* MakeError(char *message, unsigned int line, ...);