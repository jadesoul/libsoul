/**
 * File: json_test.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-27 16:10:06.391000
 * Written In: Peking University, beijing, China
 */

#include <libjade>
#include <json.h>

int main () {	
	json::array aa;
	aa.append(str("123"));
	aa.append(num(123));

	cout<<aa<<endl;
	json bb;
	bb.root=aa;
	cout<<bb<<endl;
	
	dict<int, int> a;
	a.set(1, 1);
	a[2]=2;
	cout<<a<<endl;
	
	// root.type='A';
	// root.ptr=new array();
	// array& a=*((array*)root.ptr);
	// a.append(item(str("hi")));
	// a.append(item(str("hi")));
	
	// dictionary d;
	// a.append(item(d));
	// array a2;
	// a2.append(item(str("test")));
	// a2.append(item(str("test")));
	// a.append(item(a2));
	// a.append(item(str("hi")));
	// a.append(item(str("hi")));
	// a.append(item(str("hi")));
	// a.append(item(str("hi")));
}

