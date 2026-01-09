#include <stdio.h>

#include "gram.tab.h"
#include "gocheck.h"

int main(int argc, char **argv)
{
        yyparse();
        return 0;
}

