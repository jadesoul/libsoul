#include <iostream>
#include <locale>
using namespace std;
int main( void )
{
    locale loc( "chs" );
    //locale loc( "Chinese-simplified" );
    //locale loc( "ZHI" );
    //locale loc( ".936" );
    wcout.imbue( loc );
    std::wcout << L"ÖÐ¹ú" << endl;
    return 0;
}