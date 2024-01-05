#define IDENTIFIER 0x0
#define KEYWORD 0x1
#define SEPERATOR 0x2
#define OPERATOR 0x3
#define LITERAL 0x4

typedef unsigned short token_type;

typedef struct
{
    token_type tokenType;
    char *tokenInfo;
} Token;