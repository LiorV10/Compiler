// viewer.h

#ifndef _STDLIB_H
    #include <stdlib.h>
#endif

#ifndef _STDIO_H
    #include <stdio.h>
#endif

#ifndef _COMMON_MACROS_H
    #include "../libs/CommonMacros.h"
#endif

#define MAX_LINE_LENGTH 100

typedef struct
{
    FILE *fp;
    char buffer[MAX_LINE_LENGTH];
} Stream;

void InitStream(Stream *stream, char *path);
char* NextLine(Stream *stream);
void ResetStream(Stream *stream);
void CloseStream(Stream *stream);
void ExitWithError(char *error);
BOOL EndOfStream(Stream *stream);