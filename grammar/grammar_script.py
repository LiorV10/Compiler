import os

base_path = os.path.dirname(os.path.realpath(__file__))
definitions = f"{base_path}/grammar_definitions"
grammar = f"{base_path}/grammar_rules"
output = f"{base_path}/GrammarConstruction.c"
rules_num = 0

output_file = open(output, 'w')
is_token = False

with open(definitions, 'r') as file:
    for line in reversed(file.readlines()):
        line = line.replace('\n', '')
        if line == '':
            is_token = True
            continue
        
        if is_token:
            output_file.write(f'''Expression *{line}expression = malloc(sizeof(Expression));
PushLinearLinkedList(&grammar->expressions);
grammar->expressions->info = {line}expression;
{line}expression->isTerminal = TRUE;
{line}expression->value.terminal = {line};
{line}expression->visited = FALSE;
{line}expression->node = NULL;\n''')
        else:
            output_file.write(f'''NonTerminal *{line} = malloc(sizeof(NonTerminal));
PushLinearLinkedList(&grammar->nonTerminals);
grammar->nonTerminals->info = {line};
{line}->name = "{line}";
{line}->visited = FALSE;
InitLinearLinkedList(&{line}->rules);\n''')
            
            output_file.write(f'''Expression *{line}expression = malloc(sizeof(Expression));
PushLinearLinkedList(&grammar->expressions);
grammar->expressions->info = {line}expression;
{line}expression->isTerminal = FALSE;
{line}expression->value.nonTerminal = {line};
{line}expression->visited = FALSE;
{line}expression->node = NULL;\n''')

with open(grammar, 'r') as file:
    for line in file.readlines():
        line = line.replace('\n', '').strip()
        lhs, rhs = line.split(':')
        output_file.write(f'Rule *rule_{rules_num} = malloc(sizeof(Rule));\nInitLinearLinkedList(&rule_{rules_num}->expressions);\nrule_{rules_num}->nonTerminal = {lhs};\n')
        for expression in rhs.split(' ')[::-1]:
            output_file.write(f'PushLinearLinkedList(&rule_{rules_num}->expressions);\nrule_{rules_num}->expressions->info = {expression}expression;\n')

        output_file.write(f'PushLinearLinkedList(&{lhs}->rules);\n{lhs}->rules->info = rule_{rules_num};\n')
        rules_num += 1

output_file.close()