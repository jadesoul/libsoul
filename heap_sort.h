#ifndef HEAP_SORT_H_1324967193_53
#define HEAP_SORT_H_1324967193_53
/**
 * File: heap_sort.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:26:33.528000
 * Written In: Peking University, beijing, China
 */

//heap_sort
//most bad: O(nlogn)
//average: O(nlogn)

template <  class Container >
void heap_sort(Container& c) {
	make_heap(c.begin(), c.end());
	sort_heap(c.begin(), c.end());
}

template <  class RandomAccessIterator >
void heap_sort(RandomAccessIterator begin, RandomAccessIterator end) {
	RandomAccessIterator i, j;
	make_heap(begin, end);
	sort_heap(begin, end);
}

#endif /* HEAP_SORT_H_1324967193_53 */
