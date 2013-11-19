#ifndef UTILS_H_1356506613_42
#define UTILS_H_1356506613_42
/**
 * File: utils.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 15:23:33.424000
 * Written In: Peking University, beijing, China
 */

#include "bootstrap.h"
#include "datetime.h"
#include "random.h"
#include "debug.h"
#include "logging.h"
#include "corelib.h"
#include "filesys.h"
#include "network.h"

// template<class T>
// inline list<T> list(set<T>& s) {
	// return list<T>(s.begin(), s.end());
// }

template<class T>
inline set<T> unique(list<T>& l) {
	set<T> s;
	uint n=l.size();
	for_n(i, n) s.add(l[i]);
	return s;
}

template<class T>
inline list<T> uniqued(list<T>& l) {
	return list<T>(unique(l));
}

// void sys_init(uint id=0);
// void sys_gap(char* msg, uint id=0, bool update=true);

#endif /* UTILS_H_1356506613_42 */
