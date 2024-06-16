// SemanticAnalyzer.h

#ifndef _TYPE_SYSTEM_H
    #include "../libs/TypeSystem.h"
#endif

#ifndef _ABSTRACT_SYNTAX_TREE_H
    #include "../libs/AbstractSyntaxTree.h"
#endif

#ifndef _GRAMMAR_H
    #include "../libs/Grammar.h"
#endif

#ifndef _ACTIONS
    #include "../grammar/actions.h"
#endif

void AnalyzeSemantics(AbstractSyntaxTreeNode **astRoot, ErrorHandler *erros);