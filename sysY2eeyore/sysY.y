%{
#include "parser.hpp"

static basenode *root;
extern "C"{
    int yylex();
}
extern YYSTYPE yylval;
extern FILE* yyin;
extern FILE* yyout;
extern void scantree(basenode*);
%}

%token TYPE_INT TYPE_VOID TYPE_CONST MAIN IF ELSE WHILE BREAK CONTINUE RETURN LOWER_THAN_ELSE
%token ASSIGN ADD MINUS MUL DIV MOD NOT LESS MORE LEQ GEQ EQUAL AND OR NEQ
%token LPR RPR LBRK RBRK LBRAC RBRAC COMMA SEMCOL
%token INT_CONST ID ERROR
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%
Program : CompUnit {$$=$1; root = $1;}
CompUnit: Decl{ 
                basenode* tmp = new basenode(_compunit);
                tmp->Son.push_back($1);
                $$ = tmp;
            }
        | FuncDef{
                basenode* tmp = new basenode(_compunit);
                tmp->Son.push_back($1);
                $$ = tmp;
            }
        | CompUnit Decl{
                auto tmp = $1;
                tmp->Son.push_back($2);
                $$ = tmp;
        }
        | CompUnit FuncDef{
                auto tmp = $1;
                tmp->Son.push_back($2);
                $$ = tmp;
        }
        ;
Decl :
      ConstDecl{
                basenode* tmp = new basenode(_decl);
                tmp->Son.push_back($1);
                $$ = tmp;
        }
        | VarDecl{
                basenode* tmp = new basenode(_decl);
                tmp->Son.push_back($1);
                $$ = tmp;
        }
        ;
BType:
      TYPE_INT{
            basenode* tmp = new basenode(_btype);
            tmp->Son.push_back($1);
            $$ = tmp;
      }     
      | TYPE_VOID{
            basenode* tmp = new basenode(_btype);
            tmp->Son.push_back($1);
            $$ = tmp;
      }
      ;

ConstDecl: TYPE_CONST BType ConstSeqDecl SEMCOL{
                basenode* tmp = new basenode(_constdecl);
                tmp->Son.push_back($2);
                tmp->Son.push_back($3);
                $$=tmp;
        }
        ;

ConstSeqDecl: ConstDef{
                basenode* tmp = new basenode(_defconstlist);
                tmp->Son.push_back($1);
                $$ = tmp;
        }
        | ConstSeqDecl COMMA ConstDef{
                basenode* tmp = new basenode(_defconstlist);
                tmp->Son.push_back($1);
                tmp->Son.push_back($3);
                $$ = tmp;
        }
        ;

ConstDef: ID MD_Array ASSIGN ConstInitVal{
              basenode* tmp = new basenode(_constdef);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              tmp->Son.push_back($3);
              tmp->Son.push_back($4);
              $$ = tmp;
        }
        ;

MD_Array: {
              basenode *tmp = new basenode(_mddim);
              $$ = tmp;
        }
        | MD_Array LBRK ConstExp RBRK{
              basenode* tmp = new basenode(_mddim);
              tmp->Son.push_back($1);
              tmp->Son.push_back($3);
              $$ = tmp;
        }
        ;

ConstInitVal: ConstExp{
              basenode* tmp = new basenode(_constinitval);
              tmp->Son.push_back($1);
              $$ = tmp;
        }
        | LBRAC ConstSeqInitVal RBRAC{
              basenode* tmp = new basenode(_constinitval);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              tmp->Son.push_back($3);
              $$ = tmp;
        }
        | LBRAC RBRAC{
              basenode* tmp = new basenode(_constinitval);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              $$ = tmp;
        }
        ;

ConstSeqInitVal: ConstInitVal{
              basenode* tmp = new basenode(_constseqinitval);
              tmp->Son.push_back($1);
              $$ = tmp;
        }
        | ConstSeqInitVal COMMA ConstInitVal{
              basenode* tmp = new basenode(_constseqinitval);
              tmp->Son.push_back($1);
              tmp->Son.push_back($3);
              $$ = tmp;
        }
        ;

VarDecl: BType VarSeqDef SEMCOL{
              basenode* tmp = new basenode(_vardecl);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              $$ = tmp;
        } 
        ;

VarSeqDef: VarDef{
              basenode*tmp = new basenode(_varseqdef);
              tmp->Son.push_back($1);
              $$ = tmp;
        }
        | VarSeqDef COMMA VarDef{
              basenode* tmp = new basenode(_varseqdef);
              tmp->Son.push_back($1);
              tmp->Son.push_back($3);
              $$ = tmp;
        }
        ;

VarDef: ID MD_Array{
              basenode* tmp = new basenode(_vardef);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              $$ = tmp;
        }
        | ID MD_Array ASSIGN InitVal{
              basenode* tmp = new basenode(_vardef);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              tmp->Son.push_back($3);
              tmp->Son.push_back($4);
              $$ = tmp;
        }
        ;
  
InitVal: Exp{
              basenode* tmp = new basenode(_initval);
              tmp->Son.push_back($1);
              $$ = tmp;
        }
        | LBRAC RBRAC{
              basenode* tmp = new basenode(_initval);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              $$ = tmp;
        }
        | LBRAC InitSeqVal RBRAC{
              basenode* tmp = new basenode(_initval);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              tmp->Son.push_back($3);
              $$ = tmp;
        }
        ;

InitSeqVal: InitVal{
              basenode* tmp = new basenode(_initseqval);
              tmp->Son.push_back($1);
              $$ = tmp;
        }
        | InitSeqVal COMMA InitVal{
              basenode* tmp = new basenode(_initseqval);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              tmp->Son.push_back($3);
              $$ = tmp;
        }
        ;

FuncDef:  BType ID LPR RPR Block{
              basenode* tmp = new basenode(_funcdef);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              tmp->Son.push_back($3);
              tmp->Son.push_back($4);
              tmp->Son.push_back($5);
              $$ = tmp;
        }
        | BType ID LPR FuncFParams RPR Block{
              basenode* tmp = new basenode(_funcdef);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              tmp->Son.push_back($3);
              tmp->Son.push_back($4);
              tmp->Son.push_back($5);
              tmp->Son.push_back($6);
              $$ = tmp;
        }
        ;

FuncFParams: FuncFParam{
              basenode* tmp = new basenode(_funcfparams);
              tmp->Son.push_back($1);
              $$ = tmp;
        }
        | FuncFParams COMMA FuncFParam{
              basenode* tmp = new basenode(_funcfparams);
              tmp->Son.push_back($1);
              tmp->Son.push_back($3);
              $$ = tmp;
        }
        ;

FuncFParam: TYPE_INT ID{
              basenode* tmp = new basenode(_funcfparam);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              $$ = tmp;
        }
        | TYPE_INT ID LBRK RBRK MD_Array{
              basenode* tmp = new basenode(_funcfparam);
              tmp->Son.push_back($1);
              tmp->Son.push_back($2);
              tmp->Son.push_back($3);
              tmp->Son.push_back($4);
              tmp->Son.push_back($5);
              $$ = tmp;
        }
        ;

Block: LBRAC RBRAC{
            basenode* tmp = new basenode(_block);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        | LBRAC BlockSeqItem RBRAC{
            basenode* tmp = new basenode(_block);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;

BlockSeqItem: BlockItem{
            basenode* tmp = new basenode(_blockseqitem);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | BlockSeqItem BlockItem{
            basenode* tmp = new basenode(_blockseqitem);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        ;

BlockItem: Decl{
            basenode* tmp = new basenode(_blockitem);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | Stmt{
            basenode* tmp = new basenode(_blockitem);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;



Stmt: LVal ASSIGN Exp SEMCOL{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | Exp SEMCOL{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            $$ = tmp; 
        }
        | SEMCOL{
            basenode* tmp = new basenode(_stmt);
            $$ = tmp;
        }
        | Block{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | IF LPR Cond RPR Stmt ELSE Stmt{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            tmp->Son.push_back($6);
            tmp->Son.push_back($7);
            $$ = tmp;
        }
        | IF LPR Cond RPR Stmt %prec LOWER_THAN_ELSE{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            $$ = tmp;
        }
        | WHILE LPR Cond RPR Stmt{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            tmp->Son.push_back($5);
            $$ = tmp; 
        }
        | BREAK SEMCOL{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | CONTINUE SEMCOL{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | RETURN SEMCOL{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | RETURN Exp SEMCOL{
            basenode* tmp = new basenode(_stmt);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        ;

Exp: AddExp{
            basenode* tmp = new basenode(_exp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

Cond: LOrExp{
            basenode* tmp = new basenode(_cond);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

LVal: ID LVal_Array{
            basenode* tmp = new basenode(_lval);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        ;
LVal_Array: {
              basenode *tmp = new basenode(_lvaldim);
              $$ = tmp;
        }
        | LVal_Array LBRK ConstExp RBRK{
              basenode* tmp = new basenode(_lvaldim);
              tmp->Son.push_back($1);
              tmp->Son.push_back($3);
              $$ = tmp;
        }
        ;
PrimaryExp: LPR Exp RPR{
            basenode* tmp = new basenode(_primaryexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | LVal{
            basenode* tmp = new basenode(_primaryexp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | Number{
            basenode* tmp = new basenode(_primaryexp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

Number: INT_CONST{
            basenode* tmp = new basenode(_number);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

//before UnaryExp

UnaryExp: PrimaryExp{
            basenode* tmp = new basenode(_unaryexp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | ID LPR RPR{
            basenode* tmp = new basenode(_unaryexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        | ID LPR FuncRParams RPR{
            basenode* tmp = new basenode(_unaryexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            tmp->Son.push_back($4);
            $$ = tmp;
        }
        | UnaryOp UnaryExp{
            basenode* tmp = new basenode(_unaryexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            $$ = tmp;
        }
        ;

UnaryOp: ADD{
            basenode* tmp = new basenode(_unaryop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | MINUS{
            basenode* tmp = new basenode(_unaryop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | NOT{
            basenode* tmp = new basenode(_unaryop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

FuncRParams: Exp{
            basenode* tmp = new basenode(_funcrparams);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | FuncRParams COMMA Exp{
            basenode* tmp = new basenode(_funcrparams);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;

MulExp: UnaryExp{
            basenode* tmp = new basenode(_mulexp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | MulExp MulOp UnaryExp{
            basenode* tmp = new basenode(_mulexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;

MulOp: MUL{
            basenode* tmp = new basenode(_mulop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | DIV{
            basenode* tmp = new basenode(_mulop);
            tmp->Son.push_back($1);
            $$ = tmp; 
        }
        | MOD{
            basenode* tmp = new basenode(_mulop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

AddExp: MulExp{
            basenode* tmp = new basenode(_addexp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | AddExp AddOp MulExp{
            basenode* tmp = new basenode(_addexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;

AddOp: ADD{
            basenode* tmp = new basenode(_addop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | MINUS{
            basenode* tmp = new basenode(_addop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

RelExp: AddExp{
            basenode* tmp = new basenode(_relexp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | RelExp RelOp AddExp{
            basenode* tmp = new basenode(_relexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;

RelOp: LESS{
            basenode* tmp = new basenode(_relop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | LEQ{
            basenode* tmp = new basenode(_relop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | MORE{
            basenode* tmp = new basenode(_relop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | GEQ{
            basenode* tmp = new basenode(_relop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

EqExp: RelExp{
            basenode* tmp = new basenode(_eqexp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | EqExp EqOp RelExp{
            basenode* tmp = new basenode(_eqexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;

EqOp: EQUAL{
            basenode* tmp = new basenode(_eqop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | NEQ{
            basenode* tmp = new basenode(_eqop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

LAndExp: EqExp{
            basenode* tmp = new basenode(_landexp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | LAndExp LAndOp EqExp{
            basenode* tmp = new basenode(_landexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;

LAndOp: AND{
            basenode* tmp = new basenode(_landop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

LOrExp: LAndExp{
            basenode* tmp = new basenode(_lorexp);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        | LOrExp LOrOp LAndExp{
            basenode* tmp = new basenode(_lorexp);
            tmp->Son.push_back($1);
            tmp->Son.push_back($2);
            tmp->Son.push_back($3);
            $$ = tmp;
        }
        ;

LOrOp: OR{
            basenode* tmp = new basenode(_lorop);
            tmp->Son.push_back($1);
            $$ = tmp;
        }
        ;

ConstExp: AddExp{
            basenode* tmp = new basenode(_constexp);
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
