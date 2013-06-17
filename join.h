#ifndef JOIN_H_1325054147_89
#define JOIN_H_1325054147_89

/**
 * File: join.h
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * 
 * Date: 2011-12-28 14:35:47.895000
 * Written In: Peking University, beijing, China
 */

#include "includes.h"

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




#endif /* JOIN_H_1325054147_89 */
