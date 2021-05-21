# sysYCompiler
3-stage sysY compiler using lex and yacc

the current eeyore2tigger has no register allocation

别问我为什么不用store，我只是想把功能给过了罢了

提醒一下riscV的return和函数声明时候的addi也要满足int12的要求，否则要先load到s0里处理
