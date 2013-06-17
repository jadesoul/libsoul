#ifndef COUNT_H_1325398226_46
#define COUNT_H_1325398226_46
/**
 * File: count.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * Licensed under the GNU General Public License:
 * http://www.gnu.org/licenses/gpl.html
 * 
 * Date: 2012-01-01 14:10:26.486000
 * Written In: Peking University, beijing, China
 */

#include "includes.h"

/**
 *  count
 *	
 *  count for sequence [begin1, end1) has how many 
 *  sub sequence [begin2, end2)
 *  by jadesoul @ 2012-1-1 14:15:07
 */
template <class InputIterator1, class InputIterator2>
size_t count(InputIterator1 begin1, InputIterator1 end1,
			InputIterator2 begin2, InputIterator2 end2 ) {
	ptrdiff_t len1=distance(begin1, end1), len2=distance(begin2, end2);
	if (len1<len2) return 0;
	size_t cnt=0;
	while ((begin1=std::search(begin1, end1, begin2, end2))!=end1) {
		advance(begin1, len2);
		++cnt;
	}
	return cnt;
}


#endif /* COUNT_H_1325398226_46 */
