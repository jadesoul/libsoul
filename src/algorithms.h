#ifndef ALGORITHMS_H_1324965987_26
#define ALGORITHMS_H_1324965987_26
/**
 * File: algorithms.hpp
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-27 14:06:27.255000
 * Written In: Peking University, beijing, China
 */

/**
 *  slice -- slice a big container by a range to get a smaller one (will copy a new one)
 *
 *  by jadesoul @ 2010-10-1
 *  return a new container
*/

#include "bootstrap.h"

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



/**
 *  startswith
 *	
 *  test if the elements in [first1, last1) startswith the elements in [first2, last2)
 *  by jadesoul @ 2010-9-30
 *	
 *  usage sample: cout<<boolalpha<<startswith(p, p+12, q, q+5);
*/
template<class InputIterator1, class InputIterator2>
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
bool startswith(	InputIterator1 first1,
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


/**
 *  endswith
 *
 *  test if the elements in [first1, last1) endswith the elements in [first2, last2)
 *  by jadesoul @ 2010-9-30
 *
 *  usage sample: cout<<boolalpha<<endswith(p, p+12, q, q+5);
*/
template <  class InputIterator1,
class InputIterator2	>
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


/**
 *  split -- split a big container into many subcontainers by a specified small delimiter container
 *
 *  by jadesoul @ 2010-10-1
 *  return a vector consists of pairs, each pair has a begin iterator
 *  and a end iterator of the prime container
*/
template <  class InputIterator1,
class InputIterator2	>
vector<pair<InputIterator1, InputIterator1> > split(
	InputIterator1 first1,
	InputIterator1 last1,
	InputIterator2 first2,
	InputIterator2 last2	) {
	vector<pair<InputIterator1, InputIterator1> > result;
	pair<InputIterator1, InputIterator1> tmp;

	ptrdiff_t len1 = distance(first1, last1), len2 = distance(first2, last2);
	if (len1 < len2) return result;
	InputIterator1 start = first1, stop = search(first1, last1, first2, last2);
	if (stop==last1) return result;
	do {
		result.push_back( make_pair(start, stop) );
		advance(stop, len2);
		start = stop;
		stop = search(start, last1, first2, last2);
	} while (stop!=last1);
	assert( stop==last1 );
	result.push_back( make_pair(start, last1) );
	return result;
}

// Better Version
template <class SequenceIterator, class DelimiterIterator, class OutputIterator>
OutputIterator split(SequenceIterator sbegin, SequenceIterator send, DelimiterIterator dbegin, DelimiterIterator dend, OutputIterator result) {
	ptrdiff_t slen = distance(sbegin, send), dlen = distance(dbegin, dend);
	if (slen<dlen) return result;
	SequenceIterator start = sbegin, stop=search(sbegin, send, dbegin, dend);
	if (stop==send) return result;
	do {
		*result++=start;
		*result++=stop;
		advance(stop, dlen);
		start = stop;
		stop = search(start, send, dbegin, dend);
	} while (stop!=send);
	assert(stop==send);
	*result++=start;
	*result++=send;
	return result;
}

// Container Version
template <class SequenceContainer, class DelimiterContainer, class OutputContainer>
inline OutputContainer& split(SequenceContainer& seq, DelimiterContainer& deli, OutputContainer& out) {
	split(seq.begin(), seq.end(), deli.begin(), deli.end(), inserter(out, out.end()));
	return out;
}


/**
 *  join -- join all elememts in a Fragments container with a Glue container.
 *  That is join some Fragments with Glue between every two Fragments.
 *  In this case, each element in the Fragments is still a container, each element
 *  in this container is similiar to each element in the Glue.
 *  by jadesoul @ 2011-12-29
 *  return the end iterator of the result
 */

// List_join_ListOfList
// Elememt_join_List
template <class GlueInputIterator, class FragmentsInputIterator, class OutputIterator>
OutputIterator join(GlueInputIterator gbegin, GlueInputIterator gend, FragmentsInputIterator fbegin, FragmentsInputIterator fend, OutputIterator result) {
	
	// for special cases, move fast
	if (fbegin==fend) return result;
	
	// copy first frag
	result=std::copy(fbegin->begin(), fbegin->end(), result);
	
	// advance(result, distance(fbegin->begin(), fbegin->end()));
	// iterator_traits<FragmentsInputIterator>::value_type::iterator begin, end;
	
	// begin=fbegin->begin(), end=fbegin->end();
	
	
	GlueInputIterator stump=gbegin;
	while (++fbegin!=fend) {
		// insert a glue before each frag
		while (gbegin!=gend) *result++=*gbegin++;
		gbegin=stump;
		// copy frag
		result=std::copy(fbegin->begin(), fbegin->end(), result);
	}
	return result;
}

// Container Version
template <class GlueContainer, class FragmentsContainer, class OutputContainer>
inline OutputContainer& join(const GlueContainer& glue, const FragmentsContainer& fragments, OutputContainer& out) {
	join(glue.begin(), glue.end(), fragments.begin(), fragments.end(), inserter(out, out.end()));
	return out;
}

/**
 *  join -- join all elememts in a Fragments container with a Glue container.
 *  That is join some Fragments with Glue between every two Fragments.
 *  In this case, each element in the Fragments is similiar to each element in the Glue.
 *  by jadesoul @ 2011-12-28
 *  return the end iterator of the result
 */

// List_join_List
// Elememts_join_Elememts
template <class GlueInputIterator, class FragmentsInputIterator, class OutputIterator>
OutputIterator join(GlueInputIterator gbegin, GlueInputIterator gend, FragmentsInputIterator fbegin, FragmentsInputIterator fend, OutputIterator result, int /*flag*/) {
	
	// for special cases, move fast
	if (gbegin==gend) return std::copy(fbegin, fend, result);
	if (fbegin==fend) return result;
	
	// copy first frag
	*result++=*fbegin++;
	GlueInputIterator stump=gbegin;
	while (fbegin!=fend) {
		// insert a glue before each frag
		while (gbegin!=gend) *result++=*gbegin++;
		gbegin=stump;
		// copy frag
		*result++=*fbegin++;
	}
	return result;
}


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



//cardinal_sort (ji shu sort)
//hill_sort (xi er sort)


//heap_sort
//most bad: O(nlogn)
//average: O(nlogn)

template<class Container>
void heap_sort(Container& c) {
	make_heap(c.begin(), c.end());
	sort_heap(c.begin(), c.end());
}

template<class RandomAccessIterator>
void heap_sort(RandomAccessIterator begin, RandomAccessIterator end) {
	RandomAccessIterator i, j;
	make_heap(begin, end);
	sort_heap(begin, end);
}



//merge_sort
/*
  * tmp is a temporary helper container which at least has the same size of region [first, last)
  */

//O(nlogn)
template <  class RandomAccessIterator >
void merge_sort(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator tmp) {
	assert( last>first );
	ptrdiff_t len=last-first;
	if (len>1) {
		ptrdiff_t half_len=len/2;
		RandomAccessIterator mid=first+half_len;
		merge_sort(first, mid, tmp);
		merge_sort(mid, last, tmp+half_len);
		merge(first, mid, mid, last, tmp);
		copy(tmp, tmp+len, first);
	}
}

/*
  * compare function version
  */
template <  class RandomAccessIterator, class Compare >
void merge_sort(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator tmp, Compare cmp) {
	assert( last>first );
	ptrdiff_t len=last-first;
	if (len>1) {
		ptrdiff_t half_len=len/2;
		RandomAccessIterator mid=first+half_len;
		merge_sort(first, mid, tmp, cmp);
		merge_sort(mid, last, tmp+half_len, cmp);
		merge(first, mid, mid, last, tmp, cmp);
		copy(tmp, tmp+len, first);
	}
}

/*
 * improvement of merge sort
 * by divide the container into 4 parts
 */
template <  class RandomAccessIterator >
void merge_sort_improved(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator tmp) {
	assert( last>first );
	ptrdiff_t len=last-first;
	if (len<=16) {
		insert_sort(first, last);
	} else {
		ptrdiff_t len_half=len/2;
		RandomAccessIterator mid=first+len_half;

		ptrdiff_t len_left=mid-first;
		ptrdiff_t len_quarter_left=len_left/2;
		RandomAccessIterator quarter_left=first+len_quarter_left;
		merge_sort_improved(first, quarter_left, tmp);
		merge_sort_improved(quarter_left, mid, tmp+len_quarter_left);

		ptrdiff_t len_right=last-mid;
		ptrdiff_t len_quarter_right=len_right/2;
		RandomAccessIterator quarter_right=mid+len_quarter_right;
		merge_sort_improved(mid, quarter_right, tmp+len_half);
		merge_sort_improved(quarter_right, last, tmp+len_half+len_quarter_right);

		merge(first, quarter_left, quarter_left, mid, tmp);
		merge(mid, quarter_right, quarter_right, last, tmp+len_half);
		merge(tmp, tmp+len_half, tmp+len_half, tmp+len, first);
	}
}


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


//insert_sort
// O(n^2)

template <  class RandomAccessIterator >
void insert_sort(RandomAccessIterator begin, RandomAccessIterator end) {
	RandomAccessIterator i, j;
	for (i=begin+1; i<end; ++i) {
		for (j=i; j>begin && *i < *(j-1); --j) ;
		if (j!=i) rotate(j, i, i+1);
	}
}

//using binary search when insert
// O(n log n)

template <  class RandomAccessIterator >
void binary_insert_sort(RandomAccessIterator begin, RandomAccessIterator end) {
	RandomAccessIterator i, low, high, mid;
	for (i=begin+1; i<end; ++i) {
		low=begin;
		high=i-1;
		while (low<high) {
			mid=low+(high-low)/2;
			if (*mid==*i) {
				low=mid;//let low represent the result
				break;
			}
			else if (*mid<*i) low=mid+1;
			else high=mid-1;
		}
		if (low!=i) rotate(low, i, i+1);
	}
}


//bubble_sort
// O(n^2)
template < class RandomAccessIterator >
void bubble_sort(RandomAccessIterator first, RandomAccessIterator last) {
	typedef RandomAccessIterator iter_t;
	for (iter_t end=last-1; first!=end; --end) {
		for (iter_t it=first; it!=end; ++it) {
			if (*it > *(it+1)) iter_swap(it, it+1) ;
		}
	}
}


//select_sort
//select the smallest element and exchange it with the n-th element
//O(n^2)

template< class iterator >
void select_sort(iterator begin, iterator end) {
	for (iterator round=begin; round<end-1; ++round) {
		iterator min=round;
		for (iterator it=round+1; it<end; ++it)
			if (*it<*min) min=it;
		iter_swap(round, min);
	}
}


//exchange_sort
//O(n^2)
template< class iterator >
void exchange_sort(iterator begin, iterator end) {
	for (iterator now=begin; now<end-1; ++now) {
		for (iterator it=now+1; it<end; ++it)
			if (*now>*it) iter_swap(now, it);
	}
}


/* search */
/* graph algorithms  */
//dijkstra with priority queen


template<class T, class I>
inline T sum(I begin, I end) {
	return std::accumulate(begin, end, T());
}

template<class C>
inline typename C::value_type sum(const C& c) {
	return sum<typename C::value_type>(c.begin(), c.end());
}


/* dynamic_programming */
//max_sub_sum
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


//edit_distance
/*
[first, last) indicades the string a
[begin, end) indicades the string b
return the edit distance of a, b
*/
template<class iterator>   //RandomAccessIterator
uint edit_distance(iterator first, iterator last, iterator begin, iterator end) {
	uint m=last-first;
	uint n=end-begin;
	assert(m>=0 AND n>=0);
	iterator& a=first;
	iterator& b=begin;
	uint r;
	if (m==0) { r=n; }
	else if (n==0) { r=m; }
	else {
		uint** d=new uint*[m+1];	//动态规划表格
		for_n(i, m+1) d[i]=new uint[n+1];

		for_n(i, m+1) d[i][0]=i;
		for_n(j, n+1) d[0][j]=j;

		for_tany(uint, i, 1, m) {
			for_tany(uint, j, 1, n) {
				uint x=d[i-1][j]+1; //删除，上方
				uint y=d[i][j-1]+1; //插入，左方
				uint z=d[i-1][j-1]+(*(a+i-1)==*(b+j-1)?0:1); //替换，左上方
				uint t=(x<y?x:y);
				d[i][j]=(t<z?t:z);
			}
		}
		r=d[m][n];

		for_n(i, m+1) delete [] d[i];
		delete [] d;
	}
	return r;
}


//find_iter
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


//min
// template<class T> 
// inline const T& min(const T& a, const T& b) {
	// return a<b ? a : b;
// }

template<class T> 
inline const T& min(const T& a, const T& b, const T& c) {
	return min(min(a, b), c);
}


//max
// template<class T>
// inline const T& max(const T& a, const T& b) {
	// return a>b ? a : b;
// }

template<class T>
inline const T& max(const T& a, const T& b, const T& c) {
	return max(max(a, b), c);
}


/**
 *  backtracking_8queen
*/

/**
 *  backtracking_01bag
*/

/**
 *  backtracking_travel_sales_man
*/

/**
 *  dynamic_programming_sales_man
*/



/*
STL Algorithms
<algorithm>
Non-modifying sequence operations:
for_each		Apply function to range (template function)
find			Find value in range (function template)
find_if		 Find element in range (function template)
find_end	Find last subsequence in range (function template)
find_first_of	Find element from set in range (function template)
adjacent_find	Find equal adjacent elements in range (function template)
count		   Count appearances of value in range (function template)
count_if	Return number of elements in range satisfying condition (function template)
mismatch	Return first position where two ranges differ (function template)
equal		   Test whether the elements in two ranges are equal (function template)
search		  Find subsequence in range (function template)
search_n	Find succession of equal values in range (function template)


Modifying sequence operations:
copy			Copy range of elements (function template)
copy_backward	Copy range of elements backwards (function template)
swap			Exchange values of two objects (function template)
swap_ranges	Exchange values of two ranges (function template)
iter_swap	Exchange values of objects pointed by two iterators (function template)
transform	Apply function to range (function template)
replace		 Replace value in range (function template)
replace_if	Replace values in range (function template)
replace_copy	Copy range replacing value (function template)
replace_copy_if	Copy range replacing value (function template)
fill			Fill range with value (function template)
fill_n		  Fill sequence with value (function template)
generate	Generate values for range with function (function template)
generate_n	Generate values for sequence with function (function template)
remove		  Remove value from range (function template)
remove_if	Remove elements from range (function template)
remove_copy	Copy range removing value (function template)
remove_copy_if	Copy range removing values (function template)
unique		  Remove consecutive duplicates in range (function template)
unique_copy	Copy range removing duplicates (function template)
reverse		 Reverse range (function template)
reverse_copy	Copy range reversed (function template)
rotate		  Rotate elements in range (function template)
rotate_copy	Copy rotated range (function template)
random_shuffle	Rearrange elements in range randomly (function template)
partition	Partition range in two (function template)
stable_partition	 Partition range in two - stable ordering (function template)


Sorting:
sort			Sort elements in range (function template)
stable_sort	Sort elements preserving order of equivalents (function template)
partial_sort	Partially Sort elements in range (function template)
partial_sort_copy	 Copy and partially sort range (function template)
nth_element	Sort element in range (function template)


Binary search (operating on sorted ranges):
lower_bound	Return iterator to lower bound (function template)
upper_bound	Return iterator to upper bound (function template)
equal_range	Get subrange of equal elements (function template)
binary_search	Test if value exists in sorted array (function template)


Merge (operating on sorted ranges):
merge		   Merge sorted ranges (function template)
inplace_merge	Merge consecutive sorted ranges (function template)
includes	Test whether sorted range includes another sorted range (function template)
set_union	Union of two sorted ranges (function template)
set_intersection			Intersection of two sorted ranges (function template)
set_difference	Difference of two sorted ranges (function template)
set_symmetric_difference	Symmetric difference of two sorted ranges (function template)


Heap:
push_heap	   Push element into heap range (function template)
pop_heap	Pop element from heap range (function template)
make_heap	Make heap from range (function template)
sort_heap	Sort elements of heap (function template)


Min/max:
min			 Return the lesser of two arguments (function template)
max			 Return the greater of two arguments (function template)
min_element	Return smallest element in range (function template)
max_element	Return largest element in range (function template)
lexicographical_compare	 Lexicographical less-than comparison (function template)
next_permutation	 Transform range to next permutation (function template)
prev_permutation	 Transform range to previous permutation (function template)

<numeric>
accumulate	 Accumulate values in range (function template)
adjacent_difference	 Compute adjacent difference of range (function template)
inner_product	 Compute cumulative inner product of range (function template)
partial_sum	 Compute partial sums of range (function template)
*/

#endif /* ALGORITHMS_H_1324965987_26 */
