#include <fstream>
#include <string>
#include <cstdint>
enum encoding_type{
	ASCII, UTF_8, UTF_16, UTF_32
};
//holds the value of a character
	//using the class symbol allows for
	//character encoding agnosticism.
class Symbol{
	//assuming that largest character value is capped at 2^64
		uint64_t value;
	public:
		Symbol(unsigned char_size, char * character);
		bool operator==(Symbol l, Symbol r);
		bool operator!=(Symbol l, Symbol r);
};

class encoded_file{
	encoding_type enc_type;
	
	public:
	encoded_file(encoding_type type, std::string filename);

};
