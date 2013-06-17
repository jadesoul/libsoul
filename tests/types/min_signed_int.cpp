/**
 * File: min_signed_int.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-08-31 12:15:03.282000
 * Written In: Peking University, beijing, China
 */

#include <jadesoul.hpp>

int main () {
    int a=0x7FFFFFFF;
	cout<<a<<endl;
	cout<<a+1<<endl;
    a=0xFFFFFFFF;
	cout<<a<<endl;
	cout<<a-1<<endl;
	cout<<int(min_sint1)<<endl;
	cout<<int(min_sint2)<<endl;
	cout<<min_sint4<<endl;
	cout<<max_sint4<<endl;
    
}

