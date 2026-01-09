#include "gocheck.h"

size_t nesting_level(const struct AST *root)
{
        if (root->type != AST_If)
                return 0;

        size_t max = 1;
        const struct AST *cur;
        for (cur = root->next; cur != nullptr; cur = cur->next) {
                // WIP: probably shouldn't check the AST.next.
                // I will return to this once the parser can build the AST.
                size_t child_nest_level = nesting_level(cur) + max;
                max = (max < child_nest_level) ? child_nest_level : max;
        }

        return max;
}

