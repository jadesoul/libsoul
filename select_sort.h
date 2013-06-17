#ifndef SELECT_SORT_H_1324967393_25
#define SELECT_SORT_H_1324967393_25
/**
 * File: select_sort.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:29:53.246000
 * Written In: Peking University, beijing, China
 */

//select_sort
//select the smallest element and exchange it with the n-th element
//O(n^2)

template< class iterator >
void select_sort(iterator begin, iterator end) {
	for (iterator round=begin; round<end-1; ++round) {
		iterator min=round;
		for (iterator it=round+1; it<end; ++it)
			if (*it<*min) min=it;
		iter_swap(round, min);
	}
}

#endif /* SELECT_SORT_H_1324967393_25 */
