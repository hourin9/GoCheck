#include "../gocheck.h"

bool leads_to_rome(const struct AST *func)
{
        if (!func)
                return false;

        if (func->type == AST_Return)
                return true;

        /*
         * if cond {
         *      return true;
         * } else cond {
         *      return something;
         * } else {
         *      return somethingelse;
         * }
         */
        if (func->type == AST_If) {
                if (!func->otherwise)
                        return false;

                return leads_to_rome(func->then) &&
                       leads_to_rome(func->otherwise);
        }

        if (func->type == AST_Func)
                return false;

        const struct AST *cur = func->rhs;
        while (cur != nullptr) {
                if (leads_to_rome(cur))
                        return true;
                cur = cur->next;
        }

        return false;
}

