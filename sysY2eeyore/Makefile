all: lex yacc sysY

sysY: lex.yy.o sysY.tab.o scantree.o scanexp.o scanblock.o convert.o
	g++ -Wno-register -O2 -lm -std=c++17 sysY.tab.o lex.yy.o scantree.o scanexp.o scanblock.o \
	convert.o -o compiler -Idirs

lex: sysY.l parser.hpp
	flex -o lex.yy.cpp sysY.l

yacc: sysY.y parser.hpp
	bison -d -o sysY.tab.cpp sysY.y

lex.yy.o: lex.yy.cpp parser.hpp sysY.tab.hpp
	g++ -Wno-register -O2 -lm -std=c++17 lex.yy.cpp -c -Idirs

sysY.tab.o: sysY.tab.cpp parser.hpp
	g++ -Wno-register -O2 -lm -std=c++17 sysY.tab.cpp -c -Idirs

scantree.o: scantree.cpp parser.hpp
	g++ -Wno-register -O2 -lm -std=c++17 scantree.cpp -c -Idirs

scanexp.o: scanexp.cpp parser.hpp
	g++ -Wno-register -O2 -lm -std=c++17 scanexp.cpp -c -Idirs

scanblock.o: scanblock.cpp parser.hpp
	g++ -Wno-register -O2 -lm -std=c++17 scanblock.cpp -c -Idirs

convert.o: convert.cpp parser.hpp
	g++ -Wno-register -O2 -lm -std=c++17 convert.cpp -c -Idirs
	
clean:
	rm *.o sysY.tab.cpp *.h *.c lex.yy.cpp sysY.tab.hpp
