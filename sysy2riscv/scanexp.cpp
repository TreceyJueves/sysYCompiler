#include "parser.hpp"

extern int var_cnt, tmp_cnt, param_cnt, label_cnt;
extern int label_cnt, func_cnt;
extern int layer;
extern bool noprint;
extern bool return_void;
extern std::map<std::string, std::map<int, int> >  ID2T;//ID layer Tid
extern std::map<int, std::map<std::string, int> > L2ID;//layer ID Tid
extern std::vector<int> tmp_array;//record initialization of multidimension array(数组的大小)
extern std::map<int, std::pair<std::pair<int, int>, v_type> > var_type;//Tid value/id, index/size(only array),type
extern std::map<int, std::vector<int> > var_array;//Tid Size
extern std::map<int, std::map<int,int> > const_array;//Tid index value
extern std::map<std::string, std::pair<int,v_type> > func_param;//param of func, name, pid, type
extern std::map<std::string, std::map<std::string, int>> func_var;//funcname, varname, varid
extern std::string cur_funcID;//name of current processing function
extern std::map<std::string, bool> func_returnvoid;

extern void scanblock(s_basenode* , bool, int, int);
extern void scanblockseqitem(s_basenode*, bool, int, int);
extern void scanblockitem(s_basenode*, bool, int, int);
extern void scanstmt(s_basenode*, bool, int, int);
extern std::pair<std::pair<int, int>, v_type> scancond(s_basenode*, bool, int, int);
extern std::pair<std::pair<int, int>, v_type> scanlorexp(s_basenode*, bool, int, int);
extern std::pair<std::pair<int, int>, v_type> scanlandexp(s_basenode*, bool, int, int);
extern std::pair<std::pair<int, int>, v_type> scaneqexp(s_basenode*, bool, int, int);
extern std::pair<std::pair<int, int>, v_type> scanrelexp(s_basenode*, bool, int, int);
extern std::string scanlorop(s_basenode*, bool);
extern std::string scanlandop(s_basenode*, bool);
extern std::string scanrelop(s_basenode*, bool);

std::pair<std::pair<int, int>, v_type> scanexp(s_basenode*, bool);
int scanconstexp(s_basenode*, bool);
std::pair<std::pair<int, int>, v_type> scanaddexp(s_basenode*, bool);
std::pair<std::pair<int, int>, v_type> scanmulexp(s_basenode*, bool);
std::pair<std::pair<int, int>, v_type> scanunaryexp(s_basenode*, bool);
std::pair<std::pair<int, int>, v_type> scanprimaryexp(s_basenode*, bool);
std::pair<std::pair<int, int>, v_type> scanlval(s_basenode*, bool);
std::pair<std::pair<int, int>, v_type> scannumber(s_basenode*, bool);
std::string scanaddop(s_basenode*, bool);
std::string scanmulop(s_basenode*, bool);
std::string scanunaryop(s_basenode*, bool);
void scanfuncrparams(s_basenode*, bool);
void scanlvalarray(s_basenode*, bool, std::vector<std::pair<std::pair<int, int>, v_type>>&);

extern std::string exp2str(std::pair<std::pair<int,int>, v_type>);

//<<int, int>, v_type> //id value type



std::pair<std::pair<int, int>, v_type> scanexp(s_basenode* root, bool isdec){
    auto s = root->Son;
    if(s.size() != 1){
        s2eerror("Exp Error: wrong number of sons\n");
    }
    return scanaddexp(s[0], isdec);
}
int scanconstexp(s_basenode* root, bool isdec){
    auto s = root->Son;
    if(s.size() != 1){
        s2eerror("Exp Error: wrong number of sons\n");
    }
    auto res = scanaddexp(s[0], isdec);
    if(res.second != _const_var){
        s2eerror("ConstExp Error: should be const value\n");
    }
    return res.first.second;
}
std::pair<std::pair<int, int>, v_type> scanaddexp(s_basenode* root, bool isdec){
    auto s = root->Son;
    printf("scanning add exp\n");
    printf("exp type: %d\n",root->type);
    auto ret = std::make_pair(std::make_pair(0,0), _null);
    if(s.size() == 1)
        return scanmulexp(s[0], isdec);
    else if(s.size() == 3){
        auto op1 = scanaddexp(s[0], isdec);
        auto sym = scanaddop(s[1], isdec);
        auto op2 = scanmulexp(s[2], isdec);

        if(op1.second == _const_var && op2.second == _const_var){//no need to claim a new variable
            if(sym == "+"){
                return std::make_pair(std::make_pair(-1, op1.first.second + op2.first.second), _const_var);
            }
            else{
                return std::make_pair(std::make_pair(-1, op1.first.second - op2.first.second), _const_var);
            }
        }
        else if(op1.second == _const_var){
            if(isdec && !noprint)
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            int i1 = op1.first.second;
            int i2 = op2.first.first;
            char c;                    
            if(op2.second == _tmp_var)
                c = 't';
            else if(op2.second == _func_var)
                c = 'p';
            else
                c = 'T';
            if(sym == "+"){
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %d + %c%d\n", tmp_cnt, i1, c, i2);
                }
            }
            else{ //sym = '-'                  
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %d - %c%d\n", tmp_cnt, i1, c, i2);
                }
            }
            auto res = std::make_pair(std::make_pair(tmp_cnt,0), _tmp_var);
            tmp_cnt++;
            return res;
        }
        else if(op2.second == _const_var){
            if(isdec && !noprint)
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            char c;
            if(op1.second == _tmp_var)
                c = 't';
            else if(op1.second == _func_var)
                c = 'p';
            else
                c = 'T';
            int i1 = op1.first.first;
            int i2 = op2.first.second;
            if(sym == "+"){                    
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %c%d + %d\n", tmp_cnt, c, i1, i2);
                }
            }
            else{ //sym = '-'         
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %c%d - %d\n", tmp_cnt, c, i1, i2);
                }
            }
            auto res = std::make_pair(std::make_pair(tmp_cnt,0), _tmp_var);
            tmp_cnt++;
            return res;
        }
        else{
            if(isdec && !noprint)
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            char c1 = 'T',c2 = 'T';
            if(op1.second == _tmp_var)
                c1 = 't';
            if(op2.second == _tmp_var)
                c2= 't';
            if(op1.second == _func_var)
                c1 = 'p';
            if(op2.second == _func_var)
                c2 = 'p';
            if(!isdec && !noprint){
                if(sym == "+"){
                    fprintf(s2eout, "t%d = %c%d + %c%d\n", tmp_cnt, c1, op1.first.first, c2, op2.first.first);
                }
                else{
                    fprintf(s2eout, "t%d = %c%d - %c%d\n", tmp_cnt, c1, op1.first.first, c2, op2.first.first);
                }
            }
            auto res =  std::make_pair(std::make_pair(tmp_cnt, 0), _tmp_var);
            tmp_cnt++;
            return res;
        }
    }
    else{
        s2eerror("AddExp Error: wrong number of sons\n");
        return ret;
    }
}

std::string scanaddop(s_basenode* root, bool isdec){
    auto s = root->Son;
    if(s[0]->type == _add)
        return "+";
    else if(s[0]->type == _minus)
        return "-";
    else{
        s2eerror("AddOp Error: wrong type of son\n");
        return "";
    }
}

std::string scanmulop(s_basenode* root, bool isdec){
    auto s = root->Son;
    if(s[0]->type == _mul)
        return "*";
    else if(s[0]->type == _div)
        return "/";
    else if(s[0]->type == _mod)
        return "%";
    else{
        s2eerror("MulOp Error: wrong type of son\n");
        return "";
    }
}

std::string scanunaryop(s_basenode* root, bool isdec){
    
    auto s = root->Son;
    if(s[0]->type == _add)
        return "+";
    else if(s[0]->type == _minus)
        return "-";
    else if(s[0]->type == _not)
        return "!";
    else{
        s2eerror("UnaryOp Error: wrong type of son\n");
        return "";
    }
}

std::pair<std::pair<int, int>, v_type> scanmulexp(s_basenode* root, bool isdec){
    auto s = root->Son;
    auto ret = std::make_pair(std::make_pair(-1,-1), _const_var);
    if(s.size() == 1)
        return scanunaryexp(s[0], isdec);
    else if(s.size() == 3){
        auto op1 = scanmulexp(s[0], isdec);
        auto sym = scanmulop(s[1], isdec);
        auto op2 = scanunaryexp(s[2], isdec);

        if(op1.second == _const_var && op2.second == _const_var){//no need to claim a new variable
            if(sym == "*"){
                return std::make_pair(std::make_pair(-1, op1.first.second * op2.first.second), _const_var);
            }
            else if(sym == "/"){
                return std::make_pair(std::make_pair(-1, op1.first.second / op2.first.second), _const_var);
            }
            else{
                return std::make_pair(std::make_pair(-1, op1.first.second % op2.first.second), _const_var);
            }
        }
        else if(op1.second == _const_var){
            if(isdec && !noprint)
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            char c;                    
            int i1 = op1.first.second;
            int i2 = op2.first.first;
            if(op2.second == _tmp_var)
                c = 't';
            else if(op2.second == _func_var)
                c = 'p';
            else
                c = 'T';
            if(sym == "*"){
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %d * %c%d\n", tmp_cnt, i1, c, i2);
                }
            }
            else if(sym == "/"){ //sym = '/'                  
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %d / %c%d\n", tmp_cnt, i1, c, i2);
                }
            }
            else{//sym = %
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %d %% %c%d\n", tmp_cnt, i1, c, i2);
                }
            }
            auto res = std::make_pair(std::make_pair(tmp_cnt,0), _tmp_var);
            tmp_cnt++;
            return res;
        }
        else if(op2.second == _const_var){
            if(isdec && !noprint)
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            char c;
            if(op1.second == _tmp_var)
                c = 't';
            else if(op1.second == _func_var)
                c = 'p';
            else
                c = 'T';               
            int i1 = op1.first.first;
            int i2 = op2.first.second;

            if(sym == "*"){                    
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %c%d * %d\n", tmp_cnt, c, i1, i2);
                }
            }
            else if(sym == "/"){ //sym = '/'                  
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %c%d / %d\n", tmp_cnt, c, i1, i2);
                }
            }
            else { //sym = '%'                  
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %c%d %% %d\n", tmp_cnt, c, i1, i2);
                }
            }
            auto res = std::make_pair(std::make_pair(tmp_cnt,0), _tmp_var);
            tmp_cnt++;
            return res;
        }
        else{
            if(isdec && !noprint)
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            char c1 = 'T',c2 = 'T';
            if(op1.second == _tmp_var)
                c1 = 't';
            if(op2.second == _tmp_var)
                c2= 't';
            if(op1.second == _func_var)
                c1 = 'p';
            if(op2.second == _func_var)
                c2 = 'p';
            if(!isdec && !noprint){
                if(sym == "*"){
                    fprintf(s2eout, "t%d = %c%d * %c%d\n", tmp_cnt, c1, op1.first.first, c2, op2.first.first);
                }
                else if(sym == "/"){
                    fprintf(s2eout, "t%d = %c%d / %c%d\n", tmp_cnt, c1, op1.first.first, c2, op2.first.first);
                }
                else{//sym = %
                    fprintf(s2eout, "t%d = %c%d %% %c%d\n", tmp_cnt, c1, op1.first.first, c2, op2.first.first);
                }
            }
            auto res =  std::make_pair(std::make_pair(tmp_cnt, 0), _tmp_var);
            tmp_cnt++;
            return res;
        }
    }
    else{
        s2eerror("AddExp Error: wrong number of sons\n");
        return ret;
    }
}

std::pair<std::pair<int, int>, v_type> scanunaryexp(s_basenode* root, bool isdec){
    auto s = root->Son;
    printf("scanning unaryexp\n");
    printf("exp type: %d\n",root->type);
    if(s.size() == 1){
        return scanprimaryexp(s[0], isdec);
    }  
    else if(s.size() == 2){
        auto s1 = scanunaryop(s[0], isdec);
        auto s2 = scanunaryexp(s[1], isdec);
        auto res = std::make_pair(std::make_pair(-1,-1), _tmp_var);
        if(s2.second == _const_var){
            if(s1 == "!"){
                res.first.second = !s2.first.second;
                res.second = _const_var; 
            }
            else if(s1 == "-"){
                res.first.second = -s2.first.second;
                res.second = _const_var;
            }
            else{
                res.first.second = s2.first.second;
                res.second = _const_var;
            }
            return res;
        }
        else{
            res.first.first = tmp_cnt;
            res.second = _tmp_var; 
            char c = 'T';
            if(s2.second == _tmp_var)
                c = 't';
            if(s2.second == _func_var)
                c = 'p';
            if(isdec && !noprint)
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            if(s1 == "!"){
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = ! %c%d\n", tmp_cnt, c, s2.first.first);
                }
            }
            else if(s1 == "-"){
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = - %c%d\n", tmp_cnt, c, s2.first.first);
                }
            }
            else{
                if(!isdec && !noprint){
                    fprintf(s2eout, "t%d = %c%d\n",tmp_cnt, c, s2.first.first);
                }
            }
            tmp_cnt++;
            return res;
        }
    }
    else if(s.size() == 3){//function without param
        //remember to add libfunction
        printf("function without param\n");
        std::string func_ID = s[0]->ID;
        if(func_returnvoid.find(func_ID) == func_returnvoid.end()) {
            s2eerror("UnaryExp Error: Function Undefined\n");
            return std::make_pair(std::make_pair(0,0),_null);
        }
        else if(func_returnvoid[func_ID] == true){
            printf("call function without return val\n");
            if(!isdec && !noprint)
                fprintf(s2eout, "call f_%s\n", func_ID.c_str());
            return std::make_pair(std::make_pair(0,0),_null);
        } 
        else{
            printf("call function with return val\n");
            if(isdec && !noprint)
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            if(!isdec && !noprint)
                fprintf(s2eout, "t%d = call f_%s\n", tmp_cnt, func_ID.c_str());
            int tt = tmp_cnt++;
            return std::make_pair(std::make_pair(tt,0),_tmp_var);
        }  
    }
    else if(s.size() == 4){
        //remember to add libfunction
        printf("function with param\n");
        std::string func_ID = s[0]->ID;
        scanfuncrparams(s[2], isdec);
        if(func_returnvoid.find(func_ID) == func_returnvoid.end()) {
            s2eerror("UnaryExp Error: Function Undefined\n");
            return std::make_pair(std::make_pair(0,0),_null);
        }
        else if(func_ID == "starttime"||func_ID == "stoptime"){
            if(!noprint && !isdec){
                fprintf(s2eout, "param %d\n", lineNo);
                fprintf(s2eout, "call f__sysy_%s\n", func_ID.c_str());
            }
            return std::make_pair(std::make_pair(0,0),_null);;
        }
        else if(func_returnvoid[func_ID] == true){
            printf("call function without return val\n");
            if(!isdec&& !noprint)
                fprintf(s2eout, "call f_%s\n", func_ID.c_str());
            return std::make_pair(std::make_pair(0,0),_null);
        } 
        else{
            printf("call function with return val\n");
            if(isdec && !noprint)
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            if(!isdec && !noprint)
                fprintf(s2eout, "t%d = call f_%s\n", tmp_cnt, func_ID.c_str());
            int t = tmp_cnt++;
            return std::make_pair(std::make_pair(t,0), _tmp_var);
        }  
    }
    else{
        s2eerror("UnaryExp Error: wrong number of sons\n");
        return std::make_pair(std::make_pair(0,0),_null);
    }
}

void scanfuncrparams(s_basenode* root, bool isdec){
    auto s = root->Son;
    if(s.size() == 1){
        //problem val array 传参!!! 记住把val array的size传过去！
        auto exp = scanexp(s[0], isdec);
        if(exp.second == _const_var){
            if(!isdec && !noprint)
                fprintf(s2eout, "param %d\n", exp.first.second);
        }
        else if(exp.second == _tmp_var){
            if(!isdec && !noprint)
                fprintf(s2eout, "param t%d\n", exp.first.first);
        }
        else if(exp.second == _func_var || exp.second == _func_var_array){
            if(!isdec && !noprint)
                fprintf(s2eout, "param p%d\n", exp.first.first);
        }
        else{
            if(isdec && !noprint){
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            }
            if(!isdec && !noprint){
                fprintf(s2eout, "t%d = T%d\n", tmp_cnt, exp.first.first);
                fprintf(s2eout, "param t%d\n", tmp_cnt);

            }
            tmp_cnt++;
        }
    }
    else if(s.size() == 3){
        scanfuncrparams(s[0], isdec);
        auto exp = scanexp(s[2], isdec);
        if(exp.second == _const_var){
            if(!isdec && !noprint)
                fprintf(s2eout, "param %d\n", exp.first.second);
        }
        else if(exp.second == _tmp_var){
            if(!isdec && !noprint)
                fprintf(s2eout, "param t%d\n", exp.first.first);
        }
        else if(exp.second == _func_var || exp.second == _func_var_array){
            if(!isdec && !noprint)
                fprintf(s2eout, "param p%d\n", exp.first.first);
        }
        else{
            if(isdec && !noprint)
                fprintf(s2eout,"var t%d\n", tmp_cnt);
            if(!isdec && !noprint){
                fprintf(s2eout,"t%d = T%d\n", tmp_cnt, exp.first.first);
                fprintf(s2eout, "param t%d\n", tmp_cnt);
            }
            tmp_cnt++;
        }
    }
    else{
        s2eerror("FuncRParams Error: wrong number of sons\n");
    }
    return;
}

std::pair<std::pair<int, int>, v_type> scanprimaryexp(s_basenode* root, bool isdec){
    auto s = root->Son;
    printf("scanning primaryexp\n");
    printf("exp type: %d\n",root->type);
    printf("num of sons: %ld\n", s.size());
    if(s.size() == 3){
        return scanexp(s[1], isdec);
    }
    else if(s.size() == 1){
        if(s[0]->type == _number){
            return scannumber(s[0], isdec);
        }
        else if(s[0]->type == _lval){
            //unfinished need to process lval
            auto lv =  scanlval(s[0], isdec);
            if(lv.second == _const_var_array || lv.second == _var_array){
                if(lv.first.second != -1){//array with index
                    if(isdec && !noprint)
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = T%d[t%d]\n", tmp_cnt, lv.first.first, lv.first.second);
                    }
                    int t = tmp_cnt++;
                    return std::make_pair(std::make_pair(t, 0), _tmp_var);
                }
                else{//array simply a symbol
                    if(isdec && !noprint)
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = T%d\n", tmp_cnt, lv.first.first);
                    }
                    int t = tmp_cnt++;
                    return std::make_pair(std::make_pair(t,0), _tmp_var);
                }
            }
            else if(lv.second == _func_var_array){
                if(lv.first.second != -1){
                    if(isdec && !noprint)
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = p%d[t%d]\n", tmp_cnt, lv.first.first, lv.first.second);
                    }
                    int t = tmp_cnt++;
                    return std::make_pair(std::make_pair(t, 0), _tmp_var); 
                } 
                else{
                    if(isdec && !noprint)
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = p%d\n", tmp_cnt, lv.first.first);
                    }
                    int t = tmp_cnt++;
                    return std::make_pair(std::make_pair(t, 0), _tmp_var);   
                } 
            }
            else{
                //problem here
            //    fprintf(s2eout, "lv.val: %d\n", lv.first.second);
                return lv;
            }
        }
        else{
            printf("%d\n", s[0]->type);
            s2eerror("PrimaryExp Error: wrong type of son\n");
            return std::make_pair(std::make_pair(0,0), _null);
        }
    }
    else{
        s2eerror("PrimaryExp Error: wrong number of sons\n");
        return std::make_pair(std::make_pair(0,0), _null);
    }
}

std::pair<std::pair<int, int>, v_type> scanlval(s_basenode* root, bool isdec){
    printf("scan lval\n");
    printf("type: %d\n", root->type);
    auto cur_lval_array = std::vector<std::pair<std::pair<int, int>, v_type>>();
    auto s = root->Son;
    printf("number of sons: %ld\n", s.size());
    std::string lval_ID = s[0]->ID;
    scanlvalarray(s[1], isdec, cur_lval_array);
    int cur_lay = layer;
    if(ID2T.find(lval_ID) == ID2T.end()){
        auto err = "LVal Error: "+lval_ID+" undefined\n";
        s2eerror(err.c_str());
        return std::make_pair(std::make_pair(0,0), _null);
    }
    while(ID2T[lval_ID].find(cur_lay) == ID2T[lval_ID].end() && cur_lay >= 0)
        cur_lay--;
    int val_tid = ID2T[lval_ID][cur_lay];
    printf("val_tid:%d, type:%d\n", val_tid, var_type[val_tid].second);
    if(cur_lval_array.size() == 0){
        printf("lval_array.size: %ld\n", cur_lval_array.size());
        auto res = var_type[val_tid];
        if(res.second == _func_var_array || res.second == _var_array || res.second == _const_var_array)
            res.first.second = -1;
        return res;
    }

    else{
        printf("lval is array\n");
        int index = 0;
        int tmp_ID = -1;
        printf("lval_array.size: %ld\n", cur_lval_array.size());
        for(int i = 0; i < cur_lval_array.size(); i++){
            if(cur_lval_array[i].second == _const_var){
                printf("constvar\n");
                printf("%d, %d\n",cur_lval_array[i].first.second,var_array[val_tid][i+1]);
                index += cur_lval_array[i].first.second*var_array[val_tid][i+1];
            }
            else if(cur_lval_array[i].second == _var || cur_lval_array[i].second == _tmp_var ){
                printf("var\n");
                printf("%d, %d\n",cur_lval_array[i].first.first,var_array[val_tid][i+1]);
                char c = 'T';
                if(cur_lval_array[i].second == _tmp_var)
                    c = 't';
                if(tmp_ID == -1){
                    tmp_ID = tmp_cnt;
                    if(isdec && !noprint)
                        fprintf(s2eout, "var t%d\n", tmp_ID);
                    if(!isdec && !noprint)
                        fprintf(s2eout, "t%d = %c%d * %d\n", tmp_ID, c,cur_lval_array[i].first.first, var_array[val_tid][i+1]*4); 
                    tmp_cnt++;
                }
                else{
                    int old_cnt = tmp_cnt;
                    tmp_cnt++;
                    if(isdec && !noprint){
                        fprintf(s2eout, "var t%d\n",old_cnt);
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    }
                        
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = %c%d * %d\n", old_cnt, c, cur_lval_array[i].first.first,var_array[val_tid][i+1]*4);
                        fprintf(s2eout, "t%d = t%d + t%d\n", tmp_cnt, old_cnt, tmp_ID);
                    }
                    tmp_ID = tmp_cnt++;
                }
            }
            else if(cur_lval_array[i].second == _func_var){
                if(tmp_ID == -1){
                    tmp_ID = tmp_cnt;
                    if(isdec && !noprint)
                        fprintf(s2eout, "var t%d\n", tmp_ID);
                    if(!isdec && !noprint)
                        fprintf(s2eout, "t%d = p%d * %d\n", tmp_ID, cur_lval_array[i].first.first, var_array[val_tid][i+1]*4); 
                    tmp_cnt++;
                }
                else{
                    int old_cnt = tmp_cnt;
                    tmp_cnt++;
                    if(isdec && !noprint){
                        fprintf(s2eout, "var t%d\n", old_cnt);
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    }
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = p%d * %d\n", old_cnt, cur_lval_array[i].first.first,var_array[val_tid][i+1]*4);
                        fprintf(s2eout, "t%d = t%d + t%d\n", tmp_cnt, old_cnt, tmp_ID);
                    }
                    tmp_ID = tmp_cnt++;
                }
            }
            else if(cur_lval_array[i].second ==  _func_var_array){
                if(tmp_ID == -1){
                    if(isdec && !noprint)
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = p%d[t%d] * %d\n", tmp_cnt, cur_lval_array[i].first.first, cur_lval_array[i].first.second, var_array[val_tid][i+1]*4);
                    }
                    tmp_ID = tmp_cnt++;
                }
                else{
                    int old_cnt = tmp_cnt;
                    tmp_cnt++;
                    if(isdec && !noprint){
                        fprintf(s2eout, "var t%d\n",old_cnt);
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    }
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = p%d[t%d] * %d\n", old_cnt, cur_lval_array[i].first.first, cur_lval_array[i].first.second,var_array[val_tid][i+1]*4);
                        fprintf(s2eout, "t%d = t%d + t%d\n", tmp_cnt, old_cnt, tmp_ID);
                    }
                    tmp_ID = tmp_cnt++;
                }
            }
            else if(cur_lval_array[i].second == _var_array || cur_lval_array[i].second == _const_var_array){
                if(tmp_ID == -1){
                    if(isdec && !noprint)
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = T%d[t%d] * %d\n", tmp_cnt, cur_lval_array[i].first.first, cur_lval_array[i].first.second, var_array[val_tid][i+1]*4);
                    }
                    tmp_ID = tmp_cnt++;
                }
                else{
                    int old_cnt = tmp_cnt;
                    tmp_cnt++;
                    if(isdec && !noprint){
                        fprintf(s2eout, "var t%d\n",old_cnt);
                        fprintf(s2eout, "var t%d\n", tmp_cnt);
                    }
                    if(!isdec && !noprint){
                        fprintf(s2eout, "t%d = T%d[t%d] * %d\n", old_cnt, cur_lval_array[i].first.first, cur_lval_array[i].first.second,var_array[val_tid][i+1]*4);
                        fprintf(s2eout, "t%d = t%d + t%d\n", tmp_cnt, old_cnt, tmp_ID);
                    }
                    tmp_ID = tmp_cnt++;
                }
            }
            else{
                s2eerror("wrong type of sons\n");
            }
        }
        if(tmp_ID == -1){
            if(isdec && !noprint){
                fprintf(s2eout, "var t%d\n", tmp_cnt);
            }
            if(!isdec && !noprint){
                fprintf(s2eout, "t%d = %d\n", tmp_cnt, index*4);
            }
            tmp_ID = tmp_cnt++;
            return std::make_pair(std::make_pair(var_type[val_tid].first.first, tmp_ID), var_type[val_tid].second);
        }
        else{
            if(index){
                if(!isdec && !noprint)
                    fprintf(s2eout, "t%d = t%d + %d\n", tmp_ID, tmp_ID, index*4);
            }
            return std::make_pair(std::make_pair(var_type[val_tid].first.first, tmp_ID), var_type[val_tid].second);
        }
    }
}

void scanlvalarray(s_basenode* root, bool isdec, std::vector<std::pair<std::pair<int, int>, v_type>>& cur_lval_array){
    auto s = root->Son;
    printf("scanlvalarray\n");
    printf("type:%d\n",root->type);
    printf("number of sons: %ld\n", s.size());
    if(s.size() == 0){
        return;
    }
    else if(s.size() == 2){
        scanlvalarray(s[0], isdec, cur_lval_array);
        auto exp = scanexp(s[1], isdec);
        cur_lval_array.push_back(exp);
        return;
    }
    else{
        s2eerror("LValArray Error: wrong number of sons\n");
        return;
    }
}

std::pair<std::pair<int, int>, v_type> scannumber(s_basenode* root, bool isdec){
    auto s = root->Son;
    printf("scan number\n");
    printf("type: %d\n", root->type);
    printf("number of sons: %ld\n", s.size());
    if(s.size() == 1){
        int num = s[0]->val;
        return std::make_pair(std::make_pair(0, num), _const_var);
    }
    else{
        s2eerror("Number Error: wrong number of sons\n");
        return std::make_pair(std::make_pair(0,0), _null);
    }
}