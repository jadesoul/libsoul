#ifndef REPEAT_H_1325419617_88
#define REPEAT_H_1325419617_88
/**
 * File: repeat.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * Licensed under the GNU General Public License:
 * http://www.gnu.org/licenses/gpl.html
 * 
 * Date: 2012-01-01 20:06:57.878000
 * Written In: Peking University, beijing, China
 */

#include "includes.h"

/**
 *  repeat
 *	
 *  repeat sequence [begin1, end1) for n times 
 *  
 *  by jadesoul @ 2012-1-1 22:28:16
 */
template <class BidirectionalIterator, class OutputIterator>
OutputIterator repeat(BidirectionalIterator begin, BidirectionalIterator end, OutputIterator out, size_t n) {
	for (uint i=0; i<n; ++i) out=std::copy(begin, end, out);
	return out;
}


#endif /* REPEAT_H_1325419617_88 */
