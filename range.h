#ifndef RANGE_H_1356528080_44
#define RANGE_H_1356528080_44
/**
 * File: range.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 21:21:20.443000
 * Written In: Peking University, beijing, China
 */

#include "bootstrap.h"
#include "split.h"
#include "slice.h"

/**
  * range -- Interval types implementation
  *
  * range use start, stop and step to stand for a range
  * it takes a range expression as parameter
  * the format of range expression is like python
  * example: [0:1], [3:], [10:-1], [1:10:2]
  */

class range {
public:
	int start;
	int stop;
	int step;
	const static int first=min_sint4;
	const static int last=max_sint4;

	range(int start, int stop, int step=1): start(start), stop(stop), step(step) {}
	range(int len=0) : start(0), stop(len), step(1) {}
	range(const string& range_expr);
	range& operator =(const string& range_expr);
	inline bool very_begin() const { return start==first; }
	inline bool very_end() const { return stop==last; }
	inline void operator ()(const string& range_expr) { construct_from_str(range_expr); }
	friend ostream& operator<<(ostream& out, const range& r);
	vec_int to_vec();
private:
	void construct_from_str(const string& range_expr);
	
};

extern range __tmp_range;

typedef range rg;
#define RG __tmp_range=

/**
 *  slice -- slice a big container by a range to get a smaller one (will copy a new one)
 *
 *  by jadesoul @ 2010-10-1
 *  return a new container
*/

//improve slice
template <  class Container >
inline Container slice(Container& c, const range& r) {
	return slice(c, r.start, r.stop, r.step);
}

#endif /* RANGE_H_1356528080_44 */
