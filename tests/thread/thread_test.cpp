/**
 * File: thread_test.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 16:14:15.408000
 * Written In: Peking University, beijing, China
 */

#include <thread.h>
#include <libjade>

class mythread : public thread {
protected:
	void run() {
		for_n(i, 10000) {
			cout<<"123"<<endl;
			for_n(j, 100000000);
		}
	}
};

int main() {
	mythread t;
	//t.start();
	int a;
	str b="this is str";
	cout<<fmtstr_ulong<<" "<<b<<endl;
	cin>>a;
	return 0;
}
