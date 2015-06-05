#ifndef LUTHOR_H
#define LUTHOR_H
	#include <string>
	#include <fstream>
	#include <queue>

	enum token_type{
		start = 0, 
	//generated::start
			type, regexp, NIL,
	//generated::end
		end		
		};

class Token{
	public:
		Token();
		Token(token_type type, std::string value);
		token_type type();
		std::string value();
	protected:
		token_type _type;
		//value given by the lexer that creates it 
		std::string _value;	
};

class Lexer{
	protected:	
		std::queue<Token> token_list;
		void populate_list(ifstream &text);
		bool meet_condition(char curChar, char * condition);
		//each state will have a set of states to go to with the 
		// first number being the number of states
			//the conditions to move to them
			//the first character shows the length of the string
			//the second character of the condition can be \0 \1 \2 
				//\0 for being one of any in the string
				//\1 for being any character except that in the string
			
		typedef struct state{
			bool end_state;
			int * next_state_index;
			char ** next_state_conditions;
		};

	public:
		Lexer(std::string text_filename);
		Token next_token();
};
#endif
