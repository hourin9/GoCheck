%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(char const*);
%}

%union {
        char *str;
}

%token FOR
%token FUNC
%token VAR

%token <str> ID
%token <str> STR_LIT

%start input
%%

input: stmt_list
     ;

stmt_list: %empty
         | stmt_list stmt
         ;

stmt: variable_decl ';'
    | expression ';'
    | for_loop
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
          | fncall
          ;

fncall: ID '(' arg_list ')' { printf("calling func %s\n", $1); }
      ;

arg_list: %empty
        | expression
        | arg_list ',' expression
        ;

block: '{' stmt_list '}'
     ;

for_loop: FOR expression block { printf("loop\n"); }
        | FOR block { printf("inf loop\n"); }
        ;

%%

void yyerror(char const *msg)
{
        fprintf(stderr, "%s\n", msg);
        exit(1);
}

