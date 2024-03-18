// viewer.c

#include "viewer.h"

void InitStream(Stream *stream, char *path)
{
    FILE *fp = fopen(path, "rt");

    !fp ? ExitWithError("Could not find the source file.") : ZERO;
    stream->fp = fp;
}

char* NextLine(Stream *stream)
{
    return (fgets(stream->buffer, MAX_LINE_LENGTH, stream->fp));
}

void ResetStream(Stream *stream)
{
    fseek(stream->fp, ZERO, SEEK_SET);
}

BOOL EndOfStream(Stream *stream)
{
    return (feof(stream->fp));
}

void CloseStream(Stream *stream)
{
    fclose(stream->fp) ? exit(ONE) : ZERO;
}

void ExitWithError(char *error)
{
    fputs(error, stderr);
    fputc('\n', stderr);
    
    exit(ONE);
}