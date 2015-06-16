#include <iostream>
#include "luthor.h"	
using namespace std;
int main(int argc, char * argv[]){
	//parse the args
	//read the input file
	Lexer l("test_file.txt");
	Token t;
	do{
		t = l.next_token();
		if(t.type() == type)
			cout << "Type: ";
		else if(t.type() == regexp)
			cout << "Regexp: ";
		
		cout << t.value() << endl;
	}while(t.type() != token_type::end);
	//construct the DFA code corresponding to the input file
	//write the code to file(s)
return 0;
}
