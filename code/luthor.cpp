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

void Token::populate_list(ifstream &text){
	//add the start token to the token_list
	token_list.push(Token(token_type::start, "");
	//generated::start
		//the tables of states for each type
		state type_table[] = {
			{false, 1, {1},    {"\3\0\n"} },
			{false, 2, {1, 2}, {"\3\1:", "\3\0:"} },
			{true,  1, {0},    {"\2\1"} }
		};

		state regexp_table[] = {
			{false, 1, {1},    {"\3\0:"} },
			{false, 2, {1, 2}, {"\3\1\n","\3,\0\n"} },
			{true,  1, {0},    {"\2\1"}  }
		};

		int table_num = 2;	
		//the tables in one table of tables lol
		state * tables[] = {type_table, regexp_table};
		//the actual state of each type's expression
		int table_states = {0, 0};
		
	//generated::end
		//the value to be set if a recognizer recognizes something
		std::string cur_value;
		//the number of 
		char curChar;
		//until the file reaches the end
		while(!text.eof()){
			curChar = text.get();
			//for each state and corresponding state table
				//find the next state
			for(int i = 0; i < table_num; i++){
				//get the current state from the set of tables
				state cur_state = tables[i][table_states[i]];
				//set the next state given the current char and the state
				table_states[i] = next_state(curChar, cur_state);		
				//get the now updated state and check to see if is the end
				cur_state = tables[i][table_states[i]];	
				if(cur_state.end_state)
			}	
		};
	
	token_list.push(Token(token_type::end, "");
};

bool meet_condition(char curChar, char * condition);

int Lexer::next_state(char cur_char, state cur_state){
	char * cur_condition;
	//for each potential state, check to see if the char meets the conditions
	for(int i = 0; i < cur_state.num_states; i++){
		cur_condition = cur_state.next_state_conditions[i];
		if(meet_condition(cur_char, cur_condition))	
			return cur_state.next_state_index[i];
	}
//if no conditions were met reset to the start state
return 0;
};

bool meet_condition(char curChar, char * condition){
	//the modifier is set true if the condition is false upon
	bool retVal = (condition[1] == 0);
	//this code does two things
		//if allowing only the characters mention
			//if the characte matches any in the array return true 
		//if allowing all characters except those mentioned
			//if the character matches any in the array return false
	for(int i = 2; i < condition[0]; i++){
		if( (curChar == condition[i])) return retVal;
//no characters were found return false/true.	
return !retVal;
};
