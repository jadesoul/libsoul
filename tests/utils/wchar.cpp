/**
 * File: wchar.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-07-20 11:15:06.506000
 * Written In: Peking University, beijing, China
 */

#include <jadesoul.hpp>
#include <jadesoul/utils/wchar.hpp>

int main () {
        string s="你好";
        wstring ws=L"你好";

        cout<<s<<endl;
        cout<<wstringtostring(ws)<<endl;
        cout<<narrow(ws)<<endl;

	wcout.imbue(locale(locale(), "", LC_CTYPE));
	// wcout.imbue(locale(""));
        // wcout.imbue(locale_platform);
        wcout<<ws<<endl;
        wcout<<stringtowstring(s)<<endl;
        wcout<<widen(s)<<endl;

        wofstream fout("fout.txt");
        fout.imbue(locale_platform);
        fout<<ws<<endl;
        fout<<stringtowstring(s)<<endl;
        fout<<widen(s)<<endl;

	
//        string in;
//	copy(utf8in(s.begin()), utf8in(s.end()), back_inserter(in));
//	cout<<in<<endl;
	// copy(utf8in(s.begin()), utf8in(s.end()), back_inserter(wvect));
	// cout<<string(utf8in(s.begin()), utf8in(s.end()))<<endl;
}

