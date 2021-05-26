#include "t_parser.hpp"

int t_lineNo = 1;
int stk = -1;


void scantigger(t_basenode*);
void scanglobalvardecl(t_basenode*);
void scanfuncdef(t_basenode*);
void scanfunctionhead(t_basenode*);
void scanexpressions(t_basenode*);
void scanfunctionend(t_basenode*);
void scanexpression(t_basenode*);

void scanglobalvardecl(t_basenode* root){
    auto s = root->Son;
    if(s.size() == 2){
        auto v = s[0]->ID.c_str();
        auto n = s[1]->val;
        fprintf(yyout, "\t.global %s\n", v);
        fprintf(yyout, "\t.section .sdata\n");
        fprintf(yyout, "\t.align 2\n");
        fprintf(yyout, "\t.type %s, @object\n", v);
        fprintf(yyout, "\t.size %s, 4\n", v);
        fprintf(yyout, "%s:\n",v);
        fprintf(yyout, "\t.word %d\n", n);
    }
    else if(s.size() == 3){
        auto v = s[0]->ID.c_str();
        auto n1 = s[2]->val;
        fprintf(yyout, "\t.comm %s, %d, 4\n", v, n1);
    }
    else{
        yyerror("GlobalVarDecl Error: wrong number of sons\n");
    }
}

void scanfuncdef(t_basenode* root){
    auto s = root->Son;
    if(s.size() == 3){
        scanfunctionhead(s[0]);
        scanexpressions(s[1]);
        scanfunctionend(s[2]);
    }
    else if(s.size() == 2){
        scanfunctionhead(s[0]);
        scanfunctionend(s[1]);
    }
    else{
        yyerror("FuncDef Error: wrong number of sons\n");
    }
}

void scanfunctionhead(t_basenode* root){
    auto s = root->Son;
    if(s.size() == 3){
        auto v = s[0]->ID.c_str();
        auto v1 = v+2;
        stk = s[2]->val;
        stk = (stk/4 +1)*16;
        fprintf(yyout, "\t.text\n");
        fprintf(yyout, "\t.align 2\n");
        fprintf(yyout, "\t.global %s\n",v1);
        fprintf(yyout, "\t.type %s, @function\n",v1);
        fprintf(yyout, "%s:\n",v1);
        if(stk >= -2044 && stk <= 2047){
            fprintf(yyout, "\taddi sp, sp, -%d\n",stk);
            fprintf(yyout, "\tsw ra, %d(sp)\n", stk-4);
        }
        else{
            fprintf(yyout, "\tli s0, %d\n",stk);
            fprintf(yyout, "\tsub sp, sp, s0\n");
            fprintf(yyout,"\tadd s0, s0, sp\n");
            fprintf(yyout, "\tsw ra, -4(s0)\n");
        }
    }
    else{
        yyerror("FunctionHead Error: wrong number of sons\n");
    }
}

void scanfunctionend(t_basenode* root){
    auto s = root->Son;
    if(s.size() == 2){
        auto v = s[1]->ID.c_str();
        auto v1 = v+2;
        fprintf(yyout, "\t.size %s, .-%s\n", v1, v1);
    }
    else{
        yyerror("Functionend Error: wrong number of sons\n");
    }
}

void scanexpressions(t_basenode* root){
    auto s = root->Son;
    if(s.size() == 1){
        scanexpression(s[0]);
    }
    else if(s.size() == 2){
        scanexpressions(s[0]);
        scanexpression(s[1]);
    }
    else{
        yyerror("Expressions Error: wrong number of sons\n");
    }
}

void scanexpression(t_basenode* root){
    auto s = root->Son;
    if(s.size() == 1){//case enter label return
        if(s[0]->type == _enter){
            //do nothing
        }
        else if(s[0]->type == _label){
            fprintf(yyout, ".%s:\n",s[0]->ID.c_str());
        }
        else if(s[0]->type == _return){
            if(stk >= -2044 && stk <= 2047){
                fprintf(yyout, "\tlw ra, %d(sp)\n",stk-4);
                fprintf(yyout,"\taddi sp, sp, %d\n",stk);
            }//debugging
            else{
                fprintf(yyout, "\tli s0, %d\n", stk);
                fprintf(yyout, "\tadd s0, s0, sp\n");
                fprintf(yyout, "\tlw ra, -4(s0)\n");
                fprintf(yyout, "\tli s0, %d\n", stk);
                fprintf(yyout, "\tadd sp, sp, s0\n");
            }
            fprintf(yyout, "\tret\n");
            
        }
        else{
            yyerror("Expression Error1: wrong type of son\n");
        }
    }
    else if(s.size() == 5){
        if(s[1]->type == _assign && s[4]->type == _reg){//case REG ASSIGN REG OP REG ENTER
            auto op = s[3]->ID;
            if(op == "+")
                fprintf(yyout, "\tadd %s, %s, %s\n", s[0]->ID.c_str(), s[2]->ID.c_str(), s[4]->ID.c_str());
            else if(op == "-")
                fprintf(yyout, "\tsub %s, %s, %s\n", s[0]->ID.c_str(), s[2]->ID.c_str(), s[4]->ID.c_str());
            else if(op == "*")
                fprintf(yyout, "\tmul %s, %s, %s\n", s[0]->ID.c_str(), s[2]->ID.c_str(), s[4]->ID.c_str());
            else if(op == "/")
                fprintf(yyout, "\tdiv %s, %s, %s\n", s[0]->ID.c_str(), s[2]->ID.c_str(), s[4]->ID.c_str());
            else if(op == "%")
                fprintf(yyout, "\trem %s, %s, %s\n", s[0]->ID.c_str(), s[2]->ID.c_str(), s[4]->ID.c_str());
            else if(op == "&&"){
                fprintf(yyout, "\tsnez %s, %s\n", s[0]->ID.c_str(), s[2]->ID.c_str());
                fprintf(yyout, "\tsnez s0, %s\n", s[4]->ID.c_str());
                fprintf(yyout, "\tand %s, %s, s0\n", s[0]->ID.c_str(), s[0]->ID.c_str());
            }
            else if(op == "||"){
                fprintf(yyout, "\tor %s, %s, %s\n", s[0]->ID.c_str(), s[2]->ID.c_str(), s[4]->ID.c_str());
                fprintf(yyout, "\tsnez %s, %s\n", s[0]->ID.c_str(),s[0]->ID.c_str());
            }
            else if(op == "<")
                fprintf(yyout, "\tslt %s, %s, %s\n", s[0]->ID.c_str(),s[2]->ID.c_str(),s[4]->ID.c_str());
            else if(op == ">")
                fprintf(yyout, "\tsgt %s, %s, %s\n", s[0]->ID.c_str(),s[2]->ID.c_str(),s[4]->ID.c_str());
            else if(op == "<="){
                fprintf(yyout, "\tsgt %s, %s, %s\n", s[0]->ID.c_str(),s[2]->ID.c_str(),s[4]->ID.c_str());
                fprintf(yyout, "\tseqz %s, %s\n", s[0]->ID.c_str(), s[0]->ID.c_str());
            }
            else if(op == ">="){
                fprintf(yyout, "\tslt %s, %s, %s\n", s[0]->ID.c_str(),s[2]->ID.c_str(),s[4]->ID.c_str());
                fprintf(yyout, "\tseqz %s, %s\n", s[0]->ID.c_str(), s[0]->ID.c_str());
            }
            else if(op == "!="){
                fprintf(yyout, "\txor %s, %s, %s\n", s[0]->ID.c_str(),s[2]->ID.c_str(),s[4]->ID.c_str());
                fprintf(yyout, "\tsnez %s, %s\n", s[0]->ID.c_str(), s[0]->ID.c_str());
            }
            else if(op == "=="){
                fprintf(yyout, "\txor %s, %s, %s\n", s[0]->ID.c_str(),s[2]->ID.c_str(),s[4]->ID.c_str());
                fprintf(yyout, "\tseqz %s, %s\n", s[0]->ID.c_str(), s[0]->ID.c_str());
            }
            else{
                yyerror("Expression Error: wrong type of operator\n");
            }
        }
        else if(s[1]->type == _assign && s[4]->type == _const_int){//case REG ASSIGN REG OP CONST_INT
            auto op = s[3]->ID;
            auto reg1 = s[0]->ID.c_str();
            auto reg2 = s[2]->ID.c_str();
            auto imm = s[4]->val;
            if(op == "+"){
                if(imm <= 2047 && imm > -2048)
                    fprintf(yyout, "\taddi %s, %s, %d\n", reg1, reg2, imm);
                else{
                    fprintf(yyout, "\tli s0, %d\n", imm);
                    fprintf(yyout, "\tadd %s, %s, s0\n", reg1, reg2);
                }
            }
            else if(op == "<"){
                if(imm <= 2047 && imm > -2048)
                    fprintf(yyout, "\tslti %s, %s, %d\n", reg1, reg2, imm);
                else{
                    fprintf(yyout,"\tli s0, %d\n", imm);
                    fprintf(yyout, "\tslt %s, %s, s0\n", reg1, reg2);
                }
            }
            else if(op == "-"){
                if(imm <= 2048 && imm >= -2047){
                    fprintf(yyout, "\taddi %s, %s, %d\n",reg1,reg2,-imm);
                }
                else{
                    fprintf(yyout,"\tli s0, %d\n", imm);
                    fprintf(yyout, "\tsub %s, %s, s0\n", reg1, reg2);
                }
            }
            else if(op == "*"){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\tmul %s, %s, s0\n", reg1, reg2);
            }
            else if(op == "/"){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\tdiv %s, %s, s0\n", reg1, reg2);
            }
            else if(op == "%"){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\trem %s, %s, s0\n", reg1, reg2);
            }
            else if(op == "&&"){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\tsnez %s, %s\n", reg1, reg2);
                fprintf(yyout, "\tsnez s0, s0\n");
                fprintf(yyout, "\tand %s, %s, s0\n", reg1, reg1);
            }
            else if(op == "||"){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\tor %s, %s, s0\n", reg1, reg2);
                fprintf(yyout, "\tsnez %s, %s\n", reg1, reg1);
            }
            else if(op == ">"){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\tsgt %s, %s, s0\n", reg1,reg2);
            }
            else if(op == "<="){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\tsgt %s, %s, s0\n", reg1, reg2);
                fprintf(yyout, "\tseqz %s, %s\n", reg1, reg1);
            }
            else if(op == ">="){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\tslt %s, %s, s0\n", reg1, reg2);
                fprintf(yyout, "\tseqz %s, %s\n", reg1, reg1);
            }
            else if(op == "=="){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\txor %s, %s, s0\n", reg1, reg2);
                fprintf(yyout, "\tseqz %s, %s\n", reg1, reg1);
            }
            else if(op == "!="){
                fprintf(yyout, "\tli s0, %d\n",imm);
                fprintf(yyout, "\txor %s, %s, s0\n", reg1, reg2);
                fprintf(yyout, "\tsnez %s, %s\n", reg1, reg1);
            }
            else{
                yyerror("Expression Error 5: wrong type of operator\n");
            }
        }
        else{
            yyerror("Expression Error 5: wrong type of sons\n");
        }
    }
    else if(s.size() == 4){//case REG ASSIGN OP REG ENTER
        auto reg1 = s[0]->ID.c_str();
        auto op = s[2]->ID;
        auto reg2 = s[3]->ID.c_str();
        if(op == "+"){
            fprintf(yyout, "\tmv %s, %s\n", reg1, reg2);
        }
        else if(op == "-"){
            fprintf(yyout,"\tneg %s, %s\n",reg1, reg2);
        }
        else if(op == "!"){
            fprintf(yyout, "\tseqz %s, %s\n", reg1, reg2);
        }
        else{
            yyerror("Expression Error 4: wrong type of operation\n");
        }
    }
    else if(s.size() == 3){
        if(s[0]->type == _reg && s[2]->type == _reg){//case reg assign reg
            fprintf(yyout, "\tmv %s, %s\n", s[0]->ID.c_str(), s[2]->ID.c_str());
        }
        else if(s[0]->type == _reg && s[2]->type == _const_int){
            fprintf(yyout, "\tli %s, %d\n", s[0]->ID.c_str(), s[2]->val);
        }
        else if(s[0]->type == _store){//case STORE REG NUM ENTER
            auto reg1 = s[1]->ID.c_str();
            auto num = s[2]->val;
            if(num <= 511 && num >= -512)
                fprintf(yyout, "\tsw %s, %d(sp)\n", reg1, num*4);
            else{
                fprintf(yyout, "\tli s0, %d\n", num*4);
                fprintf(yyout,"\tadd s0, sp, s0\n");
                fprintf(yyout, "\tsw %s, 0(s0)\n", reg1);
            }
        }
        else if(s[0]->type == _load && s[1]->type == _const_int){//case LOAD NUM REG ENTER
            auto reg1 = s[2]->ID.c_str();
            auto num = s[1]->val;
            if(num <= 511 && num >= -512)
                fprintf(yyout, "\tlw %s, %d(sp)\n", reg1, num*4);
            else{//unfinished not knowing what to do
                fprintf(yyout, "\tli s0, %d\n", num*4);
                fprintf(yyout,"\tadd s0, sp, s0\n");
                fprintf(yyout, "\tlw %s, 0(s0)\n", reg1);
            }
        }
        else if(s[0]->type == _load && s[1]->type == _variable){
            auto g_var = s[1]->ID.c_str();
            auto reg = s[2]->ID.c_str();
            fprintf(yyout, "\tlui %s, %%hi(%s)\n", reg, g_var);
            fprintf(yyout, "\tlw %s, %%lo(%s)(%s)\n", reg, g_var, reg);
        }
        else if(s[0]->type == _loadaddr && s[1]->type==_const_int){
            auto num = s[1]->val;
            auto reg = s[2]->ID.c_str();
            if(num >= -512 && num <= 511){
                fprintf(yyout, "\taddi %s, sp, %d\n", reg, num*4);
            }
            else{
                fprintf(yyout,"\tli s0, %d\n", num * 4);
                fprintf(yyout, "\tadd %s, s0, sp\n",reg);
            }
        }
        else if(s[0]->type == _loadaddr && s[1]->type == _variable){
            auto g_var = s[1]->ID.c_str();
            auto reg = s[2]->ID.c_str();
            fprintf(yyout, "\tla %s, %s\n", reg, g_var);
        }
        else{
            yyerror("Expression Error 3: wrong type of son\n");
        }
    }
    else if(s.size() == 6){
        if(s[0]->type == _if){
            auto op = s[2]->ID;
            auto reg1 = s[1]->ID.c_str();
            auto reg2 = s[3]->ID.c_str();
            auto label = s[5]->ID.c_str();
            if(op == "<"){
                fprintf(yyout, "\tblt %s, %s, .%s\n", reg1, reg2, label);
            }
            else if(op == ">"){
                fprintf(yyout, "\tbgt %s, %s, .%s\n", reg1, reg2, label);
            }
            else if(op == "<="){
                fprintf(yyout, "\tble %s, %s, .%s\n", reg1, reg2, label);
            }
            else if(op == ">="){
                fprintf(yyout, "\tbge %s, %s, .%s\n", reg1, reg2, label);
            }
            else if(op == "!="){
                fprintf(yyout, "\tbne %s, %s, .%s\n", reg1, reg2, label);
            }
            else if(op == "=="){
                fprintf(yyout, "\tbeq %s, %s, .%s\n", reg1, reg2, label);
            }
            else{
                yyerror("Expression Error 2: wrong type of operator\n");
            }
        }
        else if(s[1]->type == _lbrk){//case REG LBRK CONST_INT RBRK ASSIGN REG
            auto reg1 = s[0]->ID.c_str();
            auto imm = s[2]->val;
            auto reg2 = s[5]->ID.c_str();
            if(imm >= -2048 && imm <= 2047){//int12
                fprintf(yyout, "\tsw %s, %d(%s)\n", reg2, imm, reg1);
            }
            else{
                fprintf(yyout, "\tli s0, %d\n", imm);
                fprintf(yyout, "\tadd s0, s0, %s\n", reg1);
                fprintf(yyout, "\tsw %s, 0(s0)\n", reg2);
            }
        }
        else if(s[1]->type == _assign){//case REG ASSIGN REG LBRK CONST_INT RBRK
            auto reg1 = s[0]->ID.c_str();
            auto reg2 = s[2]->ID.c_str();
            auto imm = s[4]->val;
            if(imm >= -2048 && imm <= 2047){
                fprintf(yyout, "\tlw %s, %d(%s)\n", reg1, imm, reg2);
            }
            else{
                fprintf(yyout,"\tli s0, %d\n", imm);
                fprintf(yyout, "\tadd s0, s0, %s\n", reg2);
                fprintf(yyout, "\tlw %s, 0(s0)\n", reg1);
            }
        }
        else{
            yyerror("Expression Error 6: wrong type of sons\n");
        }
    }
    else if(s.size() == 2){
        if(s[0]->type == _goto){//case goto label
            auto label = s[1]->ID.c_str();
            fprintf(yyout, "\tj .%s\n",label);
        }
        else if(s[0]->type == _call){
            auto func= s[1]->ID.c_str()+2;
            fprintf(yyout,"\tcall %s\n", func);
        }
        else{
            yyerror("Expression Error 2:wrong type of sons\n");
        }
    }
    else{
        yyerror("Expression Error: wrong number of sons\n");
    }
}

void scantigger(t_basenode* root){
    stk = -1;
    t_lineNo = 1;
    for(auto it: root->Son){
        switch(it->type){
            case _enter:
                break;
            case _globalvardecl:
                scanglobalvardecl(it);
                break;
            case _funcdef:
                scanfuncdef(it);
                break;
            default:
                yyerror("Tree Error: wrong type of son\n");
        }
    }
}
