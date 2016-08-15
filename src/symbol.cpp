#include "symbol.h"
using namespace symbol_luthor;

/*****Symbol_stream******/
symbol_stream::symbol_stream(std::fstream * f, encoding enc){
  this->file = f; this->enc = enc;
	switch(enc){
		case UTF_8: symbol_size_valid(UTF8_MAX_SIZE); break;
		case UTF_32BE: //fall through to UTF32LE: same code for both
		case UTF_32LE: symbol_size_valid(UTF32_SIZE); break;
		
	}
};

symbol symbol_stream::from_UTF8(std::fstream *file){
symbol retVal = 0;
  //work on the first byte get the total number of bytes
  char cur_char = file->get();
  int byte_count = 1;
	//while there is a bit with value of 1 at the end
    //increment the byte count and shift the character left by 1 bit
  while( (cur_char & 0x80) != 0){
   byte_count++;
  cur_char = cur_char << 1;
  };
  
  //shift the bits in the character back the bits at the top should be 0s now
		//don't forget that there may not have even been a shift in the first place
  cur_char >> (byte_count - 1);

	//put the value of the current char into the returned symbol
  retVal = retVal | cur_char;
  for(int i = 1; i < byte_count; i++){
    cur_char = file->get();

		//if the byte isn't a continuation
	  	//report error
		//otherwise shift the return value by 6 bits and add in the cur_char
		if( (cur_char & 0x80) == 0)
      throw invalid_UTF8_character;
		else{
	  	retVal << 6;
	  	retVal = retVal | (cur_char & 0x3F);
		}
  };
return retVal;  
};

/** Gets the next symbol from the filestream. Assumes the bit order is Big endian.
* @param file  the file from which the next character will be taken.
* @return the next UTF-32 character in the file in big endian. 
*/
symbol symbol_stream::from_UTF32BE(std::fstream *file){
  symbol retVal = 0;
  char sym[UTF32_SIZE]; file->get(sym, UTF32_SIZE);
  //starting from first to last pump the value into the symbol.
  for(int i = 0; i < SYMBOL_SIZE; i++)
	  retVal = (retVal|sym[i]) << 8;
return retVal;
};

/** Get the next symbol from the filestream. Assumes the bit order is Little endian.
* @param file  the file from which the next character will be taken.
* @return the next UTF-32 character in the file in little endian. 
*/
symbol symbol_stream::from_UTF32LE(std::fstream *file){
  symbol retVal = 0;
	//starting from the last to the first pump the value into the symbol
  char sym[UTF32_SIZE]; file->get(sym, UTF32_SIZE);
  for(int i = SYMBOL_SIZE; i >= 0; i--)
 	  retVal = (retVal|sym[i]) << 8;
return retVal;
};

/** Checks if the file has ended.
* @return true iff the end of the file has been reached
*/
bool symbol_stream::eof(){ return file->eof();}

/** Checks the number of bytes given with the size of the type symbol. 
 * Throws exception if wrong type.
 * @Param num_bytes the number of bytes of the input characters
 */
void symbol_stream::symbol_size_valid(int num_bytes){
	if(SYMBOL_SIZE < num_bytes)
    throw input_char_too_big;

}

/**
* @return The next symbol in the stream using the internally set encoding.
*/
symbol symbol_stream::next_symbol(){ 
  switch(this->enc){
	case UTF_8: return from_UTF8(this->file);
	case UTF_32BE: return from_UTF32BE(this->file);
	case UTF_32LE: return from_UTF32LE(this->file);
	
  }
}

