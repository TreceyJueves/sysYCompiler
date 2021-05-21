all: lex yacc tigger

tigger: tigger.yy.o tigger.tab.o scantigger.o
	g++ -Wno-register -O2 -lm -std=c++17 tigger.tab.o tigger.yy.o scantigger.o -o compiler -Idirs

lex: tigger.l t_parser.hpp
	flex -o tigger.yy.cpp tigger.l

yacc: tigger.y t_parser.hpp
	bison -d -o tigger.tab.cpp tigger.y

tigger.yy.o: tigger.yy.cpp t_parser.hpp tigger.tab.hpp
	g++ -Wno-register -O2 -lm -std=c++17 tigger.yy.cpp -c -Idirs

tigger.tab.o: tigger.tab.cpp t_parser.hpp
	g++ -Wno-register -O2 -lm -std=c++17 tigger.tab.cpp -c -Idirs

scantigger.o: scantigger.cpp t_parser.hpp
	g++ -Wno-register -O2 -lm -std=c++17 scantigger.cpp -c -Idirs
	
clean:
	rm *.o tigger.tab.cpp *.h *.c tigger.yy.cpp tigger.tab.hpp
