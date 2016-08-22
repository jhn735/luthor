#include <iostream>
#include <fstream>
#include "luthor.h"
#include "symbol.h"
#include <bitset>	
#include <string>
using namespace std;
using namespace lexer_luthor;
using namespace symbol_luthor;
int main(int argc, char * argv[]){
/*	//test symbol_stream
	fstream file("test_file.txt");
	cout << endl << "Chars ";
//	while(!file.eof())
		cout << (char)file.get() << " ";
	file.close();

	cout << endl << "intVal ";
	fstream fi("test_file.txt");
//	while(!fi.eof())
		cout << bitset<64>( fi.get() ) << " ";
	fi.close();

	cout << endl << "symbol ";
	fstream fb("test_file.txt");
	cout << endl;
	symbol_stream s(&fb, symbol_stream::encoding::UTF_8);
//	while(!s.eof())
		cout << bitset<64>( s.next_symbol() ) << " ";
	fb.close();
*/

	//parse the args
	//read the input file
	Lexer l(m);
	Token t;
	fstream file("test_file.txt");

	//print out the test file just so we know what we are dealing with
  ifstream f;
		f.open("test_file.txt");
		while(!f.eof())
			cout << (char)f.get();


	symbol_stream s(&file, symbol_stream::encoding::UTF_8);
	do{
		t = l.next_token(s);
		if(t.type() == type)
			cout << "Type: ";
		else if(t.type() == regexp)
			cout << "Regexp: ";
		else cout << "error: no token found!!" << endl;

		symbol_string val = t.value();
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
