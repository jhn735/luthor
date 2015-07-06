#ifndef LUTHOR_H
#define LUTHOR_H
	#include <string>
	#include <fstream>
	#include <queue>
	#include <string>
	#include "symbol.h"

enum token_type{
	start = 0,
	//generated::start
			type, regexp,
	//generated::end
	NIL, end
};

typedef std::basic_string<symbol> symbol_string;

class Token{
	public:
		Token();
		Token(token_type type, std::string value);
		token_type type();
		symbol_string value();
	protected:
		token_type _type;
		//value given by the lexer that creates it 
		symbol_string _value;	
};

class Lexer{
	protected:	
		std::queue<Token> token_list;
		void populate_list(std::ifstream &text);
			
		//the possible state of the recognizers of a pattern
		//each state will have a set of states to go to with the 
			//the conditions to move to them
			//the first character shows the length of the string
			//the second character of the condition can be \0 \1 \2 
				//\0 for being one of any in the string
				//\1 for being any character except that in the string
		typedef struct state_transition{
			int next_state_index; char * next_state_conditions;
		} state_transition;

		class state{
			public:
				state(int num_transitions, ...);
				int num_transitions;
				std::vector<state_transition> transitions;
		};
		
		int next_state(char cur_char, state cur_state);
	public:
		Lexer(std::ifstream &text);
		Token next_token();
};
#endif
