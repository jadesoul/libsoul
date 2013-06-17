#ifndef DICT_H_1357370085_57
#define DICT_H_1357370085_57
/**
 * File: dict.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-05 15:14:45.569642
 * Written In: Peking University, beijing, China
 */

#include "bootstrap.h"

#define DICT_BASE_HASH_MAP 0
#define DICT_BASE_RBTREE_MAP 1
#define DICT_BASE_OPEN_ADDR_HASH_MAP 2

#define DICT_BASE_TYPE DICT_BASE_HASH_MAP

#if (DICT_BASE_TYPE==DICT_BASE_HASH_MAP)

template<class K>
inline const uint __gethash(const K& k) { return k.tohash(); }
template<class K>
inline const uint __gethash(const K* k) { return (uint)k; }
#define Macro__over_load_gethash__KeyType(K)\
inline const uint __gethash(const K& k) { return (uint)k; }
Macro__over_load_gethash__KeyType(char);
Macro__over_load_gethash__KeyType(uchar);
Macro__over_load_gethash__KeyType(short);
Macro__over_load_gethash__KeyType(ushort);
Macro__over_load_gethash__KeyType(int);
Macro__over_load_gethash__KeyType(uint);
Macro__over_load_gethash__KeyType(long);
Macro__over_load_gethash__KeyType(ulong);
Macro__over_load_gethash__KeyType(float);
Macro__over_load_gethash__KeyType(double);
#undef Macro__over_load_gethash__KeyType

template<>
inline const uint __gethash(const string& k) {
	uint h=0, i=k.size();
	while(i>0) h=107*h+k[--i];
	return h;
}

template<class key>
struct hashmgr {
	enum {
		bucket_size=1<<2,
		min_buckets=1<<14
	};
	inline const uint operator()(const key& k) const {
		return __gethash(k);
	}
	inline const bool operator()(const key& key1, const key& key2) const {
		return key1<key2;
	}
};

template<class key, class value>
class dict : public hash_map<key, value, hashmgr<key> > {
public:
	typedef hash_map<key, value, hashmgr<key> > dict_base;
	
	/**************************************************
	output operator: <<
	**************************************************/
	friend ostream& operator<<(ostream& o, dict& d) {
		return o<<"[dict (hash_map) len="<<d.size()<<"]";
	}
	

#endif /*DICT_BASE_HASH_MAP*/

	//common implementations here
	dict():dict_base() {}
	
	typedef typename dict_base::value_type element;
	typedef typename dict_base::iterator iterator;
	typedef typename dict_base::const_iterator citerator;
	
	typedef ::list<key> klist;
	typedef ::list<value> vlist;
	typedef ::set<key> kset;
	typedef ::set<value> vset;
	
	typedef ::list<const element*> cpelist;
	typedef ::list<const key*> cpklist;
	typedef ::list<const value*> cpvlist;
	
	
	inline iterator begin() { return dict_base::begin(); }
	inline iterator end() { return dict_base::end(); }
	inline bool empty() { return dict_base::empty(); }
	inline size_t size() const { return dict_base::size(); }
	inline void clear() { dict_base::clear(); }
	
	// get a value by key
	// if key exists, put the value in the holder and return true
	// else return flase
	inline bool get(const key& k, value& holder) {
		iterator i=find(k);
		if (i==end()) return false;
		holder=i->second;
		return true;
	}
	
	inline bool operator !() { return empty(); }
	inline bool haskey(const key& k) { return find(k)!=end(); }
	inline void set(const key& k, const value& v) { (*this)[k]=v; }
	
	//shadow copy
	inline dict copy() { return dict(*this); }
	
	// deep copy
	inline dict clone() { return copy(); }
	
	/**************************************************
	fromkeys:
		dict.fromkeys(ks [,v]) -> New dict with keys from ks
		and values equal to v. v defaults to value().
	**************************************************/
	inline dict& fromkeys(const kset& ks, const value& v=value()) {
		clear();
		for_iter(i, kset, ks) set(*i, v);
		return *this;
	}
	
	/**************************************************
	keys:	D.keys() -> list of D's keys
	**************************************************/
	inline klist keys() {
		klist ks;
		dict& me=*this;
		for_iter(i, dict, me) ks.append(i->first);
		return ks;
	}

	/**************************************************
	values:	D.values() -> list of D's values
	**************************************************/
	inline vlist values() {
		vlist vs;
		dict& me=*this;
		for_iter(i, dict, me) vs.append(i->second);
		return vs;
	}
	
	/**************************************************
	pkeys:	D.pkeys() -> list of D's keys as pointers
	**************************************************/
	inline cpklist pkeys() {
		cpklist ks;
		dict& me=*this;
		for_iter(i, dict, me) ks.append(&i->first);
		return ks;
	}

	/**************************************************
	pvalues:	D.pvalues() -> list of D's values as pointers
	**************************************************/
	inline cpvlist pvalues() {
		cpvlist vs;
		dict& me=*this;
		for_iter(i, dict, me) vs.append(&i->second);
		return vs;
	}
	
	/**************************************************
	pitems:
		D.pitems() -> return all entry pointers as items
	**************************************************/
	inline cpelist pitems() {
		cpelist es;
		dict& me=*this;
		for_iter(i, dict, me) es.append((element*)i);
		return es;
	}
	
#if (DICT_BASE_TYPE==DICT_BASE_HASH_MAP)
//
#endif /*DICT_BASE_HASH_MAP*/


};
#endif /* DICT_H_1357370085_57 */
