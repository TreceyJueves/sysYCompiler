%{
#include "parser.hpp"
#include "sysY.tab.hpp"
extern "C"
{
	int yylex(void);
	int yywrap(void);
}
extern int yyerror(const char*);
%}


letter 	[a-zA-Z]
digit   [0-9]
oct_digit [0-7]
hex_digit [0-9A-Fa-f]
integer [1-9]{digit}*
oct_integer 0{oct_digit}*
hex_integer 0[xX]{hex_digit}+
const_int ({integer}|{oct_integer}|{hex_integer})
string \"[^"\n]*\"
identifier	[a-zA-Z_]([a-zA-Z_0-9])*
whitespace	[ \t]
enter [\n]|[\r][\n]
comment "//"[^\n]*|("/*"([^\*]|(\*)*[^\*/])*(\*)*"*/")
%%

{enter} { lineNo++;}
"int" { basenode* tmp = new basenode(_int); yylval = tmp; return TYPE_INT;}
"void" { basenode* tmp = new basenode(_void); yylval = tmp; return TYPE_VOID;}
"const" { basenode* tmp = new basenode(_const); yylval = tmp; return TYPE_CONST;}
"if" { basenode* tmp = new basenode(_if); yylval = tmp; return IF;}
"else" { basenode* tmp = new basenode(_else); yylval = tmp; return ELSE;}
"while" { basenode* tmp = new basenode(_while); yylval = tmp; return WHILE;}
"break" { basenode* tmp = new basenode(_break); yylval = tmp; return BREAK;}
"continue" { basenode* tmp = new basenode(_continue); yylval = tmp; return CONTINUE;}
"return" { basenode* tmp = new basenode(_return); yylval = tmp; return RETURN;} 

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

"("	{ basenode* tmp = new basenode(_lpr); yylval = tmp; return LPR; }
")"	{ basenode* tmp = new basenode(_rpr); yylval = tmp; return RPR; }
"["	{ basenode* tmp = new basenode(_lbrk); yylval = tmp; return LBRK; }
"]"	{ basenode* tmp = new basenode(_rbrk); yylval = tmp; return RBRK; }
"{"	{ basenode* tmp = new basenode(_lbrac); yylval = tmp; return LBRAC; }
"}"	{ basenode* tmp = new basenode(_rbrac); yylval = tmp; return RBRAC; }
","	{ basenode* tmp = new basenode(_comma); yylval = tmp; return COMMA; }
";"	{ basenode* tmp = new basenode(_semcol); yylval = tmp; return SEMCOL; }



{const_int} { basenode* tmp = new basenode(_int_const); 
			if(yytext[0]!='0'){
				tmp->val = atoi(yytext);
			}
			else if(yytext[1] == 'x' || yytext[1] == 'X'){
				tmp->val = strtol(yytext, NULL, 16);
			}
			else{
				tmp->val = strtol(yytext, NULL, 8);
			}
			yylval = tmp; return INT_CONST;}
{comment} {}
{whitespace} {}
{identifier} {
			basenode* tmp = new basenode(_id);
			tmp->ID = yytext;
			yylval = tmp;
			return ID;}

.	{ char msg[100] = "unrecognized input "; strcat(msg, yytext); yyerror(msg); return ERROR;}
%%

int yywrap()
{
	return 1;
}
