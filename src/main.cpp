#include <iostream>
#include "luthor.h"	
#include <string>
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

		string val = t.value();
		for(int i = 0; i < val.size(); i++){
			if(val[i] == '\n') cout << "\\n";
			else cout << val[i];
		}
		cout << endl;
	}while(t.type() != token_type::end);
	//construct the DFA code corresponding to the input file
	//write the code to file(s)
return 0;
}
