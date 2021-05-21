#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stack>

enum node_type{
    resv = 0,
    _lbrk,
    _rbrk,
    _malloc,
    _enter,
    _if,
    _goto,
    _call,
    _return,
    _store,
    _load,
    _loadaddr,
    _end,
    _col,
    _assign,
    _op,
    _reg,
    _label,
    _func,
    _variable,
    _const_int,
    _program,
    _globalvardecl,
    _funcdef,
    _functionheader,
    _functionend,
    _expressions,
    _expression,
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