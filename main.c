#include <stdio.h>

#include "gram.tab.h"
#include "gocheck.h"

extern struct AST *parser_ast;

int main(int argc, char **argv)
{
        if (yyparse() != 0)
                return 1;
        recursive_print(stdout, parser_ast, 0);
        printf("%zu\n", nesting_level(parser_ast));

        return 0;
}

