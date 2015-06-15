#ifndef LUTHOR_ARGS_H
#define LUTHOR_ARGS_H
	#include <string>
typedef struct {
	std::string input;
	std::string output;
	
} Program_Settings;

Program_Settings parse_args(int argc, char * argv[]);

#endif
