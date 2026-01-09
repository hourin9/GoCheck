#include <stdio.h>

#include "gram.tab.h"
#include "gocheck.h"

int main(int argc, char **argv)
{
        struct AST *test = node(AST_If, nullptr, nullptr);
        test->next = node(AST_If, nullptr, nullptr);
        printf("%zu\n", nesting_level(test));

        yyparse();
        return 0;
}

