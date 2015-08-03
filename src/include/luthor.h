#ifndef LUTHOR_H
#define LUTHOR_H
	#include <string>
	#include <queue>
	#include <string>
	#include <fstream>
	#include <vector>

namespace luthor{

enum token_type{
	start = 0,
	//generated::start
			type, regexp,
	//generated::end
	NIL, end
};

typedef char32_t symbol;
//number of bytes contained within a symbol
const size_t symbol_size = 4;

typedef std::basic_string<symbol> symbol_string;

class symbol_stream{
  public:
	//different encoding types including endianess in UTF32
	enum encoding{ UTF_8, UTF_32BE, UTF_32LE};
	
	symbol_stream(std::fstream *f, encoding enc);
	bool eof();
	symbol next_symbol();
  private:
	std::fstream * file;
	encoding enc;
	int next_byte();
	symbol from_UTF8(std::fstream *file);
	symbol from_UTF32BE(std::fstream *file);
	symbol from_UTF32LE(std::fstream *file);

};

class Token{
  public:
	Token();
	Token(token_type type, symbol_string value);
	token_type type();
	symbol_string value();
  protected:
	token_type _type;
	//value given by the lexer that creates it 
	symbol_string _value;	
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
	int next_state_index; symbol * next_state_conditions;
	static bool meets_condition(symbol cur_sym, symbol * condition);
  } state_transition;

  public:
	state(int num_transitions, ...);
	//State transitions given a symbol
		//Each return the index of the next transition.
	int next_state(symbol cur_sym);
	static int next_state(symbol cur_sym, state cur_state);

	std::vector<state_transition> transitions;
};

class state_table{
  std::vector<state> _table; 
  symbol_string _cur_value;
  int cur_state_index; token_type _type;

  public:
	state_table(token_type type, std::vector<state> table);
	void update(symbol cur_sym);
	bool initial_state();
	bool final_state();
	void reset();
	symbol_string value();
	token_type type();
};

class Lexer{
  protected:
	std::vector<state_table> _table_set;

  public:
	Lexer(std::vector<state_table> table_set);
	Token next_token(symbol_stream &text);
};

extern std::vector<state_table> m;
};//end namespace luthor

#endif
