#ifndef ENDSWITH_H_1324966538_22
#define ENDSWITH_H_1324966538_22
/**
 * File: endswith.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:15:38.224000
 * Written In: Peking University, beijing, China
 */
 

/**
 *  endswith
 *
 *  test if the elements in [first1, last1) endswith the elements in [first2, last2)
 *  by jadesoul @ 2010-9-30
 *
 *  usage sample: cout<<boolalpha<<endswith(p, p+12, q, q+5);
*/
template <  class InputIterator1,
class InputIterator2    >
bool endswith(InputIterator1 first1,
                    InputIterator1 last1,
                    InputIterator2 first2,
                    InputIterator2 last2) {
	ptrdiff_t len1 = distance(first1, last1), len2 = distance(first2, last2);
	if (len1 < len2) return false;
	while (first2 != last2) {
		if (*--last1 != *--last2) return false;
	}
	return true;
}

/**
 *  endswith using comp function
 *
 *  test if the elements in [first1, last1) endswith the elements in [first2, last2)
 *  by jadesoul @ 2010-9-30
 *
 *  usage sample: cout<<boolalpha<<endswith(p, p+12, q, q+5, equal_to<char>());
*/
template <  class InputIterator1,
class InputIterator2,
class Function  >
bool endswith(InputIterator1 first1,
                    InputIterator1 last1,
                    InputIterator2 first2,
                    InputIterator2 last2,
                    Function comp) {
	ptrdiff_t len1 = distance(first1, last1), len2 = distance(first2, last2);
	if (len1 < len2) return false;
	while (first2 != last2) {
		if (!comp(*--last1 , *--last2)) return false;
	}
	return true;
}

#endif /* ENDSWITH_H_1324966538_22 */
