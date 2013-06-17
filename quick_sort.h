#ifndef QUICK_SORT_H_1324967314_99
#define QUICK_SORT_H_1324967314_99
/**
 * File: quick_sort.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:28:34.993000
 * Written In: Peking University, beijing, China
 */


//quick_sort
//overload the partition funciton in STL
//this version has only 2 params while the one in STL has 3
//most bad: O(n^2)
//average: O(nlogn)

template <class iterator >
iterator partition(iterator begin, iterator end) {
	assert(begin<end);
	iterator i=begin, j=end-1;
	typename iterator_traits<iterator>::value_type v=*i;
	if (i<j) {
		while(i<j) {// there is some problem here
			while (i<j && *j>v) --j;
			if (i==j) break;
			*i++=*j;
			while (i<j && *i<v) ++i;
			if (i==j) break;
			*j--=*i;
		}
	}
	*i=v;
	return i;
}


template< class iterator >
void quick_sort(iterator begin, iterator end) {
	if (end-begin>1) {
		iterator k=partition(begin, end);
		quick_sort(begin, k);
		quick_sort(k+1, end);
	}
}

#endif /* QUICK_SORT_H_1324967314_99 */
