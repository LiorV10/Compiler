#define _TYPE_SYSTEM_H

#ifndef _SYMBOL_TABLE_H
    #include "SymbolTable.h"
#endif

typedef enum {
                CHAR_TYPE, SHORT_TYPE, INTEGER_TYPE, LONG_TYPE, FLOAT_TYPE, 
                DOUBLE_TYPE, VOID_TYPE, POINTER_TYPE, ARRAY_TYPE, STRUCT_TYPE, 
                TYPES_COUNT
            } TypeKind;

typedef struct Type Type;

struct Type
{
    TypeKind type;
    unsigned short size;
    Type *baseType;
    Symbol *structDef;
    void *fields;
};

typedef struct 
{
    char *name;
    unsigned short offset;
    Type *type;
} Field;

Field *FindField(Type *source, char *name);
void AddField(Type *source, char *name, unsigned short offset, Type *type);