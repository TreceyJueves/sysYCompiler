#include"e_parser.hpp"
//准备做寄存器不分配的了。。。不想debug了
int e_lineNo = 0;
int e_curplace = 0;//0 for global 1 for local
int global_cnt = 0;
int var_in_func = 0;//record numbers of variables in func for stack
int e_curlayer = 0;
int regs[28] = {1};//0 x0 1-7 t0-t6 8-19 s0-s11 20-27 a0-a7 0 for unused, 1 for used
std::map<std::string, std::map<int,var_info> > ID2Var;
std::map<std::string, stack_info> Func2Stack;//record stackinfo of a function
void e_initialize();
void e_scantree(e_basenode*);
void scandeclaration(e_basenode*);
void scaninitialization(e_basenode*);
int get_reg();
std::string trans_reg(int);
std::vector<init_info> init_vector;

extern void scanfunctiondef(e_basenode*);

//things to do:记住在main里初始化全局变量......

void e_initialize(){
    e_curplace = 0;
    global_cnt = 0;
    var_in_func = 0;
    e_curlayer = 0;
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
    //printf("%d",i);
    e2terror("illegal register\n");
    return "";
}

void scandeclaration(e_basenode* root){
    //this part + intialization have trouble
    //printf("start scanning declaration\n");
    auto s = root->Son;        
    auto id_name = s.back()->ID;        
    var_info vars;
    if(e_curplace == 0){//isglobal
        vars.is_local = 0;
        if(s.size() == 1){
            vars.is_array = 0;
            vars.place = 0;
            vars.stack_place = global_cnt;
            if(ID2Var.find(id_name) != ID2Var.end() && ID2Var[id_name].find(e_curlayer) != ID2Var[id_name].end()){
                std::string err = "Declaration Error: variable "+ id_name + "redeclared\n";
                e2terror(err.c_str());
            }
            ID2Var[id_name][e_curlayer] = vars;
            fprintf(e2tout, "v%d = 0\n", global_cnt++);
        }
        else if(s.size() == 2){
            int num = s[0]->val;
            vars.is_array = 1;
            vars.place = 0;
            vars.stack_place = global_cnt;
            if(ID2Var.find(id_name) != ID2Var.end() && ID2Var[id_name].find(e_curlayer) != ID2Var[id_name].end()){
                std::string err = "Declaration Error: variable array"+ id_name + "redeclared\n";
                e2terror(err.c_str());
            }
            ID2Var[id_name][e_curlayer] = vars;
            fprintf(e2tout, "v%d = malloc %d\n", global_cnt++, num);
        }
        else{
            e2terror("Declaration Error: wrong number of sons\n");
        }
    }
    else{
        vars.is_local = 1;
        if(s.size() == 1){
            //printf("declaration 1 here\n");
            vars.is_array = 0;
            vars.stack_place = var_in_func++;
            vars.place = 0;
            if(ID2Var.find(id_name) != ID2Var.end() && ID2Var[id_name].find(e_curlayer) != ID2Var[id_name].end()){
                std::string err = "Declaration Error: variable "+ id_name + "redeclared\n";
                e2terror(err.c_str());
            }
            ID2Var[id_name][e_curlayer] = vars;
        }
        if(s.size() == 2){
            //printf("declaration 2 here\n");
            int num = s[0]->val;
            vars.is_array = 1;
            vars.stack_place = var_in_func;
            vars.place = 0;
            var_in_func += num/4;
            if(ID2Var.find(id_name) != ID2Var.end() && ID2Var[id_name].find(e_curlayer) != ID2Var[id_name].end()){
                std::string err = "Declaration Error: variable array"+ id_name + "redeclared\n";
                e2terror(err.c_str());
            }
            ID2Var[id_name][e_curlayer] = vars;
        }
    }
    return;
}

void scaninitialization(e_basenode* root){
    //printf("start scanning initialization\n");
    auto s = root->Son;
    if(s.size() == 2){//single variable
        auto var_name = s[0]->ID;
        int num = s[1]->val;
        int var_lay = e_curlayer;
        if(ID2Var.find(var_name) == ID2Var.end()){
            auto str = "variable "+var_name+"undefined\n";
            e2terror(str.c_str());
        }
        while(var_lay >= 0 && ID2Var[var_name].find(var_lay) == ID2Var[var_name].end()){
            var_lay--;
        }
        if(var_lay < 0){
            e2terror("wrong layer of variable\n");
        }
        int var_local = ID2Var[var_name][var_lay].is_local;
        int var_place = ID2Var[var_name][var_lay].stack_place;
        if(var_local == 0){//global variable
         //   auto output = "v"+std::to_string(var_place)+" = "+std::to_string(num)+"\n";
            //fprintf(e2tout, "%s",output.c_str());
            init_info ss;
            ss.var_name = "v"+std::to_string(var_place);
            ss.index = -1;
            ss.value = num;
            init_vector.push_back(ss);
        }
        if(var_local == 1){//local variable
        exit(153);
            e2terror("Initialization error: local variable cannot be initialized outside\n");
        }
    }
    else if(s.size() == 3){
        auto var_name = s[0]->ID;
        auto place_in_array = s[1]->val;
        auto num = s[2]->val;
        int var_lay = e_curlayer;
        if(ID2Var.find(var_name) == ID2Var.end()){
            auto str = "variable "+var_name+"undefined\n";
            e2terror(str.c_str());
        }
        while(var_lay >= 0 && ID2Var[var_name].find(var_lay) == ID2Var[var_name].end()){
            var_lay--;
        }
        if(var_lay < 0){
            e2terror("wrong layer of variable\n");
        }
        int var_local = ID2Var[var_name][var_lay].is_local;
        int var_place = ID2Var[var_name][var_lay].stack_place;
        if(var_local == 0){//global variable
        //    auto output = "v"+std::to_string(var_place)+" ["+std::to_string(place_in_array)+"] = "+std::to_string(num)+"\n";
        //    fprintf(e2tout, "%s",output.c_str());
            init_info ss;
            ss.var_name = "v"+std::to_string(var_place);
            ss.index = place_in_array;
            ss.value = num;
            init_vector.push_back(ss);
        }
        if(var_local == 1){//local variable
            exit(184);
            e2terror("Initialization Error: local variable cannot be initialized outside\n");
        }
    }
    else{
        e2terror("Initialization Error: wrong number of sons\n");
    }
}


void e_scantree(e_basenode* root){
    e_initialize();
    for(auto it: root->Son){
        switch(it->type){
            case _declaration:
                e_curplace = 0;
                scandeclaration(it);
                break;
            case _initialization:
                e_curplace = 0;
                //printf("scanning initialization\n");
                scaninitialization(it);
                break;
            case _functiondef:
                scanfunctiondef(it);
                break;
            case _enter:
                break;
            default:
                e2terror("Tree Error: wrong type of sons\n");
                break;
        }
    }
}
