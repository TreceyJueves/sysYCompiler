%{
    #include "t_parser.hpp"
    extern "C"{
        int yylex();
    }
    extern YYSTYPE yylval;
    extern FILE* yyin;
    extern FILE* yyout;
    extern void scantigger(basenode*);
    static basenode* root;
%}

%token ENTER LBRK RBRK MALLOC IF GOTO CALL RETURN STORE
%token LOAD LOADADDR COL END ASSIGN VARIABLE
%token OP REG LABEL FUNC
%token CONST_INT

%%
Start: Program{
    $$ = $1;
    root = $1;
}
Program: Program GlobalVarDecl{
            basenode* tmp = $1;
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        | Program FuncDef{
            auto tmp = $1;
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        | Program ENTER{
            auto tmp = $1;
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        | GlobalVarDecl{
            basenode* tmp = new basenode(_program);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | ENTER{
            basenode* tmp = new basenode(_program);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | FuncDef{
            basenode* tmp = new basenode(_program);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

GlobalVarDecl: VARIABLE ASSIGN CONST_INT ENTER{
            auto tmp = new basenode(_globalvardecl);
            tmp->Son.push_back($1);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | VARIABLE ASSIGN MALLOC CONST_INT ENTER{
            auto tmp = new basenode(_globalvardecl);
            tmp->Son.push_back($1);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            $$ = tmp;
        }
        ;

FuncDef: FunctionHeader Expressions FunctionEnd{
            auto tmp = new basenode(_funcdef);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | FunctionHeader FunctionEnd{
            auto tmp = new basenode(_funcdef);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        ;

FunctionHeader: FUNC LBRK CONST_INT RBRK LBRK CONST_INT RBRK ENTER{
            auto tmp = new basenode(_functionheader);
            tmp->Son.push_back($1);
            tmp->Son.push_back($3);
            tmp->Son.push_back($6);
            $$ = tmp;
        }
        ;

Expressions: Expressions Expression{
            auto tmp = new basenode(_expressions);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        | Expression{
            auto tmp = new basenode(_expressions);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

FunctionEnd: END FUNC{
            auto tmp = new basenode(_functionend);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        ;

Expression: ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | REG ASSIGN REG OP REG ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            $$ = tmp;
        } 
        | REG ASSIGN REG OP CONST_INT ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            $$ = tmp;
        }
        | REG ASSIGN OP REG ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            $$ = tmp;
        }
        | REG ASSIGN REG ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | REG ASSIGN CONST_INT ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | REG LBRK CONST_INT RBRK ASSIGN REG ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            tmp->Son.push_back($6);
            $$ = tmp;
        }
        | REG ASSIGN REG LBRK CONST_INT RBRK ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            tmp->Son.push_back($6);
            $$ = tmp;
        }
        | IF REG OP REG GOTO LABEL ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            tmp->Son.push_back($6);
            $$ = tmp;
        }
        | GOTO LABEL ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        | LABEL COL ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | CALL FUNC ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        | RETURN ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | STORE REG CONST_INT ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | LOAD CONST_INT REG ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | LOAD VARIABLE REG ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | LOADADDR CONST_INT REG ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | LOADADDR VARIABLE REG ENTER{
            auto tmp = new basenode(_expression);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
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
    scantigger(root);
	return 0;
}