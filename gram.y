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
%token IMPORT
%token PACKAGE
%token VAR

%type <node> stmt stmt_list block expression variable_decl
%type <node> type_opt assignment_opt id_list
%type <node> branch else_opt for_loop
%type <node> arg_opt arg_list fncall
%type <node> import package

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
    | expression ';' { $$ = $1; }
    | for_loop { $$ = $1; }
    | branch { $$ = $1; }
    | import ';' { $$ = $1; }
    | package ';' { $$ = $1; }
    ;

variable_decl: VAR id_list type_opt assignment_opt {
                // TODO: handle types in assignment
                struct AST *ids = $2;
                struct AST *type = $3;
                $$ = decl_node(ids, type);
             }
             ;

id_list: ID { $$ = leaf(AST_Id, $1); }
       | id_list ',' ID {
                struct AST *root = leaf(AST_Id, $1->sval);
                root->next = leaf(AST_Id, $3);
                $$ = root;
       }
       ;

type_opt: %empty { $$ = nullptr; }
        | ID { $$ = leaf(AST_Id, $1); }
        ;

assignment_opt: %empty { $$ = nullptr; }
              | '=' expression { $$ = $2; }

expression: ID { $$ = leaf(AST_Id, $1); }
          | STR_LIT { $$ = leaf(AST_Id, $1); }
          | fncall { $$ = $1; }
          ;

fncall: expression '(' arg_opt ')' {
        $$ = call_node($1, $3);
      }
      ;

arg_opt: %empty { $$ = nullptr; }
       | arg_list { $$ = $1; }
       ;

arg_list: expression { $$ = $1; }
        | arg_list ',' expression {
                $1->next = $3;
                $$ = $1;
        }
        ;

block: '{' stmt_list '}' { $$ = $2; }
     ;

for_loop: FOR expression block { printf("loop\n"); }
        | FOR block { printf("inf loop\n"); }
        ;

branch: IF expression block else_opt {
        $$ = if_node($2, $3);
      }
      ;

else_opt: ELSE branch { $$ = $2; }
        | ELSE block { $$ = $2; }
        | %empty { $$ = nullptr; }
        ;

package: PACKAGE STR_LIT { $$ = package_node($2); }
       ;

import: IMPORT STR_LIT { $$ = import_node($2); }
      ;

%%

void yyerror(char const *msg)
{
        fprintf(stderr, "%s\n", msg);
        exit(1);
}

