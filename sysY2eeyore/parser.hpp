#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stack>

enum node_type
{
    resv = 0,
    _compunit, //compunit
    _decl,
    _constdecl, //constant declaration
    _btype,
    _defconstlist, //5 sequence of constant declaration
    _constdef,     //const define
    _constexp,
    _mddim,        //dimension of variable defined
    _constseqinitval,
    _constseqval, //10
    _constinitval,
    _vardecl,
    _varseqdef,
    _vardef,
    _initval,//15
    _initseqval,
    _funcdef,
    _funcfparams,
    _funcfparam,
    _block,//20
    _blockitem,
    _blockseqitem,
    _stmt,
    _exp,
    _cond,//25
    _lval,
    _lvaldim,
    _primaryexp,
    _number,
    _unaryexp,//30
    _unaryop,
    _funcrparams,
    _mulexp,
    _mulop,
    _addexp,//35
    _addop,
    _relexp,
    _relop,
    _eqexp,
    _eqop,//40
    _landexp,
    _landop,
    _lorexp,
    _lorop,
    _int,//45
    _void,
    _const,
    _if,
    _else,
    _while,//50
    _break,
    _continue,
    _return,
    _assign,
    _add,//55
    _minus,
    _mul,
    _div,
    _mod,
    _not,//60
    _less,
    _more,
    _leq,
    _geq,
    _equal,//65
    _and,
    _or,
    _neq,
    _lpr,
    _rpr,//70
    _lbrk,
    _rbrk,
    _lbrac,
    _rbrac,
    _comma,//75
    _semcol,
    _int_const,
    _id,//78
};

enum v_type
{
    _var = 0,
    _var_array,
    _tmp_var,
    _tmp_var_array,
    _const_var,
    _const_var_array,
    _func_var,
    _func_var_array,
    _null,
};

struct basenode
{
    enum node_type type;
    std::vector<basenode *> Son;
    int val;
    std::string ID;
    basenode(enum node_type _type)
    {
        printf("type: %d\n",_type);
        type = _type;
        Son = std::vector<basenode *>();
    }
};
extern int lineNo;
extern int yyerror(const char*);
extern FILE* yyin, *yyout;
#define YYSTYPE basenode *