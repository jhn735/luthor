#ifndef CODE_H 
#define CODE_H
	#define LUTHOR_H_P_1 "#ifndef LUTHOR_H\n\
#define LUTHOR_H\n\
\t#include <string>\n\
\t#include <fstream>\n\
\n\
\tenum token_type{\n\
\t\tNULL,\n\
\t//generated::start\n\
"
	#define LUTHOR_H_P_2 "\t//generated::end\n\
\t\t};\n\
\n\
class Token{\n\
\tpublic:\n\
\t\tToken();\n\
\t\tToken(token_type type, std::string value);\n\
\t\ttoken_type type();\n\
\t\tstd::string value();\n\
\tprotected:\n\
\t\tstd::string _type;\n\
\t\t//value given by the lexer that creates it \n\
\t\tstd::string _value;\t\n\
};\n\
\n\
class Lexer{\n\
\tprotected:\n\
\t\tifstream text;\n\
\tpublic:\n\
\t\tLexer(std::string text_filename);\n\
\t\t~Lexer();\n\
\t\tToken next_token();\n\
};\n\
#endif\n\
"
	#define LUTHOR_CPP_P_1 "#include \"luthor.h\"\n\
#include <string>\n\
#include <fstream>\n\
\n\
Token::Token(){\n\
\t//the default values are null \n\
\tthis->_type = \"\"; this->_value = \"\";\n\
};\n\
\n\
Token::Token(std::string type, std::string value){\n\
\t//set the name and value of this token\n\
\tthis->_type = type; this->_value = value;\n\
};\n\
\n\
std::string Token::type(){ return _type;};\n\
std::string Token::value(){ return _value;};\n\
\n\
Lexer::Lexer(std::string text_filename){\n\
\t//open the text file\n\
\ttext.open(text_filename);\n\
\t//check to make sure that the file actually opens\n\
\t\t//for now it just outputs file not found.\n\
\tif(!text){\n\
\t\tstd::cout << std::endl << \"File not found!!!!\" << std::endl;\n\
\t}\n\
\n\
};\n\
\n\
//make sure the text is closed upon exiting\n\
Lexer::~Lexer(){\n\
\ttext.close();\n\
};\n\
\n\
Token Lexer::next_token(){\n\
Token retVal;\n\
//generated::start\n\
"
	#define LUTHOR_CPP_P_2 "//generated::end\n\
return retVal;\n\
}:\n\
\n\
"
#endif
