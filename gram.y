%{
#include <stdio.h>
#include <stdlib.h>

#include "gocheck.h"

extern int yylex();
void yyerror(char const*);
%}

%union {
        char *str;
        struct AST *node;
}

%token ELSE
%token FOR
%token FUNC
%token IF
%token VAR

%type <node> stmt stmt_list block expression variable_decl branch for_loop

%{
struct AST *parser_ast;
%}

%token <str> ID
%token <str> STR_LIT

%start input
%%

input: stmt_list { parser_ast = $1; }
     ;

stmt_list: %empty { $$ = nullptr; }
         | stmt_list stmt {
                if ($1 == nullptr)
                        $$ = $2;
                else {
                        struct AST *tmp = $1;
                        while (tmp->next)
                                tmp = tmp->next;
                        tmp->next = $2;
                        $$ = $1;
                }
         }
         ;

stmt: variable_decl ';' { $$ = $1; }
    | expression ';'
    | for_loop
    | branch
    ;

variable_decl: VAR id_list type_opt assignment { printf("var w/ asg\n"); }
             | VAR ID type_opt {
                struct AST *id = leaf(AST_Id, $2);
                $$ = node(AST_VarDecl, id, nullptr);
             }
             ;

id_list: id_list ',' ID
       | ID
       ;

type_opt: %empty
        | ID
        ;

assignment: '=' expression

expression: ID { $$ = leaf(AST_Id, $1); }
          | STR_LIT { $$ = leaf(AST_Id, $1); }
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

branch: IF expression block else_opt
      ;

else_opt: ELSE branch
        | ELSE block
        | %empty
        ;

%%

void yyerror(char const *msg)
{
        fprintf(stderr, "%s\n", msg);
        exit(1);
}

