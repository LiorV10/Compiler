// viewer.h

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _STDARG_H
    #include <stdarg.h>
#endif

#ifndef _COMMON_MACROS_H
    #include "../libs/CommonMacros.h"
#endif

#define MAX_LINE_LENGTH 128

typedef struct
{
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
} Stream;

void InitStream(Stream *stream, char *path, char *mode);
char* NextLine(Stream *stream);
void WriteStream(Stream *stream, char *buffer, va_list args);
void ResetStream(Stream *stream);
void CloseStream(Stream *stream);
void ExitWithError(char *error);
BOOL EndOfStream(Stream *stream);