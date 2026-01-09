%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(char const*);
%}

%union {
        char *str;
}

%token <str> ID

%start input
%%

input:
    ;

%%

void yyerror(char const *msg)
{
        fprintf(stderr, "%s\n", msg);
        exit(1);
}

