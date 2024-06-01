
#include "Construction.h"

static BOOL terminals = TRUE;
static int x = 0;

Expression *MakeExpression(Grammar *g, char *line)
{
    Expression *e = malloc(sizeof(Expression));

    e->firstSet = ZERO;
    e->node = NULL;
    e->nodeKey = ZERO;

    if (terminals)
    {
        e->isTerminal = TRUE;
        e->value.terminal = x++;

        PushLinearLinkedList(&g->expressions);
        g->expressions->info = e;
    }
    else
    {
        NonTerminal *nt = malloc(sizeof(NonTerminal));

        nt->name = strdup(line);
        nt->rules = NULL;

        e->isTerminal = FALSE;
        e->value.nonTerminal = nt;

        PushLinearLinkedList(&g->expressions);
        g->expressions->info = e;

        PushLinearLinkedList(&g->nonTerminals);
        g->nonTerminals->info = nt;
    }

    return e;
}

void WriteSemantic(char *a, FILE *f, int n, char *s, int m)
{
    fprintf(f, "AbstractSyntaxTreeNode* Semantic_%d(void *scopeStack, Stack *semanticStack)\n{\n", n);
    fprintf(f, "// %s\n", a);
    fprintf(f, "AbstractSyntaxTreeNode *_$_$ = NULL;\n");

    for (; m; m--)
    {
        fprintf(f, "AbstractSyntaxTreeNode *_$%d = PopStack(semanticStack);\n", m - 1);
    }

    fputs(s, f);
    fprintf(f, "\nreturn _$_$;\n}\n", s);
}

int strct(char *s, char c)
{
    int count = 0;

    for (; *s; s++) count += *s == c;

    return count;
}

Grammar BUILD()
{
    FILE *grammar_defs = fopen(GRAMMAR_DEFINITIONS, "rt");
    FILE *grammar_rules = fopen(GRAMMAR_RULES, "rt");
    FILE *semantics = fopen(SEMANTICS_FILE, "wt");

    fprintf(semantics, "#include \"semantics.h\"\n");
    // fprintf(semantics, "#define _SEMANTICS\ntypedef enum {");

    StringsDictionary tbl;

    InitStringsDictionary(&tbl);

    char line[512] = {ZERO};
    char line_[512] = {ZERO};

    char *nonTerminal;
    char *expressions;
    char *semantic;

    Grammar g = {.expressions = NULL, .nonTerminals = NULL};

    fgets(line, 256, grammar_defs);

    while (!feof(grammar_defs))
    {
        if (*line == '\n')
        {
            terminals = !terminals;
            fgets(line, 256, grammar_defs);
            continue;
        }

        if (terminals)
        {
            char *terminal = strtok(line, " ");

            sscanf(terminal, "%s", terminal);
            // fprintf(semantics, "%s, ", terminal);
        }

        sscanf(line, "%s", line_);
        InsertStringsDictionary(&tbl, line_, MakeExpression(&g, line_));        
    
        // puts(line_);

        fgets(line, 256, grammar_defs);
    }

    // fprintf(semantics, "TOKENS_NUM } TokenType;\n#define PATTERNS {");

    fseek(grammar_defs, ZERO, SEEK_SET);
    fgets(line, 256, grammar_defs);

    terminals = TRUE;

    while (terminals)
    {
        if (*line == '\n')
        {
            terminals = !terminals;
            fgets(line, 256, grammar_defs);
            continue;
        }

        char *terminal = strtok(line, " ");
        char *pattern = strtok(NULL, "\n");

        if (pattern)
        {
           // fprintf(semantics, "%s, ", pattern);
        }
        
        fgets(line, 256, grammar_defs);
    }

    // fprintf(semantics, "\"\"}\n");

    fgets(line, 512, grammar_rules);

    fputs("AbstractSyntaxTreeNode *DefaultSemanticAction(void *scopeStack, Stack *semanticStack)"
          "{ return PopStack(semanticStack); }\n", semantics);

    // return;

    int rule = 0;

    while (!feof(grammar_rules))
    {
        nonTerminal = strtok(line, ":");
        expressions = strtok(NULL, "{");
        semantic = strtok(NULL, "}");

        // puts(nonTerminal);
        // puts(expressions);

        if (semantic)
        {
            WriteSemantic(nonTerminal, semantics, rule, semantic, strct(expressions, ' '));
            // puts(semantic);
        }

        expressions = strtok(expressions, " ");

        Expression *e = LookupStringsDictionary(&tbl, nonTerminal);

        // printf("RULE_%d: %s\n", rule, e->value.nonTerminal->name);

        // puts("");

        rule++;
        fgets(line, 512, grammar_rules);
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
    fgets(line, 512, grammar_rules);

    rule = ZERO;

    while (!feof(grammar_rules))
    {
        nonTerminal = strtok(line, ":");
        expressions = strtok(NULL, "{");        
        semantic = strtok(NULL, "}");

        NonTerminal *current = ((Expression*)LookupStringsDictionary(&tbl, nonTerminal))->value.nonTerminal;
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
            PushStack(&temp, LookupStringsDictionary(&tbl, expressions));
        }

        while (!IsEmptyStack(&temp))
        {
            PushLinearLinkedList(&r->expressions);
            r->expressions->info = PopStack(&temp);
        }

        PushLinearLinkedList(&current->rules);
        current->rules->info = r;

        rule++;
        fgets(line, 512, grammar_rules);
    }
    
    fseek(grammar_rules, ZERO, SEEK_SET);
    fgets(line, 512, grammar_rules);

    LinearLinkedListNode *nonTerminalsPtr, *rulesPtr;
    int rules[rule];
    rule = ZERO;


    for (nonTerminalsPtr = g.nonTerminals; nonTerminalsPtr; nonTerminalsPtr = nonTerminalsPtr->nextNode)
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

    if (0)
    while (!feof(grammar_rules))
    {
        nonTerminal = strtok(line, ":");
        expressions = strtok(NULL, "@");        
        semantic = strtok(NULL, "@");

        NonTerminal *current = ((Expression*)LookupStringsDictionary(&tbl, nonTerminal))->value.nonTerminal;
        Rule *r = malloc(sizeof(Rule));
        Stack temp;

        if (semantic)
        {
            fprintf(semantics, "rules[%d]->semanticAction = Semantic_%d;\n", rule, rule);
        }

        rule++;
        fgets(line, 512, grammar_rules);
    }

    fputs("}\n", semantics);

    fclose(grammar_defs);
    fclose(grammar_rules);
    fclose(semantics);

    return g;
}