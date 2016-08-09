#ifndef LUTHOR_H
#define LUTHOR_H
	#include "symbol.h"
	#include <string>
	#include <queue>
	#include <string>
	#include <fstream>
	#include <vector>

namespace lexer_luthor{

enum token_type{
	start = 0,
	//generated::start
			type, regexp,
	//generated::end
	NIL, end
};


class Token{
  public:
	Token();
	Token(token_type type, symbol_luthor::symbol_string value);
	token_type type();
	symbol_luthor::symbol_string value();
  protected:
	token_type _type;
	//value given by the lexer that creates it 
	symbol_luthor::symbol_string _value;	
};

//The possible state of the recognizers of a pattern.
//Each state will have a set of states to go to with the 
	//the conditions to move to them.
//The first character shows the length of the string.
//The second character of the condition can be \0 \1 \2 
	//\0 for being one of any in the string
	//\1 for being any character except that in the string
class state{
  typedef struct state_transition{
	int next_state_index; symbol_luthor::symbol * next_state_conditions;
	static bool meets_condition(symbol_luthor::symbol cur_sym, symbol_luthor::symbol * condition);
	bool meets_condition(symbol_luthor::symbol cur_sym);
  } state_transition;

  public:
	state(int num_transitions, ...);
	//State transitions given a symbol
		//Each return the index of the next transition.
	int next_state(symbol_luthor::symbol cur_sym);
	static int next_state(symbol_luthor::symbol cur_sym, state cur_state);

	std::vector<state_transition> transitions;
};

class state_table{
  std::vector<state> _table; 
  symbol_luthor::symbol_string _cur_value;
  int cur_state_index; token_type _type;

  public:
	state_table(token_type type, std::vector<state> table);
	void update(symbol_luthor::symbol cur_sym);
	bool initial_state();
	bool final_state();
	void reset();
	symbol_luthor::symbol_string value();
	token_type type();
};

class Lexer{
  protected:
	std::vector<state_table> _table_set;

  public:
	Lexer(std::vector<state_table> table_set);
	Token next_token(symbol_luthor::symbol_stream &text);
};

extern std::vector<state_table> m;
};//end namespace luthor

#endif
