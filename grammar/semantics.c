#include "semantics.h"
AbstractSyntaxTreeNode *DefaultSemanticAction(void *scopeStack, Stack *semanticStack, ErrorHandler *errors){ return PopStack(semanticStack); }
AbstractSyntaxTreeNode* Semantic_1(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// translation_unit
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_2(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// translation_unit
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$1;   
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_5(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$7 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$6 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$5 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 ExitScope(scopeStack); MakeAbstractSyntaxTree(&_$_$); Symbol* s; MakeSymbol(&s); s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s); BIT_SET(s->kind, FUNCTION_KIND_MASK); SetBaseType(&_$1->type, _$0->type); s->type = _$_$->type = _$1->type; _$_$->info = s; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$3; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$6; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_6(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 MakeAbstractSyntaxTree(&_$_$); _$_$->info = _$1->info; Symbol* s; MakeSymbol(&s); s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s); BIT_SET(s->kind, FUNCTION_KIND_MASK); _$_$->type = s->type = _$0->type; _$_$->info = s; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_7(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$5 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 ExitScope(scopeStack); MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = NULL; Symbol* s; MakeSymbol(&s); s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s); BIT_SET(s->kind, FUNCTION_KIND_MASK); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_8(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = NULL; Symbol* s; MakeSymbol(&s); BIT_SET(s->kind, FUNCTION_KIND_MASK); SetBaseType(&_$1->type, _$0->type); _$_$->type = s->type = _$1->type; s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s);
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_10(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// block_enter_paren
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 EnterScope(scopeStack); _$_$ = _$0; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_11(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// jump_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateReturn; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_12(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// jump_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateReturn; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$1;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_13(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// iteration_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4; _$_$->GenerationFunction = GenerateWhile; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_14(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// iteration_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$6 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$5 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; _$_$->GenerationFunction = GenerateFor; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$3; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$6; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_15(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// iteration_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$5 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; _$_$->GenerationFunction = GenerateFor; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$3; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$5; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_16(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
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
AbstractSyntaxTreeNode* Semantic_17(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
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
AbstractSyntaxTreeNode* Semantic_19(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// expression_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_20(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// statement_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateStatements; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_21(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// statement_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$1;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_22(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; _$_$->GenerationFunction = GenerateStatements; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_23(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$1;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_24(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// compound_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$);
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_25(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// compound_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
ExitScope(scopeStack); _$_$ = _$1; _$_$->GenerationFunction = GenerateBlock; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_26(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// block_enter
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
EnterScope(scopeStack); _$_$ = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_37(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_abstract_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Type *type = malloc(sizeof(Type)); type->size = atoi(((Symbol*)_$2->info)->name); type->type = ARRAY_TYPE; type->baseType = NULL; SetBaseType(&_$0->type, type); ((Symbol*)_$0->info)->type = _$0->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_38(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_abstract_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$0; Type *type = malloc(sizeof(Type)); type->size = POINTER_SIZE; type->type = POINTER_TYPE; type->baseType = NULL; SetBaseType(&_$0->type, type); ((Symbol*)_$0->info)->type = _$0->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_44(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// abstract_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->lvalue = TRUE;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_45(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// abstract_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; Type *arrayType = _$1->type; for (; arrayType && arrayType->baseType; arrayType = arrayType->baseType); if (arrayType) arrayType->baseType = _$0; _$1->type = ((Symbol*)_$1->info)->type = (arrayType ? arrayType : _$0); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_50(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// parameter_declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; InsertSymbol(scopeStack, _$1->info); BIT_SET(((Symbol*)_$1->info)->kind, VARIABLE_KIND_MASK); SetBaseType(&_$1->type, _$0->type); ((Symbol*)_$1->info)->type = _$1->type; if (!((Type*)_$1->type)->size) MakeError(errors, "Incomplete type `%s` is not allowed", ((Symbol*)_$0->info)->name); if(_$1->type && ((Type*)_$1->type)->type == ARRAY_TYPE) CalculateArraySize(_$1->type); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_51(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// parameter_declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; InsertSymbol(scopeStack, _$1->info); BIT_SET(((Symbol*)_$1->info)->kind, VARIABLE_KIND_MASK); Type *t; for (t = _$1->type; t && t->baseType; t = t->baseType); !t ? _$1->type = _$0->type : (t->baseType = _$0->type); ((Symbol*)_$1->info)->type = _$1->type; if(_$1->type && ((Type*)_$1->type)->type == ARRAY_TYPE) for(Type *base = ((Type*)_$1->type)->baseType; base && base->type != POINTER_TYPE; base = base->baseType) ((Type*)_$1->type)->size *= base->size; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_52(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// parameter_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$);  _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; _$0->GenerationFunction = GenerateDeclaration; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_53(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// parameter_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$2; _$2->GenerationFunction = GenerateDeclaration; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_55(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// pointer
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 MakeType(&_$_$, FALSE); ((Type*)_$_$)->type = POINTER_TYPE; ((Type*)_$_$)->size = POINTER_SIZE; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_56(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// pointer
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 MakeType(&_$_$, FALSE); ((Type*)_$_$)->type = POINTER_TYPE; ((Type*)_$_$)->size = POINTER_SIZE; ((Type*)_$_$)->baseType = _$1;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_57(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 Symbol* symbol; MakeSymbol(&symbol); symbol->name = ((Token*)_$0->info)->lexeme; _$0->info = symbol; _$_$ = _$0; _$0->type = NULL; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_58(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Type *type = malloc(sizeof(Type)); type->size = atoi(((Symbol*)_$2->info)->name); type->type = ARRAY_TYPE; type->baseType = NULL; SetBaseType(&_$0->type, type); ((Symbol*)_$0->info)->type = _$0->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_59(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$0; Type *ptr = malloc(sizeof(Type)); ptr->type = POINTER_TYPE; ptr->size = 8; ptr->baseType = _$0->type; _$0->type = ptr; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_60(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$1; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_62(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$0; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_63(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; Type *arrayType = _$1->type; for (; arrayType && arrayType->baseType; arrayType = arrayType->baseType); if (arrayType) arrayType->baseType = _$0; _$1->type = ((Symbol*)_$1->info)->type = (arrayType ? arrayType : _$0); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_64(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->lvalue = TRUE;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_66(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; SetBaseType(&_$1->type, _$0->type); ((Symbol*)_$1->info)->type = _$1->type; if (!((Type*)_$1->type)->size) MakeError(errors, "Incomplete type `%s` is not allowed", ((Symbol*)_$0->info)->name); if (LookupSymbolInCurrentScope(scopeStack, ((Symbol*)_$1->info)->name)) MakeError(errors, "Duplicate field `%s`", ((Symbol*)_$1->info)->name); InsertSymbol(scopeStack, _$1->info); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_67(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; SetBaseType(&_$1->type, _$0->type); ((Symbol*)_$1->info)->type = _$1->type; if (LookupSymbolInCurrentScope(scopeStack, ((Symbol*)_$1->info)->name)) MakeError(errors, "Duplicate field `%s`", ((Symbol*)_$1->info)->name); InsertSymbol(scopeStack, _$1->info); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_68(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
LinearLinkedListNode **fields = malloc(sizeof(LinearLinkedListNode*)); InitLinearLinkedList(fields); PushLinearLinkedList(fields); (*fields)->info = _$0; _$_$ = fields; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_69(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; PushLinearLinkedList(_$_$); (*((LinearLinkedListNode**)_$_$))->info = _$1;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_70(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_or_union_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 ExitScope(scopeStack); LinearLinkedListNode *ptr; unsigned short offset = ZERO; Symbol *symbol = LookupSymbol(scopeStack, ((Symbol*)_$1->info)->name); symbol = symbol && !((Type*)symbol->type)->size ? symbol : NULL; Type *type; _$_$ = _$1; if (symbol) { type = symbol->type; _$1->info = symbol; } else { MakeType(&type, TRUE); InsertSymbol(scopeStack, (symbol = _$1->info)); } symbol->type = _$1->type = type; type->size = ZERO; type->type = STRUCT_TYPE; type->structDef = symbol; BIT_SET(type->structDef->kind, STRUCT_KIND_MASK); for (ptr = *((LinearLinkedListNode**)_$3); ptr; ptr = ptr->nextNode) { AddField(type, ((Symbol*)((AbstractSyntaxTreeNode*)ptr->info)->info)->name, type->size, ((AbstractSyntaxTreeNode*)ptr->info)->type); type->size += ((Type*)((AbstractSyntaxTreeNode*)ptr->info)->type)->size; } 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_71(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_or_union_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 ExitScope(scopeStack); MakeAbstractSyntaxTree(&_$_$); LinearLinkedListNode *ptr; unsigned short offset = ZERO; Symbol *symbol; MakeSymbol(&symbol); Type *type; _$_$->info = symbol; MakeType(&type, TRUE); symbol->type = _$_$->type = type; type->size = ZERO; type->type = STRUCT_TYPE; type->structDef = symbol; BIT_SET(type->structDef->kind, STRUCT_KIND_MASK); for (ptr = *((LinearLinkedListNode**)_$2); ptr; ptr = ptr->nextNode) { AddField(type, ((Symbol*)((AbstractSyntaxTreeNode*)ptr->info)->info)->name, type->size, ((AbstractSyntaxTreeNode*)ptr->info)->type); type->size += ((Type*)((AbstractSyntaxTreeNode*)ptr->info)->type)->size; } 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_72(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_or_union_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$1; if (!_$1->info || !BIT_TEST(((Symbol*)_$1->info)->kind, STRUCT_KIND_MASK)) MakeError(errors, "`%s` is not a struct", ((Symbol*)_$1->info)->name); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_73(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->type = (Type*)LookupSymbol(scopeStack, "void")->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_74(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$  = _$0; _$0->type = (Type*)LookupSymbol(scopeStack, "char")->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_75(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$  = _$0; _$0->type = (Type*)LookupSymbol(scopeStack, "short")->type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_76(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$  = _$0; _$0->type = (Type*)LookupSymbol(scopeStack, "int")->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_77(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->type  = (Type*)LookupSymbol(scopeStack, "float")->type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_78(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$  = _$0; _$0->type = (Type*)LookupSymbol(scopeStack, "long")->type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_79(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->type  = (Type*)LookupSymbol(scopeStack, "double")->type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_82(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// init_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateDeclaration;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_83(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// init_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateDeclaration; _$_$->AnalysisFunction = AnalyzeDeclaration; _$0->lvalue = TRUE; _$_$->info = _$0->info; _$_$->type = _$0->type; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_85(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration_specifiers
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$0; if (!_$0->info || !BIT_TEST(((Symbol*)_$0->info)->kind, TYPE_KIND_MASK)) { MakeError(errors, "`%s` is not a type", ((Symbol*)_$0->info)->name); } 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_86(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$_$->GenerationFunction = NULL; InsertSymbol(scopeStack, _$1->info); BIT_SET(((Symbol*)_$1->info)->kind, STRUCT_KIND_MASK); Type *type; MakeType(&type, TRUE); _$1->type = ((Symbol*)_$1->info)->type = type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_87(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_88(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$2; if (LookupSymbol(scopeStack, ((Symbol*)_$2->info)->name)) BIT_UNION(((Symbol*)_$2->info)->kind, ((Symbol*)_$1->info)->kind, KINDS_COUNT); InsertSymbol(scopeStack, _$2->info); BIT_SET(((Symbol*)_$2->info)->kind, TYPE_KIND_MASK); SetBaseType(&_$2->type, _$1->type); ((Symbol*)_$2->info)->type = _$2->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_89(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; if (LookupSymbolInCurrentScope(scopeStack, ((Symbol*)_$1->info)->name)) { MakeError(errors, "`%s` already exists", ((Symbol*)_$1->info)->name); return _$_$;} InsertSymbol(scopeStack, _$1->info); BIT_SET(((Symbol*)_$1->info)->kind, VARIABLE_KIND_MASK); SetBaseType(&_$1->type, _$0->type); ((Symbol*)_$1->info)->type = _$1->type; if (!((Type*)_$1->type)->size) { MakeError(errors, "Incomplete type `%s` is not allowed", ((Symbol*)_$0->info)->name); } if(_$1->type && ((Type*)_$1->type)->type == ARRAY_TYPE) CalculateArraySize(_$1->type); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_91(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateArithmeticExpression; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_92(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// assignment_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateAssignment;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_94(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// assignment_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$_$->info = NULL; _$_$->AnalysisFunction = AnalyzeAssignment; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_97(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// and_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateAnd; _$_$->AnalysisFunction = AnalyzeBitwise; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_99(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// logical_and_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->evaluateAsExpression = FALSE; _$_$->GenerationFunction = GenerateLogicalAnd; _$_$->AnalysisFunction = AnalyzeLogical; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_101(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// exclusive_or_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateXor; _$_$->AnalysisFunction = AnalyzeBitwise; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_103(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// equality_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateEEQ; _$_$->AnalysisFunction = AnalyzeRelational; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; _$0->lvalue = FALSE; _$2->lvalue = FALSE; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_104(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// equality_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateNEQ; _$_$->AnalysisFunction = AnalyzeRelational; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_106(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateGT; _$_$->AnalysisFunction = AnalyzeRelational; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_107(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateLT; _$_$->AnalysisFunction = AnalyzeRelational; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_108(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateGE;  _$_$->AnalysisFunction = AnalyzeRelational;_$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_109(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateLE; _$_$->AnalysisFunction = AnalyzeRelational; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_111(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// shift_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateLSHIFT; _$_$->AnalysisFunction = AnalyzeBitwise; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_112(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// shift_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateRSHIFT; _$_$->AnalysisFunction = AnalyzeBitwise; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_114(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// additive_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$0->lvalue = _$2->lvalue = FALSE; _$_$->GenerationFunction = GenerateAddition; _$_$->AnalysisFunction = AnalyzeAddition; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_115(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// additive_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$0->lvalue = _$2->lvalue = FALSE; _$_$->GenerationFunction = GenerateSubtraction; _$_$->AnalysisFunction = AnalyzeSubtraction; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_117(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$);  _$_$->label = _$1->label; _$0->lvalue = _$2->lvalue = FALSE; _$_$->GenerationFunction = GenerateMult; _$_$->AnalysisFunction = AnalyzeMultDiv; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_118(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateDivision; _$_$->AnalysisFunction = AnalyzeMultDiv; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_119(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->label = _$1->label; _$_$->GenerationFunction = GenerateMod; _$_$->AnalysisFunction = AnalyzeMod; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_122(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateDereference; _$0->AnalysisFunction = AnalyzeDereference; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_123(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateNeg; _$0->AnalysisFunction = AnalyzeNeg; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_124(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateReference; _$0->AnalysisFunction = AnalyzeReference; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_125(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateLogicalNot; _$0->AnalysisFunction = AnalyzeLogical; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_127(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = _$1->info; _$_$->label = _$0->label; _$_$->type = _$1->type; _$_$->GenerationFunction = _$0->GenerationFunction; _$_$->AnalysisFunction = _$0->AnalysisFunction; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$1; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_128(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// argument_expression_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$);  _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; if (_$0->type && !((Type*)_$0->type)->size) MakeError(errors, "Expression must have arithmetic type"); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_129(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// argument_expression_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$2; if (_$2->type && !((Type*)_$2->type)->size) MakeError(errors, "Expression must have arithmetic type");  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_131(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 MakeAbstractSyntaxTree(&_$_$); _$2 = _$2->childrenManager->info; AbstractSyntaxTreeNode *addition; MakeAbstractSyntaxTree(&addition); *SetAbstractSyntaxTreeNodeChild(_$_$) = addition; _$_$->lvalue = FALSE; addition->lvalue = FALSE; _$_$->GenerationFunction = GenerateDereference; _$_$->AnalysisFunction = AnalyzeDereference; _$0->lvalue = _$2->lvalue = FALSE; addition->GenerationFunction = GenerateAddition; addition->AnalysisFunction = AnalyzeAddition; addition->info = NULL; *SetAbstractSyntaxTreeNodeChild(addition) = _$0; *SetAbstractSyntaxTreeNodeChild(addition) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_132(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$0; _$0->label = _$1->label; _$_$->GenerationFunction = GenerateCallWithoutParams; _$_$->lvalue = FALSE; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_133(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->label = _$1->label; _$0->GenerationFunction = GenerateCall; _$_$->lvalue = FALSE; _$0->evaluateAsExpression = FALSE; *SetAbstractSyntaxTreeNodeChild(_$0) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_134(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; _$_$->GenerationFunction = GenerateStructAccess; _$_$->AnalysisFunction = AnalyzeStructAccess; Type *structType = ((Symbol*)_$0->info)->type; for (; structType->type != STRUCT_TYPE; structType = structType->baseType); _$0->type = structType; _$0->lvalue = FALSE; _$_$->info = _$2->info; _$2->field = FindField(_$0->type, ((Symbol*)_$2->info)->name); ((Symbol*)_$_$->info)->type = _$_$->type = _$2->field ? ((Field*)_$2->field)->type : _$0->type; if (!_$2->field) MakeError(errors, "Type `%s` has no field named `%s`", ((Type*)_$0->type)->structDef->name, ((Symbol*)_$2->info)->name); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_135(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); AbstractSyntaxTreeNode *dref; MakeAbstractSyntaxTree(&dref); *SetAbstractSyntaxTreeNodeChild(_$_$) = dref; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; _$_$->GenerationFunction = GenerateStructAccess; _$_$->AnalysisFunction = AnalyzeStructAccess; Type *structType = ((Symbol*)_$0->info)->type; for (; structType->type != STRUCT_TYPE; structType = structType->baseType); dref->info = _$0->info; dref->type = _$0->type; dref->GenerationFunction = GenerateDereference; dref->AnalysisFunction = AnalyzeDereference; *SetAbstractSyntaxTreeNodeChild(dref) = _$0; _$_$->info = _$2->info; _$2->field = FindField(structType, ((Symbol*)_$2->info)->name); ((Symbol*)_$_$->info)->type = _$_$->type = _$2->field ? ((Field*)_$2->field)->type : _$0->type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_136(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// function_name
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$0; if (!BIT_TEST(((Symbol*)_$0->info)->kind, FUNCTION_KIND_MASK)) MakeError(errors, "`%s` is not a function", ((Symbol*)_$0->info)->name); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_137(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; if (!BIT_TEST(((Symbol*)_$0->info)->kind, VARIABLE_KIND_MASK)) MakeError(errors, "`%s` is not a valid identifier here", ((Symbol*)_$0->info)->name); _$_$->GenerationFunction = GenerateSymbol; Token *id = _$_$->info; _$_$->info = LookupSymbol(scopeStack, id->lexeme); if (!_$_$->info) return _$_$; _$_$->type = ((Symbol*)_$_$->info)->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_138(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); _$_$->type = symbol->type = LookupSymbol(scopeStack, "long")->type; symbol->name = ((Token*)_$0->info)->lexeme; _$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateIntegerLiteral; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_139(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); _$_$->type = symbol->type = LookupSymbol(scopeStack, "double")->type; symbol->name = ((Token*)_$0->info)->lexeme;_$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateFloatLiteral;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_140(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); symbol->name = ((Token*)_$0->info)->lexeme; Type *type; MakeType(&type, FALSE); type->type = POINTER_TYPE; type->size = 8; type->baseType = LookupSymbol(scopeStack, "char")->type; _$_$->type = symbol->type = type; _$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateStringLiteral;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_141(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = ((AbstractSyntaxTreeNode*)_$1)->childrenManager->info;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_142(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// existing_identifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol = LookupSymbol(scopeStack, ((Token*)_$0->info)->lexeme); if (symbol) {_$0->info = symbol; _$0->type = symbol->type; _$0->lvalue = TRUE; } else { MakeError(errors, "Unknown symbol: %s", ((Token*)_$0->info)->lexeme); } 
return _$_$;
}
void AssignActions(Grammar *g)
{
unsigned short currentRule = ZERO;
LinearLinkedListNode *nonTerminalsPtr, *rulesPtr;
Rule *rules[143];
for (nonTerminalsPtr = g->nonTerminals; nonTerminalsPtr; nonTerminalsPtr = nonTerminalsPtr->nextNode)
{
for (rulesPtr = ((NonTerminal*)nonTerminalsPtr->info)->rules; rulesPtr; rulesPtr = rulesPtr->nextNode)
{
rules[currentRule++] = rulesPtr->info;
}
}
rules[1]->semanticAction = Semantic_10;
rules[2]->semanticAction = Semantic_26;
rules[4]->semanticAction = Semantic_8;
rules[5]->semanticAction = Semantic_7;
rules[6]->semanticAction = Semantic_6;
rules[7]->semanticAction = Semantic_5;
rules[10]->semanticAction = Semantic_12;
rules[11]->semanticAction = Semantic_11;
rules[12]->semanticAction = Semantic_15;
rules[13]->semanticAction = Semantic_14;
rules[14]->semanticAction = Semantic_13;
rules[15]->semanticAction = Semantic_17;
rules[16]->semanticAction = Semantic_16;
rules[17]->semanticAction = Semantic_19;
rules[19]->semanticAction = Semantic_21;
rules[20]->semanticAction = Semantic_20;
rules[21]->semanticAction = Semantic_23;
rules[22]->semanticAction = Semantic_22;
rules[23]->semanticAction = Semantic_25;
rules[24]->semanticAction = Semantic_24;
rules[36]->semanticAction = Semantic_38;
rules[37]->semanticAction = Semantic_37;
rules[41]->semanticAction = Semantic_45;
rules[42]->semanticAction = Semantic_44;
rules[44]->semanticAction = Semantic_136;
rules[49]->semanticAction = Semantic_51;
rules[50]->semanticAction = Semantic_50;
rules[51]->semanticAction = Semantic_53;
rules[52]->semanticAction = Semantic_52;
rules[54]->semanticAction = Semantic_56;
rules[55]->semanticAction = Semantic_55;
rules[56]->semanticAction = Semantic_62;
rules[58]->semanticAction = Semantic_60;
rules[59]->semanticAction = Semantic_59;
rules[60]->semanticAction = Semantic_58;
rules[61]->semanticAction = Semantic_57;
rules[62]->semanticAction = Semantic_64;
rules[63]->semanticAction = Semantic_63;
rules[65]->semanticAction = Semantic_67;
rules[66]->semanticAction = Semantic_66;
rules[67]->semanticAction = Semantic_69;
rules[68]->semanticAction = Semantic_68;
rules[69]->semanticAction = Semantic_72;
rules[70]->semanticAction = Semantic_71;
rules[71]->semanticAction = Semantic_70;
rules[74]->semanticAction = Semantic_79;
rules[75]->semanticAction = Semantic_78;
rules[76]->semanticAction = Semantic_77;
rules[77]->semanticAction = Semantic_76;
rules[78]->semanticAction = Semantic_75;
rules[79]->semanticAction = Semantic_74;
rules[80]->semanticAction = Semantic_73;
rules[81]->semanticAction = Semantic_83;
rules[82]->semanticAction = Semantic_82;
rules[83]->semanticAction = Semantic_85;
rules[85]->semanticAction = Semantic_89;
rules[86]->semanticAction = Semantic_88;
rules[87]->semanticAction = Semantic_87;
rules[88]->semanticAction = Semantic_86;
rules[90]->semanticAction = Semantic_91;
rules[91]->semanticAction = Semantic_92;
rules[92]->semanticAction = Semantic_94;
rules[95]->semanticAction = Semantic_99;
rules[97]->semanticAction = Semantic_101;
rules[99]->semanticAction = Semantic_97;
rules[101]->semanticAction = Semantic_104;
rules[102]->semanticAction = Semantic_103;
rules[104]->semanticAction = Semantic_109;
rules[105]->semanticAction = Semantic_108;
rules[106]->semanticAction = Semantic_107;
rules[107]->semanticAction = Semantic_106;
rules[109]->semanticAction = Semantic_112;
rules[110]->semanticAction = Semantic_111;
rules[112]->semanticAction = Semantic_115;
rules[113]->semanticAction = Semantic_114;
rules[115]->semanticAction = Semantic_119;
rules[116]->semanticAction = Semantic_118;
rules[117]->semanticAction = Semantic_117;
rules[121]->semanticAction = Semantic_125;
rules[122]->semanticAction = Semantic_124;
rules[123]->semanticAction = Semantic_123;
rules[124]->semanticAction = Semantic_122;
rules[125]->semanticAction = Semantic_127;
rules[127]->semanticAction = Semantic_129;
rules[128]->semanticAction = Semantic_128;
rules[129]->semanticAction = Semantic_135;
rules[130]->semanticAction = Semantic_134;
rules[131]->semanticAction = Semantic_133;
rules[132]->semanticAction = Semantic_132;
rules[133]->semanticAction = Semantic_131;
rules[135]->semanticAction = Semantic_141;
rules[136]->semanticAction = Semantic_140;
rules[137]->semanticAction = Semantic_139;
rules[138]->semanticAction = Semantic_138;
rules[139]->semanticAction = Semantic_137;
rules[140]->semanticAction = Semantic_142;
rules[141]->semanticAction = Semantic_2;
rules[142]->semanticAction = Semantic_1;
}
