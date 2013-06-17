#ifndef SLICE_H_1324966077_89
#define SLICE_H_1324966077_89
/**
 * File: slice.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:07:57.894000
 * Written In: Peking University, beijing, China
 */

#include "includes.h"


/**
 *  slice -- slice a big container by a range to get a smaller one (will copy a new one)
 *
 *  by jadesoul @ 2010-10-1
 *  return a new container
*/

#include <bootstrap.h>

template <  class Container >
Container slice(Container& c, int start, int stop, int step) {
	const static int first=min_sint4;
	const static int last=max_sint4;
	typedef typename Container::iterator iterator;
	typedef typename Container::reverse_iterator reverse_iterator;
	assert( step!=0 );
	int len=c.size();
	if (len==0) return Container();

	
	if (step>0 AND start==first AND stop==last) {
		start=0;
		stop=len;
	} else if (step<0 AND start==last AND stop==first) {
		start=len-1;
		stop=-1;
	} else {
		//adjust start
		if (start<0)
			if (start+len<0) start=0;
			else start+=len;
		else if (start>len) start=len;

		//adjust stop
		if (stop<0)
			if (stop+len<0) stop=0;
			else stop+=len;
		else if (stop>len) stop=len;

		if (start==stop) return Container();

		//empty situation
		if ((start<stop AND step<0) || (start>stop AND step>0)) return Container();
	}
	if (step==1) {
		iterator first=c.begin(), last=first;
		if (start!=0)
			advance(first, start);
		if (stop==len)
			last=c.end();
		else
			advance(last, stop);
		return Container(first, last);
	} else if (step==-1) {
		start=len-start;
		stop=len+stop+1;
		reverse_iterator first=c.rbegin(), last=first;
		if (start!=0)
			advance(first, start);
		if (stop==len)
			last=c.rend();
		else
			advance(last, stop);
		return Container(first, last);
	} else {
		Container ret;
		if (start<stop AND step>0)
			for (int i=start; i<stop; i+=step) ret.push_back(c[i]);
		if (start>stop AND step<0)
			for (int i=start; i>stop; i+=step) ret.push_back(c[i]);
		return ret;
	}
}

#endif /* SLICE_H_1324966077_89 */
