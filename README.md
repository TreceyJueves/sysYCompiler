# sysYCompiler
2021春编译原理实践lab

3-stage sysY compiler using lex and yacc

整个代码是从0开始写的，没有框架（不知道以后会不会改版）

sysy2riscv为三部分合在一起之后的效果,是三阶段合在一起后经过修改得到的,和那三个单阶段的不是完全一样,可以过function_test, performance_test为386s

sysy2eeyore eeyore2tigger tigger2riscv连续使用可能出错，但是可以分别过相应的单阶段function test

https://github.com/wangchang327/compiler-lab-test-driver 是一个可以跑本地测试的小工具，将compiler和py文件放到和miniVM及open-test-case文件夹同层的地方，使用wsl或其他linux系统python3 ./test.py e/t/r即可，还需要改minivm的main.cpp之后再编译minivm，具体操作详见链接

cd ./sysy2eeyore

./compiler -S -e input.sy -o output.eeyore

cd ./eeyore2tigger

./compiler -S -e input.eeyore -o output.tigger

cd ./tigger2riscv

./compiler -S -e input.tigger -o output.S

the current eeyore2tigger has no register allocation at all (all variables stored in stack)

别问我为什么不用store，我只是想把功能给过了罢了

提醒一下riscV的return和函数声明时候的addi也要满足int12的要求，否则要先load到s0里处理

性能测试中的fft有在函数参数直接中使用函数返回值的情况, 因此需要在调用前才param, 而不能一上来一边解析一边param


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
    
最后感谢xyf,wyx,wc,lhy,hyt,hxy,lnj,lcw等等同学以及助教MaxXing对此lab的帮助
痛苦的先驱希望能够帮到后面的同学
