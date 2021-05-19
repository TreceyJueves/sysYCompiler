#include"e_parser.hpp"
//准备做寄存器不分配的了。。。不想debug了
int lineNo = 0;
int curplace = 0;//0 for global 1 for local
int global_cnt = 0;
int var_in_func = 0;//record numbers of variables in func for stack
int curlayer = 0;
int regs[28] = {1};//0 x0 1-7 t0-t6 8-19 s0-s11 20-27 a0-a7 0 for unused, 1 for used
std::map<std::string, std::map<int,var_info> > ID2Var;
std::map<std::string, stack_info> Func2Stack;//record stackinfo of a function
void initialize();
void scantree(basenode*);
void scandeclaration(basenode*);
void scaninitialization(basenode*);
int get_reg();
std::string trans_reg(int);

extern void scanfunctiondef(basenode*);

void initialize(){
    curplace = 0;
    global_cnt = 0;
    var_in_func = 0;
    curlayer = 0;
    ID2Var.clear();
}

int get_reg(){
    int i = 1;
    for(; i < 28; i++){
        if(regs[i] == 0){
            regs[i] = 1;
            return i;
        }
    }
    return 28;
}

std::string trans_reg(int i){
    if(i == 0)
        return "x0";
    if(i >= 1 && i <= 7){
        return "t"+std::to_string(i-1);
    }
    if(i>=8 && i<=19){
        return "s"+std::to_string(i-8);
    }
    if(i <=27 && i >= 20){
        return "a"+std::to_string(i-20);
    }
    printf("%d",i);
    yyerror("illigal register\n");
    return "";
}

void scandeclaration(basenode* root){
    printf("start scanning declaration\n");
    auto s = root->Son;        
    auto id_name = s.back()->ID;        
    var_info vars;
    if(curplace == 0){//isglobal
        vars.is_local = 0;
        if(s.size() == 1){
            vars.is_array = 0;
            vars.place = 0;
            vars.stack_place = global_cnt;
            if(ID2Var.find(id_name) != ID2Var.end() && ID2Var[id_name].find(curlayer) != ID2Var[id_name].end()){
                std::string err = "Declaration Error: variable "+ id_name + "redeclared\n";
                yyerror(err.c_str());
            }
            ID2Var[id_name][curlayer] = vars;
            fprintf(yyout, "v%d = 0\n", global_cnt++);
        }
        else if(s.size() == 2){
            int num = s[0]->val;
            vars.is_array = 1;
            vars.place = 0;
            vars.stack_place = global_cnt;
            if(ID2Var.find(id_name) != ID2Var.end() && ID2Var[id_name].find(curlayer) != ID2Var[id_name].end()){
                std::string err = "Declaration Error: variable array"+ id_name + "redeclared\n";
                yyerror(err.c_str());
            }
            ID2Var[id_name][curlayer] = vars;
            fprintf(yyout, "v%d = malloc %d\n", global_cnt++, num);
        }
        else{
            yyerror("Declaration Error: wrong number of sons\n");
        }
    }
    else{
        vars.is_local = 1;
        if(s.size() == 1){
            printf("declaration 1 here\n");
            vars.is_array = 0;
            vars.stack_place = var_in_func++;
            vars.place = 0;
            if(ID2Var.find(id_name) != ID2Var.end() && ID2Var[id_name].find(curlayer) != ID2Var[id_name].end()){
                std::string err = "Declaration Error: variable "+ id_name + "redeclared\n";
                yyerror(err.c_str());
            }
            ID2Var[id_name][curlayer] = vars;
        }
        if(s.size() == 2){
            printf("declaration 2 here\n");
            int num = s[0]->val;
            vars.is_array = 1;
            vars.stack_place = var_in_func;
            vars.place = 0;
            var_in_func += num/4;
            if(ID2Var.find(id_name) != ID2Var.end() && ID2Var[id_name].find(curlayer) != ID2Var[id_name].end()){
                std::string err = "Declaration Error: variable array"+ id_name + "redeclared\n";
                yyerror(err.c_str());
            }
            ID2Var[id_name][curlayer] = vars;
        }
    }
    return;
}

void scaninitialization(basenode* root){
    auto s = root->Son;
    if(s.size() == 2){//single variable
        auto var_name = s[0]->ID;
        int num = s[1]->val;
        int var_lay = curlayer;
        if(ID2Var.find(var_name) == ID2Var.end()){
            auto str = "variable "+var_name+"undefined\n";
            yyerror(str.c_str());
        }
        while(var_lay >= 0 && ID2Var[var_name].find(var_lay) == ID2Var[var_name].end()){
            var_lay--;
        }
        if(var_lay < 0){
            yyerror("wrong layer of variable\n");
        }
        int reg_num = get_reg();
        auto reg_name = trans_reg(reg_num);
        int var_local = ID2Var[var_name][var_lay].is_local;
        int var_place = ID2Var[var_name][var_lay].stack_place;
        if(var_local == 0){//global variable
            auto output = "loadaddr v"+std::to_string(var_place)+" "+reg_name+"\n";
            fprintf(yyout, "%s",output.c_str());
            auto output1 = reg_name+"[0] = "+std::to_string(num)+"\n";
            fprintf(yyout, "%s",output1.c_str());
        }
        if(var_local == 1){//local variable
            auto output = "loadaddr "+std::to_string(var_place)+" "+reg_name+"\n";
            fprintf(yyout,"%s", output.c_str());
            auto output1 = reg_name+" [0] = "+std::to_string(num)+"\n";
            fprintf(yyout, "%s", output1.c_str());
        }
        regs[reg_num] = 0;
    }
    else if(s.size() == 3){
        auto var_name = s[0]->ID;
        auto place_in_array = s[1]->val;
        auto num = s[2]->val;
        int var_lay = curlayer;
        if(ID2Var.find(var_name) == ID2Var.end()){
            auto str = "variable "+var_name+"undefined\n";
            yyerror(str.c_str());
        }
        while(var_lay >= 0 && ID2Var[var_name].find(var_lay) == ID2Var[var_name].end()){
            var_lay--;
        }
        if(var_lay < 0){
            yyerror("wrong layer of variable\n");
        }        int reg_num = get_reg();
        auto reg_name = trans_reg(reg_num);
        int var_local = ID2Var[var_name][var_lay].is_local;
        int var_place = ID2Var[var_name][var_lay].stack_place;
        if(var_local == 0){//global variable
            auto output = "loadaddr v"+std::to_string(var_place)+" "+reg_name+"\n";
            fprintf(yyout, "%s",output.c_str());
            auto output1 = reg_name+" ["+std::to_string(place_in_array)+"] = "+std::to_string(num)+"\n";
            fprintf(yyout, "%s",output1.c_str());
        }
        if(var_local == 1){//local variable
            auto output = "loadaddr "+std::to_string(var_place)+" "+reg_name+"\n";
            fprintf(yyout, "%s",output.c_str());
            auto output1 = reg_name+" ["+std::to_string(place_in_array)+"] = "+std::to_string(num)+"\n";
            fprintf(yyout, "%s", output1.c_str());
        }
        regs[reg_num] = 0;
    }
    else{
        yyerror("Initialization Error: wrong number of sons\n");
    }
}


void scantree(basenode* root){
    initialize();
    for(auto it: root->Son){
        switch(it->type){
            case _declaration:
                curplace = 0;
                scandeclaration(it);
                break;
            case _initialization:
                curplace = 0;
                scaninitialization(it);
                break;
            case _functiondef:
                scanfunctiondef(it);
                break;
            case _enter:
                break;
            default:
                yyerror("Tree Error: wrong type of sons\n");
                break;
        }
    }
}
