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

	public:
		Lexer(std::string text_filename);
		Token next_token();
};
#endif
