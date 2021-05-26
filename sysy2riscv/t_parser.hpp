#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stack>

enum t_node_type{
    resv = 0,
    _lbrk,
    _rbrk,
    _malloc,
    _enter,
    _if,//5
    _goto,
    _call,
    _return,
    _store,
    _load,//10
    _loadaddr,
    _end,
    _col,
    _assign,
    _op,//15
    _reg,
    _label,
    _func,
    _variable,
    _const_int,//20
    _program,
    _globalvardecl,
    _funcdef,
    _functionheader,
    _functionend,//25
    _expressions,
    _expression,
};

struct t_basenode
{
    enum t_node_type type;
    std::vector<t_basenode *> Son;
    int val;
    std::string ID;
    t_basenode(enum t_node_type _type)
    {
      //  printf("type: %d\n",_type);
        type = _type;
        Son = std::vector<t_basenode *>();
    }
};

extern int t_lineNo;
extern int yyerror(const char*);
extern FILE* yyin, *yyout;
#define YYSTYPE t_basenode *