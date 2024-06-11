#include "TypeSystem.h"

void InitTypeSystem(StringsDictionary *symbolTable)
{
    Symbol *currentSymbol;
    TypeKind currentType;
    char *typeNames[] = TYPE_NAMES;
    unsigned short typeSizes[] = TYPE_SIZES;

    for (currentType = ZERO; currentType != BASE_TYPES_COUNT; currentType++)
    {
        MakeSymbol(&currentSymbol);
        MakeType(&currentSymbol->_type, FALSE);

        currentSymbol->name = typeNames[currentType];
        ((Type*)currentSymbol->_type)->size = typeSizes[currentType];
        ((Type*)currentSymbol->_type)->type = currentType;
    
        InsertStringsDictionary(symbolTable, currentSymbol->name, currentSymbol);
    }
}

void MakeType(Type **type, BOOL isStruct)
{
    *type = malloc(sizeof(Type));

    (*type)->size = ZERO;
    (*type)->baseType = (*type)->structDef = (*type)->fields = NULL;
    
    if (isStruct)
        InitStringsDictionary((*type)->fields);
}

void AddField(Type *source, char *name, unsigned short offset, Type *type)
{
    Field *field = malloc(sizeof(Field));

    field->name = name;
    field->type = type;
    field->offset = offset;

    InsertStringsDictionary(source->fields, name, field);
}

Field *FindField(Type *source, char *name)
{
    while (source->baseType) source = source->baseType;
    
    return LookupStringsDictionary(source->fields, name);
}