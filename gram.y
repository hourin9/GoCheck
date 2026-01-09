%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(char const*);
%}

%union {
        char *str;
}

%token FUNC
%token VAR

%token <str> ID
%token <str> STR_LIT

%start input
%%

input: %empty
     | input variable_decl ';'
     | input expression ';'
     ;

variable_decl: VAR id_list type_opt assignment { printf("var w/ asg\n"); }
             | VAR id_list type_opt { printf("var w/o asg\n"); }
             ;

id_list: id_list ',' ID
       | ID
       ;

type_opt: %empty
        | ID
        ;

assignment: '=' expression

expression: ID
          | STR_LIT
          ;

%%

void yyerror(char const *msg)
{
        fprintf(stderr, "%s\n", msg);
        exit(1);
}

