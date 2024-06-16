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
        MakeType(&currentSymbol->type, FALSE);

        currentSymbol->name = typeNames[currentType];
        ((Type*)currentSymbol->type)->size = typeSizes[currentType];
        ((Type*)currentSymbol->type)->type = currentType;
    
        InsertStringsDictionary(symbolTable, currentSymbol->name, currentSymbol);
    }
}

void MakeType(Type **type, BOOL isStruct)
{
    *type = malloc(sizeof(Type));

    (*type)->size = ZERO;
    (*type)->baseType = (*type)->structDef = (*type)->fields = NULL;
    
    if (isStruct)
    {
        (*type)->fields = malloc(sizeof(StringsDictionary));
        InitStringsDictionary((*type)->fields);
    }
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
    return LookupStringsDictionary(source->fields, name);
}

Type* SetBaseType(Type **type, Type *base)
{
    Type *temp;

    for (temp = *type; temp && temp->baseType; temp = temp->baseType);

    temp ? temp->baseType = base : (*type = base);
    
    return (temp);
}

void CalculateArraySize(Type *arrayType)
{
    Type *prevBase;
    Type *type;
    Type temp;

    temp.type = POINTER_TYPE;
    temp.baseType = NULL;

    prevBase = SetBaseType(&arrayType, &temp);
    type = arrayType->baseType;

    while (type->type != POINTER_TYPE)
    {
        arrayType->size *= type->size;
        type = type->baseType;
    }

    type->baseType ? arrayType->size *= type->size : ZERO;
    prevBase->baseType = NULL;
}