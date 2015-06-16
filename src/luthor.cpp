#include "luthor.h"
#include <string>
#include <iostream>
#include <cstdarg>
#include <fstream>

using namespace std;
/*****Token class*******/
Token::Token(){
	//the default values are null 
	this->_type = token_type::NIL; this->_value = "";
};

Token::Token(token_type type, string value){
	//set the name and value of this token
	this->_type = type; this->_value = value;
};

token_type Token::type(){ return _type;};
string Token::value(){ return _value;};
/**********state class************/
//the first argument holds the total number of state transitions
//the next set of arguments alternate between the index of the next
	//state to transition to and the conditions met when a transition occurs
Lexer::state::state(int num_transitions, ...){
	this->num_transitions = num_transitions;
	
	//extract the arguments
	va_list args;
	va_start(args, num_transitions);
	for(int i = 0; i < num_transitions; i++){
		state_transition s;
			s.next_state_index = va_arg(args, int);
			s.next_state_conditions = va_arg(args, char*);
		transitions.push_back(s);
	}
	va_end(args);
};

/*********Lexer class*************/
Lexer::Lexer(string text_filename){
//open the text file
const char * filename = text_filename.c_str();
ifstream text(filename, ios_base::in);
	//check to make sure that the file actually opens
		//for now it just outputs file not found.
	if(!text){ cout << "\nFile not found!!!!\n";} 
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
};

void Lexer::populate_list(ifstream &text){
	//add the start token to the token_list
	token_list.push(Token(token_type::start, ""));
	//generated::start
		token_type table_types[] = {type, regexp};
		//set up the elements of each table 
			int table_size = 3;
		//the tables of states for each type
		state type_table[]{ 
			state(1, 1, "\4\0\n,"),
			state(2, 1, "\3\1:", 2, "\3\0:"),
			state(1, 0, "\2\1")
		};

		state regexp_table[]{
			state(1, 1, "\3\0:"),
			state(2, 1, "\3\1\n", 2, "\3\0\n"),
			state(1, 0, "\2\1")
		};
		
		int table_num = 2;	
		//the tables in one table of tables lol
		state * tables[] = {type_table, regexp_table};
		//the index of the end state of each table
		int last_states[] = {2, 2};
		int table_states[] = {0, 0};
	//generated::end

	string * cur_values = new string[table_num];
	char curChar;
	//the state index and the last state index 
		//to be used in the following loops
	int state_index; int last_state_index;
	//until the file reaches the end
	while(!text.eof()){
		curChar = text.get();
		//for each state and corresponding state table
			//find the next state
		for(int i = 0; i < table_num; i++){
			//get the current state index
			state_index = table_states[i];
			//get the current state from the set of tables
			state cur_state = tables[i][state_index];
			//set the next state given the current char and the state
			table_states[i] = next_state(curChar, cur_state);
			//get the now updated state and check to see if is the end
			last_state_index = state_index;
			state_index = table_states[i];

			//if the current state is the start state
				//if a transition occured from a non-start to a start state
					//erase the current string value
			//otherwise transition to a non-start state occured, add curchar
			if(state_index == 0){ 
				if(last_state_index != 0) cur_values[i].clear();
			}else cur_values[i] += curChar;
		
			//if a transition to the end state occurred
				//add a new token and reset the state
			if(state_index == last_states[i]){
				token_list.push(Token(table_types[i], cur_values[i]));
				table_states[i] = 0;
				cur_values[i].clear();
			}
		}
	};
//cap the token_list off with an 'end' type token	
token_list.push(Token(token_type::end, ""));
};

bool meet_condition(char curChar, char * condition);

int Lexer::next_state(char cur_char, state cur_state){
	char * cur_condition;
	//for each potential state, check to see if the char meets the conditions
	for(int i = 0; i < cur_state.num_transitions; i++){
		cur_condition = cur_state.transitions[i].next_state_conditions;
		//if the condition is met return the corresponding next state index
		if(meet_condition(cur_char, cur_condition))	
			return cur_state.transitions[i].next_state_index;
	}
//if no conditions were met reset to the start state
return 0;
};

bool meet_condition(char curChar, char * condition){
	//this code does two things
		//if allowing only the characters mentioned
			//return true if the characte matches any in the array 
		//if allowing all characters except those mentioned
			//return false if the character matches any in the array
	bool retVal = (condition[1] == 0);
	for(int i = 2; i < condition[0]; i++)
		if( (curChar == condition[i]) ) return retVal;
//no characters were found return false/true.	
return !retVal;
};
