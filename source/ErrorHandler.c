// ErrorHandler.c

#include "ErrorHandler.h"

void InitErrorHandler(ErrorHandler *errorHandler)
{
    InitStack(&errorHandler->errors);
    errorHandler->currentLine = ZERO;
}

BOOL ErrorsFound(ErrorHandler *errorHandler)
{
    return (!IsEmptyStack(&errorHandler->errors));
}

Error* NextError(ErrorHandler *errorHandler)
{
    return (PopStack(&errorHandler->errors));
}

void MakeError(ErrorHandler *errorHandler, char *message, ...)
{
    Error *error = malloc(sizeof(Error));
    va_list args;

    error->line = errorHandler->currentLine;

    va_start(args, message);
    vasprintf(&error->error, message, args);
    va_end(args);

    PushStack(&errorHandler->errors, error);
}