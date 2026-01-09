%{
#include "gram.tab.h"
%}

%option noyywrap

%%

"for" { return FOR; }
"func" { return FUNC; }
"var" { return VAR; }

";" { return ';'; }
"," { return ','; }
"=" { return '='; }

"{" { return '{'; }
"}" { return '}'; }

"(" { return '('; }
")" { return ')'; }

\".*\" {
        yylval.str = strdup(yytext);
        return STR_LIT;
}

[a-zA-Z_][a-zA-Z0-9_]* {
        yylval.str = strdup(yytext);
        return ID;
}

[ \t\f\v\n]+ { ; }

%%

