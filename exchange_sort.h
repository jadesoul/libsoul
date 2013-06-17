#ifndef EXCHANGE_SORT_H_1324967414_8
#define EXCHANGE_SORT_H_1324967414_8
/**
 * File: exchange_sort.hpp
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:30:14.800000
 * Written In: Peking University, beijing, China
 */

//exchange_sort
//O(n^2)
template< class iterator >
void exchange_sort(iterator begin, iterator end) {
	for (iterator now=begin; now<end-1; ++now) {
		for (iterator it=now+1; it<end; ++it)
			if (*now>*it) iter_swap(now, it);
	}
}

#endif /* EXCHANGE_SORT_H_1324967414_8 */
