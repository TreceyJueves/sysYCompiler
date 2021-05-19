%{
#include "e_parser.hpp"
static basenode* root;
extern "C"{
    int yylex();
}
extern YYSTYPE yylval;
extern FILE* yyin;
extern FILE* yyout;
extern void scantree(basenode*);
%}

%token VAR CALL PARAM RETURN END IF GOTO ENTER
%token VARIABLE FUNC LABEL CONST_INT
%token LBRK RBRK ASSIGN ADD MINUS MUL DIV MOD NOT LESS MORE LEQ GEQ EQUAL AND OR NEQ COL

%%
Program: CompUnit{$$ = $1; root = $1;}
CompUnit: Declaration {
            basenode* tmp = new basenode(_compunit);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | Initialization{
            basenode* tmp = new basenode(_compunit);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | FunctionDef{
            basenode* tmp = new basenode(_compunit);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | ENTER{
            basenode* tmp = new basenode(_compunit);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | CompUnit Declaration{
            auto tmp = $1;
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        | CompUnit Initialization{
            auto tmp = $1;
            tmp->Son.push_back($2);
            $$ = tmp;            
        }
        | CompUnit FunctionDef{
            auto tmp = $1;
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        | CompUnit ENTER{
            auto tmp = $1;
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        ;
Declaration: VAR VARIABLE ENTER{
            basenode* tmp = new basenode(_declaration);
            tmp->Son.push_back($2);
            $$ = tmp;
        }  
        | VAR CONST_INT VARIABLE ENTER{
            basenode* tmp = new basenode(_declaration);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;
Initialization: VARIABLE ASSIGN CONST_INT ENTER{
            basenode* tmp = new basenode(_initialization);
            tmp->Son.push_back($1);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | VARIABLE LBRK CONST_INT RBRK ASSIGN CONST_INT ENTER{
            basenode* tmp = new basenode(_initialization);
            tmp->Son.push_back($1);
            tmp->Son.push_back($3);
            tmp->Son.push_back($6);
            $$ = tmp;
        }
        ;
FunctionDef: FunctionHeader Statements FunctionEnd{
            basenode* tmp = new basenode(_functiondef);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;
FunctionHeader: FUNC LBRK CONST_INT RBRK ENTER{
            basenode* tmp = new basenode(_functionheader);
            tmp->Son.push_back($1);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;
Statements: Statement{
            basenode* tmp = new basenode(_statements);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | Statements Statement{
            basenode* tmp = new basenode(_statements);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        ;
FunctionEnd: END FUNC ENTER{
            basenode* tmp = new basenode(_functionend);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        ;
Statement: Expression{
            basenode* tmp = new basenode(_statement);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | Declaration{
            basenode* tmp = new basenode(_statement);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;
Expression: VARIABLE ASSIGN RightValue BinOp RightValue ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            $$ = tmp;
        }
        | VARIABLE ASSIGN Op RightValue ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            $$ = tmp;
        }
        | VARIABLE ASSIGN RightValue ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | VARIABLE LBRK RightValue RBRK ASSIGN RightValue ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            tmp->Son.push_back($6);
            $$ = tmp;            
        }
        | VARIABLE ASSIGN VARIABLE LBRK RightValue RBRK ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            tmp->Son.push_back($6);
            $$ = tmp; 
        }
        | IF RightValue LogicOp RightValue GOTO LABEL ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            tmp->Son.push_back($6);
            $$ = tmp; 
        }
        | GOTO LABEL ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp; 
        }
        | LABEL COL ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            $$ = tmp; 
        }
        | PARAM RightValue ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp; 
        }
        | CALL FUNC ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp; 
        }
        | VARIABLE ASSIGN CALL FUNC ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            $$ = tmp; 
        }
        | RETURN RightValue ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp; 
        }
        | RETURN ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            $$ = tmp; 
        }
        | ENTER{
            basenode* tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;
RightValue: VARIABLE{
            basenode* tmp = new basenode(_rightvalue);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | CONST_INT{
            basenode* tmp = new basenode(_rightvalue);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;
BinOp: Op{
            basenode* tmp = new basenode(_binop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | LogicOp{
            basenode* tmp = new basenode(_binop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;
Op: ADD{
            basenode* tmp = new basenode(_op);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | MINUS{
            basenode* tmp = new basenode(_op);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | NOT{
            basenode* tmp = new basenode(_op);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;
LogicOp: MUL{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | DIV{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | MOD{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | LESS{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | MORE{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | LEQ{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | GEQ{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | EQUAL{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | NEQ{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | AND{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | OR{
            basenode* tmp = new basenode(_logicop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

%%
int yyerror(const char* error)
{
	fprintf(stderr, "Line %d: %s\n", lineNo, error);
	exit(1);
}
int main(int argc, char** args){
    lineNo = 0;
	for (int i = 1;i < argc;i++){
		if (args[i][0] == '-'){
			switch(args[i][1]){
				case 'S':
					break;
				case 'e':
					break;
				case 'o':
					i++;
					yyout = fopen(args[i],"w");
					break;
				default:
					break;
			}		
		}
		else{
			yyin = fopen(args[i],"r");
		}		
	}
	yyparse();
	scantree(root);
	return 0;
}
