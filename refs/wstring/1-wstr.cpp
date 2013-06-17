/*
 * =====================================================================================
 *
 *       Filename:  wstr.cpp
 *
 *    Description:  test
 *        Version:  1.0
 *        Created:  06/25/2012 09:02:36 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *        Company:  
 *
 * =====================================================================================
 */
#include <wchar.h>
#include <cstddef>
#include <fstream>
#include <locale>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>
#include <cassert>
using namespace std;

void print_bytes(std::string const& str)
{
	for (size_t i=0; i<str.size(); ++i) {
		char byte=str[i];
		std::cout << std::setfill('0') << std::setw(2)
					<< std::hex << std::showbase << (byte & 0xff) << " ";
	}
	std::cout << std::endl;
}

void print_bytes(std::wstring const& str)
{
	assert(sizeof(wchar_t) == 2);
	for (size_t i=0; i<str.size(); ++i) {
		wchar_t twobytes=str[i];
		std::cout << std::setfill('0') << std::setw(2)
			<< std::hex << std::showbase
			<< (twobytes >> 8) << "-" << (twobytes & 0x00ff) << " ";
	}
	std::cout << std::endl;
}

int main()
{
	// 0xe9 0xbb 0x8f 0xee 0x84 0x9b
	// 0xe9 0xbb 0x8f 0xee 0x84 0x9b
	// 0x9e-0xcf 0xe1-0x1b
	// 0x9e-0xcf 0xe1-0x1b

	std::string u8_char = "\xe9\xbb\x8f\xee\x84\x9b"; // utf8 encoding for 𤭢
	std::wstring w_char = L"𤭢";//

	std::wstring_convert<std::codecvt_utf8<wchar_t>> utf8conv;
	std::wstring w_result = utf8conv.from_bytes(u8_char); // convert utf8 to wchar_t
	std::string u8_result = utf8conv.to_bytes(w_char); // convert wchar_t to utf8

	if (w_char != w_result)
		std::cout << "Failed to convert from 4 byte codepoint utf8 to wchar_t." << std::endl;
	if (u8_char != u8_result)
		std::cout << "Failed to convert from wchar_t to 4 byte codepointt utf8." << std::endl;

	print_bytes(u8_char);
	print_bytes(u8_result);
	print_bytes(w_char);
	print_bytes(w_result);

}
