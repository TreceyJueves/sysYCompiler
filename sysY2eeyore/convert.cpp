#include"parser.hpp"
std::string exp2str(std::pair<std::pair<int,int>, v_type>);

std::string exp2str(std::pair<std::pair<int,int>, v_type> exp){
    std::string res = "";
    switch(exp.second){
        case _const_var:
            res = std::to_string(exp.first.second);
            break;
        case _var:
            res = "T"+std::to_string(exp.first.first);
            break;
        case _tmp_var:
            res = "t"+std::to_string(exp.first.first);
            break;
        case _func_var:
            res = "p"+std::to_string(exp.first.first);
            break;
        case _const_var_array:
        case _var_array:
            if(exp.first.second == -1){
                res = "T"+std::to_string(exp.first.first);
            }
            else{
                res = "T"+std::to_string(exp.first.first)+"[t"+std::to_string(exp.first.second)+"]";
            }
            break;
        case _func_var_array:
            if(exp.first.second == -1){
                res = "p"+std::to_string(exp.first.first);
            }
            else{
                res = "p"+std::to_string(exp.first.first)+"[t"+std::to_string(exp.first.second)+"]";
            }
            break;
        default:
            yyerror("Converting Exp to String Error\n");
    }
    return res;
}