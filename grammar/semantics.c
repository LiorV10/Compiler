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
 ExitScope(scopeStack); MakeAbstractSyntaxTree(&_$_$); Symbol* s = malloc(sizeof(Symbol)); s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s); _$_$->type = s->_type = _$0; _$_$->info = s; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$3; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$6; 
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
 puts(((Symbol*)_$1->info)->name); MakeAbstractSyntaxTree(&_$_$); _$_$->info = _$1->info; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4; ((Symbol*)_$1->info)->_type = _$0; 
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
 ExitScope(scopeStack); MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = NULL; Symbol* s = malloc(sizeof(Symbol)); s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s);
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
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = NULL; Symbol* s = malloc(sizeof(Symbol));  Type *t; for (t = _$1->type; t && t->baseType; t = t->baseType); !t ? _$1->type = _$0 : (t->baseType = _$0);  _$_$->type = s->_type = _$1->type; s->name = ((Token*)_$1->info)->lexeme; InsertSymbol(scopeStack, s);
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_10(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// block_enter_paren
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 puts("moshe"); EnterScope(scopeStack); _$_$ = _$0; 
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
MakeAbstractSyntaxTree(&_$_$); _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$4;
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
ExitScope(scopeStack); _$_$ = _$1; _$_$->GenerationFunction = GenerateStatements; 
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
AbstractSyntaxTreeNode* Semantic_41(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_abstract_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$3 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Type *type = malloc(sizeof(Type)); type->size = atoi(((Symbol*)_$2->info)->name); type->type = ARRAY_TYPE; type->baseType = NULL; Type *t; for (t = _$0->type; t && t->baseType; t = t->baseType); !t ? _$0->type = type : (t->baseType = type); ((Symbol*)_$0->info)->_type = _$0->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_42(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_abstract_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Type *type = malloc(sizeof(Type)); type->size = 8; type->type = POINTER_TYPE; type->baseType = NULL; Type *t; for (t = _$0->type; t && t->baseType; t = t->baseType); !t ? _$0->type = type : (t->baseType = type); ((Symbol*)_$0->info)->_type = _$0->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_48(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// abstract_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->lvalue = TRUE;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_49(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// abstract_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; Type *arrayType = _$1->type; for (; arrayType && arrayType->baseType; arrayType = arrayType->baseType); if (arrayType) arrayType->baseType = _$0; _$1->type = ((Symbol*)_$1->info)->_type = (arrayType ? arrayType : _$0); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_54(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// parameter_declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; InsertSymbol(scopeStack, _$1->info); Type *t; for (t = _$1->type; t && t->baseType; t = t->baseType); !t ? _$1->type = _$0 : (t->baseType = _$0); ((Symbol*)_$1->info)->_type = _$1->type; if(_$1->type && ((Type*)_$1->type)->type == ARRAY_TYPE) for(Type *base = ((Type*)_$1->type)->baseType; base && base->type != POINTER_TYPE; base = base->baseType) ((Type*)_$1->type)->size *= base->size; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_55(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// parameter_declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; InsertSymbol(scopeStack, _$1->info); Type *t; for (t = _$1->type; t && t->baseType; t = t->baseType); !t ? _$1->type = _$0 : (t->baseType = _$0); ((Symbol*)_$1->info)->_type = _$1->type; if(_$1->type && ((Type*)_$1->type)->type == ARRAY_TYPE) for(Type *base = ((Type*)_$1->type)->baseType; base && base->type != POINTER_TYPE; base = base->baseType) ((Type*)_$1->type)->size *= base->size; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_57(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// parameter_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$);  _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; _$0->GenerationFunction = GenerateDeclaration; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_58(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// parameter_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$2; _$2->GenerationFunction = GenerateDeclaration; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_60(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// pointer
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 8; ((Type*)_$_$)->type = POINTER_TYPE; ((Type*)_$_$)->baseType = NULL;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_61(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// pointer
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = malloc(sizeof(Type)); ((Type*)_$_$)->size = 8; ((Type*)_$_$)->type = POINTER_TYPE; ((Type*)_$_$)->baseType = _$1;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_62(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
Symbol* symbol; MakeSymbol(&symbol); symbol->name = ((Token*)_$0->info)->lexeme; _$0->info = symbol; _$_$ = _$0; _$0->type = NULL; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_63(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
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
AbstractSyntaxTreeNode* Semantic_64(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$0; Type *ptr = malloc(sizeof(Type)); ptr->type = POINTER_TYPE; ptr->size = 8; ptr->baseType = _$0->type; _$0->type = ptr; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_65(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$1; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_67(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// direct_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = _$0; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_68(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; Type *arrayType = _$1->type; for (; arrayType && arrayType->baseType; arrayType = arrayType->baseType); if (arrayType) arrayType->baseType = _$0; _$1->type = ((Symbol*)_$1->info)->_type = (arrayType ? arrayType : _$0); 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_69(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->lvalue = TRUE;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_71(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; Type *t = _$1->type; for (; t && t->baseType; t = t->baseType); !t ? _$1->type = _$0 : (t->baseType = _$0); ((Symbol*)_$1->info)->_type = _$1->type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_72(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
LinearLinkedListNode **fields = malloc(sizeof(LinearLinkedListNode*)); InitLinearLinkedList(fields); PushLinearLinkedList(fields); (*fields)->info = _$0; _$_$ = fields; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_73(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_declaration_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; PushLinearLinkedList(_$_$); (*((LinearLinkedListNode**)_$_$))->info = _$1;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_74(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
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
AbstractSyntaxTreeNode* Semantic_76(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// struct_or_union_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = LookupSymbol(scopeStack, ((Symbol*)_$1->info)->name)->_type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_77(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = (Type*)LookupSymbol(scopeStack, "void")->_type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_78(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
 _$_$ = (Type*)LookupSymbol(scopeStack, "char")->_type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_79(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = (Type*)LookupSymbol(scopeStack, "short")->_type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_80(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = (Type*)LookupSymbol(scopeStack, "int")->_type; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_81(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = (Type*)LookupSymbol(scopeStack, "float")->_type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_82(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = (Type*)LookupSymbol(scopeStack, "long")->_type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_83(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// type_specifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = (Type*)LookupSymbol(scopeStack, "double")->_type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_86(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// init_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateDeclaration;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_87(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// init_declarator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateDeclaration; _$_$->info = _$0->info; _$_$->type = _$0->type;  _$0->GenerationFunction = GenerateDeclaration; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_89(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration_specifiers
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; puts("typedef!");
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_90(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$_$->GenerationFunction = NULL; InsertSymbol(scopeStack, _$1->info); Type *type = malloc(sizeof(Type)); type->type = STRUCT_TYPE; _$1->type = ((Symbol*)_$1->info)->_type = type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_91(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_92(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// declaration
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; InsertSymbol(scopeStack, _$1->info); Type *t; for (t = _$1->type; t && t->baseType; t = t->baseType); !t ? _$1->type = _$0 : (t->baseType = _$0); ((Symbol*)_$1->info)->_type = _$1->type; if(_$1->type && ((Type*)_$1->type)->type == ARRAY_TYPE) for(Type *base = ((Type*)_$1->type)->baseType; base && base->type != POINTER_TYPE; base = base->baseType) ((Type*)_$1->type)->size *= base->size; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_94(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateArithmeticExpression; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_95(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// assignment_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateAssignment;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_99(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// assignment_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateAdditionAssignment;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_102(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// assignment_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$_$->info = NULL; _$0->lvalue = TRUE; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_105(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// and_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateAnd; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_107(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// exclusive_or_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateXor; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_109(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// equality_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateEEQ; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; _$0->lvalue = FALSE; _$2->lvalue = FALSE; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_110(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// equality_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateNEQ; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_112(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateGT; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_113(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateLT; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_114(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateGE; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_115(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// relational_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateLE; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_117(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// shift_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateLSHIFT; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_118(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// shift_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateRSHIFT; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_120(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// additive_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$0->lvalue = _$2->lvalue = FALSE; _$_$->GenerationFunction = GenerateAddition; _$_$->AnalysisFunction = AnalyzeAddition; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_121(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// additive_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$0->lvalue = _$2->lvalue = FALSE; _$_$->GenerationFunction = GenerateSubtraction; _$_$->AnalysisFunction = AnalyzeSubtraction; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_123(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$0->lvalue = _$2->lvalue = FALSE; _$_$->GenerationFunction = GenerateMult; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_124(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateDivision; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_125(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// multiplicative_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->GenerationFunction = GenerateMod; _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_128(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateDereference; _$0->AnalysisFunction = AnalyzeDereference; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_130(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateNeg;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_131(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateReference; _$0->AnalysisFunction = AnalyzeReference; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_132(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_operator
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$0->GenerationFunction = GenerateLogNot;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_136(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// unary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); _$_$->lvalue = FALSE; _$1->lvalue = FALSE; _$_$->info = _$1->info; _$_$->type = _$1->type; _$_$->GenerationFunction = _$0->GenerationFunction; _$_$->AnalysisFunction = _$0->AnalysisFunction; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$1; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_137(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// argument_expression_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$);  _$_$->info = NULL; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_138(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// argument_expression_list
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; *SetAbstractSyntaxTreeNodeChild(_$0) = _$2;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_140(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
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
AbstractSyntaxTreeNode* Semantic_141(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateCall;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_142(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
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
AbstractSyntaxTreeNode* Semantic_143(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); *SetAbstractSyntaxTreeNodeChild(_$_$) = _$0; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; _$_$->GenerationFunction = GenerateStructAccess; _$_$->AnalysisFunction = AnalyzeStructAccess; _$0->type = ((Symbol*)_$0->info)->_type; _$0->lvalue = FALSE; _$_$->info = _$2->info; _$2->field = FindField(_$0->type, ((Symbol*)_$2->info)->name); ((Symbol*)_$_$->info)->_type = _$_$->type = _$2->field ? ((Field*)_$2->field)->type : _$0->type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_144(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
MakeAbstractSyntaxTree(&_$_$); AbstractSyntaxTreeNode *dref; MakeAbstractSyntaxTree(&dref); *SetAbstractSyntaxTreeNodeChild(_$_$) = dref; *SetAbstractSyntaxTreeNodeChild(_$_$) = _$2; _$_$->GenerationFunction = GenerateStructAccess; _$_$->AnalysisFunction = AnalyzeStructAccess; _$0->type = ((Symbol*)_$0->info)->_type; _$0->lvalue = FALSE; dref->lvalue = FALSE; _$2->lvalue = FALSE; dref->info = _$0->info; dref->type = _$0->type; dref->GenerationFunction = GenerateDereference; dref->AnalysisFunction = AnalyzeDereference; *SetAbstractSyntaxTreeNodeChild(dref) = _$0; _$_$->info = _$2->info; _$2->field = FindField(_$0->type, ((Symbol*)_$2->info)->name); ((Symbol*)_$_$->info)->_type = _$_$->type = ((Field*)_$2->field)->type;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_145(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// postfix_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$1; _$1->info = _$0->info; _$1->GenerationFunction = GenerateIncrement; *SetAbstractSyntaxTreeNodeChild(_$1) = _$0;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_147(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; _$_$->GenerationFunction = GenerateSymbol; Token *id = _$_$->info; _$_$->info = LookupSymbol(scopeStack, id->lexeme); if (!_$_$->info) return _$_$; _$_$->type = ((Symbol*)_$_$->info)->_type; _$_$->lvalue = TRUE; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_148(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); _$_$->type = symbol->_type = LookupSymbol(scopeStack, "long")->_type; symbol->name = ((Token*)_$0->info)->lexeme; _$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateIntegerLiteral; 
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_149(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); _$_$->type = symbol->_type = LookupSymbol(scopeStack, "double")->_type; symbol->name = ((Token*)_$0->info)->lexeme;_$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateFloatLiteral;  
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_150(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol; MakeSymbol(&symbol); symbol->name = ((Token*)_$0->info)->lexeme; Type *type; MakeType(&type, FALSE); type->type = POINTER_TYPE; type->size = 8; type->baseType = LookupSymbol(scopeStack, "char")->_type; _$_$->type = symbol->_type = type; _$_$->info = symbol; _$_$->lvalue = FALSE; _$_$->GenerationFunction = GenerateStringLiteral;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_151(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// primary_expression
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$2 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$1 = PopStack(semanticStack);
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = ((AbstractSyntaxTreeNode*)_$1)->childrenManager->info;
return _$_$;
}
AbstractSyntaxTreeNode* Semantic_152(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)
{
// existing_identifier
AbstractSyntaxTreeNode *_$_$ = NULL;
AbstractSyntaxTreeNode *_$0 = PopStack(semanticStack);
_$_$ = _$0; Symbol *symbol = LookupSymbol(scopeStack, ((Token*)_$0->info)->lexeme); if (symbol) {_$0->info = symbol; _$0->type = symbol->_type; } else {MakeError(errors, "Unknown symbol: %s", ((Token*)_$0->info)->lexeme); symbol = malloc(sizeof(Symbol)); symbol->name = "dummy"; _$0->info = symbol; } 
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
rules[40]->semanticAction = Semantic_42;
rules[41]->semanticAction = Semantic_41;
rules[45]->semanticAction = Semantic_49;
rules[46]->semanticAction = Semantic_48;
rules[53]->semanticAction = Semantic_55;
rules[54]->semanticAction = Semantic_54;
rules[55]->semanticAction = Semantic_58;
rules[56]->semanticAction = Semantic_57;
rules[58]->semanticAction = Semantic_61;
rules[59]->semanticAction = Semantic_60;
rules[60]->semanticAction = Semantic_67;
rules[62]->semanticAction = Semantic_65;
rules[63]->semanticAction = Semantic_64;
rules[64]->semanticAction = Semantic_63;
rules[65]->semanticAction = Semantic_62;
rules[66]->semanticAction = Semantic_69;
rules[67]->semanticAction = Semantic_68;
rules[69]->semanticAction = Semantic_71;
rules[70]->semanticAction = Semantic_73;
rules[71]->semanticAction = Semantic_72;
rules[72]->semanticAction = Semantic_76;
rules[74]->semanticAction = Semantic_74;
rules[77]->semanticAction = Semantic_83;
rules[78]->semanticAction = Semantic_82;
rules[79]->semanticAction = Semantic_81;
rules[80]->semanticAction = Semantic_80;
rules[81]->semanticAction = Semantic_79;
rules[82]->semanticAction = Semantic_78;
rules[83]->semanticAction = Semantic_77;
rules[84]->semanticAction = Semantic_87;
rules[85]->semanticAction = Semantic_86;
rules[86]->semanticAction = Semantic_89;
rules[88]->semanticAction = Semantic_92;
rules[89]->semanticAction = Semantic_91;
rules[90]->semanticAction = Semantic_90;
rules[92]->semanticAction = Semantic_94;
rules[94]->semanticAction = Semantic_99;
rules[98]->semanticAction = Semantic_95;
rules[99]->semanticAction = Semantic_102;
rules[102]->semanticAction = Semantic_107;
rules[104]->semanticAction = Semantic_105;
rules[106]->semanticAction = Semantic_110;
rules[107]->semanticAction = Semantic_109;
rules[109]->semanticAction = Semantic_115;
rules[110]->semanticAction = Semantic_114;
rules[111]->semanticAction = Semantic_113;
rules[112]->semanticAction = Semantic_112;
rules[114]->semanticAction = Semantic_118;
rules[115]->semanticAction = Semantic_117;
rules[117]->semanticAction = Semantic_121;
rules[118]->semanticAction = Semantic_120;
rules[120]->semanticAction = Semantic_125;
rules[121]->semanticAction = Semantic_124;
rules[122]->semanticAction = Semantic_123;
rules[126]->semanticAction = Semantic_132;
rules[127]->semanticAction = Semantic_131;
rules[128]->semanticAction = Semantic_130;
rules[130]->semanticAction = Semantic_128;
rules[131]->semanticAction = Semantic_136;
rules[135]->semanticAction = Semantic_138;
rules[136]->semanticAction = Semantic_137;
rules[138]->semanticAction = Semantic_145;
rules[139]->semanticAction = Semantic_144;
rules[140]->semanticAction = Semantic_143;
rules[141]->semanticAction = Semantic_142;
rules[142]->semanticAction = Semantic_141;
rules[143]->semanticAction = Semantic_140;
rules[145]->semanticAction = Semantic_151;
rules[146]->semanticAction = Semantic_150;
rules[147]->semanticAction = Semantic_149;
rules[148]->semanticAction = Semantic_148;
rules[149]->semanticAction = Semantic_147;
rules[150]->semanticAction = Semantic_152;
rules[151]->semanticAction = Semantic_2;
rules[152]->semanticAction = Semantic_1;
}
