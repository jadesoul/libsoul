#ifndef STARTSWITH_H_1324966512_44
#define STARTSWITH_H_1324966512_44
/**
 * File: startswith.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:15:12.439000
 * Written In: Peking University, beijing, China
 */

#include "includes.h"

/**
 *  startswith
 *	
 *  test if the elements in [first1, last1) startswith the elements in [first2, last2)
 *  by jadesoul @ 2010-9-30
 *	
 *  usage sample: cout<<boolalpha<<startswith(p, p+12, q, q+5);
*/
template <  class InputIterator1,
class InputIterator2    >
bool startswith(InputIterator1 first1, InputIterator1 last1,
			InputIterator2 first2, InputIterator2 last2 ) {
	ptrdiff_t len1 = distance(first1, last1), len2 = distance(first2, last2);
	if (len1 < len2) return false;
	while (first2 != last2) {
		if (*first1++ != *first2++) return false;
	}
	return true;
}

/**
 *  startswith using comp function
 *
 *  test if the elements in [first1, last1) startswith the elements in [first2, last2)
 *  by jadesoul @ 2010-9-30
 *
 *  usage sample: cout<<boolalpha<<startswith(p, p+12, q, q+5, equal_to<char>());
*/
template <  class InputIterator1,
class InputIterator2,
class Function  >
bool startswith(    InputIterator1 first1,
                    InputIterator1 last1,
                    InputIterator2 first2,
                    InputIterator2 last2,
                    Function comp   ) {
	ptrdiff_t len1 = distance(first1, last1), len2 = distance(first2, last2);
	if (len1 < len2) return false;
	while (first2 != last2) {
		if (!comp(*first1++ , *first2++)) return false;
	}
	return true;
}

/* startswith } */


#endif /* STARTSWITH_H_1324966512_44 */
