#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <stack>

enum e_node_type{
    resv = 0,
    _var,
    _call,
    _param,
    _return,
    _end,//5
    _if,
    _goto,
    _variable,
    _func,
    _label,//10
    _const_int,
    _lbrk,
    _rbrk,
    _assign,
    _add,//15
    _minus,
    _mul,
    _div,
    _mod,
    _not,//20
    _less,
    _more,
    _leq,
    _geq,
    _equal,//25
    _and,
    _or,
    _neq,
    _col,
    _compunit,//30
    _declaration,
    _initialization,
    _functiondef,
    _functionheader,
    _statements,//35
    _functionend,
    _statement,
    _expression,
    _rightvalue,
    _binop,//40
    _op,
    _logicop,
    _enter,//43
};

enum e_var_type{
    _null = 0,
    _const,
    _reg,
};

struct e_basenode
{
    enum e_node_type type;
    std::vector<e_basenode *> Son;
    int val;
    std::string ID;
    e_basenode(enum e_node_type _type)
    {
       // //printf("type: %d\n",_type);
        type = _type;
        Son = std::vector<e_basenode *>();
    }
};
struct init_info{
    std::string var_name;
    int index;
    int value;
};

struct var_info{
    int place;//-1 for e_initialize 0 for instack >0 for in reg
    int is_local;//0 for global 1 for local
    int stack_place;//-1 for e_initialize >= 0 for stack place(or global num)
    int is_array;//0 for not 1 for array
    var_info(int _place = -1, int _is_local = -1, int _stack_place = -1, int _is_array=-1){
        place = _place;
        is_local = _is_local;
        stack_place = _stack_place;
        is_array = _is_array;
    }
};

struct stack_info{
    int size;
    stack_info(int _size=-1){
        size = _size;
    }
};

extern int e_lineNo;
extern int e2terror(const char*);
extern FILE* e2tin, *e2tout;
#define E2TSTYPE e_basenode *