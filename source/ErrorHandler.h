// ErrorHandler.h

#define _ERROR_HANDLER_H

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _STDARG_H
    #include <stdarg.h>
#endif

#ifndef _STACK_H
    #include "../libs/Stack.h"
#endif

typedef struct
{
    char *error;
    unsigned int line;
} Error;

typedef struct
{
    Stack errors;
    unsigned int currentLine;
} ErrorHandler;

void InitErrorHandler(ErrorHandler *errorHandler);
BOOL ErrorsFound(ErrorHandler *errorHandler);
Error* NextError(ErrorHandler *errorHandler);
void MakeError(ErrorHandler *errorHandler, char *message, ...);