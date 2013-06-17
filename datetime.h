#ifndef DATETIME_H_1356512152_21
#define DATETIME_H_1356512152_21
/**
 * File: datetime.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 16:55:52.209000
 * Written In: Peking University, beijing, China
 */

#include "bootstrap.h"

class datetime {
	time_t secs;
#ifdef OS_WIN32
	SYSTEMTIME sys;
#else
	struct timeval now;
#endif
public:
	datetime();
	double update();//update time as now, and return how many elapsed
	friend ostream& operator <<(ostream& o, datetime& dt);
	size_t millisecs() const;
	string nowfn();//string of now for file name
	double gap(const datetime& dt) const;
	double elapse() const;//return how many elapsed till now
	inline double operator -(const datetime& r) const { return gap(r); }
};

// extern map<uint, datetime> __gdt;	//global datetime table

// void time_init(uint id=0);
// void time_gap(const char* msg, uint id=0, bool update=true);

#endif /* DATETIME_H_1356512152_21 */
