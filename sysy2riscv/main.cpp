#include "starter.hpp"
#include <stdio.h>

int main(int argc, char* argv[]){
    char eeyore_out[10] = "e.eeyore";
    char tigger_out[10] = "tt.tigger";
    char* r_out;
    char* sysy_in;
    for (int i = 1;i < argc;i++){
		if (argv[i][0] == '-'){
			switch(argv[i][1]){
				case 'S':
					break;
				case 'e':
					break;
				case 'o':
					i++;
					r_out = argv[i];
					break;
				default:
					break;
			}		
		}
		else{
			sysy_in = argv[i];
		}		
	}
    s2e(sysy_in, eeyore_out);
    e2t(eeyore_out, tigger_out);
    t2r(tigger_out, r_out);
    return 0;
}