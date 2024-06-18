// main.c

#include "Viewer.h"
#include "Construction.c"
#include "Lexer.c"
#include "Parser.c"
#include "SemanticAnalyzer.c"
#include "CodeGenerator.c"

#define NUM_OF_ARGS 3
#define SOURCE_FILE_OFFSET 1
#define DEST_FILE_OFFSET 2

struct Context
{
    char *sourcePath;
    char *destPath;

    Grammar grammar;
    CircularLinearLinkedListNode *tokens;
    AbstractSyntaxTreeNode *ast;

    Parser parser;
    CodeGenerator generator;

    ErrorHandler errorHandler;
};

//-----------------------------------------------------------------------------
//                                  Tokenize Stream                                     
//                                  ---------------                                  
//                                                                             
// General      : The function tokenizes a given stream.                                                           
//                                                                             
// Parameters   :                                                              
//      sourceStream - The stream to tokenize (In)						                                        
//      errors - The error handler context (In)						                                        
//                                                                             
// Return Value : The list of tokens.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
CircularLinearLinkedListNode* TokenizeStream(Stream *sourceStream, ErrorHandler *errors)
{
    Lexer lexer;
    CircularLinearLinkedListNode *tokens;
    CircularLinearLinkedListNode *current;
    errors->currentLine = ONE;

    InitLexer(&lexer);

    tokens = Tokenize(&lexer, NextLine(sourceStream), errors);
    
    while (!EndOfStream(sourceStream))
    {
        errors->currentLine++;

        InsertEndCircularLinearLinkedList(&tokens);
        tokens->info = malloc(sizeof(Token));
        ((Token*)tokens->info)->type = WHITESPACE;
        ((Token*)tokens->info)->lexeme = NULL;

        current = Tokenize(&lexer, NextLine(sourceStream), errors);
        current ? ConcatCircularLinearLinkedLists(&tokens, current) : ZERO;
    }

    InsertEndCircularLinearLinkedList(&tokens);
    tokens->info = malloc(sizeof(Token));
    ((Token*)tokens->info)->type = EOD;
    ((Token*)tokens->info)->lexeme = NULL;

    FreeLexer(&lexer);
    ResetStream(sourceStream);

    return (tokens);
}

//-----------------------------------------------------------------------------
//                                  Lexing Phase                                     
//                                  ------------                                  
//                                                                             
// General      : The function performs the lexical analysis phase.                                                           
//                                                                             
// Parameters   :                                                              
//       context - The compiler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
void LexingPhase(struct Context *context)
{
    Stream stream;

    InitStream(&stream, context->sourcePath, "rt");

    context->tokens = TokenizeStream(&stream, &context->errorHandler);

    CloseStream(&stream);
}

//-----------------------------------------------------------------------------
//                                  Parsing Phase                                     
//                                  -------------                                  
//                                                                             
// General      : The function performs the syntax analysis phase.                                                           
//                                                                             
// Parameters   :                                                              
//       context - The compiler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
void ParsingPhase(struct Context *context)
{
    InitParser(&context->parser, &context->grammar);

    context->ast = Parse(&context->parser, context->tokens, &context->errorHandler);

    FreeGrammar(&context->grammar);
    FreeParser(&context->parser);
}

//-----------------------------------------------------------------------------
//                                  Semantic Phase                                     
//                                  --------------                                  
//                                                                             
// General      : The function performs the semantic analysis phase.                                                           
//                                                                             
// Parameters   :                                                              
//       context - The compiler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
void SemanticPhase(struct Context *context)
{
    !ErrorsFound(&context->errorHandler) ?
        AnalyzeSemantics(&context->ast, &context->errorHandler) : ZERO;
}

//-----------------------------------------------------------------------------
//                              Code Generation Phase                                     
//                              ---------------------                                
//                                                                             
// General      : The function performs the code generation phase.                                                           
//                                                                             
// Parameters   :                                                              
//       context - The compiler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
void CodeGenerationPhase(struct Context *context)
{
    Stream stream;

    if (!ErrorsFound(&context->errorHandler))
    {
        InitStream(&stream, context->destPath, "wt");
        InitCodeGenerator(&context->generator, WriteStream, &stream);
        GenerateCode(&context->generator, context->ast);
        CloseStream(&stream);
        FreeCodeGenerator(&context->generator);
    }

    EmptyCircularLinearLinkedList(&context->tokens, FreeToken);
    FreeAbstractSyntaxTree(context->ast);
}

//-----------------------------------------------------------------------------
//                                      Report Errors                                     
//                                      -------------                                  
//                                                                             
// General      : The function reports the discovered errors.                                                           
//                                                                             
// Parameters   :                                                              
//       context - The compiler context (In)						                                        
//                                                                             
// Return Value : None.             
//-----------------------------------------------------------------------------
// T(n) = c * n + d -> O(n)
//-----------------------------------------------------------------------------
void ReportErrors(struct Context *context)
{
    Error *error;

    while (ErrorsFound(&context->errorHandler))
    {
        error = NextError(&context->errorHandler);

        printf("Error in line %d: ", error->line);
        puts(error->error);

        free(error->error);
        free(error);
    }
}

//-----------------------------------------------------------------------------
//                              C to Assembly Compiler									
//                              ----------------------								
//																				
// General : This program compiles a C program into GAS code.					
//																				
// Input   : Source C code file.								
//																				
// Process : Compilation phases.							
//																				
// Output  : Assembly code file.		
//																				
//-----------------------------------------------------------------------------
// Programmer : Lior Vidas														
// Student Id : 327654471																												
//-----------------------------------------------------------------------------
void main(unsigned short argumentsCount, char* arguments[])
{
    struct Context context;

    argumentsCount < NUM_OF_ARGS ? ExitWithError("Source or dest files were not specified.") : ZERO;

    context.sourcePath = arguments[SOURCE_FILE_OFFSET];
    context.destPath = arguments[DEST_FILE_OFFSET];

    InitErrorHandler(&context.errorHandler);

    InitGrammar(&context.grammar);
    BuildGrammarFromFile(&context.grammar);
    AssignActions(&context.grammar);

    LexingPhase(&context);
    ParsingPhase(&context);
    SemanticPhase(&context);
    CodeGenerationPhase(&context);

    system("gcc out.s -o out.o && ./out.o ; echo $?");

    ReportErrors(&context);
}