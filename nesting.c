#include "gocheck.h"

static size_t _travel_side(const struct AST *root)
{
        if (!root)
                return 0;

        if (root->type == AST_If)
                return nesting_level(root);

        size_t max_depth = 0;
        const struct AST *cur = root->next;
        for (; cur != nullptr; cur = cur->next) {
                size_t depth = _travel_side(cur);
                if (depth > max_depth)
                        max_depth = depth;
        }

        return max_depth;
}

size_t nesting_level(const struct AST *root)
{
        if (!root || root->type != AST_If)
                return 0;

        size_t do_side = _travel_side(root->then);

        size_t otherwide_side = 0;
        const struct AST *otherwise = root->otherwise;
        if (otherwise)
                otherwide_side = (otherwise->type == AST_If)
                        ? nesting_level(otherwise) - 1
                        : _travel_side(otherwise);

        return 1 + ((do_side > otherwide_side) ? do_side : otherwide_side);
}

