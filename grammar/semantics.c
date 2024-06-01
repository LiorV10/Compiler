#include "semantics.h"
AbstractSyntaxTreeNode *DefaultSemanticAction(void *scopeStack, Stack *semanticStack){ return PopStack(semanticStack); }
AbstractSyntaxTreeNode* Semantic_1(void *scopeStack, Stack *semanticStack)
{
// translation_unit
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_2(void *scopeStack, Stack *semanticStack)
{
// translation_unit
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$1;   
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_6(void *scopeStack, Stack *semanticStack)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$5 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = _$1->info; ((Symbol*)_$1->info)->type = ((Token*)_$0->info)->type; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$3; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$5;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_7(void *scopeStack, Stack *semanticStack)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = _$1->info; ((Symbol*)_$1->info)->type = ((Token*)_$0->info)->type; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_11(void *scopeStack, Stack *semanticStack)
{
// jump_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateReturn; _$_$->info = (void*)(1); *SetAbstractSyntaxTreeNodeChild(_$_$) = _$1;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_12(void *scopeStack, Stack *semanticStack)
{
// iteration_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_15(void *scopeStack, Stack *semanticStack)
{
// selection_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$6 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$5 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; _$_$->GenerationFunction = GenerateIf; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$6; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_16(void *scopeStack, Stack *semanticStack)
{
// selection_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; _$_$->GenerationFunction = GenerateIf; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_18(void *scopeStack, Stack *semanticStack)
{
// expression_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_19(void *scopeStack, Stack *semanticStack)
{
// statement_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateStatements; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_20(void *scopeStack, Stack *semanticStack)
{
// statement_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$1;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_21(void *scopeStack, Stack *semanticStack)
{
// declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; _$_$->GenerationFunction = GenerateStatements; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_22(void *scopeStack, Stack *semanticStack)
{
// declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$1;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_24(void *scopeStack, Stack *semanticStack)
{
// compound_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
ExitScope(scopeStack); _$_$ = _$1; _$_$->GenerationFunction = GenerateStatements;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_25(void *scopeStack, Stack *semanticStack)
{
// block_enter
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
EnterScope(scopeStack); _$_$ = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_53(void *scopeStack, Stack *semanticStack)
{
// parameter_declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = _$1->info; ((Symbol*)_$1->info)->type = ((Token*)_$0->info)->type; InsertSymbol(scopeStack, _$1->info);  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_61(void *scopeStack, Stack *semanticStack)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
Symbol* symbol; MakeSymbol(&symbol); symbol->name = ((Token*)_$0->info)->lexeme; _$0->info = symbol; _$_$ = _$0; InsertSymbol(scopeStack, symbol);  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_66(void *scopeStack, Stack *semanticStack)
{
// declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; ((Symbol*)_$1->info)->type = POINTER_TYPE;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_67(void *scopeStack, Stack *semanticStack)
{
// declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->lvalue = TRUE;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_81(void *scopeStack, Stack *semanticStack)
{
// struct_or_union_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; if (*((Token*)_$1->info)->lexeme == 'a') puts("struct!"); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_82(void *scopeStack, Stack *semanticStack)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->type = VOID_TYPE;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_86(void *scopeStack, Stack *semanticStack)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->type = FLOAT_TYPE;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_93(void *scopeStack, Stack *semanticStack)
{
// init_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateAssignment; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_94(void *scopeStack, Stack *semanticStack)
{
// init_declarator_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_95(void *scopeStack, Stack *semanticStack)
{
// init_declarator_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_97(void *scopeStack, Stack *semanticStack)
{
// declaration_specifiers
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; puts("typedef!");
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_98(void *scopeStack, Stack *semanticStack)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_99(void *scopeStack, Stack *semanticStack)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$1->GenerationFunction = GenerateDeclaration; _$1->type = _$0->type; _$1->info = _$0->info;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_103(void *scopeStack, Stack *semanticStack)
{
// assignment_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateAssignment;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_107(void *scopeStack, Stack *semanticStack)
{
// assignment_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateAdditionAssignment;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_110(void *scopeStack, Stack *semanticStack)
{
// assignment_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_122(void *scopeStack, Stack *semanticStack)
{
// additive_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateAddition; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_125(void *scopeStack, Stack *semanticStack)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateMult; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_126(void *scopeStack, Stack *semanticStack)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateDivision; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_137(void *scopeStack, Stack *semanticStack)
{
// unary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_142(void *scopeStack, Stack *semanticStack)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateCall;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_143(void *scopeStack, Stack *semanticStack)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateCall; *SetAbstractSyntaxTreeNodeChild(_$0) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_146(void *scopeStack, Stack *semanticStack)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$1->info = _$0->info; _$1->GenerationFunction = GenerateIncrement; *SetAbstractSyntaxTreeNodeChild(_$1) = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_148(void *scopeStack, Stack *semanticStack)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateSymbol; Token *id = _$_$->info; _$_$->info = LookupSymbol(scopeStack, id->lexeme); _$_$->lvalue = TRUE;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_149(void *scopeStack, Stack *semanticStack)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); symbol->name = ((Token*)_$0->info)->lexeme; symbol->type = INTEGER_TYPE; _$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateIntegerLiteral;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_150(void *scopeStack, Stack *semanticStack)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); symbol->name = ((Token*)_$0->info)->lexeme; symbol->type = FLOAT_TYPE; _$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateFloatLiteral;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_152(void *scopeStack, Stack *semanticStack)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1;
return _$_$;
}
void AssignActions(Grammar *g)
{
unsigned short currentRule = ZERO;
LinearLinkedListNode *nonTerminalsPtr, *rulesPtr;
Rule *rules[153];
for (nonTerminalsPtr = g->nonTerminals; nonTerminalsPtr; nonTerminalsPtr = nonTerminalsPtr->nextNode)
{
for (rulesPtr = ((NonTerminal*)nonTerminalsPtr->info)->rules; rulesPtr; rulesPtr = rulesPtr->nextNode)
{
rules[currentRule++] = rulesPtr->info;
}
}
rules[1]->semanticAction = Semantic_25;
rules[4]->semanticAction = Semantic_7;
rules[5]->semanticAction = Semantic_6;
rules[9]->semanticAction = Semantic_11;
rules[13]->semanticAction = Semantic_12;
rules[14]->semanticAction = Semantic_16;
rules[15]->semanticAction = Semantic_15;
rules[16]->semanticAction = Semantic_18;
rules[18]->semanticAction = Semantic_20;
rules[19]->semanticAction = Semantic_19;
rules[20]->semanticAction = Semantic_22;
rules[21]->semanticAction = Semantic_21;
rules[22]->semanticAction = Semantic_24;
rules[53]->semanticAction = Semantic_53;
rules[63]->semanticAction = Semantic_61;
rules[64]->semanticAction = Semantic_67;
rules[65]->semanticAction = Semantic_66;
rules[77]->semanticAction = Semantic_81;
rules[84]->semanticAction = Semantic_86;
rules[88]->semanticAction = Semantic_82;
rules[89]->semanticAction = Semantic_93;
rules[91]->semanticAction = Semantic_95;
rules[92]->semanticAction = Semantic_94;
rules[93]->semanticAction = Semantic_97;
rules[95]->semanticAction = Semantic_99;
rules[96]->semanticAction = Semantic_98;
rules[101]->semanticAction = Semantic_107;
rules[105]->semanticAction = Semantic_103;
rules[106]->semanticAction = Semantic_110;
rules[120]->semanticAction = Semantic_122;
rules[123]->semanticAction = Semantic_126;
rules[124]->semanticAction = Semantic_125;
rules[132]->semanticAction = Semantic_137;
rules[139]->semanticAction = Semantic_146;
rules[142]->semanticAction = Semantic_143;
rules[143]->semanticAction = Semantic_142;
rules[146]->semanticAction = Semantic_152;
rules[148]->semanticAction = Semantic_150;
rules[149]->semanticAction = Semantic_149;
rules[150]->semanticAction = Semantic_148;
rules[151]->semanticAction = Semantic_2;
rules[152]->semanticAction = Semantic_1;
}
