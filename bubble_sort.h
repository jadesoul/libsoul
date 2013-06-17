#ifndef BUBBLE_SORT_H_1324967372_09
#define BUBBLE_SORT_H_1324967372_09
/**
 * File: bubble_sort.hpp
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:29:32.092000
 * Written In: Peking University, beijing, China
 */



//bubble_sort
// O(n^2)
template < class RandomAccessIterator >
void bubble_sort(RandomAccessIterator first, RandomAccessIterator last) {
	typedef RandomAccessIterator iter_t;
	for (iter_t end=last-1; first!=end; --end) {
		for (iter_t it=first; it!=end; ++it) {
			if (*it > *(it+1)) iter_swap(it, it+1) ;
		}
	}
}


#endif /* BUBBLE_SORT_H_1324967372_09 */
