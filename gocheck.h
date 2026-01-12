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

struct AST *if_node(struct AST *condition, struct AST *then);
struct AST *call_node(struct AST *callee, struct AST *argv);

// Returns maximum nested levels in branching statement
// excluding loops.
// Returns 0 if given AST node isn't an AST_If
size_t nesting_level(const struct AST*);

