#include <iostream>
#include <string>
#include <locale>
//#include <codecvt>
int main()
{
	// UTF-8 data: letter 'z', CJK ideogram 'water', musical sign 'segno'
	std::string utf8="z\xe6\xb0\xb4\xf0\x9d\x84\x8b";

	// the UTF-8 / UTF-16 standard conversion facet
	std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> utf16conv;
	std::u16string utf16 = utf16conv.from_bytes(utf8);
	std::cout << "UTF16 conversion produced " << utf16.size() << " code points:\n";
	for (size_t i=0; i<utf16.size(); ++i) {
		char16_t c=utf16[i];
		std::cout << std::hex << std::showbase << c << '\n';
	}
	
	// the UTF-8 / UTF-32 standard conversion facet
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> utf32conv;
	std::u32string utf32 = utf32conv.from_bytes(utf8);
	std::cout << "UTF32 conversion produced " << std::dec << utf32.size() << " code points:\n";
	for (size_t i=0; i<utf32.size(); ++i) {
		char32_t c=utf32[i];
		std::cout << std::hex << std::showbase << c << '\n';
	}
}
