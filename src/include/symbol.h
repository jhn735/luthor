#ifndef LUTHOR_SYMBOL_H
#define LUTHOR_SYMBOL_H
	#include <string>
	#include <fstream>
	#include <exception>
	#include <stdexcept>
namespace symbol_luthor{
typedef char32_t symbol;
//number of bytes contained within a symbol
const size_t SYMBOL_SIZE = 4;

//the number of bytes in a 32bit character
const size_t UTF32_SIZE = sizeof(char32_t);

//the maximum number of bytes in a UTF-8 character
const size_t UTF8_MAX_SIZE = 4;

typedef std::basic_string<symbol> symbol_string;

class symbol_stream{
  public:
	//different encoding types including endianess in UTF32
	enum encoding{ UTF_8, UTF_32BE, UTF_32LE};
	
	symbol_stream(std::fstream *f, encoding enc);
	bool eof();
	symbol next_symbol();

	std::runtime_error invalid_UTF8_character = std::runtime_error("Invalid UTF-8 character");
	std::runtime_error input_char_too_big =  std::runtime_error("The bit length of the input characters is too big to hold. Change the symbol type or change input type.");
  private:
	void symbol_size_valid(int num_bytes);
	std::fstream * file;
	encoding enc;
	int next_byte();
	symbol from_UTF8(std::fstream *file);
	symbol from_UTF32BE(std::fstream *file);
	symbol from_UTF32LE(std::fstream *file);

};
};


#endif
