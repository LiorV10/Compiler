enum {STRING_LITERAL, IDENTIFIER, MAIN, VOID, INT, LONG, FLOAT, DOUBLE, SHORT, CHAR, UNSIGNED, STRUCT, TYPEDEF, FOR, IF, ELSE, WHILE, RETURN, PLUS, PLUS_PLUS, MINUS, MINUS_MINUS, PLUS_EQ, MINUS_EQ, STAR_EQ, SLASH_EQ, MOD_EQ, LOG_NOT, GT, RSHIFT, LT, LSHIFT, EQ, GE, LE, EEQ, NEQ, STAR, SLASH, MOD, DOT, ARROW, COMMA, SEMI_COLON, LEFT_BRACKET, RIGHT_BRACKET, LEFT_CURLY, RIGHT_CURLY, LEFT_PAREN, RIGHT_PAREN, AMPERSAND, OR, XOR, LOG_AND, LOG_OR, FLOAT_LITERAL, INTEGER_LITERAL, WHITESPACE, EOD, TOKENS_NUM };
#define PATTERNS {"\"\001\005\002\"\002", "_\003\010_\003\010\004\010\005\002", "ma\002_\002i\002n\002", "vo\002i\002d\002", "in\002t\002", "lo\002n\002g\002", "fl\002o\002a\002t\002", "do\002u\002b\002l\002e\002", "sh\002o\002r\002t\002", "ch\002a\002r\002", "un\002s\002i\002g\002n\002e\002d\002", "st\002r\002u\002c\002t\002", "ty\002p\002e\002d\002e\002f\002", "fo\002r\002", "if\002", "el\002s\002e\002", "wh\002i\002l\002e\002", "re\002t\002u\002r\002n\002", "+", "++\002", "-", "--\002", "+=\002", "-=\002", "*=\002", "/=\002", "%=\002", "!", ">", ">>\002", "<", "<<\002", "=", ">=\002", "<=\002", "==\002", "!=\002", "*", "/", "%", ".", "->\002", ",", ";", "[", "]", "{", "}", "(", ")", "&", "|", "^", "&&\002", "||\002", "\004\006.\002\004\006\002", "\004\006", " \n\r\t\010\010\010\006//\002\001\005\002\n\002\010", ""}
#define _SEMANTICS
#ifndef _COMMON_MACROS_H
            #include "../libs/CommonMacros.h"
            #endif
    
            #ifndef _ABSTRACT_SYNTAX_TREE_H
                #include "../libs/AbstractSyntaxTree.h"
            #endif
    
            #ifndef _STACK_H
                #include "../libs/Stack.h"
            #endif
    
            #ifndef _GRAMMAR_H
                #include "../libs/Grammar.h"
            #endif
    
            #ifndef _TYPE_SYSTEM_H
                #include "../libs/TypeSystem.h"
            #endif
    
            #ifndef _ERROR_HANDLER_H
                #include "../source/ErrorHandler.h"
            #endif
    
            #ifndef _ACTIONS
                #include "actions.h"
            #endif
