// 一个多字节字符串和宽字符字符串互相转化的事例
#define _CRT_SECURE_NO_WARNINGS // only for vc8
#include <string>
#include <clocale>
#include <cassert>
inline const std::string to_mbcs( const std::string& src )
{
    return src;
}
const std::string to_mbcs( const std::wstring& src )
{
    char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) ); // 保存原来的locale
    setlocale( LC_CTYPE, "chs" ); // 设置当前locale为chs，这在非简体中文平台上不可缺少
    size_t count1 = wcstombs( NULL, src.c_str(), 0 ); // 计算新字符串长度
    std::string des( count1, ' ' );
    size_t count2 = wcstombs( &des[0], src.c_str(), count1 ); // 转化
    assert( count1 == count2 );
    setlocale( LC_CTYPE, old_locale ); // 恢复到原来的locale
    free( old_locale );
    return des;
}
inline const std::wstring to_wcs( const std::wstring& src )
{
    return src;
}
const std::wstring to_wcs( const std::string& src )
{
    char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) ); // 保存原来的locale
    setlocale( LC_CTYPE, "chs" ); // 设置当前locale为chs，这在非简体中文平台上不可缺少
    size_t count1 = mbstowcs( NULL, src.c_str(), 0 ); // 计算新字符串长度
    std::wstring des( count1, L' ' );
    size_t count2 = mbstowcs( &des[0], src.c_str(), count1 ); // 转化
    assert( count1 == count2 );
    setlocale( LC_CTYPE, old_locale ); // 恢复到原来的locale
    free( old_locale );
    return des;
}
#include <iostream>
int main( void )
{
    using namespace std;
    cout << to_mbcs("你好1") << endl;
    cout << to_mbcs(L"你好2") << endl;
    const locale loc( "chs" );
    wcout.imbue( loc );
    wcout << to_wcs("你好3") << endl;
    wcout << to_wcs(L"你好4") << endl;
}