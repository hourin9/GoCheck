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

struct AST *number(float f32)
{
        struct AST *node = malloc(sizeof(*node));
        *node = (struct AST){ 0 };
        node->type = AST_NumericLiteral;
        node->f32 = f32;
        return node;
}

struct AST *return_node(struct AST *expr)
{
        return node(AST_Return, nullptr, expr);
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

struct AST *var_node(struct AST *id_list, struct AST *expr, char *typeid)
{
        struct AST *n = node(AST_VarDecl, id_list, expr);
        n->typeid = typeid;
        return n;
}

struct AST *const_node(struct AST *id_list, struct AST *expr, char *typeid)
{
        struct AST *n = node(AST_ConstDecl, id_list, expr);
        n->typeid = typeid;
        return n;
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

