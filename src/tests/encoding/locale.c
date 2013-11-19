#include <stdio.h>
#include <locale.h>
int main( void )
{
    setlocale( LC_ALL, "chs" );
    //setlocale( LC_ALL, "Chinese-simplified" );
    //setlocale( LC_ALL, "ZHI" );
    //setlocale( LC_ALL, ".936" );
    wprintf( L"ÖÐ¹ú" );
    return 0;
}