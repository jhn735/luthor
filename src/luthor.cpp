#include "luthor.h"
#include <string>
#include <iostream>
#include <cstdarg>
#include <fstream>

using namespace std;
using namespace lexer_luthor;
using namespace symbol_luthor;
/*****Token class*******/
Token::Token(){
  //the default values are null 
  this->_type = token_type::NIL; this->_value = {};
};

Token::Token(token_type type, symbol_string value){
  //set the name and value of this token
  this->_type = type; this->_value = value;
};

token_type Token::type(){ return _type;};
symbol_string Token::value(){ return _value;};
/**********state class************/
//the first argument holds the total number of state transitions
//the next set of arguments alternate between the index of the next
  //state to transition to and the conditions met when a transition occurs 
  //in the form of a UString
state::state(int num_transitions, ...){
  //extract the arguments
  va_list args;
  va_start(args, num_transitions);
  for(int i = 0; i < num_transitions; i++){
	state_transition s;
	  s.next_state_index = va_arg(args, int);
    //get the condition list and copy the values over
	  char const * char_list = va_arg(args, char const *);
    s.next_state_conditions =  new symbol[char_list[0]];
    for(int i = 0; i < char_list[0]; i++)
      s.next_state_conditions[i] = char_list[i]; 

	transitions.push_back(s);
  }
  va_end(args);
};

int state::next_state(symbol cur_sym){
  symbol* cur_condition;
  //for each potential state, check to see if the char meets the conditions
  for(int i = 0; i < transitions.size(); i++){
	//if the condition is met return the corresponding next state index
	if(transitions[i].meets_condition(cur_sym))  
	  return transitions[i].next_state_index;
  }
//if no conditions were met reset to the start state
return 0;
};

bool state::state_transition::meets_condition
	  (symbol cur_sym, symbol* condition){
  //this code does two things
	//if allowing only the characters mentioned
	  //return true if the character matches any in the array 
	//if allowing all characters except those mentioned
	  //return false if the character matches any in the array
  bool retVal = (condition[1] == 1);
  for(int i = 2; i < condition[0]; i++)
		if( cur_sym == condition[i] ) return retVal;
//if no match was found return the opposite of what would've been returned
return !retVal;  
};

bool state::state_transition::meets_condition(symbol cur_sym){
	return meets_condition(cur_sym, this->next_state_conditions);
}

/***********state_table class***********/
//the variable argument is the states held within the table
state_table::state_table(token_type type, int table_size,  ...){
  this->_type = type;
	
  va_list args;
  
  va_start(args, table_size);
  for(int i = 0; i < table_size; i++){
	  this->_table.push_back( va_arg(args, state));
  }
  va_end(args);
  reset();
};

void state_table::update(symbol cur_sym){
  //get the current state from the set of tables
  state cur_state = this->_table[this->cur_state_index];
  //save the current state index and get the next one
  int last_index = this->cur_state_index;
 this->cur_state_index = cur_state.next_state(cur_sym);

  //if the current state is the start state 
	//implicit(do not record string)
	//if a transition occured from a non-start to a start state, reset
  //otherwise a transition to a non-start state occured, add cur symbol
  if(initial_state()){ 
		if(last_index != 0) reset();
  }else this->_cur_value.push_back(cur_sym);
 int i = 0; 
};

bool state_table::initial_state(){
  return this->cur_state_index == 0;
};

bool state_table::final_state(){
  return this->cur_state_index == (this->_table.size()-1);
};

void state_table::reset(){
  this->cur_state_index = 0;
  this->_cur_value.clear();
};

symbol_string state_table::value(){ return this->_cur_value; };

token_type state_table::type(){ return this->_type;}

/*********Lexer class*************/
Lexer::Lexer(std::vector<state_table> table_set){
  this->_table_set = table_set;
};

Token Lexer::next_token(symbol_stream &text){
  symbol cur_sym;
  if(text.eof()) return Token(end, U"");
  //until the file reaches the end
  while(!text.eof()){
	cur_sym = text.next_symbol();
	//for each state and corresponding state table
	  //find the next state
	for(int i = 0; i < this->_table_set.size(); i++){
		//Create a reference to the table as shorthand
	  state_table * table = &(this->_table_set[i]);
	  table->update(cur_sym);
	  //if a transition to the end state occurred
		//return the token and reset the state
	  if( table->final_state() ){
		  Token retVal(table->type(), table->value());
		  table->reset();
	  return retVal;
	  }
	}//end for
  }//end while

//if no tokens are found return empty token
return Token();
};

char const * type_stateCond1 = "\4\0\n,";

//tables generated
  //generated::start
std::vector<state_table> lexer_luthor::m = { 
  state_table(
	type, 3, 
	  state(1, 1, "\4\0\n"),
	  state(2, 1, "\3\0:", 2, "\3\1:\0"),
	  state(0)
  )
};
  //generated::end

