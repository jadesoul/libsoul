// string wstring _bstr_t的互相转换 (2012-04-18 10:54:31)转载
// 标签： 杂谈	分类： C/Cpp
// 今天在研究VC++ 使用 ADO 读取MS SQKSERVER 数据库时， 发现：
// string ansi字符串
// wstring unicode字符串
// _bstr_t com字符串
// 之间的转换关系，示例如下：
// ex_02_wstring_cv_string.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "string"
#include "icrsint.h"
#include "comutil.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	wstring ws1,ws2;
	ws2 = L"春如旧，人空瘦，泪痕红浥鲛绡透。桃花落，闲池阁，山盟虽在，锦书难托。莫、莫、莫。";
	// 从 unicode 字符串转化为 ansi字符串
	string s = (char *) _bstr_t ( ws2.c_str() );
	// 从 ansi字符串转化为 unicode 字符串
	ws1 = ( wchar_t *) ( _bstr_t ( s.c_str( ) ));
	setlocale(LC_ALL, "chs");
	wprintf( L"原wstring串=%s\n",ws2.c_str());
	printf( "转换为string串=%s\n", s.c_str());
	wprintf( L"转换为wstring串=%s\n",ws1.c_str());
	::CoUninitialize();
	getchar();
	return 0;
}

// --- 结果 ---
// 原wstring串=春如旧，人空瘦，泪痕红浥鲛绡透。桃花落，闲池阁，山盟虽在，锦书难托。莫、莫、莫。
// 转换为string串=春如旧，人空瘦，泪痕红浥鲛绡透。桃花落，闲池阁，山盟虽在，锦书难托。莫、莫、莫。
// 转换为wstring串=春如旧，人空瘦，泪痕红浥鲛绡透。桃花落，闲池阁，山盟虽在，锦书难托。莫、莫、莫。