%{
#include "gram.tab.h"
%}

%option noyywrap

%%

[a-zA-Z_][a-zA-Z0-9_]* {
    yylval.str = strdup(yytext);
    return ID;
}

[ \t\f\v\n]+ { ; }

%%

