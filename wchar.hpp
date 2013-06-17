#ifndef WCHAR_HPP_1342710163_79
#define WCHAR_HPP_1342710163_79
/**
 * File: wchar.hpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-07-19 23:02:43.788000
 * Written In: Peking University, beijing, China
 */

#include "includes.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <ctime>
#include <stdexcept>
#include <exception>
#include <string>
#include <locale>

using std::locale;
// using std::codecvt;
// using std::mbstate_t;

using std::string;
using std::wstring;

using std::wcin;
using std::wcout;

using std::wfstream;
using std::wifstream;
using std::wofstream;

typedef wchar_t wchar;
typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;

string wstringtostring(const wstring& input, const char* using_locale="zh_CN.UTF-8") {
	string current_locale=setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, using_locale);
	const wchar* src = input.c_str();
	size_t dst_len = 3 * input.size() + 1;
	char *dst = new char[dst_len];
	memset(dst, 0, dst_len);
	wcstombs(dst, src, dst_len);
	string output=dst;
	delete [] dst;
	setlocale(LC_ALL, current_locale.c_str());
	return output;
}

wstring stringtowstring(const string& input, const char* using_locale="zh_CN.UTF-8") {
	string current_locale=setlocale(LC_ALL, NULL);
	setlocale(LC_ALL, using_locale);
	const char* src = input.c_str();
	size_t dst_len = input.size() + 1;
	wchar *dst = new wchar[dst_len];
	wmemset(dst, 0, dst_len);
	mbstowcs(dst, src, dst_len);
	wstring output = dst;
	delete [] dst;
	setlocale(LC_ALL, current_locale.c_str());
	return output;
}

// the code below is modified from ustl, thanks for ustl
// -----------------------------------------------------------------------

// This file is part of the uSTL library, an STL implementation.
//
// Copyright (c) 2005 by Mike Sharov <msharov@users.sourceforge.net>
// This file is free software, distributed under the MIT License.
//
// This file contains stream iterators that read and write UTF-8 encoded
// characters. The encoding is defined as follows:
//
// U-00000000 - U-0000007F: 0xxxxxxx
// U-00000080 - U-000007FF: 110xxxxx 10xxxxxx
// U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
// U-00010000 - U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
// U-00200000 - U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
// U-04000000 - U-7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
// U-80000000 - U-FFFFFFFF: 11111110 100000xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx


//----------------------------------------------------------------------

inline size_t utf8_bytes(wchar v);
inline size_t utf8_bytes(const wchar* first, const wchar* last);
inline size_t utf8_seq_bytes(wchar c);

//----------------------------------------------------------------------

/// Returns the number of bytes required to UTF-8 encode \p v.
inline size_t utf8_bytes(wchar v) {
	if ((uint) v < 128)
		return (1);
	size_t n;
#if __i386__ || __x86_64__
	uint r = 0;
	asm ("bsr\t%2, %%eax\n\t"
	     "add\t$4, %0\n\t"
     "div\t%3":"=a"(n),"+d"(r):"r"(v),"c"(5));
#else
	static const uint c_Bounds[7] = { 0x0000007F, 0x000007FF, 0x0000FFFF, 0x001FFFFF, 0x03FFFFFF, 0x7FFFFFFF, 0xFFFFFFFF };
	for (n = 0; c_Bounds[n++] < uint(v); );
#endif
	return (n);
}

/// Measures the size of a wchar_t array in UTF-8 encoding.
inline size_t utf8_bytes(const wchar* first, const wchar* last) {
	size_t n = 0;
	for (; first<last; ++first)
		n += utf8_bytes(*first);
	return (n);
}

/// Returns the number of bytes in a UTF-8 sequence that starts with \p c.
inline size_t utf8_seq_bytes(wchar c)	// a wchar_t to keep c in a full register
{
	// Count the leading bits. Header bits are 1 * nBytes followed by a 0.
	//	0 - single byte character. Take 7 bits (0xFF >> 1)
	//	1 - error, in the middle of the character. Take 6 bits (0xFF >> 2)
	//	    so you will keep reading invalid entries until you hit the next character.
	//	>2 - multibyte character. Take remaining bits, and get the next bytes.
	// All errors are ignored, since the user can not correct them.
	//
	wchar mask = 0x80;
	size_t n = 0;
	for (; c & mask; ++n)
		mask >>= 1;
	return (n ? n : 1); // A sequence is always at least 1 byte.
}

//----------------------------------------------------------------------

/// \class utf8in_iterator utf8.h ustl.h
/// \ingroup IteratorAdaptors
///
/// \brief An iterator adaptor to character containers for reading UTF-8 encoded text.
///
/// For example, you can copy from ustl::string to ustl::vector<wchar_t> with
/// copy (utf8in (str.begin()), utf8in (str.end()), back_inserter(wvect));
/// There is no error handling; if the reading frame slips you'll get extra
/// characters, one for every misaligned byte. Although it is possible to skip
/// to the start of the next character, that would result in omitting the
/// misformatted character and the one after it, making it very difficult to
/// detect by the user. It is better to write some strange characters and let
/// the user know his file is corrupted. Another problem is overflow on bad
/// encodings (like a 0xFF on the end of a string). This is checked through
/// the end-of-string nul character, which will always be there as long as
/// you are using the string class.
///
template<typename Iterator>
class utf8in_iterator {
public:
	typedef typename iterator_traits<Iterator>::value_type		value_type;
	typedef typename iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename iterator_traits<Iterator>::pointer		pointer;
	typedef typename iterator_traits<Iterator>::reference		reference;
public:
	explicit utf8in_iterator(const Iterator& is): m_i(is), m_v(0) { read(); }
	utf8in_iterator(const utf8in_iterator& i)	: m_i(i.m_i), m_v(i.m_v) {}
	inline const utf8in_iterator& operator=(const utf8in_iterator& i) {
		if (this!=&i) {
			m_i = i.m_i;
			m_v = i.m_v;
		}
		return (*this);
	}
	inline Iterator base() const {
		return (m_i - (utf8_bytes(m_v) - 1));
	}
	/// Reads and returns the next value.
	inline wchar operator*() const {
		return (m_v);
	}
	inline utf8in_iterator& operator++() {
		++m_i;
		read();
		return (*this);
	}
	inline utf8in_iterator operator++(int) {
		utf8in_iterator old(*this);
		operator++();
		return (old);
	}
	inline utf8in_iterator& operator+=(size_t n) {
		while (n--) operator++();
		return (*this);
	}
	inline utf8in_iterator operator+(size_t n)	{
		utf8in_iterator v (*this);
		return (v += n);
	}
	inline bool operator==(const utf8in_iterator& i) const {
		return (m_i == i.m_i);
	}
	inline bool operator<(const utf8in_iterator& i) const {
		return (m_i < i.m_i);
	}
	
	/// Returns the distance in characters (as opposed to the distance in bytes).
	difference_type operator-(const utf8in_iterator& last) const
	{
		difference_type dist = 0;
		for (Iterator first (last.m_i); first < m_i; ++dist)
			first = advance(first, utf8_seq_bytes(*first));
		return (dist);
	}

private:
	/// Steps to the next character and updates current returnable value.
	void read() {
		const ulong c = *m_i;
		size_t n_bytes = utf8_seq_bytes(c);
		m_v = c & (0xFF >> n_bytes);	// First byte contains bits after the header.
		while (--n_bytes && *++m_i)	// Each subsequent byte has 6 bits.
			m_v = (m_v << 6) | (*m_i & 0x3F);
	}
private:
	Iterator m_i;
	wchar m_v;
};


//----------------------------------------------------------------------

/// \class utf8out_iterator utf8.h ustl.h
/// \ingroup IteratorAdaptors
///
/// \brief An iterator adaptor to character containers for writing UTF-8 encoded text.
///
template<typename Iterator>
class utf8out_iterator {
public:
	typedef typename iterator_traits<Iterator>::value_type		value_type;
	typedef typename iterator_traits<Iterator>::difference_type	difference_type;
	typedef typename iterator_traits<Iterator>::pointer		pointer;
	typedef typename iterator_traits<Iterator>::reference		reference;
public:
	explicit utf8out_iterator(const Iterator& i): m_i(i) {}
	utf8out_iterator(const utf8out_iterator& i): m_i(i.m_i) {}
	inline const Iterator& base(void) const { return (m_i); }
	/// Writes \p v into the stream.
	utf8out_iterator& operator=(wchar v) {
		const size_t n_bytes = utf8_bytes(v);
		if (n_bytes > 1) {
			// Write the bits 6 bits at a time, except for the first one,
			// which may be less than 6 bits.
			register wchar shift = n_bytes * 6;
			*m_i++ = ((v >> (shift -= 6)) & 0x3F) | (0xFF << (8 - n_bytes));
			while (shift)
				*m_i++ = ((v >> (shift -= 6)) & 0x3F) | 0x80;
		} else	// If only one byte, there is no header.
			*m_i++ = v;
		return (*this);
	}
	
	inline utf8out_iterator& operator* (void) {
		return (*this);
	}
	inline utf8out_iterator& operator++ (void) {
		return (*this);
	}
	inline utf8out_iterator operator++ (int) {
		return (*this);
	}
	inline bool operator== (const utf8out_iterator& i) const {
		return (m_i == i.m_i);
	}
	inline bool operator< (const utf8out_iterator& i) const {
		return (m_i < i.m_i);
	}
private:
	Iterator m_i;
};

//----------------------------------------------------------------------

/// Returns a UTF-8 adaptor writing to \p i. Useful in conjuction with back_insert_iterator.
template <typename Iterator>
inline utf8out_iterator<Iterator> utf8out (Iterator i) {
	return (utf8out_iterator<Iterator> (i));
}

/// Returns a UTF-8 adaptor reading from \p i.
template <typename Iterator>
inline utf8in_iterator<Iterator> utf8in (Iterator i) {
	return (utf8in_iterator<Iterator> (i));
}

// -----------------------------------------------------------------------

/** Enumerate several useful character sets
 *	see reference:
 *		http://www.iana.org/assignments/character-sets
 *		http://stdcxx.apache.org/doc/stdlibref/codecvt-byname.html#sec7
 */
enum Charset {
	CHARSET_ASCII,
	CHARSET_C,
	CHARSET_GB2312,
	CHARSET_GBK,
	CHARSET_GB18030,
	CHARSET_BIG5,
	CHARSET_UTF8
};

static const char* CharsetName[] = {
#if defined(OS_WIN32)
	/***************************************************
	 *	Reference:
	 *		http://msdn.microsoft.com/en-us/library/dd317756(VS.85).aspx
	 *
	 ****************************************************/
	"",		//	ASCII(1250)
	"C",		//	C(0)
	".20936",	//	GB2312
	".936",	//	GBK
	".54936",	//	GB18030
	".950",	//	BIG5
	".65001"	//	UTF8 (not supported by VC STL)
#else
	/***************************************************
	 *	Reference:
	 *		http://www.iana.org/assignments/character-sets
	 *		http://stdcxx.apache.org/doc/stdlibref/codecvt-byname.html
	 *		http://gcc.gnu.org/onlinedocs/libstdc++/manual/codecvt.html
	 ****************************************************/
	"",					//	ASCII
	"C",					//	C
	"zh_CN.GB2312",		//	GB2312
	"zh_CN.GBK",			//	GBK
	"zh_CN.GB18030",		//	GB18030
	"zh_TW.BIG5",			//	BIG5
	"zh_CN.UTF8"			//	UTF8
#endif
};

const locale make_locale(enum Charset charset)
{
	const char* name=CharsetName[charset];
	// cout<<"now in const locale make_locale(enum Charset charset)"<<endl;
	try {
#if defined(OS_WIN32)
		//TODO:
		if (charset != CHARSET_UTF8) {
			return locale(name);
		} else {
			return locale(locale::classic(), new utf8_codecvt_facet);
		}
#else
		return locale(name);
#endif
	} catch (std::runtime_error& e) {
		cout << name << " : " << e.what() << endl;
		throw e;
	}
}

// To enable the GBK locale in ubuntu:
// 		modify the /var/lib/locale/support.d/zh-hans
//		and add a new line as:
//			zh_CN.GBK GBK
//		then run:
//			sudo locale-gen
//		or:
//			sudo dpkg-reconfigure locales

const static locale locale_utf8=make_locale(CHARSET_UTF8);

#ifdef OS_WIN32
	const static locale locale_gbk=make_locale(CHARSET_GBK);
	#define locale_platform locale_gbk
#else
	#define locale_platform locale_utf8
#endif

/** Convert given wide string to narrow string by given locale object.
*  The function is used for converting from wide char string to multibyte string.
*	Notice: Visual C++ current cannot support utf-8 locale in STL. So, for alternative
*          way, user can use system-specified way to do the conversion.
*	see also: openclas::widen();
* @returns the converted narrow multibyte string.
*/
static std::string narrow(const std::wstring& str, const locale& loc=locale_platform) {
	const codecvt_t& cc = std::use_facet<codecvt_t>(loc);

	int buf_size = static_cast<int>(cc.max_length() * (str.length() + 1));
	char* buf=new char[buf_size];

	std::mbstate_t state = std::mbstate_t();
	const wchar_t* from_next = 0;
	char* to_next = 0;

	std::codecvt_base::result result = cc.out(state,
		str.c_str(), str.c_str() + str.length(), from_next,
		buf, buf + buf_size, to_next);

	if (result==std::codecvt_base::ok)
	{
		std::string narrow_string(buf, to_next);
		delete [] buf;
		return narrow_string;
	}else{
		// cout<<"error"<<endl;
		// return std::string(buf.get(), to_next);
		delete [] buf;
		return string();
	}
}

/** Convert given narrow string to wide string by given locale object.
*  The function is used for converting from multi-byte string to wide char string.
*	Notice: Visual C++ current cannot support utf-8 locale in STL. So, for alternative
*          way, user can use system-specified way to do the conversion.
*	see also: openclas::widen();
* @returns the converted wide string.
*/
static std::wstring widen(const std::string& str, const locale& loc=locale_platform) {
	const codecvt_t& cc = std::use_facet<codecvt_t>(loc);

	size_t buf_size = str.length() + 1;
	wchar_t* buf=new wchar_t[buf_size];

	std::mbstate_t state = std::mbstate_t();
	const char* from_next = 0;
	wchar_t* to_next = 0;

	std::codecvt_base::result result = cc.in(state,
		str.c_str(), str.c_str() + str.length(), from_next,
		buf, buf + buf_size, to_next);

	if (result == std::codecvt_base::ok)
	{
		std::wstring widen_string(buf, to_next);
		delete [] buf;
		return widen_string;
	}else{
		// cout<<"error"<<endl;
		delete [] buf;
		return std::wstring();
	}
}

	
#endif /* WCHAR_HPP_1342710163_79 */
