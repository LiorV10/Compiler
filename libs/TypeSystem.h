// TypeSystem.h

#define _TYPE_SYSTEM_H

#ifndef _SYMBOL_TABLE_H
    #include "SymbolTable.h"
#endif

typedef enum {
                CHAR_TYPE, SHORT_TYPE, INTEGER_TYPE, LONG_TYPE, FLOAT_TYPE, 
                DOUBLE_TYPE, VOID_TYPE, BASE_TYPES_COUNT, POINTER_TYPE, ARRAY_TYPE,
                STRUCT_TYPE, TYPES_COUNT
            } TypeKind;

#define POINTER_SIZE 8

#define TYPE_NAMES {"char", "short", "int", "long", "float", "double", "void"}
#define TYPE_SIZES {1,      2,       4,     8,      4,        8,        0    , 0, POINTER_SIZE}

typedef struct Type Type;

struct Type
{
    TypeKind type;
    unsigned short size;
    Type *baseType;
    Symbol *structDef;
    StringsDictionary *fields;
};

typedef struct 
{
    char *name;
    unsigned short offset;
    Type *type;
} Field;

void InitTypeSystem(StringsDictionary *symbolTable);
void MakeType(Type **type, BOOL isStruct);
void AddField(Type *source, char *name, unsigned short offset, Type *type);
Field *FindField(Type *source, char *name);
Type* SetBaseType(Type **type, Type *base);
void CalculateArraySize(Type *arrayType);