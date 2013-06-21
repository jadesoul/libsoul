/**
 * File: dump.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 17:12:42.625000
 * Written In: Peking University, beijing, China
 */

#include "dump.h"

/**************************************************
format: format string to stream
**************************************************/
inline string va_format(const char* fmt, va_list ap) {
	const int MAX=1<< 12;
	char buf[MAX+1];
	vsprintf(buf, fmt, ap);
	va_end(ap);
	string ret(buf, buf+strlen(buf));
	return ret;
}

string c_format(const char* fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	string ret=va_format(fmt, ap);
	va_end(ap);
	return ret;
}

/**************************************************
log: log massage by format, auto add time
**************************************************/
void log(const char* fmt, ...) {
	va_list ap;
	datetime now;
	cout<<"LOG : "<<now<<" : ";
	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	va_end(ap);
	cout<<endl;
}
