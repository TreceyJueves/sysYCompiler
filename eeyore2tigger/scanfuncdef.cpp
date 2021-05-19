#include"e_parser.hpp"
//准备做寄存器不分配的了。。。不想debug了
//debug5rollback
extern int lineNo;
extern int curplace;//0 for global 1 for local
extern int global_cn;
extern int var_in_func;//record numbers of variables in func for stack
extern int curlayer;
extern int regs[28];//0 x0 1-7 t0-t6 8-19 s0-s11 20-27 a0-a7 0 for unused, 1 for used
extern std::map<std::string, std::map<int,var_info> > ID2Var;
extern std::map<std::string, stack_info> Func2Stack;//record stackinfo of a function
extern void intialize();
extern void scantree(basenode*);
extern void scandeclaration(basenode*);
extern void scaninitialization(basenode*);
extern int get_reg();
extern std::string trans_reg(int);

int func_state = 0;
int param_cnt = 0;//call 的时候clear
int func_param = 0;
std::string cur_func_name = "";

void scanfunctiondef(basenode*);
void scanfunctionheader(basenode*);
void scanstatements(basenode*);
//function end remember to clear symbol table and cur_layer--
void scanfunctionend(basenode*);//unfinished 
void scanstatement(basenode*);
void scanexpression(basenode*);
int scanrightvalue(basenode*);//unfinished return register
int scanvardec(basenode*);
int scanarrayaddress(basenode*);
std::string scanbinop(basenode*);
std::string scanop(basenode*);
std::string scanlogicop(basenode*);

void scanfunctiondef(basenode* root){
    auto s = root->Son;
    if(s.size() == 3){
        scanfunctionheader(s[0]);
        int st = scanvardec(s[1]);
        st+=func_param;
        fprintf(yyout, "[%d]\n", st);
        for(int i = 0; i < func_param; i++){//store param in stack
            std::string out = "store a"+ std::to_string(i)+" "+std::to_string(i)+"\n";
            fprintf(yyout, "%s", out.c_str());
        }
        scanstatements(s[1]);
        scanfunctionend(s[2]);
    }
    //function end remember to clear symbol table and cur_layer--
    else{
        yyerror("FunctionDef Error: wrong number of sons\n");
    }
}
int scanvardec(basenode* root){//unfinished scan the tree in advance remember to take array into account
    auto s = root->Son;
    if(s.size() == 0)//definitely not declaration
        return 0;
    int i = 0;
    for(auto& it: s){
        i += scanvardec(it);
    }
    if(root->type == _declaration){
        if(s.size() == 1){
            i+=1;
        }
        else if(s.size() == 2){
            int nm = s[0]->val;
            nm = nm/4;
            i+=nm;
        }
    }
    return i;
}
void scanfunctionheader(basenode* root){
    auto s = root->Son;
    func_state = 0;
    if(s.size() == 2){
        curplace = 1;//in local
        curlayer++;
        std::string func_name = s[0]->ID;
        cur_func_name = func_name;
        int num = s[1]->val;
        func_param = num;
        std::string func_def_pt1 = func_name + " ["+std::to_string(num)+"] ";
        fprintf(yyout, "%s", func_def_pt1.c_str());
        func_state = 0;//used to record whether caught an expression;
        var_in_func = num;//stack for params
        for(int i = 0; i < num; i++){
            var_info vars;
            vars.is_array = 0;
            vars.is_local = 1;
            vars.place = 0;
            vars.stack_place = i;
            std::string ss = "p"+ std::to_string(i);
            ID2Var[ss][curlayer] = vars;
        }
    } 
    else{
        yyerror("FunctionHeader Error: Wrong number of sons\n");
    }
}

void scanfunctionend(basenode* root){
    auto s = root->Son;
    if(s.size() == 2){
        std::string out = "end "+cur_func_name+"\n";
        fprintf(yyout, "%s", out.c_str());
        for(auto& t:ID2Var){
            if(t.second.find(curlayer) != t.second.end()){
                t.second.erase(curlayer);
            }
        }
        for(int i = 0; i < func_param; i++){
            regs[i+20] = 0;
        }
        func_param = 0;
        curlayer--;
    }
}

void scanstatements(basenode* root){
    printf("start scanning statements\n");
    auto s = root->Son;
    if(s.size() == 1){
        scanstatement(s[0]);
    }
    else if(s.size() == 2){
        scanstatements(s[0]);
        auto grand_son = s[1]->Son;
        printf("grandson type: %d\n",grand_son[0]->type);
        scanstatement(s[1]);
    }
    else{
        yyerror("Statements Error: wrong number of sons\n");
    }
}

void scanstatement(basenode* root){
    printf("start scanning statement\n");
    auto s = root->Son;
    if(s.size() == 1){
        if(s[0]->type == _expression){
            scanexpression(s[0]);
        }
        else if(s[0]->type == _declaration){
            scandeclaration(s[0]);
        }
        else{
            yyerror("Statement Error: wrong type of son\n");
        }
    }
    else{
        yyerror("Statement Error: wrong number of sons\n");
    }
}

void scanexpression(basenode* root){
    printf("start scanning expression\n");
    auto s = root->Son;
    if(s.size() == 5){//VARIABLE ASSIGN RightValue BinOp RightValue
        std::string var_name = s[0]->ID;
        int reg_l = -1;
        int reg_r = -1;
        if(s[2]->Son[0]->type == _variable){//here
            auto sname = s[2]->Son[0]->ID;
            int var_lay2 = curlayer;
            while(var_lay2 >= 0 && ID2Var[sname].find(var_lay2) == ID2Var[sname].end()){
                var_lay2--;
            }
            if (ID2Var[sname][var_lay2].is_array){
                reg_l = scanarrayaddress(s[2]->Son[0]);
                reg_r = scanrightvalue(s[4]);
                auto r = trans_reg(reg_r);
                std::string outi = r+" = "+r+" * 4\n";
                fprintf(yyout, "%s", outi.c_str());
            }
            else{
                reg_l = scanrightvalue(s[2]);
                reg_r = scanrightvalue(s[4]);
            }
        }
        else if(s[4]->Son[0]->type == _variable){//here
            auto sname = s[4]->Son[0]->ID;
            int var_lay2 = curlayer;
            while(var_lay2 >= 0 && ID2Var[sname].find(var_lay2) == ID2Var[sname].end()){
                var_lay2--;
            }
            if (ID2Var[sname][var_lay2].is_array){
                reg_r = scanarrayaddress(s[4]->Son[0]);
                reg_l = scanrightvalue(s[2]);
                auto l = trans_reg(reg_l);
                std::string outi = l+" = "+l+" * 4\n";
                fprintf(yyout, "%s", outi.c_str());
            }
            else{
                reg_l = scanrightvalue(s[2]);
                reg_r = scanrightvalue(s[4]);
            }
        }
        else{
            reg_l = scanrightvalue(s[2]);
            reg_r = scanrightvalue(s[4]);
        }
        std::string name_l = trans_reg(reg_l);//always send reg for convenience
        std::string name_r = trans_reg(reg_r);//always send reg for convenience
        std::string op = scanbinop(s[3]);
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
        std::string output = name_l+" = "+ name_l +" "+op+" "+ name_r+"\n";
        fprintf(yyout,"%s", output.c_str());
        if(var_local == 0){//global variable
            std::string output1 = "loadaddr v"+std::to_string(var_place)+" "+ reg_name+"\n";
            fprintf(yyout, "%s",output1.c_str());
        }
        else if(var_local == 1){//local variable
            std::string output1 = "loadaddr " + std::to_string(var_place)+" "+ reg_name+"\n";
            fprintf(yyout, "%s",output1.c_str());
        }
        else{
            yyerror("Expression Error 5: wrong type of var_local_val\n");
        }
        std::string output2 = reg_name+" [0] = "+name_l+"\n";
        fprintf(yyout, "%s", output2.c_str());
        if(reg_l != 0)
            regs[reg_l] = 0;//free the reg used
        if(reg_r != 0)
            regs[reg_r] = 0;//free the reg used
        if(reg_num != 0)
            regs[reg_num] = 0;
    }
    else if(s.size() == 3){//case VARIABLE (ASSIGN) Op RightValue
        std::string var_name = s[0]->ID;
        auto reg_l = scanrightvalue(s[2]);
        std::string name_l = trans_reg(reg_l);//always send reg for convenience
        std::string op = scanop(s[1]);
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
        std::string output = name_l+" = "+op+" "+ name_l+"\n";
        fprintf(yyout,"%s", output.c_str());
        if(var_local == 0){//global variable
            std::string output1 = "loadaddr v"+std::to_string(var_place)+" "+ reg_name+"\n";
            fprintf(yyout, "%s",output1.c_str());
        }
        else if(var_local == 1){//local variable
            std::string output1 = "loadaddr " + std::to_string(var_place)+" "+ reg_name+"\n";
            fprintf(yyout, "%s", output1.c_str());
        }
        else{
            yyerror("Expression Error 3: wrong type of var_local_val\n");
        }
        std::string output2 = reg_name+" [0] = "+name_l+"\n";
        fprintf(yyout, "%s", output2.c_str());
        if(reg_l != 0)
            regs[reg_l] = 0;
        if(reg_num != 0)
            regs[reg_num] = 0;
    }
    else if(s.size() == 2){//VariableAssign GotoLabel ParamRightValue CallFunc ReturnRightValue
        if(s[0]->type == _variable){//case Variable assign Right Value
            printf("case Variable assign Right Value\n");
            std::string var_name = s[0]->ID;
            int reg_l = -1;
            if(s[1]->Son[0]->type == _variable){
                auto sname = s[1]->Son[0]->ID;
                int var_lay2 = curlayer;
                while(var_lay2 >= 0 && ID2Var[sname].find(var_lay2) == ID2Var[sname].end()){
                    var_lay2--;
                }
                if (ID2Var[sname][var_lay2].is_array){
                    reg_l = scanarrayaddress(s[1]->Son[0]);
                }
                else{
                    reg_l = scanrightvalue(s[1]);
                }
            }
            else{
                reg_l = scanrightvalue(s[1]);
            }
            std::string name_l = trans_reg(reg_l);//always send reg for convenience
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
            printf("var place: %d\n",var_place);
            if(var_local == 0){//global variable
                std::string output1 = "loadaddr v"+std::to_string(var_place)+" "+ reg_name+"\n";
                fprintf(yyout, "%s",output1.c_str());
            }
            else if(var_local == 1){//local variable
                std::string output1 = "loadaddr " + std::to_string(var_place)+" "+ reg_name+"\n";
                fprintf(yyout, "%s",output1.c_str());
            }
            else{
                yyerror("Expression Error: wrong type of var_local_val\n");
            }
            std::string output2 = reg_name+" [0] = "+name_l+"\n";
            fprintf(yyout, "%s", output2.c_str());
            if(reg_l != 0)
                regs[reg_l] = 0;
            if(reg_num != 0)
                regs[reg_num] = 0;
        }
        else if(s[0]->type == _goto){
            auto label = s[1]->ID;
            std::string output = "goto "+ label+"\n";
            fprintf(yyout, "%s", output.c_str());
        }
        else if(s[0]->type == _param){//param rightvalue
            int p_reg = param_cnt+20;
            auto p_reg_name = trans_reg(p_reg);
            regs[p_reg] = 1;
            std::string p_name = "";
            int p_isarray = 0;
            if(s[1]->Son[0]->type == _variable){
                p_name = s[1]->Son[0]->ID;
                p_isarray = ID2Var[p_name][curlayer].is_array;
            }
            int reg_num = -1;
            if(s[1]->Son[0]->type == _const_int || p_isarray == 0)
                reg_num = scanrightvalue(s[1]);
            else
                reg_num = scanarrayaddress(s[1]->Son[0]);
            auto reg_name = trans_reg(reg_num);
            std::string output = p_reg_name + " = " +reg_name+"\n";
            fprintf(yyout, "%s", output.c_str());
            if(reg_num != 0)
                regs[reg_num] = 0;
            param_cnt++;
        }
        else if(s[0]->type == _call){
            auto func_name = s[1]->ID;
            param_cnt = 0;
            std::string output = "call "+ func_name+"\n";
            fprintf(yyout, "%s", output.c_str());
        }
        else if(s[0]->type == _return){//case return rightvalue
            printf("case : return rightvalue\n");
            int ret_reg = -1;
            if(s[1]->Son[0]->type == _variable){
                auto sname = s[1]->Son[0]->ID;
                int var_lay2 = curlayer;
                while(var_lay2 >= 0 && ID2Var[sname].find(var_lay2) == ID2Var[sname].end()){
                    var_lay2--;
                }
                if (ID2Var[sname][var_lay2].is_array){
                    ret_reg = scanarrayaddress(s[1]->Son[0]);
                }
                else{
                    ret_reg = scanrightvalue(s[1]);
                }
            }
            else
                ret_reg = scanrightvalue(s[1]);
            auto ret_name = trans_reg(ret_reg);
            if(ret_reg != 20){
                std::string output = "a0 = "+ret_name+"\n";
                fprintf(yyout, "%s", output.c_str());
            }
            printf("return here2\n");
            fprintf(yyout,"return\n");
            if(ret_reg != 0)
                regs[ret_reg] = 0;
        }
        else{
            printf("sontype: %d\n",s[0]->type);
            yyerror("Expression Error 2: Wrong type of sons\n");
        }
    }
    else if(s.size() == 1){//case return / label
        printf("case expression size1:\n");
        if(s[0]->type == _return){
            printf("return here\n");
            fprintf(yyout, "return\n");
        }
        else if(s[0]->type == _label){
            printf("case label:\n");
            auto str = s[0]->ID;
            fprintf(yyout,"%s:\n", str.c_str());
        }
        else if(s[0]->type == _enter){
            //enter do nothing, skip
        }
        else{
            yyerror("Expression Error 1: wrong type of son\n");
        }
    }
    else if(s.size() == 4){//case VARIABLE ASSIGN CALL FUNC
        auto func_name = s[3]->ID;
        std::string output = "call "+func_name+"\n";
        fprintf(yyout, "%s", output.c_str());
        std::string var_name = s[0]->ID;
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
            std::string output1 = "loadaddr v"+std::to_string(var_place)+" "+ reg_name+"\n";
            fprintf(yyout, "%s",output1.c_str());
        }
        else if(var_local == 1){//local variable
            std::string output1 = "loadaddr " + std::to_string(var_place)+" "+ reg_name+"\n";
            fprintf(yyout, "%s",output1.c_str());
        }
        else{
            yyerror("Expression Error 4: wrong type of var_local val\n");
        }
        std::string output2 = reg_name + " [0] = a0"+ "\n";
        fprintf(yyout, "%s", output2.c_str());
        param_cnt = 0;
    }
    else if(s.size() == 6){
    //unfinished
        if(s[0]->type == _if){//case if rightvalue logicop rightvalue goto label
            int reg_l = scanrightvalue(s[1]);
            int reg_r = scanrightvalue(s[3]);
            auto op = scanlogicop(s[2]);
            auto name_l = trans_reg(reg_l);
            auto name_r = trans_reg(reg_r);
            auto label = s[5]->ID;
            std::string output = "if "+name_l+" "+op +" "+name_r+ " goto "+ label+"\n";
            fprintf(yyout, "%s", output.c_str());
            if(reg_l != 0)
                regs[reg_l] = 0;
            if(reg_r != 0)
                regs[reg_r] = 0;
        }
        else if(s[4]->type == _assign){//VARIABLE LBRK RightValue RBRK ASSIGN RightValue
            printf("VARIABLE LBRK RightValue RBRK ASSIGN RightValue\n");
            printf("%d, %d, %d, %d, %d, %d\n",s[0]->type, s[1]->type, s[2]->type, s[3]->type, s[4]->type, s[5]->type);
            std::string var_name = s[0]->ID;
            printf("here\n");
            auto reg_l = scanrightvalue(s[2]);
            printf("here2\n");
            auto reg_r = scanrightvalue(s[5]);
            std::string name_r = trans_reg(reg_r);
            std::string name_l = trans_reg(reg_l);//always send reg for convenience
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
                std::string output1 = "loadaddr v"+std::to_string(var_place)+" "+ reg_name+"\n";
                fprintf(yyout, "%s",output1.c_str());
            }
            else if(var_local == 1 && var_name[0] != 'p'){//local variable
                printf("array not param\n");
                std::string output1 = "loadaddr " + std::to_string(var_place)+" "+ reg_name+"\n";
                fprintf(yyout, "%s", output1.c_str());
            }
            else if(var_local == 1 && var_name[0] == 'p'){
                printf( "param array\n");
                std::string output1 = "load " + std::to_string(var_place)+" "+ reg_name+"\n";
                fprintf(yyout, "%s", output1.c_str());
            }
            else{
                yyerror("Expression Error 3: wrong type of var_local_val\n");
            }
            std::string outp = reg_name + " = "+ reg_name+" + " + name_l+"\n";
            fprintf(yyout, "%s", outp.c_str());
            outp = reg_name+ " [0] = "+ name_r+"\n";
            fprintf(yyout, "%s", outp.c_str());
            if(reg_num != 0)
                regs[reg_num] = 0;
            if(reg_r != 0)
                regs[reg_r] = 0;
            if(reg_l != 0)
                regs[reg_l] = 0;
        }
        else if(s[1]->type == _assign){//case VARIABLE ASSIGN VARIABLE LBRK RightValue RBRK
            printf("case VARIABLE ASSIGN VARIABLE LBRK RightValue RBRK\n");
            std::string var_name_l = s[0]->ID;
            std::string var_name_r = s[2]->ID;
            auto reg_l = scanrightvalue(s[4]);
            std::string name_l = trans_reg(reg_l);//always send reg for convenience
            int var_lay_l = curlayer;
            int var_lay_r = curlayer;
            if(ID2Var.find(var_name_l) == ID2Var.end()){
                auto str = "variable "+var_name_l+"undefined\n";
                yyerror(str.c_str());
            }
            while(var_lay_l >= 0 && ID2Var[var_name_l].find(var_lay_l) == ID2Var[var_name_l].end()){
                var_lay_l--;
            }
            if(var_lay_l < 0){
                yyerror("wrong layer of variable\n");
            }
            int reg_num_l = get_reg();
            auto reg_name_l = trans_reg(reg_num_l);
            int var_local_l = ID2Var[var_name_l][var_lay_l].is_local;
            int var_place_l = ID2Var[var_name_l][var_lay_l].stack_place;
            if(var_local_l == 0){//global variable
                std::string output1 = "loadaddr v"+std::to_string(var_place_l)+" "+ reg_name_l+"\n";
                fprintf(yyout, "%s",output1.c_str());
            }
            else if(var_local_l == 1){//local variable
                std::string output1 = "loadaddr " + std::to_string(var_place_l)+" "+ reg_name_l+"\n";
                fprintf(yyout, "%s", output1.c_str());
            }
            else{
                yyerror("Expression Error 3: wrong type of var_local_val\n");
            }

            if(ID2Var.find(var_name_r) == ID2Var.end()){
                auto str = "variable "+var_name_r+"undefined\n";
                yyerror(str.c_str());
            }
            while(var_lay_r >= 0 && ID2Var[var_name_r].find(var_lay_r) == ID2Var[var_name_r].end()){
                var_lay_r--;
            }
            if(var_lay_r < 0){
                yyerror("wrong layer of variable\n");
            }
            int reg_num_r = get_reg();
            auto reg_name_r = trans_reg(reg_num_r);
            int var_local_r = ID2Var[var_name_r][var_lay_r].is_local;
            int var_place_r = ID2Var[var_name_r][var_lay_r].stack_place;
            if(var_local_r == 0){//global variable
                std::string output1 = "loadaddr v"+std::to_string(var_place_r)+" "+ reg_name_r+"\n";
                fprintf(yyout, "%s",output1.c_str());
            }
            else if(var_local_r == 1 && var_name_r[0] != 'p'){//local variable
                printf("array not param\n");
                std::string output1 = "loadaddr " + std::to_string(var_place_r)+" "+ reg_name_r+"\n";
                fprintf(yyout, "%s", output1.c_str());
            }
            else if(var_local_r == 1 && var_name_r[0] == 'p'){//local variable
                printf("param array\n");
                std::string output1 = "load " + std::to_string(var_place_r)+" "+ reg_name_r+"\n";
                fprintf(yyout, "%s", output1.c_str());
            }
            else{
                yyerror("Expression Error 3: wrong type of var_local_val\n");
            }
            std::string outi = reg_name_r + " = " + reg_name_r + " + " + name_l +"\n";
            fprintf(yyout, "%s", outi.c_str());
            int tmp_reg = get_reg();
            auto tmp_name = trans_reg(tmp_reg);
            std::string out2 = tmp_name + " = " + reg_name_r + " [0]\n";
            fprintf(yyout, "%s", out2.c_str());
            std::string out3 = reg_name_l + " [0] = " + tmp_name +"\n";
            fprintf(yyout, "%s", out3.c_str()); 
            if(tmp_reg != 0)
                regs[tmp_reg] = 0;
            if(reg_l != 0)
                regs[reg_l] = 0;
            if(reg_num_l != 0)
                regs[reg_num_l] = 0;
            if(reg_num_r != 0)
                regs[reg_num_r] = 0;
        }
        else{
            yyerror("Expression Error 6: wrong type of sons\n");
        }
    }
    else{
        yyerror("Expression Error: wrong number of sons\n");
    }
}

std::string scanbinop(basenode* root){
    auto s = root->Son;
    if(s.size() == 1){
        if(s[0]->type == _op){
            return scanop(s[0]);
        }
        else if(s[0]->type == _logicop){
            return scanlogicop(s[0]);
        }
        else{
            yyerror("BinOp Error: Wrong type of son\n");
            return "";
        }
    }
    else{
        yyerror("BinOp Error: wrong number of sons\n");
        return "";
    }
}

std::string scanop(basenode* root){
    auto s = root->Son;
    if(s.size() == 1){
        switch(s[0]->type){
            case _add:
                return "+";
                break;
            case _minus:
                return "-";
                break;
            case _not:
                return "!";
                break;
            default:
                yyerror("Op Error: wrong type of son\n");
                return "";
        }
    }
    else{
        yyerror("Op Error: wrong number of sons\n");
        return "";
    }
}
int scanarrayaddress(basenode* root){
 //   fprintf(yyout,"load array address\n");
    int regi = get_reg();
    auto reg_name = trans_reg(regi);
    auto varid = root->ID;
    int var_layer = curlayer;    
    while(var_layer >= 0 && ID2Var[varid].find(var_layer) == ID2Var[varid].end()){
        var_layer--;
    }
    int islocal =  ID2Var[varid][var_layer].is_local;
    int stackplace = ID2Var[varid][var_layer].stack_place;
    if(islocal){
        std::string out = "loadaddr "+std::to_string(stackplace)+" "+reg_name+"\n";
        fprintf(yyout, "%s", out.c_str());
    }
    else{
        std::string out = "loadaddr v"+std::to_string(stackplace)+" "+reg_name+"\n";
        fprintf(yyout, "%s", out.c_str());
    }
    return regi;
}
std::string scanlogicop(basenode* root){
    auto s = root->Son;
    if(s.size() == 1){
        switch(s[0]->type){
            case _mul:
                return "*";
                break;
            case _div:
                return "/";
                break;
            case _mod:
                return "%";
                break;
            case _less:
                return "<";
                break;
            case _more:
                return ">";
                break;
            case _leq:
                return "<=";
                break;
            case _geq:
                return ">=";
                break;
            case _equal:
                return "==";
                break;
            case _neq:
                return "!=";
                break;
            case _and:
                return "&&";
                break;
            case _or:
                return "||";
                break;
            default:
                yyerror("LogicOp Error: wrong type of son\n");
                return "";
        }
    }
    else{
        yyerror("LogicOp Error: wrong number of sons\n");
        return "";
    }
}

int scanrightvalue(basenode* root){
    auto s = root->Son;
    printf("rightvalue type: %d\n",root->type);
    if(s.size() == 1){
        if(s[0]->type == _variable){
            std::string var_name = s[0]->ID;
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
                std::string output1 = "load v"+std::to_string(var_place)+" "+ reg_name+"\n";
                fprintf(yyout, "%s",output1.c_str());
            }
            else if(var_local == 1){//local variable
                std::string output1 = "load " + std::to_string(var_place)+" "+ reg_name+"\n";
                fprintf(yyout, "%s", output1.c_str());
            }
            else{
                yyerror("Rightvalue Error variable: wrong type of var_local_val\n");
            }
            return reg_num;
        }
        else if(s[0]->type == _const_int){
            int value = s[0]->val;
            int reg_n = get_reg();
            std::string reg_name = trans_reg(reg_n);
            std::string output = reg_name + " = " + std::to_string(value)+"\n";
            fprintf(yyout, "%s", output.c_str());
            return reg_n;
        }
        else{
            yyerror("RightValue Error 1: wrong type of son\n");
            return -1;
        }
    }
    else{
        printf("num of sons: %ld\n",s.size());
        yyerror("RightValue Error: wrong number of sons\n");
        return -1;
    }
}
