#ifndef COMMON_H_1359787116_51
#define COMMON_H_1359787116_51
/**
 * File: common.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-02-02 14:38:36.511000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>

//matrix 2d, each cell is a value
template<class T>
class matrix2d {
protected:
	T* matrix;
	uint row, col;
public:
	matrix2d(uint row, uint col):row(row), col(col) {
		uint n=row*col+1;//in case of row*col==0
		matrix=new T[n];
	}
	inline const T& operator() (uint i, uint j) const {
		assert(i<row AND j<col);
		return matrix[i*col+j];
	}
	inline T& operator() (uint i, uint j) {
		assert(i<row AND j<col);
		return matrix[i*col+j];
	}
	virtual ~matrix2d() {
		delete [] matrix;
	}
};

//matrix 2d in head, each cell holds a ptr to a real cell
//auto deconstruct the active values when matrix deconstruct
template<class T>
class matrix2d_heap : public matrix2d<T*> {
public:
	typedef matrix2d<T*> matrix_base;
protected:
	inline T*& visit(uint i, uint j) {
		T*& p=matrix_base::operator()(i, j);
		if (!p) p=new T;
		assert(p);//make sure alloc success
		return p;
	}//visit a cell, make it active if not active
public:
	matrix2d_heap(uint row, uint col):matrix_base(row, col) {
		uint n=row*col;//for all ptr except the last 1 more
		for_n(i, n) matrix_base::matrix[i]=NULL;//all init as null
	}

	inline bool is_active(uint i, uint j) const { return matrix_base::operator()(i, j)!=NULL; }

	inline T& operator() (uint i, uint j) {
		return *visit(i, j);
	}
	virtual ~matrix2d_heap() {
		uint n=matrix_base::row*matrix_base::col;//for all ptr except the last 1 more
		for_n(i, n) if (matrix_base::matrix[i]) delete matrix_base::matrix[i];//delete the cell in heap
	}
};

template<class A, class B>
class select_first {
public:
	inline const A& operator ()(const pair<A, B>& p) const { return p.first; }
	inline const A& operator ()(const pair<const A, B>& p) const { return p.first; }
	inline const A& operator ()(const pair<A, const B>& p) const { return p.first; }
	inline const A& operator ()(const pair<const A, const B>& p) const { return p.first; }
	inline A& operator ()(pair<A, B>& p) { return p.first; }
	inline A& operator ()(pair<A, const B>& p) { return p.first; }
};

template<class A, class B>
class select_second {
public:
	inline const B& operator ()(const pair<A, B>& p) const { return p.second; }
	inline const B& operator ()(const pair<const A, B>& p) const { return p.second; }
	inline const B& operator ()(const pair<A, const B>& p) const { return p.second; }
	inline const B& operator ()(const pair<const A, const B>& p) const { return p.second; }
	inline B& operator ()(pair<A, B>& p) { return p.second; }
	inline B& operator ()(pair<const A, B>& p) { return p.second; }
};

template<class A, class B, class C>
class select_second_first {
public:
	inline const B& operator ()(const pair<A, const pair<B, C> >& p) const { return p.second.first; }
	inline B& operator ()(pair<A, pair<B, C> >& p) { return p.second.first; }
};

template<class A, class B, class C>
class select_second_second {
public:
	inline const C& operator ()(const pair<A, const pair<B, C> >& p) const { return p.second.second; }
	inline C& operator ()(pair<A, pair<B, C> >& p) { return p.second.second; }
	inline C& operator ()(pair<const A, pair<B, C> >& p) { return p.second.second; }
	inline C& operator ()(pair<const A, pair<const B, C> >& p) { return p.second.second; }
};

template<class T>
class select_myself {
public:
	inline const T& operator ()(const T& t) const { return t; }
	inline T& operator ()(T& t) { return t; }
};

#endif /* COMMON_H_1359787116_51 */
