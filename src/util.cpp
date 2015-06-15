#include "utils.h"
#include <cstdarg>

//allocates space for a array of char arrays with the values of arguments
	//and returns the pointer
char ** chr(int num_strings, ...){
	va_list args;
	va_start(args, num_strings);
	//initialize the array of char*
	char ** retVal = new char*[num_strings];

	//for each of the strings as arguments 
		//set the value of the strings
		//assuming the strings are pascal strings
	for(int i = 0; i < num_strings; i++){
		char * n = va_args(args, char *);
		retVal[i] = new char[ (int)n[0] ];
		//copy the string into the retval
		for(int j = 0; j < (int)n[0]; j++)
			retVal[i][j] = n[j];
	};
		
};

void chr_del(int num_strings, char ** &chr){
	//delete all the strings in the 
	for(int i = 0; i < num_strings; i++)
		delete chr[i];
	//delete the array of arrays
	delete chr;
};
