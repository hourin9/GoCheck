#include "../gocheck.h"

#include <stdbool.h>
#include <stdio.h>

// TODO: use Analysis context struct instead of this.
static bool _globalScope = true;

struct AnalysisResult analyze_ast(const struct AST *node)
{
        struct AnalysisResult res = { 0 };

        if (node->type == AST_Func) {
                if (node->typeid != nullptr)
                        res.always_return = leads_to_rome(node->rhs)
                                ? 1
                                : -1
                                ;

                return res;
        }

        res.nesting = nesting_level(node);

        res.bad_global = _globalScope
                && (node->type == AST_VarDecl);

        res.magic_number = seek_magic_number(node);

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

                        fprintf(where,
                                "@ Exit function %s\n",
                                code->sval);
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

                if (res.magic_number)
                        fprintf(where,
                                "? Magic number detected (%g)\n",
                                res.magic_number->f32);

                if (res.always_return == -1)
                        fprintf(where,
                                "! Function %s does not return from all paths\n",
                                code->sval);
        }
}

