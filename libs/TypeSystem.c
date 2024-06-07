#include "TypeSystem.h"

void AddField(Type *source, char *name, unsigned short offset, Type *type)
{
    Field *f = malloc(sizeof(Field));

    f->name = name;
    f->type = type;
    f->offset = offset;

    InsertStringsDictionary(source->fields, name, f);
}

Field *FindField(Type *source, char *name)
{
    while (source->baseType) source = source->baseType;
    
    return LookupStringsDictionary(source->fields, name);
}