// һ�����ֽ��ַ����Ϳ��ַ��ַ�������ת��������
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
    char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) ); // ����ԭ����locale
    setlocale( LC_CTYPE, "chs" ); // ���õ�ǰlocaleΪchs�����ڷǼ�������ƽ̨�ϲ���ȱ��
    size_t count1 = wcstombs( NULL, src.c_str(), 0 ); // �������ַ�������
    std::string des( count1, ' ' );
    size_t count2 = wcstombs( &des[0], src.c_str(), count1 ); // ת��
    assert( count1 == count2 );
    setlocale( LC_CTYPE, old_locale ); // �ָ���ԭ����locale
    free( old_locale );
    return des;
}
inline const std::wstring to_wcs( const std::wstring& src )
{
    return src;
}
const std::wstring to_wcs( const std::string& src )
{
    char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) ); // ����ԭ����locale
    setlocale( LC_CTYPE, "chs" ); // ���õ�ǰlocaleΪchs�����ڷǼ�������ƽ̨�ϲ���ȱ��
    size_t count1 = mbstowcs( NULL, src.c_str(), 0 ); // �������ַ�������
    std::wstring des( count1, L' ' );
    size_t count2 = mbstowcs( &des[0], src.c_str(), count1 ); // ת��
    assert( count1 == count2 );
    setlocale( LC_CTYPE, old_locale ); // �ָ���ԭ����locale
    free( old_locale );
    return des;
}
#include <iostream>
int main( void )
{
    using namespace std;
    cout << to_mbcs("���1") << endl;
    cout << to_mbcs(L"���2") << endl;
    const locale loc( "chs" );
    wcout.imbue( loc );
    wcout << to_wcs("���3") << endl;
    wcout << to_wcs(L"���4") << endl;
}