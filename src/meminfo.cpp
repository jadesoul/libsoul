/**
 * File: meminfo.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 17:21:23.649000
 * Written In: Peking University, beijing, China
 */

#include "meminfo.h"

/**
 * memory information
 */

meminfo::meminfo() {
#ifdef ENV_WIN32_MSVC
	HANDLE handle=GetCurrentProcess();
	GetProcessMemoryInfo(handle, &pmc, sizeof(pmc));
#else
#endif
}

ostream& operator <<(ostream& o, meminfo& mi) {
#ifdef ENV_WIN32_MSVC
	return o<<"Mem Usage:"
			<<endl
			
			<<"WorkingSetSize="
			<<mi.nice_repr(mi.pmc.WorkingSetSize)
			<<endl
			
			<<"PeakWorkingSetSize="
			<<mi.nice_repr(mi.pmc.PeakWorkingSetSize)
			<<endl
			
			<<"PagefileUsage="
			<<mi.nice_repr(mi.pmc.PagefileUsage)
			<<endl
			
			<<"PeakPagefileUsage"
			<<mi.nice_repr(mi.pmc.PeakPagefileUsage)
			<<endl;
#else
#endif
	return o;
}

//return physical memory size
size_t meminfo::phys() {
#ifdef ENV_WIN32_MSVC
	return pmc.WorkingSetSize;
#else
	return 0;
#endif
}

//return virtual memory size
size_t meminfo::virtu() {
#ifdef ENV_WIN32_MSVC
	return pmc.PagefileUsage;
#else
	return 0;
#endif
}

uchar meminfo::get_unit(ulong bytes) {
	ulong& b=bytes;
	const uchar B=1, K=2, M=3, G=4, T=5, P=6;
	if (b<(1<<10)) return B;
	if (b<(1<<20)) return K;
	if (b<(1<<30)) return M;
	b/=1<<30;
	if (b<(1<<10)) return G;
	if (b<(1<<20)) return T;
	if (b<(1<<30)) return P;
	return B;
}

string meminfo::nice_repr(ulong bytes) {
	ulong& b=bytes;
	// uchar u=get_unit(labs(b));
	uchar u=get_unit(b);
	const uchar B=1, K=2, M=3, G=4, T=5, P=6;
	char buf[50];
	if (u==B) sprintf(buf, fmtstr_ulong, b);
	else if (u==K) sprintf(buf, "%.1fK", (float)b/(1<<10));
	else if (u==M) sprintf(buf, "%.1fM", (float)b/(1<<20));
	else if (u==G) sprintf(buf, "%.1fG", (float)b/(1<<30));
	else if (u==T) sprintf(buf, "%.1fT", (float)b/(1<<30)/(1<<10));
	else if (u==P) sprintf(buf, "%.1fP", (float)b/(1<<30)/(1<<20));
	else sprintf(buf, fmtstr_ulong, b);
	return buf;
}


map<uint, meminfo> __gmt;	//global meminfo table

void mem_init(uint id) {
	__gmt[id]=meminfo();
}

void mem_gap(char* msg, uint id, bool update) {
	if_not_in(id, __gmt) return;
	meminfo now;
	cout<<msg<<": "<<now.nice_repr(now.virtu()-__gmt[id].virtu())<<endl;
	if (update) __gmt[id]=now;
}

