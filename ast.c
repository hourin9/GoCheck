#include "gocheck.h"

#include <stdlib.h>

struct AST *node(enum ASTType t, struct AST *lhs, struct AST *rhs)
{
        struct AST *node = malloc(sizeof(*node));
        *node = (struct AST){ 0 };
        node->type = t;
        node->lhs = lhs;
        node->rhs = rhs;
        return node;
}

struct AST *leaf(enum ASTType t, char *sval)
{
        struct AST *node = malloc(sizeof(*node));
        *node = (struct AST){ 0 };
        node->type = t;
        node->sval = sval;
        return node;
}

struct AST *if_node(struct AST *condition, struct AST *then)
{
        return node(AST_If, condition, then);
}

struct AST *call_node(struct AST *callee, struct AST *argv)
{
        return node(AST_Call, callee, argv);
}

struct AST *package_node(char *name)
{
        return leaf(AST_Package, name);
}

struct AST *import_node(char *name)
{
        return leaf(AST_Import, name);
}

struct AST *decl_node(struct AST *id_list, struct AST *expr)
{
        return node(AST_VarDecl, id_list, expr);
}

struct AST *func_node
        ( char *name
        , char *type
        , struct AST *argv
        , struct AST *body
        )
{
        struct AST *func = node(AST_Func, argv, body);
        func->sval = name;
        func->typeid = type;
        return func;
}

