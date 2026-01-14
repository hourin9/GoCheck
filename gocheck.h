#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

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
        AST_Func,
        AST_StringLiteral,
        AST_NumericLiteral,
};

struct AST {
        enum ASTType type;
        float f32;
        char *sval,
             *typeid;

        // Using separate union containing structs for statements,
        // for example struct ControlFlow, struct BinaryOp would've
        // been better, but I don't want to touch it yet.
        //
        // Therefore I'm going with anonymous union to create aliases,
        // making the code at least easier to be figured out.

        union {
                struct AST *lhs,
                           *cond;
        };

        union {
                struct AST *rhs,
                           *then;
        };

        union {
                struct AST *otherwise;
        };

        struct AST *next;
};

void recursive_print(FILE*, const struct AST*, int depth);

struct AST *node(enum ASTType, struct AST *lhs, struct AST *rhs);
struct AST *leaf(enum ASTType, char *sval);
struct AST *number(float);

struct AST *package_node(char *name);
struct AST *import_node(char *name);
struct AST *if_node(struct AST *condition, struct AST *then);
struct AST *call_node(struct AST *callee, struct AST *argv);
struct AST *decl_node(struct AST *id_list, struct AST *expr);
struct AST *func_node
        ( char *name
        , char *type
        , struct AST *argv
        , struct AST *body
        );

// TODO: better solution that can carry analysis context.
struct AnalysisResult {
        // uint8_t is more than enough. No one nests more than
        // 100 times.
        uint8_t nesting;
};

// Analyzes one node.
struct AnalysisResult analyze_ast(const struct AST*);

// Walks the entire code tree and prints diagnosis result.
void analyze_and_print(FILE *where, const struct AST*);

// Returns maximum nested levels in branching statement
// excluding loops.
// Returns 0 if given AST node isn't an AST_If
size_t nesting_level(const struct AST*);

