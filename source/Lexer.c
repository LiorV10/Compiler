// Lexer.c

#include "Lexer.h"

//-----------------------------------------------------------------------------
//                                      Init Lexer                                     
//                                      ----------                                  
//                                                                             
// General      : The function initializer the lexer context.                                                           
//                                                                             
// Parameters   :                                                              
//      lexer - The lexer context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
// n - total length of all regex patterns
//-----------------------------------------------------------------------------
void InitLexer(Lexer *lexer)
{
    TokenType tokenType;
    unsigned short patternsSize;
    
    char *patterns[] = PATTERNS;

    patternsSize = TOKENS_NUM - ONE;
    lexer->nfa = RegexToNFA(*patterns, ONE);

    for (tokenType = ONE; tokenType < patternsSize; tokenType++)
    {
        lexer->nfa = Union(lexer->nfa, RegexToNFA(patterns[tokenType], tokenType + ONE));
    }
}

//-----------------------------------------------------------------------------
//                                      Create Token                                     
//                                      ------------                                  
//                                                                             
// General      : The function creates a token from a match.                                                           
//                                                                             
// Parameters   :                                                              
//      info - The match (In)						                                        
//      type - The token type (In)						                                        
//                                                                             
// Return Value : The token.             
//-----------------------------------------------------------------------------
// T(n) = d -> O(1) 
//-----------------------------------------------------------------------------
Token* CreateToken(struct Match *info, TokenType type)
{
    Token *token = malloc(sizeof(Token));
    
    *token = (Token){.lexeme = info->start, .type = type};

    return (token);
}

//-----------------------------------------------------------------------------
//                                      Next Token                                     
//                                      ----------                                 
//                                                                             
// General      : The function extracts the next token from the input.                                                           
//                                                                             
// Parameters   :                                                              
//      source - The input string (I/O)						                                        
//      nfa - The regex NFA (In)						                                        
//      errors - The error handler context (In)						                                        
//                                                                             
// Return Value : The token, if legal.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n) 
//-----------------------------------------------------------------------------
Token* NextToken(char **source, StateMachine *nfa, ErrorHandler *erros)
{
    struct Match *currentMatch;
    TokenType type;
    Token *token = NULL;

    currentMatch = ExecuteRegex(nfa, *source);

    if (currentMatch)
    {
        type = currentMatch->matchType;

        *source += (currentMatch->end - currentMatch->start);

        type != WHITESPACE ? 
            token = CreateToken(currentMatch, type): 
            free(currentMatch->start);

        free(currentMatch);
    }
    else
    {
        MakeError(erros, "Unknown token `%c`", **source);
        (*source)++;
    }

    return (token);
}

//-----------------------------------------------------------------------------
//                                      Tokenize                                     
//                                      --------                                  
//                                                                             
// General      : The function tokenizes an input.                                                           
//                                                                             
// Parameters   :                                                              
//      lexer - The lexer context (In)						                                        
//      source - The input string (In)						                                        
//      errors - The error handler context (In)						                                        
//                                                                             
// Return Value : The list of extracted tokens.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
CircularLinearLinkedListNode* Tokenize(Lexer *lexer, char *source, ErrorHandler *errors)
{
    CircularLinearLinkedListNode *tokens;
    
    InitCircularLinearLinkedList(&tokens);

    while (*source)
    {
        tokens ? 
            InsertEndCircularLinearLinkedList(&tokens) : 
            InsertLastCircularLinearLinkedList(&tokens);

        while(*source && !(tokens->info = NextToken(&source, lexer->nfa, errors)));
    }

    if (!tokens->info)
    {
        tokens == tokens->nextNode ? 
            DeleteLastCircularLinearLinkedList(&tokens) : 
            DeleteEndCircularLinearLinkedList(&tokens);
    }

    return (tokens);
}

//-----------------------------------------------------------------------------
//                                      Free Lexer                                     
//                                      ----------                                 
//                                                                             
// General      : The function frees the lexer context.                                                           
//                                                                             
// Parameters   :                                                              
//      lexer - The lexer context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
void FreeLexer(Lexer *lexer)
{
    EmptyStateMachine(lexer->nfa);
}