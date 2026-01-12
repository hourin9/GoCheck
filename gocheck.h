#pragma once

#include <stddef.h>

enum ASTType {
        AST_Invalid,
        AST_VarDecl,
        AST_If,
        AST_For,
        AST_Id,
        AST_StmtList,
        AST_Call,
        AST_Package,
        AST_Import,
};

struct AST {
        enum ASTType type;
        char *sval,
             *typeid;
        struct AST *lhs, *rhs;
        struct AST *next;
};

struct AST *node(enum ASTType, struct AST *lhs, struct AST *rhs);
struct AST *leaf(enum ASTType, char *sval);

struct AST *package_node(char *name);
struct AST *import_node(char *name);
struct AST *if_node(struct AST *condition, struct AST *then);
struct AST *call_node(struct AST *callee, struct AST *argv);
struct AST *decl_node(struct AST *id_list, struct AST *expr);

// Returns maximum nested levels in branching statement
// excluding loops.
// Returns 0 if given AST node isn't an AST_If
size_t nesting_level(const struct AST*);

