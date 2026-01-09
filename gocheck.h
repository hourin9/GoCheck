#pragma once

enum ASTType {
        AST_VarDecl,
        AST_If,
        AST_For,
        AST_Id,
        AST_StmtList,
};

struct AST {
        enum ASTType type;
        char *sval;
        struct AST *lhs, *rhs;
        struct AST *next;
};

struct AST *node(enum ASTType, struct AST *lhs, struct AST *rhs);
struct AST *leaf(enum ASTType, char *sval);

