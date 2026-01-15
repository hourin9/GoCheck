%{
#include "gram.tab.h"
%}

%option noyywrap

%%

"const" { return CONST; }
"else" { return ELSE; }
"for" { return FOR; }
"func" { return FUNC; }
"if" { return IF; }
"import" { return IMPORT; }
"package" { return PACKAGE; }
"return" { return RETURN; }
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

[0-9]+(\.[0-9]+)? {
        yylval.f32 = atof(yytext);
        return NUM_LIT;
}

[a-zA-Z_][a-zA-Z0-9_]* {
        yylval.str = strdup(yytext);
        return ID;
}

[ \t\f\v\n]+ { ; }

%%

