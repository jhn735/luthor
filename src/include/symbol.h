#ifndef LUTHOR_SYMBOL_H
#define LUTHOR_SYMBOL_H
	#include <string>
	#include <fstream>

namespace symbol_luthor{
typedef char32_t symbol;
//number of bytes contained within a symbol
const size_t symbol_size = 4;

typedef std::basic_string<symbol> symbol_string;

//assuming 1 byte UTF_8 or ascii
symbol char_to_symbol(char cur_char);

class symbol_stream{
  public:
	//different encoding types including endianess in UTF32
	enum encoding{ UTF_8, UTF_32BE, UTF_32LE};
	
	symbol_stream(std::fstream *f, encoding enc);
	bool eof();
	symbol next_symbol();

  private:
	std::fstream * file;
	encoding enc;
	int next_byte();
	symbol from_UTF8(std::fstream *file);
	symbol from_UTF32BE(std::fstream *file);
	symbol from_UTF32LE(std::fstream *file);

};
};


#endif
