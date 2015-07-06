#include <string>
//symbol
typedef uint64_t symbol;
typedef int64_t int_type;
namespace std{
template <> struct char_traits<symbol>{
	static bool   eq(symbol s1, symbol s2){ return s1 == s2; };
	static bool   lt(symbol s1, symbol s2){ return s1 < s2;  };
	static size_t length(const symbol* s) { 
		int i = 0; size_t size = 0;
		while(s[i] != 0){ i++; size++;}
	return s[0];     
	};
	static void   assign(symbol& r, const symbol& c) noexcept{ r = c; };
	static symbol* assign(symbol* p, size_t n, symbol c){
		for(int i = 0; i < n; i++)
			assign(p[i], c);
	return p;
	};

	static int compare(const symbol* s1, const symbol* s2, size_t n){
		while(n-- > 0){
			if( lt(*s1, *s2) ) return -1;
			if( lt(*s2, *s1) ) return 1;
			s1++; s2++;
		};
	return 0;
	};
	static const symbol* find(const symbol* p, size_t n, const symbol& c){
		while(n-- > 0){
			if( eq(*p, c) ) return p;
			p++;
		};
	return NULL;
	};
	static symbol* move( symbol* dest, const symbol* src, size_t n){
		//make a temp array containing the substring
		symbol * temp = new symbol[n];
		copy(temp, src, n);
		//copy it over to the dest
		copy(dest, temp, n);
		//delete the temp array
		delete[] temp;
	};
	
	static symbol* copy(symbol* dest, const symbol* src, size_t n){
		symbol s;
		for(int i = 0; (i < n); i++){
			assign(s, src[i]);
			if(s == '\0') break;
			assign(dest[i], s);
		};
	
	};
	
	static constexpr int_type eof() noexcept{ return 0;};
	
	static constexpr int_type not_eof(int_type c) noexcept{
		return (c != eof())?c:eof();
	};
	
	static constexpr int_type to_int_type (symbol c) noexcept{
		return (int_type)c;
	};

	static constexpr bool eq_int_type( int_type x, int_type y){
		return x == y;
	};
		
	}//end char_traits
}//end std;
