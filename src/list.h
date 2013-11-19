#ifndef LIST_H_1357754018_39
#define LIST_H_1357754018_39
/**
 * File: list.h
 * Description: 
 *
 * Copyright (c) 2010-2013 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-10 01:53:38.386874
 * Written In: Peking University, beijing, China
 */

#include "bootstrap.h"
#include "algorithms.h"

#include "str.h"
#include "set.h"


// template<class element, class container=std::list<element> >
template<class element, class container=std::vector<element> >
class list : public container {
public:
	typedef element value_type;
	typedef typename container::iterator iterator;
	typedef typename container::const_iterator citerator;
	typedef typename container::reverse_iterator riterator;
	typedef typename container::const_reverse_iterator criterator;
	
public:
	// for iterators
	inline iterator begin() { return container::begin(); }
	inline iterator end() { return container::end(); }
	inline riterator rbegin() { return container::rbegin(); }
	inline riterator rend() { return container::rend(); }
	
	inline citerator begin() const { return container::begin(); }
	inline citerator end() const { return container::end(); }
	inline criterator rbegin() const { return container::rbegin(); }
	inline criterator rend() const { return container::rend(); }
	
	// for size query
	inline const uint size() const { return container::size(); }
	inline void resize(const uint& n) const { return container::resize(n); }
	inline const bool empty() const { return container::empty(); }
	
	// for pos to iter
	inline iterator iter(const int& i) { return ((i<0)?end():begin())+i; }
	inline iterator jter(const int& i) { return ((i<=0)?end():begin())+i; }
	inline citerator iter(const int& i) const { return ((i<0)?end():begin())+i; }
	inline citerator jter(const int& i) const { return ((i<=0)?end():begin())+i; }
	
	inline riterator riter(const int& i) { return ((i<0)?rend():rbegin())+i; }
	inline riterator rjter(const int& i) { return ((i<=0)?rend():rbegin())+i; }
	inline criterator riter(const int& i) const { return ((i<0)?rend():rbegin())+i; }
	inline criterator rjter(const int& i) const { return ((i<=0)?rend():rbegin())+i; }
	
	/**************************************************
	constructors:
	**************************************************/
	//init a list from another container
	//template<class AnotherContainer>
	//list(const AnotherContainer& con):container(con.begin(), con.end()) {}
	
	//init a list from another container, using selector
	// template<class AnotherContainer, class Selector>
	// list(const AnotherContainer& con) {
		// Selector selector;
		// for_iter(it, AnotherContainer, con) append(selector(*it));
	// }
	
	//init a list from iterators
	template<class Iterator>
	list(Iterator b, Iterator e):container(b, e) {}
	
	// init list from a list of values
	template<class T1, class T2, class T3>
	inline list(const T1& t1, const T2& t2, const T3& t3) {
		append(t1).append(t2).append(t3);
	}
	template<class T1, class T2, class T3, class T4>
	list(const T1& t1, const T2& t2, const T3& t3, const T4& t4) {
		append(t1).append(t2).append(t3).append(t4);
	}
	template<class T1, class T2, class T3, class T4, class T5>
	list(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5) {
		append(t1).append(t2).append(t3).append(t4).append(t5);
	}
	template<class T1, class T2, class T3, class T4, class T5, class T6>
	list(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6) {
		append(t1).append(t2).append(t3).append(t4).append(t5).append(t6);
	}
	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7>
	list(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6, const T7& t7) {
		append(t1).append(t2).append(t3).append(t4).append(t5).append(t6).append(t7);
	}
	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8>
	list(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6, const T7& t7, const T8& t8) {
		append(t1).append(t2).append(t3).append(t4).append(t5).append(t6).append(t7).append(t8);
	}
	template<class T1, class T2, class T3, class T4, class T5, class T6, class T7, class T8, class T9>
	list(const T1& t1, const T2& t2, const T3& t3, const T4& t4, const T5& t5, const T6& t6, const T7& t7, const T8& t8, const T9& t9) {
		append(t1).append(t2).append(t3).append(t4).append(t5).append(t6).append(t7).append(t8).append(t9);
	}
	
	list() {}
	list(const list& r):container(r) {};
	list(uint n, const element& e):container(n, e) {};
	list(const set<element>& r):container(r.begin(), r.end()) {};
	list(const container& r):container(r) {};
	list(iterator begin, iterator end):container(begin, end) {}
	list(citerator begin, citerator end):container(begin, end) {}
	list(riterator begin, riterator end):container(begin, end) {}
	list(criterator begin, criterator end):container(begin, end) {}
	list(const element* begin, const element* end):container(begin, end) {}
	
	/**************************************************
	output operator: <<
	**************************************************/
	ostream& save(ostream& o) const {
		uint n=size();
		o<<"[ ";
		for_n(i, n) {
			o<<at(i);
			if (i!=n-1) o<<',';
			o<<' ';
		}
		return o<<']';
	}
	friend ostream& operator<<(ostream& o, const list& l) {
		return l.save(o);
	}

	ostream& save(ostream& o) {
		uint n=size();
		o<<"[ ";
		for_n(i, n) {
			o<<at(i);
			if (i!=n-1) o<<',';
			o<<' ';
		}
		return o<<']';
	}
	friend ostream& operator<<(ostream& o, list& l) {
		return l.save(o);
	}
	/**************************************************
	assign operator: =
	**************************************************/
	// inline list& operator=(const list& r) {
		// return assign(r);
	// }
	// inline list& assign(const list& r) {
		// con=r.con;
		// return *this;
	// }
	
	/**************************************************
	bool expressions:	== != > >= < <=
	**************************************************/
	// bool operator==(const list& r) {
		// if (this==&r) return true;
		// if (size()!=r.size()) return false;
		// return std::equal(begin(), end(), r.begin());
	// }
	// bool operator!=(const list& r) {
		// return !(*this==r);
	// }
	// bool operator>(const list& r) {
		// return size()>r.size();
	// }
	// bool operator<=(const list& r) {
		// return !(*this>r);
	// }
	// bool operator<(const list& r) {
		// return size()<r.size();
	// }
	// bool operator>=(const list& r) {
		// return !(*this<r);
	// }
	
	/**************************************************
	operators:	+= + *= *
	**************************************************/
	inline list& operator+=(const list& r) {
		return this->extend(r);
	}
	inline list operator+(const list& r) {
		return clone().extend(r);
	}
	inline list& operator*=(const uint& n) {
		if (n==0) {
			clear();
		} else if (n!=1) {
			reserve(size()*(n-1));
			::repeat(begin(), end(), inserter(*this, end()), n);
		}
		return *this;
	}
	inline list operator*(const uint& n) {
		return clone()*=n;
	}
	
	/**************************************************
	[] and at
	**************************************************/
	// for elements selection, using base class method, for speed
	inline element& operator [](uint i) {
		// return elem(i);
		return container::operator[](i);
	}
	
	inline const element& operator [](uint i) const {
		// return elem(i);
		return container::operator[](i);
	}
	
	inline element& at(uint i) {
		return container::at(i);
	}
	
	inline const element& at(uint i) const {
		return container::at(i);
	}
	
	// for element selection supporting nagtive index
	inline element& elem(int i) {
		return *iter(i);
	}
	
	inline const element& elem(int i) const {
		return *iter(i);
	}
	
	inline element& operator()(int i) {
		return elem(i);
	}
	
	inline const element& operator()(int i) const {
		return elem(i);
	}
	
	// for slice
	inline list operator()(const int& i, const int& j) {
		return list(iter(i), jter(j));
	}
	
	// for slice uint
	inline list operator()(const uint& i, const uint& j) {
		return list(begin()+i, begin()+j);
	}

	// inline list operator()(const int& start, const int& stop, const int& step) {//TODO
		// return list(iter(i), jter(j));
	// }
	
	inline list head(const int& j) {
		return list(begin(), jter(j));
	}
	
	inline list tail(const int& i) {
		return list(iter(i), end());
	}
	
	/**************************************************
	contains:	x.contains(y) <==> y in x
	**************************************************/
	inline bool contains(const element& r) {
		return std::search(begin(), end(), &r, (&r)+1)!=end();
	}
	
	/**************************************************
	del:	x.del(i) <==> del x[i]
	**************************************************/
	list& del(const int& i=0) {
		erase(iter(i));
		return *this;
	}
	
	/**************************************************
	del:	x.del(i, j) <==> del x[i:j]
		Use of negative indices is also supported.
	**************************************************/
	list& del(const int& i, const int& j) {
		erase(iter(i), jter(j));
		return *this;
	}

	uint tohash() {
		return (uint)this;
	}

	/**************************************************
	append:	L.append(object)
			append object to end
	**************************************************/
	// for modifiers
	inline list& append(const element& r) {
		container::push_back(r);
		return *this;
	}
	
	/**************************************************
	clear:	L.clear()
			clear all
	**************************************************/
	inline list& clear() {
		container::clear();
		return *this;
	}

	/**************************************************
	count:	L.count(value) -> integer
			return number of occurrences of value
	**************************************************/
	inline uint count(const element& e, int start=0, int end=0) {
		return ::count(iter(start), jter(end), (&e), (&e)+1);
	}

	/**************************************************
	extend:	L.extend(iterable)
			extend list by appending elements from the iterable
	**************************************************/
	inline list& extend(const list& r) {
		insert(end(), r.begin(), r.end());
		return *this;
	}
	template<class Iterator>
	inline list& extend(Iterator b, Iterator e) {
		container::insert(end(), b, e);
		return *this;
	}

	/**************************************************
	find:	L.find(value, [start, [stop]]) -> integer
			return first index of value
	rfind:	L.find(value, [start, [stop]]) -> integer
			return the last index of value
	**************************************************/
	inline int find(const list& sub, int start=0, int end=0) const {
		citerator a=iter(start), b=jter(end);
		if (a>=b) return -1;
		citerator c=std::search(a, b, sub.begin(), sub.end());
		return (c==b)?-1:c-a;
	}

	inline int rfind(const list& sub, int start=0, int end=0) const {
		uint l=size();
		start=(start>0)?l-1-start:-start-l;
		end=(end>0)?l-1-end:-end-l;
		criterator a=rjter(end), b=riter(start);
		if (a>=b) return -1;
		criterator c=std::search(a, b, sub.rbegin(), sub.rend());
		return (c==b)?-1:(b-c)-sub.size()-1;
	}
	
	/**************************************************
	insert:	L.insert(index, object)
			insert object before index
	**************************************************/
	inline list& insert(const element& r, int i=0) {
		insert(iter(i), r);
		return *this;
	}

	/**************************************************
	push:	L.push(item) -> L
			append an item at last
	pop:		L.pop() -> item
			remove and return item at last
	**************************************************/
	inline list& push(const element& r) {
		return append(r);
	}
	
	inline element& front() { return container::front(); }
	inline element& front() const { return container::front(); }
	inline element& back() { return container::back(); }
	inline element& back() const { return container::back(); }
	inline void pop_back() { container::pop_back(); }
	
	inline element pop() {
		// if (empty()) return NULL; //TODO
		assert(!empty());
		element tmp=back();
		pop_back();
		return tmp;
	}
	
	/**************************************************
	inject:	L.inject(item) -> L
			insert an item at first
	shift:	L.shift() -> item
			remove and return item at first
	**************************************************/
	inline list& inject(const element& r) {
		return insert(r);
	}
	
	inline list& prepend(const element& r) {
		return insert(r);
	}
	
	inline element shift() {
		// if (empty()) return NULL; //TODO
		assert(!empty());
		element tmp=front();
		del(0);
		return tmp;
	}

	/**************************************************
	index:	L.index(value) -> int
			return the first position if found, or -1
			O(n)
	**************************************************/
	int index(const element& e) const {
		uint l=size();
		for_n(i, l) if ((*this)[i]==e) return i;
		return -1;
	}
	int rindex(const element& e) const {
		uint l=size();
		for_n(i, l) if ((*this)[l-1-i]==e) return l-1-i;
		return -1;
	}
	
	/**************************************************
	remove:	L.remove(value)
			remove first occurrence of value
	**************************************************/
	inline list& remove(const element& e) {
		uint i=index(e);
		if (i!=-1) del(i);
		return *this;
	}
	
	/**************************************************
	reverse:		L.reverse() -> L
				reverse *IN PLACE*
	reversed:	L.reversed() -> new L
				reverse with copy
	**************************************************/
	list& reverse() {
		std::reverse(begin(), end());
		return *this;
	}
	
	inline list reversed() {
		return list(rbegin(), rend());
	}
 
	/**************************************************
	sort:	L.sort(cmp=None, key=None, reverse=False)
			stable sort *IN PLACE*;
			cmp(x, y) -> -1, 0, 1
	sorted:	L.sort(cmp=None, key=None, reverse=False) -> new L
			return a sorted copy
	**************************************************/
	// template<class Selector>//TODO
	
	list& sort() {
		std::sort(begin(), end());
		return *this;
	}
	inline list sorted() {
		return clone().sort();
	}
	
	list& rsort() {
		std::sort(rbegin(), rend());
		return *this;
	}
	inline list rsorted() {
		return clone().rsort();
	}
	
	/*************************************************
	L.copy() -> new L
		Return a shadow copy of list L, is the same to L
		in the first level
	*************************************************/
	inline list copy() {
		return list(*this);
	}
	
	/*************************************************
	L.clone() -> new L
		Return a deep copy of list L, which is a clone
		of L. The same in all level
	*************************************************/
	inline list clone() {
		return list(*this);
	}
	
	// foreach
	template<class Function>
	void foreach(Function f) {
		std::for_each(begin(), end(), f);
	}
	
	template<class Function>
	void map(Function f) {//map a function to all elements
		std::for_each(begin(), end(), f);
	}
	
	template<class Function, class Selector>
	void map(Function f) {//map a function to all elements
		Selector selector;
		list& me=*this;
		for_iter(it, list, me) f(selector(*it));
	}
	
	template<class Function>
	inline list& filter(Function f) {//filter elements, remain only elements that f() returns true
		list& me=*this;
		uint n=size(), j;
		for_n(i, n) {
			j=n-1-i;
			if (!f(me[j])) del(j);
		}
		return me;
	}
	
	template<class Function>
	inline list filtered(Function f) {//filter elements, remain only elements that f() returns true
		return clone().filter(f);
	}
	
	// use g as a glue to join this list
	inline str glue(const str& g) {
		return g.join(*this);
	}
};

#define Macro__typedefs_of_list__Element_Name_Alias(E, N, A)\
typedef ::list<E> N;\
typedef N A;

Macro__typedefs_of_list__Element_Name_Alias(char, listchar, Lchar)
Macro__typedefs_of_list__Element_Name_Alias(uchar, listuchar, Luchar)
Macro__typedefs_of_list__Element_Name_Alias(int, listint, Lint)
Macro__typedefs_of_list__Element_Name_Alias(uint, listuint, Luint)
Macro__typedefs_of_list__Element_Name_Alias(short, listshort, Lshort)
Macro__typedefs_of_list__Element_Name_Alias(ushort, listushort, Lushort)
Macro__typedefs_of_list__Element_Name_Alias(float, listfloat, Lfloat)
Macro__typedefs_of_list__Element_Name_Alias(double, listdouble, Ldouble)
Macro__typedefs_of_list__Element_Name_Alias(str, liststr, Lstr)

#endif /* LIST_H_1357754018_39 */
