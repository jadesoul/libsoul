#ifndef MEMINFO_H_1356513680_9
#define MEMINFO_H_1356513680_9
/**
 * File: meminfo.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 17:21:20.897000
 * Written In: Peking University, beijing, China
 */

#include "bootstrap.h"

/**
 * memory information
 */

class meminfo {
private:
#ifdef ENV_WIN32_MSVC
	PROCESS_MEMORY_COUNTERS pmc;
#else
#endif
public:
	meminfo();
	friend ostream& operator <<(ostream& o, meminfo& mi);
	size_t phys();	//return physical memory size
	size_t virtu();	//return virtual memory size
	uchar get_unit(ulong bytes);
	string nice_repr(ulong bytes);
};

extern map<uint, meminfo> __gmt;	//global meminfo table

void mem_init(uint id=0);
void mem_gap(char* msg="", uint id=0, bool update=true);

#endif /* MEMINFO_H_1356513680_9 */
