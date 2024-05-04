import os
import re

def evaluate(action: str, expressions: int):
    body = '{\n'
    body += 'AbstractSyntaxTreeNode *result = NULL;\n'

    for i in range(expressions, -1, -1):
        body += f'AbstractSyntaxTreeNode *_${i} = PopStack(semanticStack);\n'

    body += action.replace('$$', 'result').replace('$', '_$')
    body += '\nreturn result;\n}'
    return body


base_path = os.path.dirname(os.path.realpath(__file__))
definitions = f"{base_path}/grammar_definitions"
grammar = f"{base_path}/grammar_rules"
output = f"{base_path}/GrammarConstruction.c"

rules_num = 0
is_token = False

grammar_rules = ''
semantic_actions = ''

semantic_actions += f'''AbstractSyntaxTreeNode* DefaultSemanticAction(void *scopeStack, Stack *semanticStack)
                {evaluate("$$ = $0;", 0)}
            '''

grammar_rules += '''void InitGrammar(Grammar *grammar)
{
    InitLinearLinkedList(&grammar->nonTerminals);
    InitLinearLinkedList(&grammar->expressions);

    
'''

with open(definitions, 'r') as file:
    for line in reversed(file.readlines()):
        line = line.replace('\n', '')
        if line == '':
            is_token = True
            continue
        
        if is_token:
            grammar_rules += f'''Expression *{line}expression = malloc(sizeof(Expression));
PushLinearLinkedList(&grammar->expressions);
grammar->expressions->info = {line}expression;
{line}expression->isTerminal = TRUE;
{line}expression->value.terminal = {line};
{line}expression->visited = FALSE;
{line}expression->node = NULL;\n'''
        else:
            grammar_rules += f'''NonTerminal *{line} = malloc(sizeof(NonTerminal));
PushLinearLinkedList(&grammar->nonTerminals);
grammar->nonTerminals->info = {line};
{line}->name = "{line}";
{line}->visited = FALSE;
InitLinearLinkedList(&{line}->rules);\n'''
            
            grammar_rules += f'''Expression *{line}expression = malloc(sizeof(Expression));
PushLinearLinkedList(&grammar->expressions);
grammar->expressions->info = {line}expression;
{line}expression->isTerminal = FALSE;
{line}expression->value.nonTerminal = {line};
{line}expression->visited = FALSE;
{line}expression->node = NULL;\n'''

with open(grammar, 'r') as file:
    for line in file.readlines():
        line = line.replace('\n', '').strip()
        lhs, rhs = line.split(':')
        grammar_rules += f'''Rule *rule_{rules_num} = malloc(sizeof(Rule));
        InitLinearLinkedList(&rule_{rules_num}->expressions);
        rule_{rules_num}->semanticAction = NULL;
        rule_{rules_num}->nonTerminal = {lhs};\n'''

        if '{' in rhs:
            rhs, semantic = rhs.split('{')
            semantic_actions += f'''AbstractSyntaxTreeNode* semantic_{rules_num}(void *scopeStack, Stack *semanticStack)
                {evaluate(semantic[:-1], rhs.strip().count(' '))}
            '''
            grammar_rules += f'rule_{rules_num}->semanticAction = semantic_{rules_num};\n'

        rhs = rhs.strip()

        for expression in rhs.split(' ')[::-1]:
            grammar_rules += f'PushLinearLinkedList(&rule_{rules_num}->expressions);\nrule_{rules_num}->expressions->info = {expression}expression;\n'

        grammar_rules += f'PushLinearLinkedList(&{lhs}->rules);\n{lhs}->rules->info = rule_{rules_num};\n'
        rules_num += 1

grammar_rules += '}'

with open(output, 'w') as file:
    file.write(semantic_actions)
    file.write(grammar_rules)