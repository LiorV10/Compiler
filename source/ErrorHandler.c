// ErrorHandler.c

#include "ErrorHandler.h"

Error* MakeError(char *message, unsigned int line, ...)
{
    Error *error = malloc(sizeof(Error));
    va_list args;

    va_start(args, line);

    error->line = line;
    vasprintf(&error->error, message, args);

    va_end(args);

    return (error);
}