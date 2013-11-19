/**
 * File: codecvt_in_c++0x.cpp
 * Description:
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 *
 * Date: 2012-06-25 14:42:57.630000
 * Written In: Peking University, beijing, China
 */

// Unicode, Raw String and codecvt in C++0x
// ==============================

// ---+ In C++0x/c++11, there are some new features regarding the strings and the encoding, and their conversions.

// let 's simply show you a source file which hopefully can tell you what is the right for everything.

#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <string>
#include <locale> // for the std::locale
#include <cstring> // for memset and others.

///////////////////////////////////////////////////////////////////////////////
// in this chapter, the knowledge of the unicode will be 	      //
//   there are a couple new types and new operations (mostly are conversion_ //
// added to the c++0x      //
///////////////////////////////////////////////////////////////////////////////

// below is the mbstate_t static field to be used
// outside of the CodeConvert function
std::mbstate_t out_cvt_state;

template
<typename In, typename Out, typename InS, typename OutS, size_t Max_In_Size >
OutS CodeConvert(const InS &ins);

template
<typename In, typename Out, typename InS, typename OutS, size_t Max_In_Size>
OutS CodeConvert(const InS& ins) {
	std::locale sys_loc("");
	const In* src_insrc = ins.c_str();
	const size_t BUFFER_SIZE = ins.size() * Max_In_Size;
	const size_t OUT_SIZE = sizeof(Out);
	// TODO:
	//  reasonable size , it may be too large the allocation to
	//  on the Out[BUFFER_SIZE]
	Out * extern_buffer = new Out[BUFFER_SIZE];
	memset(extern_buffer, 0, BUFFER_SIZE * OUT_SIZE);

	const In * intern_from = src_insrc;
	const In * intern_from_end = intern_from + ins.size();
	const In * intern_from_next = 0;

	Out * extern_from = extern_buffer;
	Out * extern_from_end = extern_from + BUFFER_SIZE;
	Out * extern_from_next = 0;

	typedef std::codecvt<In, Out, std::mbstate_t> CodeCvtFacet;

	// TODO:
	//  it is required to have the typename in front of the
	//     CodeCvtFacet
	// It is because of the CodeCvtFacet is a dependent scope, which means it required
	// to explicitly tell the compiler that the CodeCvtFacet is a type
	//
	typename CodeCvtFacet::result cvt_rst = std::use_facet<CodeCvtFacet>(sys_loc).out(
	                                            out_cvt_state,
	                                            intern_from,
	                                            intern_from_end,
	                                            intern_from_next,
	                                            extern_from,
	                                            extern_from_end,
	                                            extern_from_next
	                                        );

	if (cvt_rst != CodeCvtFacet::ok) {
		switch (cvt_rst) {
		case CodeCvtFacet::error:
			std::cerr << "partial";
			break;
		case CodeCvtFacet::partial:
			std::cerr << "partial";
			break;
		case CodeCvtFacet::noconv:
			std::cerr << "noconv";
			break;
		default:
			std::cerr << "unknown";
			break;

		}
		std::cerr << ", please check out_cvt_state."
		          << std::endl;
	}
	OutS result = extern_buffer;
	delete[] extern_buffer;
	return result;

};

std::string CodeConvertU16(const std::u16string & s)
{

	const int Max_In_Size = 4;
	std::locale sys_loc("");
	const char16_t * src_insrc = s.c_str();
	const size_t BUFFER_SIZE = s.size() * Max_In_Size;
	const size_t OUT_SIZE = sizeof(char);
	// TODO:
	//  reasonable size , it may be too large the allocation to
	//  on the Out[BUFFER_SIZE]
	char * extern_buffer = new char[BUFFER_SIZE];
	memset(extern_buffer, 0, BUFFER_SIZE * OUT_SIZE);

	const char16_t * intern_from = src_insrc;
	const char16_t * intern_from_end = intern_from + s.size();
	const char16_t * intern_from_next = 0;

	char * extern_from = extern_buffer;
	char * extern_from_end = extern_from + BUFFER_SIZE;
	char * extern_from_next = 0;

	typedef std::codecvt<char16_t, char, std::mbstate_t> CodeCvtFacet;

	// TODO:
	//  it is required to have the typename in front of the
	//     CodeCvtFacet
	// It is because of the CodeCvtFacet is a dependent scope, which means it required
	// to explicitly tell the compiler that the CodeCvtFacet is a type
	//
	typename CodeCvtFacet::result cvt_rst = std::use_facet<CodeCvtFacet>(sys_loc).out(
	                                            out_cvt_state,
	                                            intern_from,
	                                            intern_from_end,
	                                            intern_from_next,
	                                            extern_from,
	                                            extern_from_end,
	                                            extern_from_next
	                                        );

	if (cvt_rst != CodeCvtFacet::ok) {
		switch (cvt_rst) {
		case CodeCvtFacet::error:
			std::cerr << "partial";
			break;
		case CodeCvtFacet::partial:
			std::cerr << "partial";
			break;
		case CodeCvtFacet::noconv:
			std::cerr << "noconv";
			break;
		default:
			std::cerr << "unknown";
			break;

		}
		std::cerr << ", please check out_cvt_state."
		          << std::endl;
	}
	std::string result = extern_buffer;
	delete[] extern_buffer;
	return result;
}

int main(int argc, char * argv[])
{

	char16_t char16; // 16-bit character
	char32_t char32; // 32-bit character

	char16 = u'x';  // 16-bit lieral
	char32 = U'x';  // 32-bit lteral

	char cpp98char = 'x';   // 'x' as a char
	wchar_t cpp92wchar = L'x';         // c++98 wchar_t


	const char16_t * char16_s = u"UCS-2 string literal";
	const char32_t * char32_s = U"UCS-4 string literal";

	const char * cpp98char_s = "Ordinary/narrow string literal";
	const wchar_t * cpp98wchar_s = L"Wide string literal";


	// const charu8_t * charu8_s = u8"UTF-8 string literal";
	
	// Code pointscan be specified via \unnnn and \Unnnnnnn
	// u8"G clef: \U0001D11E"  // )
	// u"Thai character Khomut: \u0E5B"  // ?
	// U"Skull and crossbones: \u2620"  // ?
	
	// and as you can see, there is no difference between a
	// char * and a u8 string.
	auto u8_s = "你好This is a u8 string";
	const char * charu8_s = u8"你好This is au8 string literal";
	std::cout << "typeid(u8_s).name() is "<< typeid(u8_s).name()<< std::endl;
	std::cout << "typeid(charu8_s).name() is "<<typeid(charu8_s).name()<< std::endl;
	std::cout << "typeid(char16_s) is "<< typeid(char16_s).name()<< std::endl;
	
	// there are added converters that
	// aim to help convert
	// among the different types of encodings
	// there are
	//   * UTF32 -><- UCS-16 -><- UCS-8

// C++98 guarantees only two codecvt facets:    //
//  char ? char (std::codecvt<char, char, std::mbstate_t>)    //
//    “Degenerate” – no conversion performed.    //
//   wchar_t ? char (std::codecvt<wchar_t, char, std::mbstate_t>)  //
// C++0x adds:    //
//   UTF-16 ? UTF-8 (std::codecvt<char16_t, char, std::mbstate_t>) //
//   UTF-32 ? UTF-8 (std::codecvt<char32_t, char, std::mbstate_t>) //
//  UTF-8 ? UCS-2, UTF-8 ? UCS-4 (std::codecvt_utf8)    //
//  UTF-16 ? UCS-2, UTF-16 ? UCS-4 (std::codecvt_utf16)    //
//  UTF-8 ? UTF-16 (std::codecvt_utf8_utf16)    //
//  Behaves like std::codecvt<char16_t, char, std::mbstate_t>    //



	std::string s1 = "this a a normal string literal";
	std::wstring s2 = L"This is a wchar_t string literal";
	std::u16string s3 = u"This is a UCS2 encoding literal";
	std::u32string s4= U"This is a UCS4 encoding literal";

	std::cout << "normal string: " << s1 << std::endl;
		
/* 	std::string out_str1 = CodeConvert<wchar_t, char, std::wstring, std::string, 4>(s2);
	std::cout << "wstring: "<< out_str1<< std::endl;
	
	std::string out_str2 = CodeConvert<char16_t, char, std::u16string, std::string, 8>(s3);
	std::cout << "u16string: "<< out_str2<< std::endl;
	
	std::string out_str3 = CodeConvert<char32_t, char, std::u32string, std::string, 4>(s4);
	std::cout << "u32string: "<< out_str3<< std::endl; */

	// out_str = CodeConvertU16(s3);
	// std::cout << "u16string: "
	          // << out_str
	          // << std::endl;
	// std::cout<<"ok2"<<std::endl;
	
	
	// also , there is IO based conversion
	// which unlike the C++98,which requires the change to to string locales,
	// can directly change the encoding.

	// std::wbuffer_convert : IO-based encoding
	// std::wstring_convert : in memory encoding
	return 0;
}

// ---+ The rest result,

// however, unfortunately, not all the feature that has been advertised by the GNU has been fully implemented.

// for starter, there is no impl on the codecvt on the utf-16/utf-32 to char conversion.

