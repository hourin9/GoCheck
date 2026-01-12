#include <stdio.h>

#include "gram.tab.h"
#include "gocheck.h"

extern struct AST *parser_ast;

int main(int argc, char **argv)
{
        struct AST *test = node(AST_If, nullptr, nullptr);
        test->next = node(AST_If, nullptr, nullptr);
        printf("%zu\n", nesting_level(test));

        if (yyparse() != 0)
                return 1;

        struct AST *cur = parser_ast;
        while (cur != nullptr) {
                printf("Node of type %d\n", cur->type);
                cur = cur->next;
        }

        return 0;
}

