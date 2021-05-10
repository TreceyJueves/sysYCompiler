#include "parser.hpp"

extern int var_cnt, tmp_cnt, param_cnt, label_cnt;
extern int func_cnt;
extern int layer;
extern bool return_void;
extern bool noprint;
extern std::map<std::string, std::map<int, int> >  ID2T;//ID layer Tid
extern std::map<int, std::map<std::string, int> > L2ID;//layer ID Tid
extern std::vector<int> tmp_array;//record initialization of multidimension array(数组的大小)
extern std::vector<std::pair<int, v_type>> tmp_array_val;//record value of each element of multidimension array（数组的元素的值）and variable type
extern std::map<int, std::pair<std::pair<int, int>, v_type> > var_type;//Tid value/id, index/size(only array),type
extern std::map<int, std::vector<int> > var_array;//Tid Size
extern std::map<int, std::map<int,int> > const_array;//Tid index value
extern std::map<std::string, std::pair<int,v_type> > func_param;//param of func, name, pid, type
extern std::string cur_funcID;//name of current processing function


extern void initialize(); 
extern void scandecl(basenode*, bool);
extern void scanconstdecl(basenode*, bool);
extern void scanvardecl(basenode*, bool);
extern void scanconstseqdecl(basenode*, bool);
extern void scanconstdef(basenode*, bool);
extern void scanvarseqdef(basenode*, bool);
extern void scanvardef(basenode*, bool);
extern std::string scanconstinitval(basenode*, bool);
extern std::string scaninitval(basenode*, bool);
extern std::string scanconstseqinitval(basenode*, bool);
extern std::string scaninitseqval(basenode*, bool);
extern void process_array(int, int, std::string, bool);
extern int scanmddim(basenode*, bool);
extern int scanconstexp(basenode*, bool);
extern void scanfuncdef(basenode*, bool);
extern void scanfuncfparams(basenode*, bool);
extern void scanfuncfparam(basenode*, bool);

extern std::pair<std::pair<int, int>, v_type> scanexp(basenode*, bool);

extern std::string exp2str(std::pair<std::pair<int, int>, v_type>);

extern std::pair<std::pair<int, int>, v_type> scanexp(basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanaddexp(basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanmulexp(basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanunaryexp(basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanprimaryexp(basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scanlval(basenode*, bool);
extern std::pair<std::pair<int, int>, v_type> scannumber(basenode*, bool);
extern std::string scanaddop(basenode*, bool);
extern std::string scanmulop(basenode*, bool);
extern std::string scanunaryop(basenode*, bool);
extern void scanfuncrparams(basenode*, bool);
extern void scanlvalarray(basenode*, bool);

void scanblock(basenode* , bool, int, int);
void scanblockseqitem(basenode*, bool, int, int);
void scanblockitem(basenode*, bool, int, int);
void scanstmt(basenode*, bool, int, int);
std::pair<std::pair<int, int>, v_type> scancond(basenode*, bool, int, int);
std::pair<std::pair<int, int>, v_type> scanlorexp(basenode*, bool, int, int);
std::pair<std::pair<int, int>, v_type> scanlandexp(basenode*, bool, int, int);
std::pair<std::pair<int, int>, v_type> scaneqexp(basenode*, bool, int, int);
std::pair<std::pair<int, int>, v_type> scanrelexp(basenode*, bool, int, int);
std::string scanlorop(basenode*, bool);
std::string scanlandop(basenode*, bool);
std::string scanrelop(basenode*, bool);
std::string scaneqop(basenode* , bool );

void scanblock(basenode* root, bool isdec, int brkpt, int ctnpt){
    auto s = root->Son;
    if(s.size() == 2){
        return;
    }
    else if(s.size() == 3){
        scanblockseqitem(s[1], isdec, brkpt, ctnpt);
    }
    else{
        yyerror("Block Error: wrong number of sons\n");
    }
    for(auto& t:L2ID[layer]){
        //partly incorrect need to rewrite
        ID2T[t.first].erase(layer);
        if(ID2T[t.first].size() == 0)
            ID2T.erase(t.first);
        var_array.erase(t.second);
        var_type.erase(t.second);
    }
    L2ID.erase(layer);//clear out params induced in this block;
    return;
}

void scanblockseqitem(basenode* root, bool isdec, int brkpt, int ctnpt){
    auto s = root->Son;
    printf("startscanblockseqitem\n");
    if(s.size() == 1){
        scanblockitem(s[0], isdec, brkpt, ctnpt);
    }
    else if(s.size() == 2){
        scanblockseqitem(s[0], isdec, brkpt, ctnpt);
        scanblockitem(s[1], isdec, brkpt, ctnpt);
    }
    else{
        yyerror("BlockSeqItem Error: wrong number of sons\n");
    }
    return;
}

void scanblockitem(basenode* root, bool isdec, int brkpt, int ctnpt){
    printf("start scan blockitem \n");
    auto s = root->Son;
    switch(s[0]->type){
        case _decl:
            printf("case decl:\n");
            scandecl(s[0], isdec);
            break;
        case _stmt:
            printf("case stmt:\n");
            scanstmt(s[0], isdec, brkpt, ctnpt);
            break;
        default:
            yyerror("BlockItem Error: illegal type\n");
    }
}

void scanstmt(basenode* root, bool isdec, int brkpt, int ctnpt){//highly possible unfinished
    auto s = root->Son;
    if(s.size() == 0)//case semcol
        return;
    else if(s.size() == 1){//case block break continue return
        switch(s[0]->type){
            case _block:
                layer++;
                printf("case block\n");
                scanblock(s[0], isdec, brkpt, ctnpt);
                layer--;
                break;
            case _break:
                printf("case break\n");
                if(!isdec && !noprint){
                    fprintf(yyout, "goto l%d\n", brkpt);
                }
                break;
            case _continue:
                printf("case continue\n");
                if(!isdec && !noprint){
                    fprintf(yyout, "goto l%d\n", ctnpt);
                }
                break;
            case _return:
                printf("case return\n");
                if(!isdec && !noprint){
                    fprintf(yyout, "return\n");
                }
                break;
            case _exp:
                scanexp(s[0], isdec);
                break;
            default:
                yyerror("Stmt Error: wrong type of son\n");
        }
    }
    else if(s.size() == 2){//case return int
        printf("case return int\n");
        if(s[0]->type != _return){
            yyerror("Stmt Error: wrong type of son, should be return\n");
        }
        printf("case return int\n");
        auto ret = scanexp(s[1], isdec);//unfinished ret should be a type of <<int(Tid/tid), int(index)>, v_type>
        if(!isdec && !noprint){
            auto str = exp2str(ret).c_str();
            fprintf(yyout, "return %s\n", str);
        }
    }
    else if(s.size() == 3){//assign
        printf("case assign\n");
        auto lval = scanlval(s[0], isdec);
        auto exp = scanexp(s[2],isdec);
        auto str = exp2str(exp);
        auto lstr = exp2str(lval);
        if(!isdec && !noprint){
            fprintf(yyout, "%s = %s\n", lstr.c_str(), str.c_str());
        }
    }
    else if(s.size() == 5){//case while / no else
        if(s[0]->type == _while){
            printf("case while\n");
            int ctnlb = label_cnt++;//place to go if continue appears, before cond
            int brklb = label_cnt++;//place to go if break appears, after stmt
            int b_true = label_cnt++;//place to go if cond == true
            int b_false = brklb;//place to go if cond == false
            if(!isdec && !noprint){
                fprintf(yyout, "l%d:\n", ctnlb);
            }
            auto cond = scancond(s[2], isdec, b_true, b_false);//can branch part be elliminated?
            printf("finished scanning cond\n");
            auto strcond = exp2str(cond);
            if(!isdec && !noprint){
                //fprintf(yyout, "if %s == 0 goto l%d\n", strcond.c_str(), brklb);
                fprintf(yyout, "l%d:\n", b_true);
            }
            scanstmt(s[4], isdec, brklb, ctnlb);
            if(!isdec && !noprint){
                fprintf(yyout, "goto l%d\n", ctnlb);
                fprintf(yyout, "l%d:\n", brklb);
            }
        }
        else if(s[0]->type == _if){//if without else
            printf("case if without else\n");
            int b_true = label_cnt++;//place to go if cond == true
            int b_false = label_cnt++;//place to go if cond == false
            auto exp = scancond(s[2], isdec, b_true, b_false);
            auto str = exp2str(exp);
            if(!isdec && !noprint){
                //fprintf(yyout,"if %s == 0 goto l%d\n", str.c_str(), b_false);
            }
            if(!isdec && !noprint){
                fprintf(yyout,"l%d:\n", b_true);
            }
            scanstmt(s[4],isdec, brkpt, ctnpt);
            if(!isdec && !noprint)
                fprintf(yyout, "l%d:\n",b_false);
        }
        else{
            yyerror("Stmt Error: wrong type of sons\n");
        }
    }
    else if(s.size() == 7){//if with else
        printf("case if with else\n");
        int b_if = label_cnt++;
        int b_else = label_cnt++;
        int b_fin = label_cnt++;
        auto cond = scancond(s[2], isdec, b_if, b_else);
        auto str = exp2str(cond);
        if(!isdec && !noprint){
            //fprintf(yyout, "if %s == 0 goto l%d\n", str.c_str(), b_else);
            fprintf(yyout,"l%d:\n", b_if);
        }
        scanstmt(s[4], isdec, brkpt, ctnpt);
        if(!isdec && !noprint)
            fprintf(yyout,"goto l%d\n", b_fin);
        if(!isdec && !noprint){
            fprintf(yyout,"l%d:\n", b_else);
        }
        scanstmt(s[6], isdec, brkpt, ctnpt);
        if(!isdec && !noprint)
            fprintf(yyout,"l%d:\n", b_fin);
    }
    else{
        printf("Number of sons : %ld\n", s.size());
        yyerror("Stmt Error: wrong number of sons\n");
    }
}

std::pair<std::pair<int, int>, v_type> scancond(basenode* root, bool isdec, int b_true, int b_false){
    auto s = root->Son;
    printf("start scanning cond\n");
    printf("exp type: %d\n",root->type);
    if(s.size() == 1){
        return scanlorexp(s[0], isdec, b_true, b_false);
    }
    else{
        yyerror("Cond Error: Wrong number of Sons\n");
        return std::make_pair(std::make_pair(0,0),_null);
    }
}
std::pair<std::pair<int, int>, v_type> scanlorexp(basenode* root, bool isdec, int b_true, int b_false){
    auto s = root->Son;
    printf("scanning lorexp\n");
    printf("exp type: %d\n",root->type);
    if(s.size() == 1){
        return scanlandexp(s[0], isdec, b_true, b_false);
    }
    else if(s.size() == 3){
        auto res1 = scanlorexp(s[0], isdec, b_true, -1);//if one part is true then all are true
        auto op = scanlorop(s[1], isdec);
        auto res2 = scanlandexp(s[2], isdec, b_true, -1);//must all are false is false
        //b_false cannot be >= 0 until all parts are calculated
        if(isdec && !noprint){
            fprintf(yyout, "var t%d\n", tmp_cnt);
        }
        auto exp1 = exp2str(res1);
        auto exp2 = exp2str(res2);
        if(!isdec && !noprint){
            fprintf(yyout, "t%d = %s || %s\n", tmp_cnt, exp1.c_str(), exp2.c_str());
            if(b_true >= 0)//if one part is true then all are true
                fprintf(yyout, "if t%d != 0 goto l%d\n", tmp_cnt, b_true);
            if(b_false >= 0)//must all are false is false
                fprintf(yyout, "if t%d == 0 goto l%d\n", tmp_cnt, b_false);
            
        }
        int t = tmp_cnt++;
        auto resu = std::make_pair(std::make_pair(t,0), _tmp_var);
        return resu;
    }
    else{
        yyerror("LorExp Error: wrong number of sons\n");
        return std::make_pair(std::make_pair(0,0), _null);
    }
}

std::string scanlorop(basenode* root, bool isdec){
    return "||";
}

std::string scanlandop(basenode* root, bool isdec){
    return "&&";
}

std::pair<std::pair<int, int>, v_type>scanlandexp(basenode* root, bool isdec, int b_true, int b_false){
    auto s = root->Son;
    printf("scanning landexp\n");
    printf("exp type: %d\n",root->type);
    if(s.size() == 1){
        return scaneqexp(s[0], isdec, b_true, b_false);
    }
    else if(s.size() == 3){
        auto res1 = scanlandexp(s[0], isdec, -1, b_false);//if one part is false then all are false
        auto op = scanlandop(s[1], isdec);
        auto res2 = scaneqexp(s[2], isdec, -1, b_false);//must all are true is true
        //b_false cannot be >= 0 until all parts are calculated
        if(isdec && !noprint){
            fprintf(yyout, "var t%d\n", tmp_cnt);
        }
        auto exp1 = exp2str(res1);
        auto exp2 = exp2str(res2);
        if(!isdec && !noprint){
            fprintf(yyout, "t%d = %s && %s\n", tmp_cnt, exp1.c_str(), exp2.c_str());
            if(b_false >= 0)//if one part is false then all are false
                fprintf(yyout, "if t%d == 0 goto l%d\n", tmp_cnt, b_false);
            if(b_true >= 0)//must all are true is true
                fprintf(yyout, "if t%d != 0 goto l%d\n", tmp_cnt, b_true);
            
        }
        int t = tmp_cnt++;
        auto resu = std::make_pair(std::make_pair(t,0), _tmp_var);
        return resu;
    }
    else{
        yyerror("LAndExp Error: Wrong number of sons\n");
        return std::make_pair(std::make_pair(0,0),_null);
    }
}

std::pair<std::pair<int, int>, v_type>scaneqexp(basenode* root, bool isdec, int b_true, int b_false){
    auto s = root->Son;
    printf("scan eqexp\n");
    printf("exp type: %d\n",root->type);
    if(s.size() == 1){
        return scanrelexp(s[0], isdec, b_true, b_false);
    }
    else if(s.size() == 3){
        auto res1 = scaneqexp(s[0], isdec, -1, -1);
        auto res2 = scanrelexp(s[2], isdec, -1, -1);
        auto op = scaneqop(s[1], isdec);
        auto exp1 = exp2str(res1);
        auto exp2 = exp2str(res2);
        if(isdec && !noprint)
            fprintf(yyout, "var t%d\n", tmp_cnt);
        if(!isdec && !noprint){
            fprintf(yyout, "t%d = %s %s %s\n", tmp_cnt, exp1.c_str(), op.c_str(), exp2.c_str());
            if(b_true >= 0)                   
                fprintf(yyout, "if t%d != 0 goto l%d\n", tmp_cnt, b_true);
            if(b_false >= 0)
                fprintf(yyout, "if t%d == 0 goto l%d\n", tmp_cnt, b_false);
        }
        int t = tmp_cnt++;
        auto resu = std::make_pair(std::make_pair(t,0), _tmp_var);
        return resu;
    }
    else{
        yyerror("EqExp Error: wrong number of sons\n");
        return std::make_pair(std::make_pair(0,0), _null);
    }
}

std::string scaneqop(basenode* root, bool isdec){
    auto s = root->Son;
    if(s.size() == 1){
        if(s[0]->type == _neq)
            return "!=";
        else if(s[0]->type == _equal)
            return "==";
        else{
            yyerror("EqOp Error: wrong type of son\n");
            return "";
        }
    }
    else{
        yyerror("EqOp Error: wrong number of sons\n");
        return "";
    }
}

std::pair<std::pair<int, int>, v_type> scanrelexp(basenode* root, bool isdec, int b_true, int b_false){
    auto s = root->Son;
    printf("scan relexp\n");
    printf("exp type: %d\n",root->type);
    if(s.size() == 1){
        printf("scan single rel exp\n");
        auto exp = scanaddexp(s[0],isdec);
        auto str = exp2str(exp);
        if(!isdec && !noprint){
            if(b_false >= 0)
                fprintf(yyout,"if %s == 0 goto l%d\n", str.c_str(), b_false);
            if(b_true >= 0)
                fprintf(yyout, "if %s != 0 goto l%d\n", str.c_str(), b_true);
        }
        return exp;
    }
    else if(s.size() == 3){
        auto exp1 = scanrelexp(s[0], isdec, -1, -1);
        auto str1 = exp2str(exp1);
        auto op = scanrelop(s[1], isdec);
        auto exp2 = scanaddexp(s[2], isdec);
        auto str2 = exp2str(exp2);
        if(isdec && !noprint){
            fprintf(yyout, "var t%d\n", tmp_cnt);
        }
        if(!isdec && !noprint){
            fprintf(yyout, "t%d = %s %s %s\n", tmp_cnt, str1.c_str(), op.c_str(), str2.c_str());
            if(b_true >= 0){
                fprintf(yyout, "if t%d != 0 goto l%d\n", tmp_cnt, b_true);
            }
            if(b_false >= 0){
                fprintf(yyout, "if t%d == 0 goto l%d\n", tmp_cnt, b_false);
            }
        }
        int t = tmp_cnt++;
        return std::make_pair(std::make_pair(t,0), _tmp_var);
    }
    else{
        yyerror("RelExp Error: wrong number of sons\n");
        return std::make_pair(std::make_pair(0,0), _null);
    }
}

std::string scanrelop(basenode* root, bool isdec){
    auto s = root->Son;
    if(s.size() == 1){
       switch(s[0]->type){
            case _less:
                return "<";
                break;
            case  _more:
                return ">";
                break;
            case _geq:
                return ">=";
                break;
            case _leq:
                return "<=";
                break;
            default:
                yyerror("RelOp Error: wrong type of son\n");
                return "";
                break;
       } 
    }
    else{
        yyerror("RelOp Error: wrong number of sons\n");
        return "";
    }
}