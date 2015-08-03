#include "luthor.h"
#include <string>
#include <iostream>
#include <cstdarg>
#include <fstream>

using namespace std;
using namespace luthor;
/*****Symbol_stream******/
symbol_stream::symbol_stream(std::fstream * f, encoding enc){
  this->file = f; this->enc = enc;
};

symbol symbol_stream::from_UTF8(std::fstream *file){
symbol retVal = 0;
  //work on the first byte get the total number of bytes
  char cur_char = file->get();
  int byte_count = 1;
  while( (cur_char & 0x80) != 0){
   byte_count++;
  cur_char = cur_char << 1;
  };
  
  cur_char >> byte_count;
  retVal = retVal | cur_char;
  for(int i = 1; i < byte_count; i++){
    cur_char = file->get();
	//if the byte isn't a continuation
	  //report error
	//otherwise shift the return value by 6 bits and add in the cur_char
	if( (cur_char & 0x80) == 0){}
	else{
	  retVal << 6;
	  retVal = retVal | (cur_char & 0x3F);
	}
  };
return retVal;  
};

symbol symbol_stream::from_UTF32BE(std::fstream *file){
  symbol retVal = 0;
  char sym[4]; file->get(sym, 4);
  for(int i = 0; i < symbol_size; i++)
	retVal = (retVal|sym[i]) << 8;
return retVal;
};

symbol symbol_stream::from_UTF32LE(std::fstream *file){
  symbol retVal = 0;
  char sym[4]; file->get(sym, 4);
  for(int i = symbol_size; i >= 0; i--)
	retVal = (retVal|sym[i]) << 8;
return retVal;
};

bool symbol_stream::eof(){ return file->eof();}

symbol symbol_stream::next_symbol(){ 
  switch(this->enc){
	case UTF_8: return from_UTF8(this->file);
	case UTF_32BE: return from_UTF32BE(this->file);
	case UTF_32LE: return from_UTF32LE(this->file);
  }
}

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
state::state(int num_transitions, ...){
  //extract the arguments
  va_list args;
  va_start(args, num_transitions);
  for(int i = 0; i < num_transitions; i++){
	state_transition s;
	  s.next_state_index = va_arg(args, int);
	  s.next_state_conditions = va_arg(args, symbol*);
	transitions.push_back(s);
  }
  va_end(args);
};

int state::next_state(symbol cur_sym){
  symbol* cur_condition;
  //for each potential state, check to see if the char meets the conditions
  for(int i = 0; i < transitions.size(); i++){
	cur_condition = transitions[i].next_state_conditions;
	//if the condition is met return the corresponding next state index
	if(state_transition::meets_condition(cur_sym, cur_condition))  
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
  bool retVal = (condition[1] == 0);
  for(int i = 2; i < condition[0]; i++)
	if( (cur_sym == condition[i]) ) return retVal;
//if no match was found return the opposite of what would've been returned
return !retVal;  
};

/***********state_table class***********/
state_table::state_table(token_type type, std::vector<state> table){
  this->_table = table;
  this->_type = type;
  reset();
};

void state_table::update(symbol cur_sym){
  //get the current state from the set of tables
  state cur_state = _table[cur_state_index];
  //save the current state index and get the next one
  int last_index = cur_state_index;
  cur_state_index = cur_state.next_state(cur_sym);

  //if the current state is the start state 
	//implicit(do not record string)
	//if a transition occured from a non-start to a start state, reset
  //otherwise a transition to a non-start state occured, add cur symbol
  if(initial_state()){ 
	if(last_index != 0) reset();
  }else _cur_value += cur_sym;
  
};

bool state_table::initial_state(){
  return cur_state_index == 0;
};

bool state_table::final_state(){
  return cur_state_index == (_table.size()-1);
};

void state_table::reset(){
  cur_state_index = 0;
  _cur_value.clear();
};

symbol_string state_table::value(){ return _cur_value; };

token_type state_table::type(){ return _type;}

/*********Lexer class*************/
Lexer::Lexer(std::vector<state_table> table_set){
  this->_table_set = table_set;
};

Token Lexer::next_token(symbol_stream &text){
  symbol cur_sym;
  if(text.eof()) return Token(end, {});
  //until the file reaches the end
  while(!text.eof()){
	cur_sym = text.next_symbol();
	//for each state and corresponding state table
	  //find the next state
	for(int i = 0; i < _table_set.size(); i++){
	  state_table table = _table_set[i];
	  table.update(cur_sym);
	  //if a transition to the end state occurred
		//return the token and reset the state
	  if( table.final_state() ){
		Token retVal(table.type(), table.value());
		table.reset();
	  return retVal;
	  }
	}//end for
  }//end while

//if no tokens are found return empty token
return Token();
};

namespace luthor{
//tables generated
  //generated::start
std::vector<state_table> m = { 
  state_table(
	type,
	{ 
	  state(1, 1, "\4\0\n,"),
	  state(2, 1, "\3\1:", 2, "\3\0:"),
	  state(1, 0, "\2\1")
	}
  ),
  state_table(
	regexp, 
	{
	  state(1, 1, "\3\0:"),
	  state(2, 1, "\3\1\n", 2, "\3\0\n"),
	  state(1, 0, "\2\1")
	}
  )
};  
  //generated::end
};
