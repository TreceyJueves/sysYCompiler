all: lex yacc eeyore

eeyore: eeyore.yy.o eeyore.tab.o scantree.o scanfuncdef.o
	g++ -Wno-register -O2 -lm -Wall -std=c++17 eeyore.tab.o eeyore.yy.o scantree.o scanfuncdef.o \
	-o compiler -Idirs

lex: eeyore.l e_parser.hpp
	flex -o eeyore.yy.cpp eeyore.l

yacc: eeyore.y e_parser.hpp
	bison -d -o eeyore.tab.cpp eeyore.y

eeyore.yy.o: eeyore.yy.cpp e_parser.hpp eeyore.tab.hpp
	g++ -Wno-register -O2 -lm -Wall -std=c++17 eeyore.yy.cpp -c -Idirs

eeyore.tab.o: eeyore.tab.cpp e_parser.hpp
	g++ -Wno-register -O2 -lm -Wall -std=c++17 eeyore.tab.cpp -c -Idirs

scantree.o: scantree.cpp e_parser.hpp
	g++ -Wno-register -O2 -lm -Wall -std=c++17 scantree.cpp -c -Idirs

scanfuncdef.o: scanfuncdef.cpp e_parser.hpp
	g++ -Wno-register -O2 -lm -Wall -std=c++17 scanfuncdef.cpp -c -Idirs
	
clean:
	rm *.o eeyore.tab.cpp *.h *.c eeyore.yy.cpp eeyore.tab.hpp
