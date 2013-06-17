/**
 * File: str.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 21:32:21.148000
 * Written In: Peking University, beijing, China
 */

#include "str.h"

str::str(const char& c) {	// construction from char
	char buf[2];
	buf[0]=c;
	buf[1]=0;
	s=buf;
}
str::str(const uchar& c) {	// construction from uchar
	char buf[2];
	buf[0]=c;
	buf[1]=0;
	s=buf;
}
str::str(const short& n) {	// construction from short
	char buf[16];
	sprintf(buf, "%d", n);
	s=buf;
}
str::str(const ushort& n) {	// construction from ushort
	char buf[16];
	sprintf(buf, "%d", n);
	s=buf;
}
str::str(const int& n) {	// construction from int
	char buf[16];
	sprintf(buf, "%d", n);
	s=buf;
}
str::str(const uint& n) {	// construction from uint
	char buf[16];
	sprintf(buf, "%u", n);
	s=buf;
}
str::str(const long& n) {	// construction from long
	char buf[32];
	sprintf(buf, "%ld", n);
	s=buf;
}
str::str(const ulong& n) {	// construction from ulong
	char buf[32];
	sprintf(buf, fmtstr_ulong, n);
	s=buf;
}
str::str(const float& n) {	// construction from float
	char buf[32];
	sprintf(buf, "%f", n);
	s=buf;
}
str::str(const double& n) {	// construction from double
	char buf[32];
	sprintf(buf, "%g", n); 
	s=buf;
}
// inline str::str(const str& s):s(s.s) {}	//copy construction

/**************************************************
bool expressions:	== != > >= < <= ! 
**************************************************/
// inline const bool str::operator==(const str& r) const { return s==r.s; }
// inline const bool str::operator<(const str& r) const { return s<r.s; }
// inline const bool str::operator>(const str& r) const { return s>r.s; }
// inline const bool str::operator!=(const str& r) const { return s!=r.s; }
// inline const bool str::operator<=(const str& r) const { return s<=r.s; }
// inline const bool str::operator>=(const str& r) const { return s>=r.s; }
// inline const bool str::operator!() const { return empty(); }

/**************************************************
tostr
output operator: <<
**************************************************/
// inline ostream& operator <<(ostream& o, const str& s) {
	// return o<<'"'<<s.s<<'"';
	// return o<<s.s;
// }

// inline const string str::tostr() const { return s; }
// inline const char* str::tocstr() const { return s.c_str(); }
const string str::repr() const { 
	return string("\"")+clone()
		.replace("\\", "\\\\").replace("\t", "\\t")
		.replace("\v", "\\v").replace("\r", "\\r")
		.replace("\n", "\\n").tostr()+"\""; 
}
	
/**************************************************
assign
operator: =
**************************************************/
// inline str& str::operator=(const str& r) {
	// return assign(r);
// }
// inline str& str::assign(const str& r) {
	// s=r.s;
	// return *this;
// }

/**************************************************
operator: + += * *=
**************************************************/
// inline str str::operator +(const str& r) {	//for connection
	// return str(s+r.s);
// }
// inline str str::added(const str& r) { return (*this)+r; }
// inline str str::operator +(const char* r) {	//for connection
	// return clone()+=r;
// }
// inline str& str::operator +=(const str& r) {
	// s+=r.s;
	// return *this;
// }
// inline str& str::add(const str& r) { return (*this)+=r; }
// inline str& str::operator +=(const string& r) {
	// s+=r;
	// return *this;
// }
// inline str& str::operator +=(const char* r) {
	// s+=r;
	// return *this;
// }
// inline str str::operator *(int n) {	//for multiply
	// return repeated(n);
// }
// inline str& str::operator *=(int n) {
	// return repeat(n);
// }

/**************************************************
operator: [](int)
operator: [](string)
at
**************************************************/
// inline char& str::operator[](int i) {	//for element visiting
	// if (i<0) i+=s.size();
	// return s[i];
// }
// inline const char& str::operator[](int i) const {
	// if (i<0) i+=s.size();
	// return s[i];
// }
// inline str str::operator [](const char* cstr) {
	// return str::slice(range(cstr));
// }
char& str::at(int i) {	//for element visiting, much more safe
	uint len=s.size();
	assert(len>0);
	while(i<0) i+=len;
	while(i>=static_cast<int>(len)) i-=len;
	return s.at(i);
}

/**************************************************
slice: substr 
operator: ()(pos)
operator: ()(start, stop, step)
**************************************************/
//for substr getter
str str::operator()(int pos) const {
	uint l=size();		
	if (pos<0) pos+=l;
	assert(pos>=0 AND pos<static_cast<int>(l));
	return s.substr(pos);
}

//for substr
str str::operator()(int start, int stop, int step) const {
	if (step==0) return "";
	uint l=size();
	if (start<0) start+=l;
	assert(start>=0 AND start<static_cast<int>(l));
	if (stop<0) stop+=l;
	if (step>0) {
		assert(stop>=0 AND stop<=static_cast<int>(l));
		int sl=stop-start;
		if (sl<=0) return "";
		if (step==1) return s.substr(start, sl);
		string ret;
		ret.reserve(sl);
		for (uint i=start; static_cast<int>(i)<stop; i+=step) ret.push_back(s[i]);
		return ret;
	} else {
		assert(stop>=-1 AND stop<static_cast<int>(l));
		int sl=start-stop;
		if (sl<=0) return "";
		if (step==-1) return string(s.rbegin()+start, s.rbegin()+(start+sl));
		string ret;
		ret.reserve(sl);
		for (uint i=start; static_cast<int>(i)>stop; i+=step) ret.push_back(s[i]);
		return ret;
	}
}

//for slice
// inline str str::slice(const range& r) {
	// return ::slice(s, r);
// }

/*************************************************
S.split([sep [,results]]) -> list of strings
	Return a list of the words in the string S, using sep as the
	delimiter string. If results is given, it will get all the 
	result list of strings. If sep is not specified, any
	whitespace string is a separator and empty strings are removed
	from the result.
*************************************************/
// template<class Container>
// inline Container& split(const str& sep, Container& results) {	//faster version
	// vector<string::iterator> o;
	// ::split(s, sep, o);
	// for (uint i=0; i<o.size(); i+=2) results.insert(results.end(), typename Container::value_type(o[i], o[i+1]));
	// return results;
// }

const vecstr str::split(const str& sep) {	//slower version
	vecstr vs;
	vs.reserve(20);
	return this->split(sep, vs);
}

vecstr str::split() {
	vecstr vs;
	vs.reserve(20);
	//TODO
	return striped().split(" ", vs);
}

/*************************************************
S.join(sequence) -> str
	Return a string which is the concatenation of the strings in the
	sequence.  The separator between elements is S.
*************************************************/
// template<class Container>
// inline str join(const Container& con) const {
	// string ret;
	// ret.reserve(1024);
	// return ::join(s, con, ret);
// }

/*************************************************
S.find(sub [,start [,end]]) -> int
	Search from left to right.
	Return the lowest index in S where substring sub is found,
	such that sub is contained within s[start:end].  Optional
	arguments start and end are interpreted as in slice notation.
	Return -1 on failure.
*************************************************/
int str::find(const str& sub, int start, int end) const {
	citerator a=(start<0?s.end():s.begin())+start, b=(end<=0?s.end():s.begin())+end;
	if (a>=b) return -1;
	citerator c=std::search(a, b, sub.begin(), sub.end());
	return (c==b)?-1:c-a;
}

/*************************************************
S.rfind(sub [,start [,end]]) -> int
	Search from right to left.
	Return the highest index in S where substring sub is found,
	such that sub is contained within s[start:end].  Optional
	arguments start and end are interpreted as in slice notation.
	Return -1 on failure.
*************************************************/
int str::rfind(const str& sub, int start, int end) const {
	uint l=size();
	if (start<0) start+=l;
	if (end<=0) end+=l;
	start=l-start;
	end=l-end;
	assert(start>0);
	assert(end>=0);
	criterator a=s.rbegin()+end, b=s.rbegin()+start;
	if (a>=b) return -1;
	criterator c=std::search(a, b, sub.rbegin(), sub.rend());
	return (c==b)?-1:(b-c)-sub.size();
}

/*************************************************
S.clone() -> new str
	Return a deep copy of string S, which is a clone
	of S.
*************************************************/
// inline str str::clone() const {
	// return s;
// }

/*************************************************
S.replace(old, new[, count]) -> S
	Return string S with all occurrences of substring old 
	replaced by new.  If the optional argument count is 
	given, only the first count occurrences are replaced.
*************************************************/
str& str::replace(const str& old, const str& new_, uint count) {
	uint start=0, olen=old.size(), nlen=new_.size();
	while(count==static_cast<uint>(-1) OR count-->static_cast<uint>(0)) {
		start=s.find(old.s, start);
		if (start==string::npos) break;
		s.replace(start, olen, new_.s);
		start+=nlen;
	}
	return *this;
}

/*************************************************
S.replaced(old, new[, count]) -> new str
	Return a copy of string S with all occurrences 
	of substring old replaced by new.  If the optional 
	argument count is given, only the first count 
	occurrences are replaced.
*************************************************/
// inline str str::replaced(const str& old, const str& new_, uint count) {
	// return clone().replace(old, new_, count);
// }

/*************************************************
S.count(sub[, start[, end]]) -> uint
	Return the number of non-overlapping occurrences of substring sub in
	string S[start:end].  Optional arguments start and end are interpreted
	as in slice notation.
*************************************************/
uint str::count(const str& sub, int start, int end) {
	return ::count((start<0?s.end():s.begin())+start, (end<=0?s.end():s.begin())+end, sub.begin(), sub.end());
}

/*************************************************
S.center(width[, fillchar]) -> string
	Return S centered in a string of length width. Padding is
	done using the specified fill character (default is a space)
*************************************************/
str str::center(uint width, char fillchar) {
	string ret(width, fillchar);
	uint l=size();
	if (width>=l) {
		int r=(width-l)/2;
		std::copy(s.begin(), s.end(), ret.begin()+r);
	} else {
		int r=(l-width)/2;
		std::copy(s.begin()+r, s.begin()+(width+r), ret.begin());
	}
	return ret;
}

/*************************************************
S.startswith(prefix[, start[, end]]) -> bool
	Return True if S starts with the specified prefix, False otherwise.
	With optional start, test S beginning at that position.
	With optional end, stop comparing S at that position.
	prefix can also be a tuple of strings to try.
*************************************************/
bool str::startswith(const str& prefix, int start, int end) const {
	return ::startswith((start<0?s.end():s.begin())+start, (end<=0?s.end():s.begin())+end, prefix.begin(), prefix.end());
}

/*************************************************
S.endswith(suffix[, start[, end]]) -> bool
	Return True if S ends with the specified suffix, False otherwise.
	With optional start, test S beginning at that position.
	With optional end, stop comparing S at that position.
	suffix can also be a tuple of strings to try.
*************************************************/
bool str::endswith(const str& prefix, int start, int end) const {
	return ::endswith((start<0?s.end():s.begin())+start, (end<=0?s.end():s.begin())+end, prefix.begin(), prefix.end());
}

/*************************************************
S.expandtabs([tabsize]) -> string
	Return a copy of S where all tab characters are expanded using spaces.
	If tabsize is not given, a tab size of 8 characters is assumed.
*************************************************/
str str::expandtabs(uint tabsize) {
	return replaced("\t", str(" ").repeated(tabsize));
}

/*************************************************
S.upper() -> S
S.uppered() -> new string
	Return a copy of the string S converted to uppercase.
*************************************************/
str& str::upper() {
	for (uint l=size(), i=0; i<l; ++i) {
		char& c=s[i];
		if (c>='a' AND c<='z') c+='A'-'a';
	}
	return *this;
}

// inline str str::uppered() {
	// return clone().upper();
// }

/*************************************************
S.lower() -> S
S.lowered() -> new string
	Return a copy of the string S converted to lowercase.
*************************************************/
str& str::lower() {
	for (uint l=size(), i=0; i<l; ++i) {
		char& c=s[i];
		if (c>='A' AND c<='Z') c+='a'-'A';
	}
	return *this;
}

// inline str str::lowered() {
	// return clone().lower();
// }

/*************************************************
S.swapcase() -> S
S.swapcased() -> new string
	Return a copy of the string S with uppercase characters
	converted to lowercase and vice versa.
*************************************************/
str& str::swapcase() {
	for (uint l=size(), i=0; i<l; ++i) {
		char& c=s[i];
		if (c>='a' AND c<='z') c+='A'-'a';
		else if (c>='A' AND c<='Z') c+='a'-'A';
	}
	return *this;
}

// inline str str::swapcased() {
	// return clone().swapcase();
// }

/*************************************************
S.reverse() -> S
S.reversed() -> new string
	Return a copy of the string S with all chars
	reversed.
*************************************************/
str& str::reverse() {
	std::reverse(s.begin(), s.end());
	return *this;
}

str str::reversed() {
	return string(s.rbegin(), s.rend());
}

/*************************************************
S.repeat(n) -> S
S.repeated(n) -> new string
	Return a copy of the string S with itself repeated
	for n times. if n<0, the reversed S will be repeated.
*************************************************/
str& str::repeat(int n) {
	str& me=*this;
	uint l=size();
	if (l==0) return me;
	if (n==0) {
		s.clear();
		return me;
	}
	else if (n<0) {
		me.reverse();
		n=-n;
	}
	for (uint i=1; static_cast<int>(i)<n; ++i) s.append(s.begin(), s.begin()+l);
	return me;
}

// inline str str::repeated(int n) {
	// return clone().repeat(n);
// }

/*************************************************
S.sort() -> S
S.sorted() -> new string
	Return a copy of the string S with all chars
	sorted.
*************************************************/
str& str::sort() {
	std::sort(s.begin(), s.end());
	return *this;
}

// inline str str::sorted() {
	// return clone().sort();
// }

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
str& str::strip(const str& chars) {
	return rstrip(chars).lstrip(chars);
}

str& str::lstrip(const str& chars) {
	s.erase(0, s.find_first_not_of(chars.s));
	return *this;
}

str& str::rstrip(const str& chars) {
	uint i=s.find_last_not_of(chars.s);
	if (i==s.npos) return *this;
	s.erase(i+1);
	return *this;
}

str str::striped(const str& chars) {
	return clone().strip(chars);
}

str str::lstriped(const str& chars) {
	return clone().lstrip(chars);
}

str str::rstriped(const str& chars) {
	return clone().rstrip(chars);
}

/**************************************************
tohash:	x.tohash() <==> Return DWORD hash
**************************************************/
const uint str::tohash() const {
	uint h=0, i=s.size();
	while(i>0) h=107*h+s[--i];
	return h;
}

// TODO 

/**************************************************
upper:	S.upper() -> string

Return a copy of the string S converted to uppercase.
**************************************************/



/**************************************************
zfill
S.zfill(width) -> string

Pad a numeric string S with zeros on the left, to fill a field
of the specified width.  The string S is never truncated.
**************************************************/

/*************************************************
<built-in method isalnum of str object at 0x0159C050>

S.isalnum() -> bool

Return True if all characters in S are alphanumeric
and there is at least one character in S, False otherwise.
*************************************************/



/*************************************************
<built-in method isalpha of str object at 0x0159C050>

S.isalpha() -> bool

Return True if all characters in S are alphabetic
and there is at least one character in S, False otherwise.
*************************************************/



/*************************************************
<built-in method isdigit of str object at 0x0159C050>

S.isdigit() -> bool

Return True if all characters in S are digits
and there is at least one character in S, False otherwise.
*************************************************/



/*************************************************
<built-in method islower of str object at 0x0159C050>

S.islower() -> bool

Return True if all cased characters in S are lowercase and there is
at least one cased character in S, False otherwise.
*************************************************/



/*************************************************
<built-in method isspace of str object at 0x0159C050>

S.isspace() -> bool

Return True if all characters in S are whitespace
and there is at least one character in S, False otherwise.
*************************************************/



/*************************************************
<built-in method isupper of str object at 0x0159C050>

S.isupper() -> bool

Return True if all cased characters in S are uppercase and there is
at least one cased character in S, False otherwise.
*************************************************/



/*************************************************
<built-in method partition of str object at 0x0159C050>

S.partition(sep) -> (head, sep, tail)

Searches for the separator sep in S, and returns the part before it,
the separator itself, and the part after it.  If the separator is not
found, returns S and two empty strings.
*************************************************/



/*************************************************
<built-in method ljust of str object at 0x0159C050>

S.ljust(width[, fillchar]) -> string

Return S left justified in a string of length width. Padding is
done using the specified fill character (default is a space).
*************************************************/



/*************************************************
<built-in method rjust of str object at 0x0159C050>

S.rjust(width[, fillchar]) -> string

Return S right justified in a string of length width. Padding is
done using the specified fill character (default is a space)
*************************************************/



/*************************************************
<built-in method splitlines of str object at 0x0159C050>

S.splitlines([keepends]) -> list of strings

Return a list of the lines in S, breaking at line boundaries.
Line breaks are not included in the resulting list unless keepends
is given and true.
*************************************************/



/*************************************************
<built-in method translate of str object at 0x0159C050>

S.translate(table [,deletechars]) -> string

Return a copy of the string S, where all characters occurring
in the optional argument deletechars are removed, and the
remaining characters have been mapped through the given
translation table, which must be a string of length 256.
*************************************************/



/*************************************************
<built-in method zfill of str object at 0x0159C050>

S.zfill(width) -> string

Pad a numeric string S with zeros on the left, to fill a field
of the specified width.  The string S is never truncated.
*************************************************/


	
	
	
/**************************************************
__add__:	x.__add__(y) <==> x+y
**************************************************/



/**************************************************
__class__:	type(object) -> the object's type
type(name, bases, dict) -> a new type
**************************************************/



/**************************************************
__contains__:	x.__contains__(y) <==> y in x
**************************************************/



/**************************************************
__delattr__:	x.__delattr__('name') <==> del x.name
**************************************************/



/**************************************************
__doc__:	str(object) -> string

Return a nice string representation of the object.
If the argument is a string, the return value is the same object.
**************************************************/



/**************************************************
__eq__:	x.__eq__(y) <==> x==y
**************************************************/



/**************************************************
__format__:	S.__format__(format_spec) -> unicode


**************************************************/



/**************************************************
__ge__:	x.__ge__(y) <==> x>=y
**************************************************/



/**************************************************
__getattribute__:	x.__getattribute__('name') <==> x.name
**************************************************/



/**************************************************
__getitem__:	x.__getitem__(y) <==> x[y]
**************************************************/



/**************************************************
__getnewargs__:	None
**************************************************/



/**************************************************
__getslice__:	x.__getslice__(i, j) <==> x[i:j]
	       
	       Use of negative indices is not supported.
**************************************************/



/**************************************************
__gt__:	x.__gt__(y) <==> x>y
**************************************************/



/**************************************************
__hash__:	x.__hash__() <==> hash(x)
**************************************************/



/**************************************************
__init__:	x.__init__(...) initializes x; see x.__class__.__doc__ for signature
**************************************************/



/**************************************************
__le__:	x.__le__(y) <==> x<=y
**************************************************/



/**************************************************
__len__:	x.__len__() <==> len(x)
**************************************************/



/**************************************************
__lt__:	x.__lt__(y) <==> x<y
**************************************************/



/**************************************************
__mod__:	x.__mod__(y) <==> x%y
**************************************************/



/**************************************************
__mul__:	x.__mul__(n) <==> x*n
**************************************************/



/**************************************************
__ne__:	x.__ne__(y) <==> x!=y
**************************************************/



/**************************************************
__new__:	T.__new__(S, ...) -> a new object with type S, a subtype of T
**************************************************/



/**************************************************
__reduce__:	helper for pickle
**************************************************/



/**************************************************
__reduce_ex__:	helper for pickle
**************************************************/



/**************************************************
__repr__:	x.__repr__() <==> repr(x)
**************************************************/



/**************************************************
__rmod__:	x.__rmod__(y) <==> y%x
**************************************************/



/**************************************************
__rmul__:	x.__rmul__(n) <==> n*x
**************************************************/



/**************************************************
__setattr__:	x.__setattr__('name', value) <==> x.name = value
**************************************************/



/**************************************************
__sizeof__:	S.__sizeof__() -> size of S in memory, in bytes
**************************************************/



/**************************************************
__str__:	x.__str__() <==> str(x)
**************************************************/



/**************************************************
__subclasshook__:	Abstract classes can override this to customize issubclass().

This is invoked early on by abc.ABCMeta.__subclasscheck__().
It should return True, False or NotImplemented.  If it returns
NotImplemented, the normal algorithm is used.  Otherwise, it
overrides the normal algorithm (and the outcome is cached).

**************************************************/



/**************************************************
_formatter_field_name_split:	None
**************************************************/



/**************************************************
_formatter_parser:	None
**************************************************/



/**************************************************
capitalize:	S.capitalize() -> string

Return a copy of the string S with only its first character
capitalized.
**************************************************/



/**************************************************
center:	S.center(width[, fillchar]) -> string

Return S centered in a string of length width. Padding is
done using the specified fill character (default is a space)
**************************************************/



/**************************************************
count:	S.count(sub[, start[, end]]) -> int

Return the number of non-overlapping occurrences of substring sub in
string S[start:end].  Optional arguments start and end are interpreted
as in slice notation.
**************************************************/



/**************************************************
decode:	S.decode([encoding[,errors]]) -> object

Decodes S using the codec registered for encoding. encoding defaults
to the default encoding. errors may be given to set a different error
handling scheme. Default is 'strict' meaning that encoding errors raise
a UnicodeDecodeError. Other possible values are 'ignore' and 'replace'
as well as any other name registerd with codecs.register_error that is
able to handle UnicodeDecodeErrors.
**************************************************/



/**************************************************
encode:	S.encode([encoding[,errors]]) -> object

Encodes S using the codec registered for encoding. encoding defaults
to the default encoding. errors may be given to set a different error
handling scheme. Default is 'strict' meaning that encoding errors raise
a UnicodeEncodeError. Other possible values are 'ignore', 'replace' and
'xmlcharrefreplace' as well as any other name registered with
codecs.register_error that is able to handle UnicodeEncodeErrors.
**************************************************/



/**************************************************
endswith:	S.endswith(suffix[, start[, end]]) -> bool

Return True if S ends with the specified suffix, False otherwise.
With optional start, test S beginning at that position.
With optional end, stop comparing S at that position.
suffix can also be a tuple of strings to try.
**************************************************/



/**************************************************
expandtabs:	S.expandtabs([tabsize]) -> string

Return a copy of S where all tab characters are expanded using spaces.
If tabsize is not given, a tab size of 8 characters is assumed.
**************************************************/



/**************************************************
find:	S.find(sub [,start [,end]]) -> int

Return the lowest index in S where substring sub is found,
such that sub is contained within s[start:end].  Optional
arguments start and end are interpreted as in slice notation.

Return -1 on failure.
**************************************************/



/**************************************************
format:	S.format(*args, **kwargs) -> unicode


**************************************************/



/**************************************************
index:	S.index(sub [,start [,end]]) -> int

Like S.find() but raise ValueError when the substring is not found.
**************************************************/



/**************************************************
isalnum:	S.isalnum() -> bool

Return True if all characters in S are alphanumeric
and there is at least one character in S, False otherwise.
**************************************************/



/**************************************************
isalpha:	S.isalpha() -> bool

Return True if all characters in S are alphabetic
and there is at least one character in S, False otherwise.
**************************************************/



/**************************************************
isdigit:	S.isdigit() -> bool

Return True if all characters in S are digits
and there is at least one character in S, False otherwise.
**************************************************/



/**************************************************
islower:	S.islower() -> bool

Return True if all cased characters in S are lowercase and there is
at least one cased character in S, False otherwise.
**************************************************/



/**************************************************
isspace:	S.isspace() -> bool

Return True if all characters in S are whitespace
and there is at least one character in S, False otherwise.
**************************************************/



/**************************************************
istitle:	S.istitle() -> bool

Return True if S is a titlecased string and there is at least one
character in S, i.e. uppercase characters may only follow uncased
characters and lowercase characters only cased ones. Return False
otherwise.
**************************************************/



/**************************************************
isupper:	S.isupper() -> bool

Return True if all cased characters in S are uppercase and there is
at least one cased character in S, False otherwise.
**************************************************/



/**************************************************
join:	S.join(sequence) -> string

Return a string which is the concatenation of the strings in the
sequence.  The separator between elements is S.
**************************************************/



/**************************************************
ljust:	S.ljust(width[, fillchar]) -> string

Return S left justified in a string of length width. Padding is
done using the specified fill character (default is a space).
**************************************************/



/**************************************************
lower:	S.lower() -> string

Return a copy of the string S converted to lowercase.
**************************************************/



/**************************************************
lstrip:	S.lstrip([chars]) -> string or unicode

Return a copy of the string S with leading whitespace removed.
If chars is given and not None, remove characters in chars instead.
If chars is unicode, S will be converted to unicode before stripping
**************************************************/



/**************************************************
partition:	S.partition(sep) -> (head, sep, tail)

Searches for the separator sep in S, and returns the part before it,
the separator itself, and the part after it.  If the separator is not
found, returns S and two empty strings.
**************************************************/



/**************************************************
replace:	S.replace (old, new[, count]) -> string

Return a copy of string S with all occurrences of substring
old replaced by new.  If the optional argument count is
given, only the first count occurrences are replaced.
**************************************************/



/**************************************************
rfind:	S.rfind(sub [,start [,end]]) -> int

Return the highest index in S where substring sub is found,
such that sub is contained within s[start:end].  Optional
arguments start and end are interpreted as in slice notation.

Return -1 on failure.
**************************************************/



/**************************************************
rindex:	S.rindex(sub [,start [,end]]) -> int

Like S.rfind() but raise ValueError when the substring is not found.
**************************************************/



/**************************************************
rjust:	S.rjust(width[, fillchar]) -> string

Return S right justified in a string of length width. Padding is
done using the specified fill character (default is a space)
**************************************************/



/**************************************************
rpartition:	S.rpartition(sep) -> (tail, sep, head)

Searches for the separator sep in S, starting at the end of S, and returns
the part before it, the separator itself, and the part after it.  If the
separator is not found, returns two empty strings and S.
**************************************************/



/**************************************************
rsplit:	S.rsplit([sep [,maxsplit]]) -> list of strings

Return a list of the words in the string S, using sep as the
delimiter string, starting at the end of the string and working
to the front.  If maxsplit is given, at most maxsplit splits are
done. If sep is not specified or is None, any whitespace string
is a separator.
**************************************************/



/**************************************************
rstrip:	S.rstrip([chars]) -> string or unicode

Return a copy of the string S with trailing whitespace removed.
If chars is given and not None, remove characters in chars instead.
If chars is unicode, S will be converted to unicode before stripping
**************************************************/



/**************************************************
split:	S.split([sep [,maxsplit]]) -> list of strings

Return a list of the words in the string S, using sep as the
delimiter string.  If maxsplit is given, at most maxsplit
splits are done. If sep is not specified or is None, any
whitespace string is a separator and empty strings are removed
from the result.
**************************************************/



/**************************************************
splitlines:	S.splitlines([keepends]) -> list of strings

Return a list of the lines in S, breaking at line boundaries.
Line breaks are not included in the resulting list unless keepends
is given and true.
**************************************************/



/**************************************************
startswith:	S.startswith(prefix[, start[, end]]) -> bool

Return True if S starts with the specified prefix, False otherwise.
With optional start, test S beginning at that position.
With optional end, stop comparing S at that position.
prefix can also be a tuple of strings to try.
**************************************************/



/**************************************************
strip:	S.strip([chars]) -> string or unicode

Return a copy of the string S with leading and trailing
whitespace removed.
If chars is given and not None, remove characters in chars instead.
If chars is unicode, S will be converted to unicode before stripping
**************************************************/



/**************************************************
swapcase:	S.swapcase() -> string

Return a copy of the string S with uppercase characters
converted to lowercase and vice versa.
**************************************************/



/**************************************************
title:	S.title() -> string

Return a titlecased version of S, i.e. words start with uppercase
characters, all remaining cased characters have lowercase.
**************************************************/



/**************************************************
translate:	S.translate(table [,deletechars]) -> string

Return a copy of the string S, where all characters occurring
in the optional argument deletechars are removed, and the
remaining characters have been mapped through the given
translation table, which must be a string of length 256.
**************************************************/



/**************************************************
upper:	S.upper() -> string

Return a copy of the string S converted to uppercase.
**************************************************/



/**************************************************
zfill:	S.zfill(width) -> string

Pad a numeric string S with zeros on the left, to fill a field
of the specified width.  The string S is never truncated.
**************************************************/
