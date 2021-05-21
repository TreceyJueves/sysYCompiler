# sysYCompiler
3-stage sysY compiler using lex and yacc

cd ./sysy2eeyore

./compiler -S -e input.sy -o output.eeyore

cd ./eeyore2tigger

./compiler -S -e input.eeyore -o output.tigger

cd ./tigger2riscv

./compiler -S -e input.tigger -o output.S

the current eeyore2tigger has no register allocation at all (all variables stored in stack)

别问我为什么不用store，我只是想把功能给过了罢了

提醒一下riscV的return和函数声明时候的addi也要满足int12的要求，否则要先load到s0里处理


sysY EBNF

    CompUnit      ::= [CompUnit] (Decl | FuncDef);



    Decl          ::= ConstDecl | VarDecl;

    ConstDecl     ::= "const" BType ConstDef {"," ConstDef} ";";

    BType         ::= "int";

    ConstDef      ::= IDENT {"[" ConstExp "]"} "=" ConstInitVal;

    ConstInitVal  ::= ConstExp | "{" [ConstInitVal {"," ConstInitVal}] "}";

    VarDecl       ::= BType VarDef {"," VarDef} ";";

    VarDef        ::= IDENT {"[" ConstExp "]"}

                | IDENT {"[" ConstExp "]"} "=" InitVal;
                
    InitVal       ::= Exp | "{" [InitVal {"," InitVal}] "}";



    FuncDef       ::= FuncType IDENT "(" [FuncFParams] ")" Block;

    FuncType      ::= "void" | "int";

    FuncFParams   ::= FuncFParam {"," FuncFParam};

    FuncFParam    ::= BType IDENT ["[" "]" {"[" ConstExp "]"}];



    Block         ::= "{" {BlockItem} "}";

    BlockItem     ::= Decl | Stmt;

    Stmt          ::= LVal "=" Exp ";"

                | [Exp] ";"
                
                | Block
                
                | "if" "(" Cond ")" Stmt ["else" Stmt]
                
                | "while" "(" Cond ")" Stmt
                
                | "break" ";"
                
                | "continue" ";"
                
                | "return" [Exp] ";";



    Exp           ::= AddExp;

    Cond          ::= LOrExp;

    LVal          ::= IDENT {"[" Exp "]"};

    PrimaryExp    ::= "(" Exp ")" | LVal | Number;

    Number        ::= INT_CONST;

    UnaryExp      ::= PrimaryExp | IDENT "(" [FuncRParams] ")" | UnaryOp UnaryExp;

    UnaryOp       ::= "+" | "-" | "!";

    FuncRParams   ::= Exp {"," Exp};

    MulExp        ::= UnaryExp | MulExp ("*" | "/" | "%") UnaryExp;

    AddExp        ::= MulExp | AddExp ("+" | "-") MulExp;

    RelExp        ::= AddExp | RelExp ("<" | ">" | "<=" | ">=") AddExp;

    EqExp         ::= RelExp | EqExp ("==" | "!=") RelExp;

    LAndExp       ::= EqExp | LAndExp "&&" EqExp;

    LOrExp        ::= LAndExp | LOrExp "||" LAndExp;

    ConstExp      ::= AddExp;
