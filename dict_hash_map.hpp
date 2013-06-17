#ifndef DICT_HASH_MAP_HPP_1325515224_72
#define DICT_HASH_MAP_HPP_1325515224_72
/**
 * File: dict.hpp
 * Description: 
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * Licensed under the GNU General Public License:
 * http://www.gnu.org/licenses/gpl.html
 * 
 * Date: 2012-01-02 22:40:24.711000
 * Written In: Peking University, beijing, China
 */

#include <str.h>
#include <list.h>

template<class key>
struct hashkey {
	enum {
		bucket_size=1<<2,
		min_buckets=1<<14
	};
	inline const uint operator()(const key& k) const {
		return k.tohash();
	}
	inline const bool operator()(const key& key1, const key& key2) const {
		return key1<key2;
	}
};

template<class key, class value>
class dict {
public:
	typedef std::pair<key, value> pair;
	typedef std::list<pair> pairs;
	typedef list<key> klist;
	typedef list<value> vlist;
	
	typedef hashkey<key> keyhash;
	typedef hash_map<key, value, keyhash> container;
	
	typedef typename container::iterator iterator;
	typedef typename container::const_iterator citerator;
	typedef typename container::reverse_iterator riterator;
	typedef typename container::const_reverse_iterator criterator;
	
private:
	container con;
	
public:
	// for iterators
	inline iterator begin() { return con.begin(); } 
	inline iterator end() { return con.end(); }
	inline riterator rbegin() { return con.rbegin(); }
	inline riterator rend() { return con.rend(); }
	
	inline citerator begin() const { return con.begin(); } 
	inline citerator end() const { return con.end(); }
	inline criterator rbegin() const { return con.rbegin(); }
	inline criterator rend() const { return con.rend(); }
	
	// for constructors
	// template<class K1, class V1>
	// dict(const K1& k1, V1& v1) {
		// con[k1]=v1;
	// }
	
	dict() {}
	dict(const dict& r):con(r.con) {}
	dict(iterator begin, iterator end):con(begin, end) {}
	dict(citerator begin, citerator end):con(begin, end) {}
	dict(riterator begin, riterator end):con(begin, end) {}
	dict(criterator begin, criterator end):con(begin, end) {}
	
	/**************************************************
	query: size empty less grater cmp
	bool expressions:	== != > >= < <= !
	**************************************************/
	inline const uint size() const { return con.size(); }
	inline const bool empty() const { return con.empty(); }
	inline const bool equals(const dict& r) const { return con==r.con; }
	inline const bool less(const dict& r) const { return con<r.con; }
	inline const bool grater(const dict& r) const { return con>r.con; }
	inline const bool cmp(const dict& r) const { return less(r); }
	
	inline bool operator==(const dict& r) { return equals(r); }
	inline bool operator!=(const dict& r) { return !equals(r); }
	inline bool operator<(const dict& r) { return less(r); }
	inline bool operator<=(const dict& r) { return !grater(r); }
	inline bool operator>(const dict& r) { return grater(r); }
	inline bool operator>=(const dict& r) { return !less(r); }
	inline bool operator!() { return empty(); }
	
	/**************************************************
	output operator: <<
	**************************************************/
	friend ostream& operator<<(ostream& out, dict& d) {
		uint l=d.size(), cnt=0;
		out<<"{ ";
		for (iterator i=d.begin(), j=d.end(); i!=j; ++i, ++cnt) {
			const key& k=i->first;
			const value& v=i->second;
			out<<k<<':'<<v;
			if (cnt!=l-1) out<<',';
			out<<' ';
		}
		return out<<'}';
	}
	
	/**************************************************
	assign operator: =
	**************************************************/
	inline dict& operator=(const dict& r) {
		return assign(r);
	}
	inline dict& assign(const dict& r) {
		con=r.con;
		return *this;
	}
	
	/**************************************************
	clear:	D.clear() -> None.  Remove all items from D.
	**************************************************/
	inline dict& clear() {
		con.clear();
		return *this;
	}
	
	/*************************************************
	copy:	D.copy() -> new D
		Return a shadow copy of dict D, is the same to D
		in the first level
	*************************************************/
	inline dict copy() {
		return dict(*this);
	}
	
	/*************************************************
	clone:	D.clone() -> new D
		Return a deep copy of dict D, which is a clone
		of D. The same in all level
	*************************************************/
	inline dict clone() {
		//TODO
		return dict();
	}
	
	/**************************************************
	fromkeys:	dict.fromkeys(S[,v]) -> New dict with keys from S and values equal to v.
	v defaults to None.
	**************************************************/
	//TODO
	
	/**************************************************
	get:	D.get(k[,d]) -> D[k] if k in D, else d.  d defaults to None.
	**************************************************/
	inline value get(const key& k, const value& dval=0) {
		return haskey(k)?con[k]:dval;
	}
	
	/**************************************************
	superget:	D.setdefault(k[,d]) -> D.get(k,d), 
				also set D[k]=d if k not in D
	**************************************************/
	inline value superget(const key& k, const value& dval) {
		if (haskey(k)) return con[k];
		con[k]=dval;
		return dval;
	}
	
	/**************************************************
	set:	D.set(k, v) -> D[k]=v
	**************************************************/
	inline void set(const key& k, const value& v) {
		con[k]=v;
	}
	
	//for element
	inline value& operator [](const key& k) {
		return con[k];
	}
	
	inline const value& operator [](const key& k) const {
		return con[k];
	}
	
	/**************************************************
	find:	Find element iterator from this dict.
	**************************************************/
	inline iterator find(const key& k) {
		return con.find(k);
	}
	inline citerator find(const key& k) const {
		return con.find(k);
	}
	
	/**************************************************
	haskey:	D.haskey(k) -> True if D has a key k, else False
	**************************************************/
	bool haskey(const key& k) const {
		return find(k)!=end();
	}
	
	/**************************************************
	items:	D.items() -> list of D's (key, value) pairs, as 2-tuples
	**************************************************/
	inline pairs items() {
		pairs pl;
		for (iterator i=begin(), j=end(); i!=j; ++i) pl.push_back(pair(i->first, i->second));
		return pl;
	}
	
	/**************************************************
	iteritems:	D.iteritems() -> an iterator over the (key, value) items of D
	**************************************************/
	//TODO
	
	/**************************************************
	iterkeys:	D.iterkeys() -> an iterator over the keys of D
	**************************************************/
	//TODO
	
	/**************************************************
	itervalues:	D.itervalues() -> an iterator over the values of D
	**************************************************/
	//TODO
	
	/**************************************************
	keys:	D.keys() -> list of D's keys
	**************************************************/
	inline klist keys() {
		klist ks;
		for (iterator i=begin(), j=end(); i!=j; ++i) ks.push_back(i->first);
		return ks;
	}
	
	/**************************************************
	values:	D.values() -> list of D's values
	**************************************************/
	inline vlist values() {
		vlist vs;
		for (iterator i=begin(), j=end(); i!=j; ++i) vs.append(i->second);
		return vs;
	}
	
	/**************************************************
	pop:	D.pop(k[,d]) -> v, remove specified key and return the corresponding value
	If key is not found, d is returned if given, otherwise KeyError is raised
	**************************************************/
	inline value pop() {
		if (con.empty()) return NULL;
		iterator i=con.begin();
		value tmp=i->second;
		con.erase(i);
		return tmp;
	}
	
	/**************************************************
	popitem:	D.popitem() -> (k, v), 
		remove and return some (key, value) pair as a
		2-tuple; but raise KeyError if D is empty
	**************************************************/
	//TODO
	
	/**************************************************
	update:	D.update(D2) -> None.  
		Update D from E and F: for k in E: D[k] = E[k]
		(if E has keys else: for (k, v) in E: D[k] = v) 
		then: for k in F: D[k] = F[k]
	**************************************************/
	void update(dict& d) {
		for(iterator i=begin(), j=end(); i!=j; ++i) {
			const key& k=i->first;
			value& val=i->second;
			if (haskey(k)) set(k, val);
		}
	}
	
	/**************************************************
	foreach:	apply function on each element
	**************************************************/
	template<class Function>
	inline void foreach(Function f) { std::for_each(begin(), end(), f); }
	
	/**************************************************
	tohash:	return an uint hash value
	**************************************************/
	inline uint tohash() {
		return static_cast<uint>(this);
	}
};

typedef dict<str, str> D;

#endif /* DICT_HASH_MAP_HPP_1325515224_72 */
