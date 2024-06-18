// Construction.c 

#include "Construction.h"

#define MAX_DEFINITION_LENGTH 256
#define MAX_RULE_LENGTH 1024

Expression *MakeExpression(Grammar *grammar, char *line, BOOL isTerminal, int *terminalsCount)
{
    Expression *expression = malloc(sizeof(Expression));
    NonTerminal *nonTerminal;

    expression->node = NULL;
    expression->nodeKey = ZERO;

    if (isTerminal)
    {
        expression->isTerminal = TRUE;
        expression->value.terminal = (*terminalsCount)++;

        PushLinearLinkedList(&grammar->expressions);
        grammar->expressions->info = expression;
    }
    else
    {
        nonTerminal = malloc(sizeof(NonTerminal));
        nonTerminal->rules = NULL;

        expression->isTerminal = FALSE;
        expression->value.nonTerminal = nonTerminal;

        PushLinearLinkedList(&grammar->expressions);
        grammar->expressions->info = expression;

        PushLinearLinkedList(&grammar->nonTerminals);
        grammar->nonTerminals->info = nonTerminal;
    }

    return expression;
}

void WriteSemantic(char *ruleName, FILE *file, int ruleNum, char *semanticAction, int expressions)
{
    fprintf(file, "AbstractSyntaxTreeNode* Semantic_%d(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)\n{\n", ruleNum);
    fprintf(file, "// %s\n", ruleName);
    fprintf(file, "AbstractSyntaxTreeNode *_$_$ = NULL;\n");

    for (; expressions; expressions--)
    {
        fprintf(file, "AbstractSyntaxTreeNode *_$%d = PopStack(semanticStack);\n", expressions - 1);
    }

    fputs(semanticAction, file);
    fprintf(file, "\nreturn _$_$;\n}\n", semanticAction);
}

int strcount(char *str, char ch)
{
    int count = ZERO;

    for (; *str; str++) count += *str == ch;

    return count;
}

void BuildGrammarFromFile(Grammar *grammar)
{
    BOOL isTerminal = TRUE;
    int terminalsCount = ZERO;
    FILE *grammar_defs = fopen(GRAMMAR_DEFINITIONS, "rt");
    FILE *grammar_rules = fopen(GRAMMAR_RULES, "rt");
    FILE *semantics = fopen(SEMANTICS_FILE, "wt");
    FILE *semantics_h = fopen(SEMANTICS_H_FILE, "wt");
    StringsDictionary *tbl = malloc(sizeof(StringsDictionary));

    InitStringsDictionary(tbl);

    char line[MAX_RULE_LENGTH];
    char *nonTerminal;
    char *expressions;
    char *semantic;

    fprintf(semantics, "#include \"semantics.h\"\n");

    fgets(line, MAX_DEFINITION_LENGTH, grammar_defs);

    if (UPDATE_HEADER)
        fprintf(semantics_h, "enum {");

    while (!feof(grammar_defs))
    {
        if (*line == '\n')
        {
            isTerminal = FALSE;
            fgets(line, MAX_DEFINITION_LENGTH, grammar_defs);
            continue;
        }

        if (isTerminal)
        {
            char *terminal = strtok(line, " ");

            sscanf(terminal, "%s", terminal);
            
            if (UPDATE_HEADER)
                fprintf(semantics_h, "%s, ", terminal);
        }

        sscanf(line, "%s", line);
        InsertStringsDictionary(tbl, line, MakeExpression(grammar, line, isTerminal, &terminalsCount));

        fgets(line, MAX_DEFINITION_LENGTH, grammar_defs);
    }

    if (UPDATE_HEADER)
    {
        fprintf(semantics_h, "TOKENS_NUM };\n#define PATTERNS {");

        fseek(grammar_defs, ZERO, SEEK_SET);
        fgets(line, MAX_DEFINITION_LENGTH, grammar_defs);

        isTerminal = TRUE;

        while (isTerminal)
        {
            if (*line == '\n')
            {
                isTerminal = !isTerminal;
                fgets(line, MAX_DEFINITION_LENGTH, grammar_defs);
                continue;
            }

            char *terminal = strtok(line, " ");
            char *pattern = strtok(NULL, "\n");

            if (pattern)
            {
                fprintf(semantics_h, "%s, ", pattern);
            }
            
            fgets(line, MAX_DEFINITION_LENGTH, grammar_defs);
        }

        fprintf(semantics_h, "\"\"}\n");
    }

    if (UPDATE_HEADER)
    {
            fprintf(semantics_h, "#define _SEMANTICS\n");
            fprintf(semantics_h, "#ifndef _COMMON_MACROS_H\n\
            #include \"../libs/CommonMacros.h\"\n\
            #endif\n\
    \n\
            #ifndef _ABSTRACT_SYNTAX_TREE_H\n\
                #include \"../libs/AbstractSyntaxTree.h\"\n\
            #endif\n\
    \n\
            #ifndef _STACK_H\n\
                #include \"../libs/Stack.h\"\n\
            #endif\n\
    \n\
            #ifndef _GRAMMAR_H\n\
                #include \"../libs/Grammar.h\"\n\
            #endif\n\
    \n\
            #ifndef _TYPE_SYSTEM_H\n\
                #include \"../libs/TypeSystem.h\"\n\
            #endif\n\
    \n\
            #ifndef _ERROR_HANDLER_H\n\
                #include \"../source/ErrorHandler.h\"\n\
            #endif\n\
    \n\
            #ifndef _ACTIONS\n\
                #include \"actions.h\"\n\
            #endif\n");
    }

    fgets(line, MAX_RULE_LENGTH, grammar_rules);
    fputs("AbstractSyntaxTreeNode *DefaultSemanticAction(void *scopeStack, Stack *semanticStack, ErrorHandler *errors)"
          "{ return PopStack(semanticStack); }\n", semantics);

    int rule = ZERO;

    while (!feof(grammar_rules))
    {
        nonTerminal = strtok(line, ":");
        expressions = strtok(NULL, "@");
        semantic = strtok(NULL, "@");

        if (semantic)
        {
            WriteSemantic(nonTerminal, semantics, rule, semantic, strcount(expressions, ' '));
        }

        rule++;
        fgets(line, MAX_RULE_LENGTH, grammar_rules);
    }

    fprintf(semantics, "void AssignActions(Grammar *g)\n{\n"
          "unsigned short currentRule = ZERO;\n"
          "LinearLinkedListNode *nonTerminalsPtr, *rulesPtr;\n"
          "Rule *rules[%d];\n"
          "for (nonTerminalsPtr = g->nonTerminals; nonTerminalsPtr; nonTerminalsPtr = nonTerminalsPtr->nextNode)\n{\n"
          "for (rulesPtr = ((NonTerminal*)nonTerminalsPtr->info)->rules; rulesPtr; rulesPtr = rulesPtr->nextNode)\n{\n"
          ""
          "rules[currentRule++] = rulesPtr->info;\n}\n}\n", rule);

    fseek(grammar_rules, ZERO, SEEK_SET);
    fgets(line, MAX_RULE_LENGTH, grammar_rules);

    rule = ZERO;

    while (!feof(grammar_rules))
    {
        nonTerminal = strtok(line, ":");
        expressions = strtok(NULL, "@");        
        semantic = strtok(NULL, "@");

        NonTerminal *current = ((Expression*)LookupStringsDictionary(tbl, nonTerminal))->value.nonTerminal;
        Rule *r = malloc(sizeof(Rule));
        Stack temp;

        InitStack(&temp);

        r->expressions = NULL;
        r->nonTerminal = current;
        r->semanticAction = NULL;
        r->id = semantic ? rule : FALSE;

        for (expressions = strtok(expressions, " ") ; expressions; expressions = strtok(NULL, " "))
        {
            sscanf(expressions, "%s", expressions);
            PushStack(&temp, LookupStringsDictionary(tbl, expressions));
        }

        while (!IsEmptyStack(&temp))
        {
            PushLinearLinkedList(&r->expressions);
            r->expressions->info = PopStack(&temp);
        }

        PushLinearLinkedList(&current->rules);
        current->rules->info = r;

        rule++;
        fgets(line, MAX_RULE_LENGTH, grammar_rules);
    }
    
    fseek(grammar_rules, ZERO, SEEK_SET);
    fgets(line, MAX_RULE_LENGTH, grammar_rules);

    LinearLinkedListNode *nonTerminalsPtr, *rulesPtr;
    int rules[rule];
    rule = ZERO;

    for (nonTerminalsPtr = grammar->nonTerminals; nonTerminalsPtr; nonTerminalsPtr = nonTerminalsPtr->nextNode)
    {
        for (rulesPtr = ((NonTerminal*)nonTerminalsPtr->info)->rules; rulesPtr; rulesPtr = rulesPtr->nextNode)
        {
            if (((Rule*)rulesPtr->info)->id)
            {
                fprintf(semantics, "rules[%d]->semanticAction = Semantic_%d;\n", rule, ((Rule*)rulesPtr->info)->id);
            }

            rule++;
        }
    }

    rule = ZERO;

    fputs("}\n", semantics);

    fclose(grammar_defs);
    fclose(grammar_rules);
    fclose(semantics);

    EmptyStringsDictionary(tbl);

    if (UPDATE_HEADER)
        fclose(semantics_h);

    return grammar;
}