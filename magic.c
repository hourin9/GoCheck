#include "gocheck.h"

static bool _qualifies_as_magic_number(float f32)
{
        int ui32 = (unsigned int)f32;
        return (f32 != (int)f32) ||
                ((ui32 != 0) && (ui32 != 1) && (ui32 != 2))
                ;
}

const struct AST *seek_magic_number(const struct AST *root)
{
        if (!root)
                return nullptr;

        if (root->type == AST_ConstDecl)
                return nullptr;

        if (root->type == AST_NumericLiteral)
                if (_qualifies_as_magic_number(root->f32))
                        return root;

        const struct AST *found = nullptr;

        found = seek_magic_number(root->lhs);
        if (found)
                return found;

        found = seek_magic_number(root->rhs);
        if (found)
                return found;

        found = seek_magic_number(root->otherwise);
        if (found)
                return found;

        return nullptr;
}

