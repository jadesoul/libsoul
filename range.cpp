/**
 * File: range.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 21:21:23.063000
 * Written In: Peking University, beijing, China
 */

#include "range.h"

/**
  * range -- Interval types implementation
  *
  * range use start, stop and step to stand for a range
  * it takes a range expression as parameter
  * the format of range expression is like python
  * example: [0:1], [3:], [10:-1], [1:10:2]
  */

range __tmp_range;

range::range(const string& range_expr) {
	construct_from_str(range_expr);
}

range& range::operator =(const string& range_expr) {
	range& me=*this;
	me.construct_from_str(range_expr);
	return me;
}

// inline bool range::very_begin() const {
	// return start==first;    //return if start is the very beginning of the range
// }
// inline bool range::very_end() const {
	// return stop==last;    //return if stop is the very end of the range
// }

// void range::operator ()(const string& range_expr) {
	// construct_from_str(range_expr);
// }

ostream& operator<<(ostream& out, const range& r) {
	out<<"range("<<r.start<<":"<<r.stop<<":"<<r.step<<") = ";
	
	if ((r.start==r.stop) || (r.start<r.stop AND r.step<0)
		|| (r.start>r.stop AND r.step>0)) return out<<"[]";
	
	bool a= (r.start==r.first || r.start==r.last);
	bool b= (r.stop==r.last || r.stop==r.first);
	if (a || b) {
		out<<"[ ";
		
		if (r.start==r.first) out<<"-Limit";
		else if (r.start==r.last) out<<"+Limit";
		else out<<r.start;
		
		out<<" ... ";
		
		if (r.stop==r.first) out<<"-Limit";
		else if (r.stop==r.last) out<<"+Limit";
		else out<<r.stop;
		
		out<<" , "<<r.step;
		return out<<" )"<<endl;
	}
	out<<"[";
	if (r.stop>r.start AND r.step>0)
		for (int i=r.start; i<r.stop; i+=r.step) out<<i<<", ";
	else if (r.stop<=r.start AND r.step<0)
		for (int i=r.start; i>r.stop; i+=r.step) out<<i<<", ";
	out<<"]"<<endl;

	return out;
}

vec_int range::to_vec() {
	vec_int vec;
	if (stop>start AND step>0)
		for (int i=start; i<stop; i+=step) vec.push_back(i);
	else if (stop<=start AND step<0)
		for (int i=start; i>stop; i+=step) vec.push_back(i);
	return vec;
}

void range::construct_from_str(const string& range_expr) {
	string deli=":";
	typedef vector<pair<string::const_iterator, string::const_iterator> > result_type;
	result_type nums(split(range_expr.begin(), range_expr.end(), deli.begin(), deli.end()));
	int nums_size=nums.size();
	assert( nums_size==2 || nums_size==3 );
	ptrdiff_t len_a=distance(nums[0].first, nums[0].second);
	if (len_a>0) {
		string s_start(nums[0].first, nums[0].second);
		start = atoi( s_start.c_str() );
	} else start=first;
	
	ptrdiff_t len_b=distance(nums[1].first, nums[1].second);
	if (len_b>0) {
		string s_stop(nums[1].first, nums[1].second);
		stop = atoi( s_stop.c_str() );
	} else stop=last;

	if (nums_size==2) step=1;
	else {
		string s_step(nums[2].first, nums[2].second);
		step = atoi( s_step.c_str() );
	}
	if (step==0) step=1;
	if (start==first && stop==last && step<0) {
		swap(start, stop);
	}
}

typedef range rg;
#define RG __tmp_range=

