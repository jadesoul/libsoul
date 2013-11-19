/**
 * File: datetime.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 16:55:56.526000
 * Written In: Peking University, beijing, China
 */

#include "datetime.h" 

datetime::datetime(): secs(time(NULL)) {
	update();
}

double datetime::update() {
	size_t old=millisecs();

	//init as now time
#ifdef OS_WIN32
	GetLocalTime(&sys);
#else
	gettimeofday(&now, NULL);
#endif

	return 0.000001*(millisecs()-old);
}

ostream& operator <<(ostream& o, datetime& dt) {
	char s[30];
#ifdef OS_WIN32
	const char* fmt="%4d-%02d-%02d %02d:%02d:%02d.%03d %1d/7";
	sprintf(s, fmt, 
			dt.sys.wYear,
			dt.sys.wMonth,
			dt.sys.wDay,
			dt.sys.wHour,
			dt.sys.wMinute, 
			dt.sys.wSecond,
			dt.sys.wMilliseconds,
			dt.sys.wDayOfWeek);
#else
	const char* fmt="%Y-%m-%d %H:%M:%S";
	strftime(s, 30, fmt, localtime(&dt.secs));
#endif
	return o<<s;
}

string datetime::nowfn() {
	char s[30];
#ifdef OS_WIN32
	const char* fmt="%4d_%02d_%02d-%02d_%02d_%02d";
	sprintf(s, fmt, 
			sys.wYear,
			sys.wMonth,
			sys.wDay,
			sys.wHour,
			sys.wMinute, 
			sys.wSecond);
#else
	const char* fmt="%Y_%m_%d-%H_%M_%S";
	strftime(s, 30, fmt, localtime(&secs));
#endif
	return s;
}

size_t datetime::millisecs() const {
	size_t ms=0;
#ifdef OS_WIN32
	ms=(size_t)secs*1000000+sys.wMilliseconds*1000;
#else
	ms=now.tv_sec*1000000+now.tv_usec;
#endif
	return ms;
}

double datetime::gap(const datetime& dt) const {
	return 0.000001*(this->millisecs() - dt.millisecs());
}

double datetime::elapse() const {
	return datetime() - (*this);
}

// map<uint, datetime> __gdt;	//global datetime table

// void time_init(uint id) {
// 	__gdt[id]=datetime();
// }

// void time_gap(const char* msg, uint id, bool update, ostream& o) {
// 	if_not_in(id, __gdt) return;
// 	o<<msg<<": "<<datetime().gap(__gdt[id])<<"ms"<<endl;
// 	if (update) __gdt[id]=datetime();
// }
