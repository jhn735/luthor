#include <cstdarg>
//allocates space for a array of char arrays and returns the pointer
char ** chr(int num_strings, ...);
void chr_del(int num_strings, char ** chr);
