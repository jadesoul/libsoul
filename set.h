#ifndef SET_H_1356530380_94
#define SET_H_1356530380_94
/**
 * File: set.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 21:59:40.945000
 * Written In: Peking University, beijing, China
 */

#include <bootstrap.h>

template<class element>
class set {
public:
	// typedef std::hash_set<element> container;
	typedef std::set<element> container;
	typedef typename container::iterator iterator;
	typedef typename container::const_iterator citerator;
	typedef typename container::reverse_iterator riterator;
	typedef typename container::const_reverse_iterator criterator;
	
private:
	container con;
	
public:
	//for iterators
	inline iterator begin() { return con.begin(); } 
	inline iterator end() { return con.end(); }
	inline riterator rbegin() { return con.rbegin(); }
	inline riterator rend() { return con.rend(); }
	
	inline citerator begin() const { return con.begin(); } 
	inline citerator end() const { return con.end(); }
	inline criterator rbegin() const { return con.rbegin(); }
	inline criterator rend() const { return con.rend(); }
	
	//for size query
	inline const uint size() const { return con.size(); }
	inline const bool empty() const { return con.empty(); }
	
	/**************************************************
	constructors:
	**************************************************/
	// template<class T1>
	// set(T1& t1) {
		// add(&t1);
	// }
	// template<class T1, class T2>
	// set(T1& t1, T2& t2) {
		// add(&t1);
		// add(&t2);
	// }
	// template<class T1, class T2, class T3>
	// set(T1& t1, T2& t2, T3& t3) {
		// add(&t1);
		// add(&t2);
		// add(&t3);
	// }
	set() {}
	set(const set& r):con(r.con) {}
	// set(iterator begin, iterator end):con(begin, end) {}
	set(citerator begin, citerator end):con(begin, end) {}
	// set(riterator begin, riterator end):con(begin, end) {}
	set(criterator begin, criterator end):con(begin, end) {}
	set(const element*& begin, const element*& end):con(begin, end) {}

	/**************************************************
	output operator: <<
	**************************************************/
	friend inline ostream& operator<<(ostream& out, const set<element>& l) {
		//TODO
		return out<<"[set]"<<endl;
	}
	
	/**************************************************
	assign operator: =
	**************************************************/
	inline set& operator=(const set& r) { return assign(r); }
	inline set& assign(const set& r) { con=r.con; return *this; }
	
	/**************************************************
	bool expressions:	== != > >= < <= ! & &= | |= ^ ^=
	math expressions:	+= + -= -
	**************************************************/
	inline bool operator==(const set& r) { return equals(r); }
	inline bool operator>(const set& r) { return this>&r; }
	inline bool operator<(const set& r) { return this<&r; }
	inline bool operator!=(const set& r) { return !(*this==r); }
	inline bool operator<=(const set& r) { return !(*this>r); }
	inline bool operator>=(const set& r) { return !(*this<r); }
	inline bool operator!() { return empty(); }
	inline set operator &(set& y) { return intersection(y); }
	inline set operator |(set& y) { return unioned(y); }
	inline set operator +(set& y) { return unioned(y); }
	inline set operator -(set& y) { return difference(y); }
	inline set operator ^(set& y) { return crossed(y); }
	inline set& operator &=(set& r) { return intersect(r); }
	inline set& operator |=(set& r) { return unionto(r); }
	inline set& operator +=(set& r) { return unionto(r); }
	inline set& operator -=(set& r) { return differ(r); }
	inline set& operator ^=(set& r) { return cross(r); }
	
	/**************************************************
	add:	Add an element to a set.
			This has no effect if the element is already present.
	**************************************************/
	inline set& add(const element& r) { con.insert(r); return *this; }
	
	/**************************************************
	del:	Delete an element from a set.
			This has no effect if the element is not yet present.
	**************************************************/
	inline set& del(iterator i) { con.erase(i); return *this; }
	inline set& del(const element& e) { con.erase(e); return *this; }
	
	/**************************************************
	find:	Find element iterator from this set.
	**************************************************/
	inline iterator find(const element& e) { return con.find(e); }
	inline citerator find(const element& e) const { return con.find(e); }
	
	/**************************************************
	contains:	x.contains(y) <==> y in x.
	**************************************************/
	inline bool contains(const element& e) const { return find(e)!=end(); }
	
	/**************************************************
	equals:	x.equals(y) <==> x == y.
	**************************************************/
	bool equals(const set& r) const {
		if (this==&r) return true;
		if (size()!=r.size()) return false;
		return std::equal(begin(), end(), r.begin());
	}
	inline uint tohash() {	//TODO
		return 0;
	}
	
	/**************************************************
	clear:	Remove all elements from this set.
	**************************************************/
	inline set& clear() { con.clear(); return *this; }

	/*************************************************
	S.copy() -> new S
		Return a shadow copy of list L, is the same to L
		in the first level
	*************************************************/
	inline set copy() { return set(*this); }
	
	/*************************************************
	S.clone() -> new S
		Return a deep copy of list L, which is a clone
		of L. The same in all level
	*************************************************/
	inline set clone() { return set(); }
	
	/**************************************************
	discard:
		Remove an element from a set if it is a member.
		If the element is not a member, do nothing.
	**************************************************/
	inline set& discard(const element& e) { 
		// iterator i=find(e);
		// if (i!=end()) del(i);
		return del(e);
	}
	
	/**************************************************
	intersect:
		Update a set with the intersection of itself and another.
	intersection:
		Return the intersection of two sets as a new set.
	(i.e. all elements that are in both sets.)
	**************************************************/
	inline set& intersect(const set& r) { return assign(intersection(r)); }
	set intersection(const set& r) {
		set inter;
		for (citerator i(r.begin()), e(r.end()); i!=e; ++i) if (contains(*i)) inter.add(*i);
		return inter;
	}
	
	/**************************************************
	unionto:
		update a set with the union of sets
	unioned:
		Return the union of sets as a new set.
		(i.e. all elements that are in either set.)
	**************************************************/
	inline set& unionto(set& r) { con.insert(r.begin(), r.end()); return *this; }
	inline set unioned(set& r) { return copy().unionto(r); }
	
	/**************************************************
	differ:	
		remove elements from this set which are both 
		in this set and other other set
	difference:	
		Return the difference of two or more sets as a new set.
		(i.e. all elements that are in this set but not the others.)
	**************************************************/
	set& differ(set& r) {
		for (iterator i=r.begin(), e=r.end(), f; i!=e; ++i) {
			f=find(*i);
			if (f!=end()) del(f);
		}
		return *this;
	}
	inline set difference(set& r) { return copy().differ(r); }
	
	/**************************************************
	cross:
		Update a set with the symmetric difference of itself and another.
		remove all in both set and add all this set don't have
	crossed:
		Return the symmetric difference of two sets as a new set.
		(i.e. all elements that are in exactly one of the sets.)
	**************************************************/
	set& cross(set& r) {
		for (iterator i=r.begin(), e=r.end(), f; i!=e; ++i) {
			f=find(*i);
			if (f!=end()) del(f);
			else add(*i);
		}
		return *this;
	}
	inline set crossed(set& r) { return copy().cross(r); }

	/**************************************************
	isdisjoint:
		Return True if two sets have a null intersection.
	**************************************************/
	inline bool isdisjoint(set& r) { return unioned(r).empty(); }
	
	/**************************************************
	issubset:
		Report whether another set contains this set.
	**************************************************/
	bool issubset(set& r) {
		// iterator i=r.con.lower_bound(*begin());
		// if (r.begin()-i>0) return false;
		// iterator j=r.con.upper_bound(*rbegin());
		// if (j>=r.end()) return false;
		// TODO
		return true;
	}
	
	/**************************************************
	issuperset:
		Report whether this set contains another set.
	**************************************************/
	inline bool issuperset(set& r) { return r.issubset(*this); }
	
	/**************************************************
	pop:	
		Remove and return an arbitrary set element.
		just remove and return the first element
	**************************************************/
	inline element pop() {
		iterator i=begin();
		element e=*i;
		del(i);
		return e;
	}
	
	/**************************************************
	remove:	Remove an element from a set;
	**************************************************/
	inline set& remove(const element& e) { return del(e); }
	
	//foreach
	template<class Function>
	inline void foreach(Function f) {
		std::for_each(begin(), end(), f);
	}
};

//typedef set<str> S;
//typedef set<int> IS;
//typedef set<uint> US;

#endif /* SET_H_1356530380_94 */
