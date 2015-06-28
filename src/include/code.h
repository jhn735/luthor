#ifndef CODE_H 
#define CODE_H
	#define LUTHOR_H_P_1 "#ifndef LUTHOR_H\n\
#define LUTHOR_H\n\
\t#include <string>\n\
\t#include <fstream>\n\
\t#include <queue>\n\
\t#include <string>\n\
\t#include <cstdint>\n\
enum token_type{\n\
\tstart = 0,\n\
\t//generated::start\n\
"
	#define LUTHOR_H_P_2 "\t//generated::end\n\
\tNIL, end\n\
};\n\
\n\
class Token{\n\
\tpublic:\n\
\t\tToken();\n\
\t\tToken(token_type type, std::string value);\n\
\t\ttoken_type type();\n\
\t\tstd::string value();\n\
\tprotected:\n\
\t\ttoken_type _type;\n\
\t\t//value given by the lexer that creates it \n\
\t\tstd::string _value;\t\n\
};\n\
\n\
class Lexer{\n\
\tprotected:\t\n\
\t\tstd::queue<Token> token_list;\n\
\t\tvoid populate_list(std::ifstream &text);\n\
\t\t\t\n\
\t\t//the possible state of the recognizers of a pattern\n\
\t\t//each state will have a set of states to go to with the \n\
\t\t\t//the conditions to move to them\n\
\t\t\t//the first character shows the length of the string\n\
\t\t\t//the second character of the condition can be \0 \1 \2 \n\
\t\t\t\t//\0 for being one of any in the string\n\
\t\t\t\t//\1 for being any character except that in the string\n\
\t\ttypedef struct state_transition{\n\
\t\t\tint next_state_index; char * next_state_conditions;\n\
\t\t} state_transition;\n\
\n\
\t\tclass state{\n\
\t\t\tpublic:\n\
\t\t\t\tstate(int num_transitions, ...);\n\
\t\t\t\tint num_transitions;\n\
\t\t\t\tstd::vector<state_transition> transitions;\n\
\t\t};\n\
\t\t\n\
\t\tint next_state(char cur_char, state cur_state);\n\
\tpublic:\n\
\t\tLexer(std::string text_filename);\n\
\t\tToken next_token();\n\
};\n\
#endif\n\
"
	#define LUTHOR_CPP_P_1 "#include \"luthor.h\"\n\
#include <string>\n\
#include <iostream>\n\
#include <cstdarg>\n\
#include <fstream>\n\
\n\
using namespace std;\n\
/*****Token class*******/\n\
Token::Token(){\n\
\t//the default values are null \n\
\tthis->_type = token_type::NIL; this->_value = \"\";\n\
};\n\
\n\
Token::Token(token_type type, string value){\n\
\t//set the name and value of this token\n\
\tthis->_type = type; this->_value = value;\n\
};\n\
\n\
token_type Token::type(){ return _type;};\n\
string Token::value(){ return _value;};\n\
/**********state class************/\n\
//the first argument holds the total number of state transitions\n\
//the next set of arguments alternate between the index of the next\n\
\t//state to transition to and the conditions met when a transition occurs\n\
Lexer::state::state(int num_transitions, ...){\n\
\tthis->num_transitions = num_transitions;\n\
\t\n\
\t//extract the arguments\n\
\tva_list args;\n\
\tva_start(args, num_transitions);\n\
\tfor(int i = 0; i < num_transitions; i++){\n\
\t\tstate_transition s;\n\
\t\t\ts.next_state_index = va_arg(args, int);\n\
\t\t\ts.next_state_conditions = va_arg(args, char*);\n\
\t\ttransitions.push_back(s);\n\
\t}\n\
\tva_end(args);\n\
};\n\
\n\
/*********Lexer class*************/\n\
Lexer::Lexer(string text_filename){\n\
//open the text file\n\
const char * filename = text_filename.c_str();\n\
ifstream text(filename, ios_base::in);\n\
\t//check to make sure that the file actually opens\n\
\t\t//for now it just outputs file not found.\n\
\tif(!text){ cout << \"\nFile not found!!!!\n\";} \n\
\telse{ populate_list(text);}\n\
//make sure the text is closed upon exiting\n\
text.close();\n\
};\n\
\n\
//returns the token at the top of the list\n\
\t//if the the list is empty then return an empty Token\n\
Token Lexer::next_token(){\n\
Token retVal;\n\
\t//if the token_list is not empty \n\
\t\t//set the retVal to the top of the list and pop\n\
\tif(!token_list.empty()){\t\n\
\t\tretVal = token_list.front();\n\
\t\ttoken_list.pop();\n\
\t}//if the the list is empty the Token is set to the default values NIL\n\
return retVal;\n\
};\n\
\n\
void Lexer::populate_list(ifstream &text){\n\
\t//add the start token to the token_list\n\
\ttoken_list.push(Token(token_type::start, \"\"));\n\
\t//generated::start\n\
"
	#define LUTHOR_CPP_P_2 "\t//generated::end\n\
\n\
\tstring * cur_values = new string[table_num];\n\
\tchar curChar;\n\
\t//the state index and the last state index \n\
\t\t//to be used in the following loops\n\
\tint state_index; int last_state_index;\n\
\t//until the file reaches the end\n\
\twhile(!text.eof()){\n\
\t\tcurChar = text.get();\n\
\t\t//for each state and corresponding state table\n\
\t\t\t//find the next state\n\
\t\tfor(int i = 0; i < table_num; i++){\n\
\t\t\t//get the current state index\n\
\t\t\tstate_index = table_states[i];\n\
\t\t\t//get the current state from the set of tables\n\
\t\t\tstate cur_state = tables[i][state_index];\n\
\t\t\t//set the next state given the current char and the state\n\
\t\t\ttable_states[i] = next_state(curChar, cur_state);\n\
\t\t\t//get the now updated state and check to see if is the end\n\
\t\t\tlast_state_index = state_index;\n\
\t\t\tstate_index = table_states[i];\n\
\n\
\t\t\t//if the current state is the start state\n\
\t\t\t\t//if a transition occured from a non-start to a start state\n\
\t\t\t\t\t//erase the current string value\n\
\t\t\t//otherwise transition to a non-start state occured, add curchar\n\
\t\t\tif(state_index == 0){ \n\
\t\t\t\tif(last_state_index != 0) cur_values[i].clear();\n\
\t\t\t}else cur_values[i] += curChar;\n\
\t\t\n\
\t\t\t//if a transition to the end state occurred\n\
\t\t\t\t//add a new token and reset the state\n\
\t\t\tif(state_index == last_states[i]){\n\
\t\t\t\ttoken_list.push(Token(table_types[i], cur_values[i]));\n\
\t\t\t\ttable_states[i] = 0;\n\
\t\t\t\tcur_values[i].clear();\n\
\t\t\t}\n\
\t\t}\n\
\t};\n\
//cap the token_list off with an 'end' type token\t\n\
token_list.push(Token(token_type::end, \"\"));\n\
};\n\
\n\
bool meet_condition(char curChar, char * condition);\n\
\n\
int Lexer::next_state(char cur_char, state cur_state){\n\
\tchar * cur_condition;\n\
\t//for each potential state, check to see if the char meets the conditions\n\
\tfor(int i = 0; i < cur_state.num_transitions; i++){\n\
\t\tcur_condition = cur_state.transitions[i].next_state_conditions;\n\
\t\t//if the condition is met return the corresponding next state index\n\
\t\tif(meet_condition(cur_char, cur_condition))\t\n\
\t\t\treturn cur_state.transitions[i].next_state_index;\n\
\t}\n\
//if no conditions were met reset to the start state\n\
return 0;\n\
};\n\
\n\
bool meet_condition(char curChar, char * condition){\n\
\t//this code does two things\n\
\t\t//if allowing only the characters mentioned\n\
\t\t\t//return true if the character matches any in the array \n\
\t\t//if allowing all characters except those mentioned\n\
\t\t\t//return false if the character matches any in the array\n\
\tbool retVal = (condition[1] == 0);\n\
\tfor(int i = 2; i < condition[0]; i++)\n\
\t\tif( (curChar == condition[i]) ) return retVal;\n\
//no characters were found return false/true.\t\n\
return !retVal;\n\
};\n\
"
#endif
