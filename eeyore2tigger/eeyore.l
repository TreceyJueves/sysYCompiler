%{
#include "e_parser.hpp"
#include "eeyore.tab.hpp"
extern "C"
{
    int yylex(void);
    int yywrap(void);
}
extern int yyerror(const char*);
%}

letter [a-zA-Z]
integer (-)?[1-9][0-9]*|"0"
identifier (_|{letter})(_|[0-9]|{letter})*
whitespace [ \t]+
enter [\n]
comment "//"[^\n]*|("/*"([^\*]|(\*)*[^\*/])*(\*)*"*/")
function f_{identifier}
variable (T|t|p){integer}
label l{integer} 

%%
{whitespace} {}
{comment} {}
{enter} {lineNo++; basenode* tmp = new basenode(_enter); yylval = tmp; return ENTER;}
"var" {basenode* tmp = new basenode(_var); yylval = tmp; return VAR;}
"call" {basenode* tmp = new basenode(_call); yylval = tmp; return CALL;}
"param" {basenode* tmp = new basenode(_param); yylval = tmp; return PARAM;}
"return" {basenode* tmp = new basenode(_return); yylval = tmp; return RETURN;}
"end" {basenode* tmp = new basenode(_end); yylval = tmp; return END;}
"if" {basenode* tmp = new basenode(_if); yylval = tmp; return IF;}
"goto" {basenode* tmp = new basenode(_goto); yylval = tmp; return GOTO;}

{variable} {basenode* tmp = new basenode(_variable); tmp->ID = yytext; yylval = tmp; return VARIABLE;}
{function} {basenode* tmp = new basenode(_func); tmp->ID = yytext; yylval = tmp; return FUNC;}
{label} {basenode* tmp = new basenode(_label); tmp->ID = yytext; yylval = tmp; return LABEL;}
{integer} {basenode* tmp = new basenode(_const_int); tmp->val = atoi(yytext); yylval = tmp; return CONST_INT;}

"[" {basenode* tmp = new basenode(_lbrk); yylval = tmp; return LBRK;}
"]" {basenode* tmp = new basenode(_rbrk); yylval = tmp; return RBRK;}
"=" { basenode* tmp = new basenode(_assign); yylval = tmp; return ASSIGN;}
"+" { basenode* tmp = new basenode(_add); yylval = tmp; return ADD;}
"-" { basenode* tmp = new basenode(_minus); yylval = tmp; return MINUS;}
"*" { basenode* tmp = new basenode(_mul); yylval = tmp; return MUL;}
"/" { basenode* tmp = new basenode(_div); yylval = tmp; return DIV;}
"%" { basenode* tmp = new basenode(_mod); yylval = tmp; return MOD;}
"!" { basenode* tmp = new basenode(_not); yylval = tmp; return NOT;}
"<" { basenode* tmp = new basenode(_less); yylval = tmp; return LESS;}
">" { basenode* tmp = new basenode(_more); yylval = tmp; return MORE;}
"<=" { basenode* tmp = new basenode(_leq); yylval = tmp; return LEQ;}
">=" { basenode* tmp = new basenode(_geq); yylval = tmp; return GEQ;}
"==" { basenode* tmp = new basenode(_equal); yylval = tmp; return EQUAL;}
"&&" { basenode* tmp = new basenode(_and); yylval = tmp; return AND;}
"||" { basenode* tmp = new basenode(_or); yylval = tmp; return OR;}
"!=" { basenode* tmp = new basenode(_neq); yylval = tmp; return NEQ;}
":" { basenode* tmp = new basenode(_col); yylval = tmp; return COL;}

. {}
%%

int yywrap(){
    return 1;
}