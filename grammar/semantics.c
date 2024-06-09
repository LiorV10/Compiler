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
AbstractSyntaxTreeNode* Semantic_5(void *scopeStack, Stack *semanticStack)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$5 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); Symbol* s = malloc(sizeof(Symbol)); s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s); _$_$->type = s->_type = _$0; _$_$->info = s; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$3; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$5; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_6(void *scopeStack, Stack *semanticStack)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->info = _$1->info; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_7(void *scopeStack, Stack *semanticStack)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$5 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = NULL; Symbol* s = malloc(sizeof(Symbol)); s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s);
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_8(void *scopeStack, Stack *semanticStack)
{
// function_definition
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = NULL; Symbol* s = malloc(sizeof(Symbol)); s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s);
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_10(void *scopeStack, Stack *semanticStack)
{
// jump_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateReturn; 
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
AbstractSyntaxTreeNode* Semantic_13(void *scopeStack, Stack *semanticStack)
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
AbstractSyntaxTreeNode* Semantic_14(void *scopeStack, Stack *semanticStack)
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
AbstractSyntaxTreeNode* Semantic_23(void *scopeStack, Stack *semanticStack)
{
// compound_statement
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$);
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
MakeAbstractSyntaxTree(&_$_$); _$_$->info = _$1->info; InsertSymbol(scopeStack, _$1->info);  Type *t = _$1->type; for (; t && t->baseType; t = t->baseType); !t ? _$1->type = _$0 : (t->baseType = _$0); _$_$->type = ((Symbol*)_$1->info)->_type = _$1->type;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_56(void *scopeStack, Stack *semanticStack)
{
// parameter_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$);  _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; _$0->GenerationFunction = GenerateDeclaration; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_57(void *scopeStack, Stack *semanticStack)
{
// parameter_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$2; _$2->GenerationFunction = GenerateDeclaration; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_59(void *scopeStack, Stack *semanticStack)
{
// pointer
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 8; ((Type*)_$_$)->type = POINTER_TYPE; ((Type*)_$_$)->baseType = NULL;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_60(void *scopeStack, Stack *semanticStack)
{
// pointer
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 8; ((Type*)_$_$)->type = POINTER_TYPE; ((Type*)_$_$)->baseType = _$1;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_61(void *scopeStack, Stack *semanticStack)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
Symbol* symbol; MakeSymbol(&symbol); symbol->name = ((Token*)_$0->info)->lexeme; _$0->info = symbol; _$_$ = _$0; _$0->type = NULL; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_62(void *scopeStack, Stack *semanticStack)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Type *type = malloc(sizeof(Type)); type->size = atoi(((Symbol*)_$2->info)->name); type->type = ARRAY_TYPE; type->baseType = NULL; Type *t; for (t = _$0->type; t && t->baseType; t = t->baseType); !t ? _$0->type = type : (t->baseType = type); ((Symbol*)_$0->info)->_type = _$0->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_65(void *scopeStack, Stack *semanticStack)
{
// declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; Type *arrayType = _$1->type; for (; arrayType && arrayType->baseType; arrayType = arrayType->baseType); if (arrayType) arrayType->baseType = _$0; _$1->type = ((Symbol*)_$1->info)->_type = (arrayType ? arrayType : _$0); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_66(void *scopeStack, Stack *semanticStack)
{
// declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->lvalue = TRUE;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_69(void *scopeStack, Stack *semanticStack)
{
// struct_declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; Type *t = _$1->type; for (; t && t->baseType; t = t->baseType); !t ? _$1->type = _$0 : (t->baseType = _$0); ((Symbol*)_$1->info)->_type = _$1->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_70(void *scopeStack, Stack *semanticStack)
{
// struct_declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
LinearLinkedListNode **fields = malloc(sizeof(LinearLinkedListNode*)); InitLinearLinkedList(fields); PushLinearLinkedList(fields); (*fields)->info = _$0; _$_$ = fields; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_71(void *scopeStack, Stack *semanticStack)
{
// struct_declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; PushLinearLinkedList(_$_$); (*((LinearLinkedListNode**)_$_$))->info = _$1;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_72(void *scopeStack, Stack *semanticStack)
{
// struct_or_union_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$4 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; Type *type = LookupSymbol(scopeStack, ((Symbol*)_$1->info)->name) ? LookupSymbol(scopeStack, ((Symbol*)_$1->info)->name)->_type : malloc(sizeof(Type)); if (!LookupSymbol(scopeStack, ((Symbol*)_$1->info)->name)) InsertSymbol(scopeStack, _$1->info); else _$1->info = LookupSymbol(scopeStack, ((Symbol*)_$1->info)->name); ((Symbol*)_$1->info)->_type = _$1->type = type; type->size = 0; type->type = STRUCT_TYPE; type->baseType = NULL; type->fields = malloc(sizeof(StringsDictionary)); InitStringsDictionary(type->fields); type->structDef = _$1->info; for (LinearLinkedListNode *p = *((LinearLinkedListNode**)_$3); p; p = p->nextNode) type->size += ((Type*)((Symbol*)((AbstractSyntaxTreeNode*)p->info)->info)->_type)->size;  unsigned short offset = 0; for (LinearLinkedListNode *p = *((LinearLinkedListNode**)_$3); p; offset += ((Type*)((Symbol*)((AbstractSyntaxTreeNode*)p->info)->info)->_type)->size, p = p->nextNode) AddField(type, ((Symbol*)((AbstractSyntaxTreeNode*)p->info)->info)->name, offset, ((Symbol*)((AbstractSyntaxTreeNode*)p->info)->info)->_type);
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_74(void *scopeStack, Stack *semanticStack)
{
// struct_or_union_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = LookupSymbol(scopeStack, ((Symbol*)_$1->info)->name)->_type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_75(void *scopeStack, Stack *semanticStack)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 0; ((Type*)_$_$)->type = VOID_TYPE; ((Type*)_$_$)->baseType = NULL;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_76(void *scopeStack, Stack *semanticStack)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 1; ((Type*)_$_$)->type = CHAR_TYPE; ((Type*)_$_$)->baseType = NULL;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_77(void *scopeStack, Stack *semanticStack)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 2; ((Type*)_$_$)->type = SHORT_TYPE; ((Type*)_$_$)->baseType = NULL;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_78(void *scopeStack, Stack *semanticStack)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 4; ((Type*)_$_$)->type = INTEGER_TYPE; ((Type*)_$_$)->baseType = NULL;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_79(void *scopeStack, Stack *semanticStack)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 4; ((Type*)_$_$)->type = FLOAT_TYPE; ((Type*)_$_$)->baseType = NULL;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_80(void *scopeStack, Stack *semanticStack)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 8; ((Type*)_$_$)->type = LONG_TYPE; ((Type*)_$_$)->baseType = NULL;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_81(void *scopeStack, Stack *semanticStack)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 8; ((Type*)_$_$)->type = DOUBLE_TYPE; ((Type*)_$_$)->baseType = NULL;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_84(void *scopeStack, Stack *semanticStack)
{
// init_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateDeclaration;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_85(void *scopeStack, Stack *semanticStack)
{
// init_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateDeclaration; _$_$->info = _$0->info; _$_$->type = _$0->type;  _$0->GenerationFunction = GenerateDeclaration; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_87(void *scopeStack, Stack *semanticStack)
{
// declaration_specifiers
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; puts("typedef!");
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_88(void *scopeStack, Stack *semanticStack)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$_$->GenerationFunction = NULL; InsertSymbol(scopeStack, _$1->info); Type *type = malloc(sizeof(Type)); type->type = STRUCT_TYPE; _$1->type = ((Symbol*)_$1->info)->_type = type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_89(void *scopeStack, Stack *semanticStack)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_90(void *scopeStack, Stack *semanticStack)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; InsertSymbol(scopeStack, _$1->info); Type *t; for (t = _$1->type; t && t->baseType; t = t->baseType); !t ? _$1->type = _$0 : (t->baseType = _$0); ((Symbol*)_$1->info)->_type = _$1->type; if(_$1->type && ((Type*)_$1->type)->type == ARRAY_TYPE) for(Type *base = ((Type*)_$1->type)->baseType; base && base->type != POINTER_TYPE; base = base->baseType) ((Type*)_$1->type)->size *= base->size; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_92(void *scopeStack, Stack *semanticStack)
{
// expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateArithmeticExpression; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_93(void *scopeStack, Stack *semanticStack)
{
// assignment_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateAssignment;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_97(void *scopeStack, Stack *semanticStack)
{
// assignment_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateAdditionAssignment;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_100(void *scopeStack, Stack *semanticStack)
{
// assignment_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$_$->info = NULL; _$0->lvalue = TRUE; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_103(void *scopeStack, Stack *semanticStack)
{
// and_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateAnd; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_105(void *scopeStack, Stack *semanticStack)
{
// equality_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateEEQ; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; _$0->lvalue = FALSE; _$2->lvalue = FALSE; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_106(void *scopeStack, Stack *semanticStack)
{
// equality_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateNEQ; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_108(void *scopeStack, Stack *semanticStack)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateGT; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_109(void *scopeStack, Stack *semanticStack)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateLT; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_110(void *scopeStack, Stack *semanticStack)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateGE; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_111(void *scopeStack, Stack *semanticStack)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateLE; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_113(void *scopeStack, Stack *semanticStack)
{
// shift_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateLSHIFT; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_114(void *scopeStack, Stack *semanticStack)
{
// shift_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateRSHIFT; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_116(void *scopeStack, Stack *semanticStack)
{
// additive_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$0->lvalue = _$2->lvalue = FALSE; _$_$->GenerationFunction = GenerateAddition; _$_$->AnalysisFunction = AnalyzeAddition; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_117(void *scopeStack, Stack *semanticStack)
{
// additive_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$0->lvalue = _$2->lvalue = FALSE; _$_$->GenerationFunction = GenerateSubtraction; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_119(void *scopeStack, Stack *semanticStack)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$0->lvalue = _$2->lvalue = FALSE; _$_$->GenerationFunction = GenerateMult; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_120(void *scopeStack, Stack *semanticStack)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateDivision; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_121(void *scopeStack, Stack *semanticStack)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateMod; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_124(void *scopeStack, Stack *semanticStack)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateDereference; _$0->AnalysisFunction = AnalyzeDereference; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_126(void *scopeStack, Stack *semanticStack)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateNeg;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_127(void *scopeStack, Stack *semanticStack)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateReference; _$0->AnalysisFunction = AnalyzeReference; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_128(void *scopeStack, Stack *semanticStack)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateLogNot;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_132(void *scopeStack, Stack *semanticStack)
{
// unary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->lvalue = FALSE; _$1->lvalue = FALSE; _$_$->info = _$1->info; _$_$->type = _$1->type; _$_$->GenerationFunction = _$0->GenerationFunction; _$_$->AnalysisFunction = _$0->AnalysisFunction; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$1; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_133(void *scopeStack, Stack *semanticStack)
{
// argument_expression_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$);  _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_134(void *scopeStack, Stack *semanticStack)
{
// argument_expression_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_136(void *scopeStack, Stack *semanticStack)
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
AbstractSyntaxTreeNode* Semantic_137(void *scopeStack, Stack *semanticStack)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateCall;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_138(void *scopeStack, Stack *semanticStack)
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
AbstractSyntaxTreeNode* Semantic_139(void *scopeStack, Stack *semanticStack)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; _$_$->GenerationFunction = GenerateStructAccess; _$_$->AnalysisFunction = AnalyzeStructAccess; _$0->type = ((Symbol*)_$0->info)->_type; _$0->lvalue = FALSE; _$_$->info = _$2->info; _$2->field = FindField(_$0->type, ((Symbol*)_$2->info)->name); ((Symbol*)_$_$->info)->_type = _$_$->type = ((Field*)_$2->field)->type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_140(void *scopeStack, Stack *semanticStack)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); AbstractSyntaxTreeNode *dref; MakeAbstractSyntaxTree(&dref); *SetAbstractSyntaxTreeNodeChild(_$_$) = dref; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; _$_$->GenerationFunction = GenerateStructAccess; _$_$->AnalysisFunction = AnalyzeStructAccess; _$0->type = ((Symbol*)_$0->info)->_type; _$0->lvalue = FALSE; dref->lvalue = FALSE; _$2->lvalue = FALSE; dref->info = _$0->info; dref->type = _$0->type; dref->GenerationFunction = GenerateDereference; dref->AnalysisFunction = AnalyzeDereference; *SetAbstractSyntaxTreeNodeChild(dref) = _$0; _$_$->info = _$2->info; _$2->field = FindField(_$0->type, ((Symbol*)_$2->info)->name); ((Symbol*)_$_$->info)->_type = _$_$->type = ((Field*)_$2->field)->type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_141(void *scopeStack, Stack *semanticStack)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$1->info = _$0->info; _$1->GenerationFunction = GenerateIncrement; *SetAbstractSyntaxTreeNodeChild(_$1) = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_143(void *scopeStack, Stack *semanticStack)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateSymbol; Token *id = _$_$->info; _$_$->info = LookupSymbol(scopeStack, id->lexeme); _$_$->type = ((Symbol*)_$_$->info)->_type; _$_$->lvalue = TRUE; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_144(void *scopeStack, Stack *semanticStack)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); _$_$->type = symbol->_type = malloc(sizeof(Type)); ((Type*)symbol->_type)->size = 8; ((Type*)symbol->_type)->type = INTEGER_TYPE; ((Type*)symbol->_type)->baseType = NULL;  symbol->name = ((Token*)_$0->info)->lexeme; symbol->type = INTEGER_TYPE; _$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateIntegerLiteral;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_145(void *scopeStack, Stack *semanticStack)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); _$_$->type = symbol->_type = malloc(sizeof(Type)); ((Type*)symbol->_type)->size = 8; ((Type*)symbol->_type)->type = FLOAT_TYPE; ((Type*)symbol->_type)->baseType = NULL; symbol->name = ((Token*)_$0->info)->lexeme; symbol->type = FLOAT_TYPE; _$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateFloatLiteral;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_146(void *scopeStack, Stack *semanticStack)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); symbol->name = ((Token*)_$0->info)->lexeme; Type *type = malloc(sizeof(Type)); type->type = POINTER_TYPE; type->size = 8; type->baseType = malloc(sizeof(Type)); type->baseType->type = CHAR_TYPE; type->baseType->size = 1; _$_$->type = symbol->_type = type; _$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateStringLiteral;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_147(void *scopeStack, Stack *semanticStack)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = ((AbstractSyntaxTreeNode*)_$1)->childrenManager->info;
return _$_$;
}
void AssignActions(Grammar *g)
{
unsigned short currentRule = ZERO;
LinearLinkedListNode *nonTerminalsPtr, *rulesPtr;
Rule *rules[148];
for (nonTerminalsPtr = g->nonTerminals; nonTerminalsPtr; nonTerminalsPtr = nonTerminalsPtr->nextNode)
{
for (rulesPtr = ((NonTerminal*)nonTerminalsPtr->info)->rules; rulesPtr; rulesPtr = rulesPtr->nextNode)
{
rules[currentRule++] = rulesPtr->info;
}
}
rules[1]->semanticAction = Semantic_25;
rules[3]->semanticAction = Semantic_8;
rules[4]->semanticAction = Semantic_7;
rules[5]->semanticAction = Semantic_6;
rules[6]->semanticAction = Semantic_5;
rules[9]->semanticAction = Semantic_11;
rules[10]->semanticAction = Semantic_10;
rules[11]->semanticAction = Semantic_14;
rules[12]->semanticAction = Semantic_13;
rules[13]->semanticAction = Semantic_12;
rules[14]->semanticAction = Semantic_16;
rules[15]->semanticAction = Semantic_15;
rules[16]->semanticAction = Semantic_18;
rules[18]->semanticAction = Semantic_20;
rules[19]->semanticAction = Semantic_19;
rules[20]->semanticAction = Semantic_22;
rules[21]->semanticAction = Semantic_21;
rules[22]->semanticAction = Semantic_24;
rules[23]->semanticAction = Semantic_23;
rules[53]->semanticAction = Semantic_53;
rules[54]->semanticAction = Semantic_57;
rules[55]->semanticAction = Semantic_56;
rules[57]->semanticAction = Semantic_60;
rules[58]->semanticAction = Semantic_59;
rules[61]->semanticAction = Semantic_62;
rules[62]->semanticAction = Semantic_61;
rules[63]->semanticAction = Semantic_66;
rules[64]->semanticAction = Semantic_65;
rules[67]->semanticAction = Semantic_69;
rules[68]->semanticAction = Semantic_71;
rules[69]->semanticAction = Semantic_70;
rules[70]->semanticAction = Semantic_74;
rules[72]->semanticAction = Semantic_72;
rules[75]->semanticAction = Semantic_81;
rules[76]->semanticAction = Semantic_80;
rules[77]->semanticAction = Semantic_79;
rules[78]->semanticAction = Semantic_78;
rules[79]->semanticAction = Semantic_77;
rules[80]->semanticAction = Semantic_76;
rules[81]->semanticAction = Semantic_75;
rules[82]->semanticAction = Semantic_85;
rules[83]->semanticAction = Semantic_84;
rules[84]->semanticAction = Semantic_87;
rules[86]->semanticAction = Semantic_90;
rules[87]->semanticAction = Semantic_89;
rules[88]->semanticAction = Semantic_88;
rules[90]->semanticAction = Semantic_92;
rules[92]->semanticAction = Semantic_97;
rules[96]->semanticAction = Semantic_93;
rules[97]->semanticAction = Semantic_100;
rules[100]->semanticAction = Semantic_103;
rules[102]->semanticAction = Semantic_106;
rules[103]->semanticAction = Semantic_105;
rules[105]->semanticAction = Semantic_111;
rules[106]->semanticAction = Semantic_110;
rules[107]->semanticAction = Semantic_109;
rules[108]->semanticAction = Semantic_108;
rules[110]->semanticAction = Semantic_114;
rules[111]->semanticAction = Semantic_113;
rules[113]->semanticAction = Semantic_117;
rules[114]->semanticAction = Semantic_116;
rules[116]->semanticAction = Semantic_121;
rules[117]->semanticAction = Semantic_120;
rules[118]->semanticAction = Semantic_119;
rules[122]->semanticAction = Semantic_128;
rules[123]->semanticAction = Semantic_127;
rules[124]->semanticAction = Semantic_126;
rules[126]->semanticAction = Semantic_124;
rules[127]->semanticAction = Semantic_132;
rules[131]->semanticAction = Semantic_134;
rules[132]->semanticAction = Semantic_133;
rules[134]->semanticAction = Semantic_141;
rules[135]->semanticAction = Semantic_140;
rules[136]->semanticAction = Semantic_139;
rules[137]->semanticAction = Semantic_138;
rules[138]->semanticAction = Semantic_137;
rules[139]->semanticAction = Semantic_136;
rules[141]->semanticAction = Semantic_147;
rules[142]->semanticAction = Semantic_146;
rules[143]->semanticAction = Semantic_145;
rules[144]->semanticAction = Semantic_144;
rules[145]->semanticAction = Semantic_143;
rules[146]->semanticAction = Semantic_2;
rules[147]->semanticAction = Semantic_1;
}
