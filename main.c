#include <stdio.h>

#include "gram.tab.h"
#include "gocheck.h"

extern struct AST *parser_ast;

int main(int argc, char **argv)
{
        if (yyparse() != 0)
                return 1;
        recursive_print(stderr, parser_ast, 0);
        analyze_and_print(stdout, parser_ast);

        return 0;
}

