#include "gocheck.h"

#include <stdbool.h>
#include <stdio.h>

// TODO: use Analysis context struct instead of this.
static bool _globalScope = true;

struct AnalysisResult analyze_ast(const struct AST *node)
{
        struct AnalysisResult res = { 0 };

        res.nesting = nesting_level(node);

        res.bad_global = _globalScope
                && (node->type == AST_VarDecl);

        return res;
}

void analyze_and_print(FILE *where, const struct AST *code)
{
        for (; code != nullptr; code = code->next) {
                if (code->type == AST_Func) {
                        _globalScope = false;
                        fprintf(where,
                                "@ Walking function %s\n",
                                code->sval);
                        analyze_and_print(where, code->rhs);
                        _globalScope = true;
                }

                struct AnalysisResult res = analyze_ast(code);

                if (res.nesting >= 3)
                        fprintf(where,
                                "! Deep nesting (%u times)\n",
                                res.nesting);

                if (res.bad_global)
                        fprintf(where,
                                "! Variable declaration in global scope\n"
                                );
        }
}

