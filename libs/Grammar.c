// Grammar.c

#include "Grammar.h"

#define SET_BIT(set, offset) ((set |= (((unsigned long)ONE << offset))))

void InitGrammar(Grammar *grammar)
{
    InitLinearLinkedList(&grammar->nonTerminals);
    InitLinearLinkedList(&grammar->expressions);
}

//-----------------------------------------------------------------------------
//                                  Initial Non-Terminal                                     
//                                  --------------------                                 
//                                                                             
// General      : The function finds the initial non terminal of 
//                the inital rule of a grammar.                                 
//                                                                             
// Parameters   :                                                              
//      grammar - The grammar (In)                                     
//                                                                             
// Return Value : The initial non terminal.             
//-----------------------------------------------------------------------------
// T(n) = d
//-----------------------------------------------------------------------------
NonTerminal* InitialNonTerminal(Grammar *grammar)
{
    return (grammar->nonTerminals->info);
}

//-----------------------------------------------------------------------------
//                                      Initial Rule                                     
//                                      ------------                               
//                                                                             
// General      : The function finds the initial rule of a grammar.                                 
//                                                                             
// Parameters   :                                                              
//      grammar - The grammar (In)                                     
//                                                                             
// Return Value : The initial rule.             
//-----------------------------------------------------------------------------
// T(n) = d
//-----------------------------------------------------------------------------
Rule* InitialRule(Grammar *grammar)
{
    return (InitialNonTerminal(grammar)->rules->info);
}

//-----------------------------------------------------------------------------
//                                      EOD Terminal                                    
//                                      ------------                               
//                                                                             
// General      : The function finds the EOD terminal 
//                (which appears at the end of every legal unit) of a grammar.                                 
//                                                                             
// Parameters   :                                                              
//      grammar - The grammar (In)                                     
//                                                                             
// Return Value : The EOD terminal.             
//-----------------------------------------------------------------------------
// T(n) = d
//-----------------------------------------------------------------------------
Expression* EODTerminal(Grammar *grammar)
{
    return (grammar->expressions->info);
}

//-----------------------------------------------------------------------------
//                              Compare Non-Terminals                                     
//                              ---------------------                                  
//                                                                             
// General      : The function compares two non terminals.                                 
//                                                                             
// Parameters   :                                                              
//      first - The first non terminal (In)                                     
//      second - The second non terminal (In)                                     
//                                                                             
// Return Value : Whether the expressions are eqaul.             
//-----------------------------------------------------------------------------
// T(n) = d 
//-----------------------------------------------------------------------------
BOOL CompareNonTerminals(ExpressionValue first, ExpressionValue second)
{
    return (first.nonTerminal == second.nonTerminal);
}

//-----------------------------------------------------------------------------
//                              Compare Terminals                                     
//                              -----------------                              
//                                                                             
// General      : The function compares two terminals.                                 
//                                                                             
// Parameters   :                                                              
//      first - The first terminal (In)                                     
//      second - The second terminal (In)                                     
//                                                                             
// Return Value : Whether the expressions are equal.             
//-----------------------------------------------------------------------------
// T(n) = d 
//-----------------------------------------------------------------------------
BOOL CompareTerminals(ExpressionValue first, ExpressionValue second)
{
    return (first.terminal == second.terminal);
}

//-----------------------------------------------------------------------------
//                                  Expression Key                                     
//                                  --------------                                  
//                                                                             
// General      : The key function for an expression.                                 
//                                                                             
// Parameters   :                                                              
//      expression - The expression (In)                                     
//                                                                             
// Return Value : The expression's key.             
//-----------------------------------------------------------------------------
// T(n) = d
//-----------------------------------------------------------------------------
unsigned long ExpressionKey(Expression *expression)
{
    return ((unsigned long)expression);
}

//-----------------------------------------------------------------------------
//                              Compare Expressions                                     
//                              -------------------                            
//                                                                             
// General      : The function compares two expressions.                                 
//                                                                             
// Parameters   :                                                              
//      first - The first expression (In)                                     
//      second - The second expression (In)                                     
//                                                                             
// Return Value : Whether the first is greater.             
//-----------------------------------------------------------------------------
// T(n) = d 
//-----------------------------------------------------------------------------
BOOL CompareExpressions(Expression *first, Expression *second)
{
    return (first == second);
}

void ExpressionFirstSet(Expression *expression)
{
    Expression *nextExpression;
    LinearLinkedListNode *rulesPtr;

    if (expression->isTerminal)
    {
        SET_BIT(expression->firstSet, expression->value.terminal);
        return;
    }

    for (rulesPtr = expression->value.nonTerminal->rules; rulesPtr; rulesPtr = rulesPtr->nextNode)
    {
        nextExpression = ((Rule*)rulesPtr->info)->expressions->info;

        if (!nextExpression->firstSet && nextExpression != expression)
        {
            ExpressionFirstSet(nextExpression);
        }
        
        expression->firstSet |= nextExpression->firstSet;
    }
}

void GrammarFirstSet(Grammar *grammar)
{
    LinearLinkedListNode *ptr;

    for (ptr = grammar->expressions; ptr; ptr = ptr->nextNode)
    {
        ((Expression*)ptr->info)->firstSet = ZERO;
    }

    for (ptr = grammar->expressions; ptr; ptr = ptr->nextNode)
    {
        !((Expression*)ptr->info)->firstSet ?
            ExpressionFirstSet(ptr->info) : ZERO;
    }
}

Item* NextItem(Item *item)
{
    Item *next = malloc(sizeof(Item));

    next->rule = item->rule;
    next->lookahead = item->lookahead;
    next->dotPosition = item->dotPosition->nextNode;

    return (next);
}

Item* InitialItem(Rule *rule, TokenType lookahead)
{
    Item *item = malloc(sizeof(Item));

    item->rule = rule;
    item->dotPosition = rule->expressions;
    item->lookahead = lookahead;

    return (item);
}

void FreeRule(Rule *rule)
{
    EmptyLinearLinkedList(&rule->expressions, NULL);
    free(rule);
}

void FreeNonTerminal(NonTerminal *nonTerminal)
{
    EmptyLinearLinkedList(&nonTerminal->rules, FreeRule);
    free(nonTerminal);
}

void FreeGrammar(Grammar *grammar)
{
    EmptyLinearLinkedList(&grammar->nonTerminals, FreeNonTerminal);
    EmptyLinearLinkedList(&grammar->expressions, free);
}