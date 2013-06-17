#ifndef FIND_ITER_H_1335030876_06
#define FIND_ITER_H_1335030876_06
/**
 * File: find_iter.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-04-22 01:54:36.064000
 * Written In: Peking University, beijing, China
 */

//find a iterator between first and last that 
template<class InputIterator, class Selector>
inline InputIterator find_iter(InputIterator first, InputIterator last, Selector sel)
{
	return sel(first, last);
}

template<class ForwardIterator>
inline ForwardIterator find_iter_max(ForwardIterator first, ForwardIterator last) {
	return max_element(first, last);
}

template<class ForwardIterator, class CompareFunction>
inline ForwardIterator find_iter_max(ForwardIterator first, ForwardIterator last, CompareFunction cmp) {
	return max_element(first, last, cmp);
}

template<class ForwardIterator>
inline ForwardIterator find_iter_min(ForwardIterator first, ForwardIterator last) {
	return min_element(first, last);
}

template<class ForwardIterator, class CompareFunction>
inline ForwardIterator find_iter_min(ForwardIterator first, ForwardIterator last, CompareFunction cmp) {
	return min_element(first, last, cmp);
}


	
	
#endif /* FIND_ITER_H_1335030876_06 */
