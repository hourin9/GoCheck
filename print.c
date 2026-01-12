#include "gocheck.h"

#include <stdio.h>

void recursive_print(FILE *where, const struct AST *node, int depth)
{
        if (!node)
                return;

        fprintf(where, "%*s[%d]", depth, "", node->type);
        if (node->sval)
                fprintf(where, "sval: %s", node->sval);
        if (node->typeid)
                fprintf(where, "type: %s", node->typeid);
        fprintf(where, "\n");

        if (node->lhs) {
                fprintf(where, "%*sLHS:\n", depth, "");
                recursive_print(where, node->lhs, depth + 4);
        }
        if (node->rhs) {
                fprintf(where, "%*sRHS:\n", depth, "");
                recursive_print(where, node->rhs, depth + 4);
        }

        if (node->next)
                recursive_print(where, node->next, depth);
}
