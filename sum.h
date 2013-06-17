#ifndef SUM_H_1357366396_13
#define SUM_H_1357366396_13
/**
 * File: sum.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-05 14:13:16.131941
 * Written In: Peking University, beijing, China
 */

template<class T, class I>
inline T sum(I begin, I end) {
	return std::accumulate(begin, end, T());
}

template<class C>
inline typename C::value_type sum(const C& c) {
	return sum<typename C::value_type>(c.begin(), c.end());
}

#endif /* SUM_H_1357366396_13 */
