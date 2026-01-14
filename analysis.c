#include "gocheck.h"

#include <stdio.h>

struct AnalysisResult analyze_ast(const struct AST *node)
{
        struct AnalysisResult res = { 0 };

        res.nesting = nesting_level(node);

        return res;
}

void analyze_and_print(FILE *where, const struct AST *code)
{
        for (; code != nullptr; code = code->next) {
                if (code->type == AST_Func) {
                        fprintf(where,
                                "@ Walking function %s\n",
                                code->sval);
                        analyze_and_print(where, code->rhs);
                }

                struct AnalysisResult res = analyze_ast(code);
                if (res.nesting >= 3)
                        fprintf(where,
                                "! Deep nesting (%u times)\n",
                                res.nesting);
        }
}

