#ifndef EDIT_DISTANCE_H_1345772111_72
#define EDIT_DISTANCE_H_1345772111_72
/**
 * File: edit_distance.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-08-24 09:35:11.721000
 * Written In: Peking University, beijing, China
 */
 
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
		uint** d=new uint*[m+1];    //动态规划表格
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

#endif /* EDIT_DISTANCE_H_1345772111_72 */

