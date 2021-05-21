%{
    #include "t_parser.hpp"
    #include "tigger.tab.hpp"
    extern "C"
    {
	int yylex(void);
	int yywrap(void);
    }
    extern int yyerror(const char*);
%}
digit [0-9]
integer (-)?{digit}+
identifier [a-zA-Z_]([a-zA-Z_0-9])*

label l{integer}
var v{integer}
func f_{identifier}
whitespace[ \t]
enter [\n]
comment "//"[^\n]*
%%

{enter} { lineNo++; yylval = new basenode(_enter); return ENTER;}
{comment} {}
{whitespace} {}

"[" {yylval = new basenode(_lbrk); return LBRK;}
"]" {yylval = new basenode(_rbrk); return RBRK;}

"malloc" {yylval = new basenode(_malloc); return MALLOC;}
"if" {yylval = new basenode(_if); return IF;}
"goto" {yylval = new basenode(_goto); return GOTO;}
"call" {yylval = new basenode(_call); return CALL;}
"return" {yylval = new basenode(_return); return RETURN;}
"store" {yylval = new basenode(_store); return STORE;}
"load" {yylval = new basenode(_load); return LOAD;}
"loadaddr" {yylval = new basenode(_loadaddr); return LOADADDR;}
"end" {yylval = new basenode(_end); return END;}
":" {yylval = new basenode(_col); return COL;}

"=" {yylval = new basenode(_assign); return ASSIGN;}
"+" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"-" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"*" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"/" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"%" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"&&" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"||" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"==" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"!=" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"<" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
">" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
">=" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"<=" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}
"!" {yylval = new basenode(_op); yylval->ID = yytext; return OP;}

"a"[0-7] {yylval = new basenode(_reg); yylval->ID = yytext; return REG;}
"t"[0-6] {yylval = new basenode(_reg); yylval->ID = yytext; return REG;}
"s"[0-9] {yylval = new basenode(_reg); yylval->ID = yytext; return REG;}
"s1"[0-1] {yylval = new basenode(_reg); yylval->ID = yytext; return REG;}
"x0" {yylval = new basenode(_reg); yylval->ID = yytext;  return REG;}

{label} {yylval = new basenode(_label); yylval->ID = yytext;  return LABEL;}
{func} {yylval = new basenode(_func); yylval->ID = yytext;  return FUNC;}
{var} {yylval = new basenode(_variable); yylval->ID = yytext;  return VARIABLE;}
{integer} {yylval = new basenode(_const_int); yylval->val = atoi(yytext); return CONST_INT;}

. {}
%%
int yywrap(){
    return 1;
}