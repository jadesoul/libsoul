#ifndef INSERT_SORT_H_1324967350_57
#define INSERT_SORT_H_1324967350_57
/**
 * File: insert_sort.hpp
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:29:10.574000
 * Written In: Peking University, beijing, China
 */
 
//insert_sort
// O(n^2)

template <  class RandomAccessIterator >
void insert_sort(RandomAccessIterator begin, RandomAccessIterator end) {
	RandomAccessIterator i, j;
	for (i=begin+1; i<end; ++i) {
		for (j=i; j>begin && *i < *(j-1); --j) ;
		if (j!=i) rotate(j, i, i+1);
	}
}

//using binary search when insert
// O(n log n)

template <  class RandomAccessIterator >
void binary_insert_sort(RandomAccessIterator begin, RandomAccessIterator end) {
	RandomAccessIterator i, low, high, mid;
	for (i=begin+1; i<end; ++i) {
		low=begin;
		high=i-1;
		while (low<high) {
			mid=low+(high-low)/2;
			if (*mid==*i) {
				low=mid;//let low represent the result
				break;
			}
			else if (*mid<*i) low=mid+1;
			else high=mid-1;
		}
		if (low!=i) rotate(low, i, i+1);
	}
}


#endif /* INSERT_SORT_H_1324967350_57 */
