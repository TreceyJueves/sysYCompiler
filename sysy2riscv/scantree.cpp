#include "parser.hpp"

int var_cnt, tmp_cnt, param_cnt, label_cnt;
bool noprint = false;
int func_cnt;
extern bool noprint;
int layer;
bool return_void;
int lineNo;
std::map<std::string, std::map<int, int> >  ID2T;//ID layer Tid
std::map<int, std::map<std::string, int> > L2ID;//layer ID Tid
std::vector<int> tmp_array;//record initialization of multidimension array(数组的大小)
std::vector<std::pair<std::pair<int, int>, v_type>> tmp_array_val;//record value of each element of multidimension array（数组的元素的值）and variable type
std::map<int, std::pair<std::pair<int, int>, v_type> > var_type;//Tid value/id, index/size(only array),type
std::map<int, std::vector<int> > var_array;
std::map<std::string, bool> func_returnvoid;
std::map<int, std::map<int,int> > const_array;//Tid index value
std::map<std::string, std::pair<int,v_type> > func_param;//param of func, name, pid, type
std::string cur_funcID;//name of current processing function

void s_initialize(); 
void scantree();
void s_scandecl(s_basenode*, bool);
void s_scanconstdecl(s_basenode*, bool);
void s_scanvardecl(s_basenode*, bool);
void s_scanconstseqdecl(s_basenode*, bool);
void s_scanconstdef(s_basenode*, bool);
void s_scanvarseqdef(s_basenode*, bool);
void s_scanvardef(s_basenode*, bool);
std::string s_scanconstinitval(s_basenode*, bool);
std::string s_scaninitval(s_basenode*, bool);
std::string s_scanconstseqinitval(s_basenode*, bool);
std::string scanseqinitval(s_basenode*, bool);
void process_array(int, int, std::string, bool);
int scanmddim(s_basenode*, bool);
void s_scanfuncdef(s_basenode*, bool);
void scanfuncfparams(s_basenode*, bool);
void scanfuncfparam(s_basenode*, bool);

extern std::pair<std::pair<int, int>, v_type> scanexp(s_basenode*, bool);
extern int scanconstexp(s_basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanaddexp(s_basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanmulexp(s_basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanunaryexp(s_basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanprimaryexp(s_basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanlval(s_basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scannumber(s_basenode*, bool);
extern std::string scanaddop(s_basenode*, bool);
extern std::string scanmulop(s_basenode*, bool);
extern std::string scanunaryop(s_basenode*, bool);
extern void scanfuncrparams(s_basenode*, bool);
extern void scanlvalarray(s_basenode*, bool);

extern std::vector<std::pair<std::pair<int, int>, v_type>> lval_array;

extern std::string exp2str(std::pair<std::pair<int,int>, v_type>);

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

void s_initialize(){
    //add runtime library function
    func_returnvoid.clear();
    func_returnvoid["getint"] = false;
	func_returnvoid["getch"] = false;
	func_returnvoid["getarray"] = false;
	func_returnvoid["putint"] = true;
	func_returnvoid["putch"] = true;
	func_returnvoid["putarray"] = true;
	func_returnvoid["starttime"] = true;
	func_returnvoid["stoptime"] = true;
    var_cnt = tmp_cnt = param_cnt = label_cnt = func_cnt = 0;
    ID2T.clear();
    var_type.clear();
    var_array.clear();
    L2ID.clear();
    const_array.clear();

    layer = 0;
}

void s_scandecl(s_basenode* root, bool isdec){
    if(root->Son.size()!=1)
        s2eerror("Decl Error: wrong number of Sons\n");
    auto s = root->Son;
    switch(s[0]->type){
        case _constdecl:
            printf("constdecl\n");
            s_scanconstdecl(s[0], isdec);
            break;
        case _vardecl:
            printf("vardecl\n");
            s_scanvardecl(s[0], isdec);
            break;
        default:
            s2eerror("Decl Error: wrong type of sons\n");
            break;
    }
    return;
}

void s_scanconstdecl(s_basenode* root, bool isdec){
    auto s = root->Son;    
    if(s.size()!=2){
        s2eerror("ConstDecl Error: wrong number of Sons\n");
    }
    if(root->Son[0]->Son[0]->type != _int){//illegal type
        s2eerror("ConstDecl Error: illegal type\n");
    }
    s_scanconstseqdecl(s[1], isdec);
    return;
}

void s_scanvardecl(s_basenode* root, bool isdec){
    auto s = root->Son;    
    printf("var decl\n");
    if(s.size()!=2){
        s2eerror("VarDecl Error: wrong number of Sons\n");
    }
    if(root->Son[0]->Son[0]->type != _int){//illegal type
        s2eerror("VarDecl Error: illegal type\n");
    }
    s_scanvarseqdef(s[1], isdec);
    return;
}

void s_scanvarseqdef(s_basenode* root, bool isdec){
    auto s = root->Son;
    //printf("starting varseqdef\n");
    if(s.size()== 1){
        printf("vardef\n");
        s_scanvardef(s[0], isdec);
    }
    else if(s.size()==2){
        s_scanvarseqdef(s[0], isdec);
        s_scanvardef(s[1], isdec);
    }
    else{
        s2eerror("VarSeqDef Error: wrong number of Sons\n");
    }
    return;
}

void s_scanvardef(s_basenode* root, bool isdec){
    auto s = root->Son;
    tmp_array.clear();
    tmp_array_val.clear();
    printf("starting definin var\n");
    int sizeofvar = scanmddim(s[1], isdec);
    printf("finished scanning dim\n");
    std::string Ident =  s[0]->ID;
    int cur_Tid;
    if(ID2T.find(Ident) == ID2T.end()){//not declared before
        ID2T[Ident] = std::map<int,int>();
        ID2T[Ident][layer] = var_cnt;
        L2ID[layer][Ident] = var_cnt;
        cur_Tid = var_cnt++;
    }
    else{
        if(ID2T[Ident].find(layer) == ID2T[Ident].end()){//not declared in this layer
            ID2T[Ident][layer] = var_cnt;
            L2ID[layer][Ident] = var_cnt;
            cur_Tid = var_cnt++;
        }
        else{
            std::string err = "Vardef Error: redeclared variable "+Ident+"\n";
            s2eerror(err.c_str());
            return;
        }
    }
    if(tmp_array.size()==0){//single variable
        printf("single variable\n");
        var_type[cur_Tid] = std::make_pair(std::make_pair(cur_Tid, 0), _var);
        if(isdec && !noprint)
            fprintf(s2eout, "var T%d\n", cur_Tid);
        if(s.size() == 4){
            std::string str_val = s_scaninitval(s[3], isdec);
        }
        if(tmp_array_val.size() > 0){
            if(tmp_array_val.back().second == _const_var){//not sure the type is correct
                if(!isdec && !noprint)
                    fprintf(s2eout, "T%d = %d\n", cur_Tid, tmp_array_val.back().first.second);
            }
            else{
                char c = 'T';
                if(tmp_array_val.back().second == _tmp_var)
                    c = 't';
                else if(tmp_array_val.back().second == _func_var)
                    c = 'p';
                if(!isdec && !noprint)
                    fprintf(s2eout, "T%d = %c%d\n", cur_Tid, c, tmp_array_val.back().first.first);
            }
        }
    }
    else{//multi-dimension array
        var_type[cur_Tid] = std::make_pair(std::make_pair(cur_Tid, sizeofvar), _var_array);
        if(isdec && !noprint)
            fprintf(s2eout, "var %d T%d\n", sizeofvar * 4, cur_Tid);
        for(int k = tmp_array.size()-1; k > 0; k--){
            tmp_array[k-1] *= tmp_array[k];
        }//to record the size of each dimension

        if(s.size() == 4){
            std::string str_val = s_scaninitval(s[3], isdec);
            process_array(cur_Tid, sizeofvar, str_val, isdec);//unfinished urgent currently giving up
        }
        tmp_array.push_back(1);
        for(int l = 0; l < tmp_array.size(); l++){
            printf("%d: %d    ", l, tmp_array[l]);
        }
        printf("\n");
        var_array[cur_Tid] = tmp_array;
    }
}

void s_scanconstseqdecl(s_basenode* root, bool isdec){
    auto s = root->Son;
    printf("start scanning const seq decl\n");
    if(s.size()== 1){
        printf("single decl\n");
        s_scanconstdef(s[0], isdec);
    }
    else if(s.size()==2){
        s_scanconstseqdecl(s[0], isdec);
        s_scanconstdef(s[1], isdec);
    }
    else{
        s2eerror("ConstSeqDecl Error: wrong number of Sons\n");
    }
    return;
}

void s_scanconstdef(s_basenode* root, bool isdec){
    printf("s_scanconstdef\n");
    auto s = root->Son;
    tmp_array.clear();
    tmp_array_val.clear();
    printf("%ld\n",s.size());
    auto sizeofvar = scanmddim(s[1], isdec);
    std::string str_val = "";
    str_val = s_scanconstinitval(s[3], isdec);
    std::string Ident =  s[0]->ID;
    int cur_Tid = -1;
    if(ID2T.find(Ident) == ID2T.end()){//not declared before
        ID2T[Ident] = std::map<int,int>();
        ID2T[Ident][layer] = var_cnt;
        L2ID[layer][Ident] = var_cnt;
        cur_Tid = var_cnt++;
    }
    else{
        if(ID2T[Ident].find(layer) == ID2T[Ident].end()){//not declared in this layer
            ID2T[Ident][layer] = var_cnt;
            L2ID[layer][Ident] = var_cnt;
            cur_Tid = var_cnt++;
        }
        else{
            std::string err = "Constdef Error: redeclared variable "+Ident+"\n";
            s2eerror(err.c_str());
            return;
        }
    }
    if(tmp_array.size()==0){//single variable
        var_type[cur_Tid] = std::make_pair(std::make_pair(cur_Tid, 0), _const_var);
        if(isdec && !noprint)
            fprintf(s2eout, "var T%d\n", cur_Tid);
        if(tmp_array_val.size() > 0){//value defined
            if(tmp_array_val.back().second == _const_var){
                var_type[cur_Tid].first.second = tmp_array_val.back().first.second;//value
                if(!isdec && !noprint)
                    fprintf(s2eout, "T%d = %d\n", cur_Tid, tmp_array_val.back().first.second);
            }
            else{
                s2eerror("ConstDef Error: const variable should be initalized with const value\n");
                return;
            }
            tmp_array_val.pop_back();
        }
    }
    else{//multi-dimension array
        var_type[cur_Tid] = std::make_pair(std::make_pair(cur_Tid,sizeofvar), _const_var_array);
        if(isdec && !noprint)
            fprintf(s2eout, "var %d T%d\n", sizeofvar *4, cur_Tid);
        for(int k = tmp_array.size()-1; k > 0; k--){
            tmp_array[k-1] *= tmp_array[k];
        }//to record the size of each dimension
        process_array(cur_Tid, sizeofvar, str_val, isdec);//unfinished urgent currently giving up
        tmp_array.push_back(1);        
        var_array[cur_Tid] = tmp_array;
    }
}

int scanmddim(s_basenode* root, bool isdec){
    printf("start scanning mddim\n");
    auto s = root->Son;
    if(s.size()==0){
        printf("s.size = 0\n");
        return 1;
    }
    else if(s.size()!=2)
        s2eerror("MdArray Error: wrong number of sons\n");
    int frontlayer = scanmddim(s[0], isdec);
    auto curlayer = scanconstexp(s[1], isdec);//unfinished
    tmp_array.push_back(curlayer);
    return frontlayer*curlayer;
}

std::string s_scanconstinitval(s_basenode* root, bool isdec){
    printf("scan constinit val\n");
    auto s = root->Son;
    if(s.size() == 1){
        printf("single exp\n");
        auto val = scanexp(s[0], isdec);
        if(val.second != _const_var){
            s2eerror("ConstInitVal Error: should be s_initialized with constexp\n");
        }
        tmp_array_val.push_back(val);
        return "n";
    }
    else if(s.size()==2){
        return "{}";
    }
    else{
        std::string tmpstr = s_scanconstseqinitval(s[1], isdec);
        return "{"+tmpstr+"}";
    }
}

std::string s_scaninitval(s_basenode* root, bool isdec){
    printf("s_scaninitval\n");
    printf("type: %d\n", root->type);
    auto s = root->Son;
    printf("initval sons :%ld\n", s.size());
    if(s.size() == 1){
        auto val = scanexp(s[0], isdec);
        tmp_array_val.push_back(val);
        printf("%d:%d\n", val.first.first, val.first.second);
        return "n";
    }
    else if(s.size()==2){
        return "{}";
    }
    else{
        std::string tmpstr = scanseqinitval(s[1], isdec);
        return "{"+tmpstr+"}";
    }
}

std::string scanseqinitval(s_basenode* root, bool isdec){
    printf("scan seq initval\n");
    printf("type: %d\n", root->type);
    auto s = root->Son;
    if(s.size() == 1){
        return s_scaninitval(s[0], isdec);
    }
    else{
        std::string tmpstr1 = scanseqinitval(s[0], isdec);
        std::string tmpstr2 = s_scaninitval(s[2], isdec);
        return tmpstr1+tmpstr2;
    }
}

std::string s_scanconstseqinitval(s_basenode* root, bool isdec){
    printf("scan constseq init val\n");
    auto s = root->Son;
    if(s.size() == 1){
        return s_scanconstinitval(s[0], isdec);
    }
    else{
        std::string tmpstr1 = s_scanconstseqinitval(s[0], isdec);
        std::string tmpstr2 = s_scanconstinitval(s[1], isdec);
        return tmpstr1+tmpstr2;
    }
}

void scantree(s_basenode* root){
    s_initialize();
    //扫第一遍进行声明
    noprint = false;
    for(auto it: root->Son){
        switch(it->type){
            case _decl:{
                noprint = false;
                s_scandecl(it, true);
                printf("decl\n");
                break;}
            case _funcdef:{
                printf("funcdef\n");
                noprint = true;
                s_scanfuncdef(it, false);
                break;}
            default:{
                s2eerror("Tree Error: wrong type of sons\n");
                break;}

        }
    }
    s_initialize();
    //扫第二遍来进行运算
    for(auto it: root->Son){
        switch(it->type){
            case _decl:{
                printf("decl2\n");
                noprint = false;
                s_scandecl(it, false);
                break;}
            case _funcdef:{
                printf("funcdef2\n");
                noprint = false;
                auto old_tmp_cnt = tmp_cnt;
                auto old_var_cnt = var_cnt;
                auto old_label_cnt = label_cnt;
                auto old_func_returnvoid = func_returnvoid;
                s_scanfuncdef(it, true);
                tmp_cnt = old_tmp_cnt;
                var_cnt = old_var_cnt;
                label_cnt = old_label_cnt;
                func_returnvoid = old_func_returnvoid;
                s_scanfuncdef(it, false);
                break;}
            default:{
                s2eerror("Tree Error: wrong type of sons\n");
                break;}

        }
    }
}

void process_array(int tid, int sizeofvar, std::string str, bool isdec){//not sure correct
//has bug!!
    int num = 0;
    std::stack<int> s;//0-(tmp_array.size()-1)
    int cur_layer= 0;
    int max_layer = tmp_array.size()-1;
    int val_index = 0;
    bool has_element = false;
    int cur_min_size = tmp_array.back();
    for(int i = 0; i < str.length(); i++){//trouble of has element
        if(str[i] == '{'){
            if(s.empty())
                cur_layer = 0;
            else
                cur_layer = s.top()+1;
            while(cur_layer <= max_layer && num % tmp_array[cur_layer] != 0)
                cur_layer++;
            if(cur_layer > max_layer){
                s2eerror("Array Initial Error: Wrong s_initializer\n");
            }
            s.push(cur_layer);
        }
        else if(str[i] == '}'){
            int cur_layer = s.top();
            while(!has_element || num % tmp_array[cur_layer] != 0){
                has_element = true;
                if(!isdec && !noprint){
                    fprintf(s2eout, "T%d[%d] = 0\n",tid, num*4);
                }
                const_array[tid][num*4] = 0;
                num++;
            }
            s.pop();
        }
        else{
            has_element = true;
            if(tmp_array_val[val_index].second == _const_var){
                const_array[tid][num*4] = tmp_array_val[val_index].first.second;
                if(!noprint && !isdec)
                    fprintf(s2eout, "T%d[%d] = %d\n", tid, num * 4, tmp_array_val[val_index].first.second);
            }
            else{
                auto str = exp2str(tmp_array_val[val_index]);
                if(!isdec && !noprint)
                    fprintf(s2eout, "T%d[%d] = %s\n",tid, num * 4, str.c_str());
            }
            num++;
            val_index++;
        }
    }
}

void s_scanfuncdef(s_basenode* root, bool isdec){
    func_param.clear();
    auto s = root->Son;
    param_cnt = 0;

    cur_funcID = s[1]->ID;
    return_void = false;
    if(func_returnvoid.find(cur_funcID) != func_returnvoid.end()){
        std::string err_str = "FuncDef Error: "+ cur_funcID +" redefined\n";
        s2eerror(err_str.c_str());
        return;
    }

    if(s[0]->Son[0]->type == _void){
        return_void = true;
        func_returnvoid[cur_funcID] = true;
    }
    else{
        return_void = false;
        func_returnvoid[cur_funcID] = false;
    }
    layer++;
    if(s.size() == 6){//has parameter
        printf("func has param\n");
        scanfuncfparams(s[3], isdec);
    }
    if(isdec && !noprint){
        fprintf(s2eout, "f_%s [%ld]\n", cur_funcID.c_str(), func_param.size());
    }
    printf("start scanning block\n");
    scanblock(s.back(), isdec, -1, -1);
    layer--;
//adding default return in case the programmer forgets to return, can be ignored if the program is written correctly
    if(return_void){
        if(!isdec && !noprint)
            fprintf(s2eout, "return\n");
    }
    if(!isdec && !noprint)
        fprintf(s2eout, "end f_%s\n", cur_funcID.c_str());
    return;
}

void scanfuncfparams(s_basenode* root, bool isdec){
    auto s = root->Son;
    if(s.size() == 1){
        scanfuncfparam(s[0], isdec);
    }
    else if(s.size() == 2){
        scanfuncfparams(s[0], isdec);
        scanfuncfparam(s[1], isdec);
    }
    else{
        s2eerror("FuncFParams Error: invalid number of sons\n");
    }
    return;
}

void scanfuncfparam(s_basenode* root, bool isdec){
    printf("scan f param\n");
    auto s = root->Son;
    std::string param_ID = s[1]->ID;
    if(s.size() == 2){
        if(func_param.find(param_ID)!=func_param.end()){
            std::string err_str = "FuncFParam Error " + param_ID + " redefined\n";
            s2eerror(err_str.c_str());
        }
        func_param[param_ID] = std::make_pair(param_cnt, _func_var);
        ID2T[param_ID][layer] = var_cnt;
        L2ID[layer][param_ID] = var_cnt;
        var_type[var_cnt] = std::make_pair(std::make_pair(param_cnt, 0),_func_var);
        var_cnt++;
        param_cnt++;
    }
    else if(s.size() == 5){
        if(func_param.find(param_ID) != func_param.end()){
            std::string err_str = "FuncFParam Error " + param_ID + " redefined\n";
            s2eerror(err_str.c_str());
        }
        func_param[param_ID] = std::make_pair(param_cnt, _func_var_array);
        ID2T[param_ID][layer] = var_cnt;
        L2ID[layer][param_ID] = var_cnt;

        tmp_array.clear();
        tmp_array.push_back(0);//the first dim of a param is [] thus using 0
        int sizeofvar = scanmddim(s[4], isdec);
        tmp_array.push_back(1);
        for(int k = tmp_array.size()-1; k > 0; k--){
            tmp_array[k-1] *= tmp_array[k];
        }
        
        var_type[var_cnt] = std::make_pair(std::make_pair(param_cnt, sizeofvar), _func_var_array);
        var_array[var_cnt] = tmp_array;
        var_cnt++;
        param_cnt++;
    }
    else{
        s2eerror("FuncFParam Error: wrong number of sons\n");
    }
    return;
}