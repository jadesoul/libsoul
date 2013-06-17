#ifndef MAX_SUB_SUM_H_1324968069_47
#define MAX_SUB_SUM_H_1324968069_47
/**
 * File: max_sub_sum.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:41:09.472000
 * Written In: Peking University, beijing, China
 */

template< class iterator >
void max_sub_sum(iterator begin,
				 iterator end,
				 iterator& first,
				 iterator& last) {
	typename iterator_traits<iterator>::value_type sum=0, b=0;
	for (iterator i=begin; i<end; ++i) {
		if (b>0) b+=*i;
		else {
			b=*i;
			first=i;
		}
		if (sum<b) {
			sum=b;
			last=i;
		}
	}
}

template< class Container, class iterator >
inline void max_sub_sum(Container& c, 
				 iterator& first,
				 iterator& last) {
	max_sub_sum(c.begin(), c.end(), first, last);
}				 

#endif /* MAX_SUB_SUM_H_1324968069_47 */
