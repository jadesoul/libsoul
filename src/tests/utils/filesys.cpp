/**
 * File: filesys.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-04-21 11:28:20.872000
 * Written In: Peking University, beijing, China
 */

#include <jadesoul.hpp>

int main () {
	cout<<"hello, world"<<endl;
	print(cwd());
	cp("filesys", "filesys_copied");
}

