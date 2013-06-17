#ifndef STR_H_1356528738_93
#define STR_H_1356528738_93
/**
 * File: str.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 21:32:18.932000
 * Written In: Peking University, beijing, China
 */

#include "bootstrap.h"
#include "range.h"

#include "algorithms.h"

class str {
public:
	typedef std::vector<str> vecstr;
	typedef std::string container;
	typedef container::iterator iterator;
	typedef container::const_iterator citerator;
	typedef container::reverse_iterator riterator;
	typedef container::const_reverse_iterator criterator;
	
private:
	container s;
	
public:
	inline iterator begin() { return s.begin(); }
	inline iterator end() { return s.end(); }
	inline riterator rbegin() { return s.rbegin(); }
	inline riterator rend() { return s.rend(); }
	
	inline citerator begin() const { return s.begin(); }
	inline citerator end() const { return s.end(); }
	inline criterator rbegin() const { return s.rbegin(); }
	inline criterator rend() const { return s.rend(); }
	
	//for size query
	inline const uint size() const { return s.size(); }
	inline const bool empty() const { return s.empty(); }
	inline const bool equals(const str& r) const { return s==r.s; }
	
	/**************************************************
	constructors:
	**************************************************/
	inline str() {}
	inline str(const char* cstr):s(cstr) {}	//construction from c-style string
	inline str(const string& cs):s(cs) {}	//construction from std string
	template<class Iterator>
	inline str(Iterator begin, Iterator end):s(begin, end) {}	//construction from two iterators
	str(const char& c);	// construction from char
	str(const uchar& c);	// construction from uchar
	str(const short& n);	// construction from short
	str(const ushort& n);	// construction from ushort
	str(const int& n);	// construction from int
	str(const uint& n);	// construction from uint
	str(const long& n);	// construction from long
	str(const ulong& n);	// construction from ulong
	str(const float& n);	// construction from float
	str(const double& n);	// construction from double
	str(const str& s):s(s.s) {}	//copy construction
	
	/**************************************************
	bool expressions:	== != > >= < <= ! 
	**************************************************/
	inline const bool operator==(const str& r) const { return s==r.s; }
	inline const bool operator<(const str& r) const { return s<r.s; }
	inline const bool operator>(const str& r) const { return s>r.s; }
	inline const bool operator!=(const str& r) const { return s!=r.s; }
	inline const bool operator<=(const str& r) const { return s<=r.s; }
	inline const bool operator>=(const str& r) const { return s>=r.s; }
	inline const bool operator!() const { return empty(); }
	operator string() { return s; }
	
	/**************************************************
	tostr
	output operator: <<
	**************************************************/
	inline friend ostream& operator <<(ostream& o, const str& s) { return o<<s.s; }
	inline friend istream& operator >>(istream& i, str& s) { return i>>s.s; }
	
	inline const string tostr() const { return s; }
	inline const char* tocstr() const { return s.c_str(); }
	const string repr() const;
	
	/**************************************************
	assign
	operator: =
	**************************************************/
	inline str& operator=(const str& r) {
		return assign(r);
	}
	inline str& assign(const str& r) {
		s=r.s;
		return *this;
	}
	
	/**************************************************
	operator: + += * *=
	**************************************************/
	inline str operator +(const str& r) {	//for connection
		return str(s+r.s);
	}
	inline str added(const str& r) { return (*this)+r; }
	// inline str operator +(const char* r) {	//for connection
		// return clone()+=r;
	// }
	inline str& operator +=(const str& r) {
		s+=r.s;
		return *this;
	}
	inline str& add(const str& r) { return (*this)+=r; }
	inline str& operator +=(const string& r) {
		s+=r;
		return *this;
	}
	// inline str& operator +=(const char* r) {
		// s+=r;
		// return *this;
	// }
	inline str operator *(int n) {	//for multiply
		return repeated(n);
	}
	inline str& operator *=(int n) {
		return repeat(n);
	}

	
	/**************************************************
	operator: [](int)
	operator: [](string)
	at
	**************************************************/
	inline char& operator[](int i) {	//for element visiting
		if (i<0) i+=s.size();
		return s[i];
	}
	inline const char& operator[](int i) const {
		if (i<0) i+=s.size();
		return s[i];
	}
	inline str operator [](const char* cstr) {
		return slice(range(cstr));
	}
	char& at(int i);	//for element visiting, much more safe

	/**************************************************
	slice: substr 
	operator: ()(pos)
	operator: ()(start, stop, step)
	**************************************************/
	//for substr getter
	str operator()(int pos) const;
	
	//for substr
	str operator()(int start, int stop, int step=1) const;
	
	//for slice
	inline str slice(const range& r) {
		return ::slice(s, r);
	}

	
	/*************************************************
	S.split([sep [,results]]) -> list of strings
		Return a list of the words in the string S, using sep as the
		delimiter string. If results is given, it will get all the 
		result list of strings. If sep is not specified, any
		whitespace string is a separator and empty strings are removed
		from the result.
	*************************************************/
	template<class Container>
	inline Container& split(const str& sep, Container& results) {	//faster version
		vector<string::iterator> o;
		::split(s, sep, o);
		for (uint i=0; i<o.size(); i+=2) results.insert(results.end(), typename Container::value_type(o[i], o[i+1]));
		return results;
	}
	
	const vecstr split(const str& sep);	//slower version
	vecstr split();
	
	/*************************************************
	S.join(sequence) -> str
		Return a string which is the concatenation of the strings in the
		sequence.  The separator between elements is S.
	*************************************************/
	template<class Container>
	inline str join(const Container& con) const {
		string ret;
		ret.reserve(1024);
		return ::join(s, con, ret);
	}
	
	/*************************************************
	S.find(sub [,start [,end]]) -> int
		Search from left to right.
		Return the lowest index in S where substring sub is found,
		such that sub is contained within s[start:end].  Optional
		arguments start and end are interpreted as in slice notation.
		Return -1 on failure.
	*************************************************/
	int find(const str& sub, int start=0, int end=0) const;
	
	/*************************************************
	S.rfind(sub [,start [,end]]) -> int
		Search from right to left.
		Return the highest index in S where substring sub is found,
		such that sub is contained within s[start:end].  Optional
		arguments start and end are interpreted as in slice notation.
		Return -1 on failure.
	*************************************************/
	int rfind(const str& sub, int start=0, int end=0) const;
	
	/*************************************************
	S.clone() -> new str
		Return a deep copy of string S, which is a clone
		of S.
	*************************************************/
	inline str clone() const { return s; }
	
	/*************************************************
	S.replace(old, new[, count]) -> S
		Return string S with all occurrences of substring old 
		replaced by new.  If the optional argument count is 
		given, only the first count occurrences are replaced.
	*************************************************/
	str& replace(const str& old, const str& new_, uint count=-1);
	
	/*************************************************
	S.replaced(old, new[, count]) -> new str
		Return a copy of string S with all occurrences 
		of substring old replaced by new.  If the optional 
		argument count is given, only the first count 
		occurrences are replaced.
	*************************************************/
	inline str replaced(const str& old, const str& new_, uint count=-1) { return clone().replace(old, new_, count); }
	
	/*************************************************
	S.count(sub[, start[, end]]) -> uint
		Return the number of non-overlapping occurrences of substring sub in
		string S[start:end].  Optional arguments start and end are interpreted
		as in slice notation.
	*************************************************/
	uint count(const str& sub, int start=0, int end=0);
	
	/*************************************************
	S.center(width[, fillchar]) -> string
		Return S centered in a string of length width. Padding is
		done using the specified fill character (default is a space)
	*************************************************/
	str center(uint width, char fillchar);
	
	/*************************************************
	S.startswith(prefix[, start[, end]]) -> bool
		Return True if S starts with the specified prefix, False otherwise.
		With optional start, test S beginning at that position.
		With optional end, stop comparing S at that position.
		prefix can also be a tuple of strings to try.
	*************************************************/
	bool startswith(const str& prefix, int start=0, int end=0) const;
	
	/*************************************************
	S.endswith(suffix[, start[, end]]) -> bool
		Return True if S ends with the specified suffix, False otherwise.
		With optional start, test S beginning at that position.
		With optional end, stop comparing S at that position.
		suffix can also be a tuple of strings to try.
	*************************************************/
	bool endswith(const str& prefix, int start=0, int end=0) const;
	
	/*************************************************
	S.expandtabs([tabsize]) -> string
		Return a copy of S where all tab characters are expanded using spaces.
		If tabsize is not given, a tab size of 8 characters is assumed.
	*************************************************/
	str expandtabs(uint tabsize=8);
	
	/*************************************************
	S.upper() -> S
	S.uppered() -> new string
		Return a copy of the string S converted to uppercase.
	*************************************************/
	str& upper();
	inline str uppered() { return clone().upper(); }
	
	/*************************************************
	S.lower() -> S
	S.lowered() -> new string
		Return a copy of the string S converted to lowercase.
	*************************************************/
	str& lower();
	inline str lowered() { return clone().lower(); }
	
	/*************************************************
	S.swapcase() -> S
	S.swapcased() -> new string
		Return a copy of the string S with uppercase characters
		converted to lowercase and vice versa.
	*************************************************/
	str& swapcase();
	inline str swapcased() { return clone().swapcase(); }
	
	/*************************************************
	S.reverse() -> S
	S.reversed() -> new string
		Return a copy of the string S with all chars
		reversed.
	*************************************************/
	str& reverse();
	str reversed();
	
	/*************************************************
	S.repeat(n) -> S
	S.repeated(n) -> new string
		Return a copy of the string S with itself repeated
		for n times. if n<0, the reversed S will be repeated.
	*************************************************/
	str& repeat(int n);
	inline str repeated(int n) { return clone().repeat(n); }
	
	/*************************************************
	S.sort() -> S
	S.sorted() -> new string
		Return a copy of the string S with all chars
		sorted.
	*************************************************/
	str& sort();
	inline str sorted() { return clone().sort(); }
	
	/*************************************************
	S.strip([chars]) -> S
	S.lstrip([chars]) -> S
	S.rstrip([chars]) -> S
	S.striped([chars]) -> string
	S.lstriped([chars]) -> string
	S.rstriped([chars]) -> string
		Return a copy of the string S with leading and trailing
		whitespace removed.
		If chars is given, remove characters in chars instead.
	*************************************************/
	str& strip(const str& chars=" \t\v\r\n\f");
	str& lstrip(const str& chars=" \t\v\r\n\f");
	str& rstrip(const str& chars=" \t\v\r\n\f");
	
	str striped(const str& chars=" \t\v\r\n\f");
	str lstriped(const str& chars=" \t\v\r\n\f");
	str rstriped(const str& chars=" \t\v\r\n\f");
	
	/**************************************************
	tohash:	x.tohash() <==> Return DWORD hash
	**************************************************/
	const uint tohash() const;
};

typedef vector<str> vecstr;

#endif /* STR_H_1356528738_93 */
