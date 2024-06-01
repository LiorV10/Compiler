// viewer.c

#include "Viewer.h"

void InitStream(Stream *stream, char *path, char *mode)
{
    stream->fp = fopen(path, mode);
    !stream->fp ? ExitWithError("Could not find the source file.") : ZERO;
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
    fclose(stream->fp) ? ExitWithError("Could not close the file correctly.") : ZERO;
}

void ExitWithError(char *error)
{
    fputs(error, stderr);
    fputc('\n', stderr);
    
    exit(ONE);
}