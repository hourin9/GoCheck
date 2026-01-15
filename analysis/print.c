#include "../gocheck.h"

void print_analysis_result(FILE *where
        , const struct AnalysisResult *what
        , const struct AST *who)
{
        if (what->nesting >= 3)
                fprintf(where,
                        "! Deep nesting (%u times)\n",
                        what->nesting);

        if (what->bad_global)
                fprintf(where,
                        "! Variable declaration in global scope\n"
                        );

        if (what->magic_number)
                fprintf(where,
                        "? Magic number detected (%g)\n",
                        what->magic_number->f32);

        if (what->always_return == -1)
                fprintf(where,
                        "! Function %s does not return from all paths\n",
                        who->sval);
}

