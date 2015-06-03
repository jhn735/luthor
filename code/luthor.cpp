#include "luthor.h"
#include <string>
#include <fstream>

/*****Token class*******/
Token::Token(){
	//the default values are null 
	this->_type = token_type.NIL; this->_value = "";
};

Token::Token(token_type type, std::string value){
	//set the name and value of this token
	this->_type = type; this->_value = value;
};

token_type Token::type(){ return _type;};
std::string Token::value(){ return _value;};

/*********Lexer class*************/
Lexer::Lexer(std::string text_filename){
//open the text file
std::ifstream text(text_filename, std::ifstream::in);
	//check to make sure that the file actually opens
		//for now it just outputs file not found.
	if(!text){ std::cout << "\nFile not found!!!!\n";} 
	else{ populate_list(text);}
//make sure the text is closed upon exiting
text.close();
};

void Token::populate_list(ifstream &text){
	//generated::start
		//the tables of states for each type
		
		//the actual state of each type's expression
	
	//generated::end
};

//returns the token at the top of the list
	//if the the list is empty then return an empty Token
Token Lexer::next_token(){
Token retVal;
	//if the token_list is not empty 
		//set the retVal to the top of the list and pop
	if(!token_list.empty()){	
		retVal = token_list.front();
		token_list.pop();
	}//if the the list is empty the Token is set to the default values NIL
return retVal;
}:

