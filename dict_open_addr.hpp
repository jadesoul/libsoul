#ifndef DICT_OPEN_ADDR_HPP_1325515224_73
#define DICT_OPEN_ADDR_HPP_1325515224_73
/**
 * File: dict.hpp
 * Description: this file implement a dict using open address method to solve the confiliction as python does
 *
 * Copyright (c) 2011 Jadesoul (Home Page: http://jadesoul.org)
 * Licensed under the GNU General Public License:
 * http://www.gnu.org/licenses/gpl.html
 * 
 * Date: 2012-01-02 22:40:24.711000
 * Written In: Peking University, beijing, China
 */

#include "str.h"
#include "list.h"

#define INIT_ENTRY_CNT	8
#define DUMMY_PTR		(entry*)(-1)

template<class key, class value>
class dict {
public:
	typedef uint hash;
	
	struct entry {
		const key k;
		value v;
		const hash h;
		entry() {}
		entry(const key& k, const value& v, const hash& h):k(k), v(v), h(h) {}
		entry(const entry& e):k(e.k), v(e.v), h(e.h) {}
	};
	
	typedef std::vector<entry*> sequence;
	
	typedef ::list<key> klist;
	typedef ::list<value> vlist;
	typedef ::set<key> kset;
	typedef ::set<value> vset;
	
	typedef ::list<const entry *> cpelist;
	typedef ::list<const key *> cpklist;
	typedef ::list<const value *> cpvlist;
	
	typedef typename sequence::iterator iterator;
	typedef typename sequence::const_iterator citerator;
	typedef typename sequence::reverse_iterator riterator;
	typedef typename sequence::const_reverse_iterator criterator;

private:
	sequence seq;
	uint len;
	uint active;
	uint dummy;
	
public:
	// for iterators
	// inline iterator begin() { return seq.begin(); } 
	// inline iterator end() { return seq.end(); }
	// inline riterator rbegin() { return seq.rbegin(); }
	// inline riterator rend() { return seq.rend(); }
	
	// inline citerator begin() const { return seq.begin(); } 
	// inline citerator end() const { return seq.end(); }
	// inline criterator rbegin() const { return seq.rbegin(); }
	// inline criterator rend() const { return seq.rend(); }
	
	// for constructors
	// template<class K1, class V1>
	// dict(const K1& k1, V1& v1) {
		// seq[k1]=v1;
	// }
	
	dict():seq(INIT_ENTRY_CNT, (entry*)NULL), len(INIT_ENTRY_CNT), active(0), dummy(0) {}
private:
	dict(const uint& cnt):seq(cnt, (entry*)NULL), len(cnt), active(0), dummy(0) {}
public:
	dict(const dict& r):seq(r.seq), len(r.len), active(r.active), dummy(r.dummy) {}
	~dict() { clean(); }
	
	/**************************************************
	output operator: <<
	**************************************************/
	friend ostream& operator<<(ostream& out, dict& d) {
		uint cnt=0;
		out<<"[dict len="<<d.len<<" active="<<d.active<<" dummy="<<d.dummy<<" usage="<<d.usage()<<"] ";
		out<<"{ ";
		for_n(i, d.len) if (d.isactive(i)) {
			++cnt;
			out<< d.seq[i]->k <<':'<< d.seq[i]->v;
			if (cnt!=d.active) out<<',';
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
		seq=r.seq;
		return *this;
	}
	
	/**************************************************
	for query: size empty less grater cmp
	bool expressions:	== != > >= < <= !
	**************************************************/
	inline const uint size() const { return active; }
	inline const bool empty() const { return seq.empty(); }
	inline const bool equals(const dict& r) const { return seq==r.seq; }
	inline const bool less(const dict& r) const { return seq<r.seq; }
	inline const bool grater(const dict& r) const { return seq>r.seq; }
	inline const bool cmp(const dict& r) const { return less(r); }
	
	inline bool operator==(const dict& r) { return equals(r); }
	inline bool operator!=(const dict& r) { return !equals(r); }
	inline bool operator<(const dict& r) { return less(r); }
	inline bool operator<=(const dict& r) { return !grater(r); }
	inline bool operator>(const dict& r) { return grater(r); }
	inline bool operator>=(const dict& r) { return !less(r); }
	inline bool operator!() { return empty(); }
	// inline dict operator &(const dict& x, const dict& y) { return x.intersection(y); }
	// inline dict operator |(const dict& x, const dict& y) { return x.unioned(y); }
	// inline dict operator +(const dict& x, const dict& y) { return x.unioned(y); }
	// inline dict operator -(const dict& x, const dict& y) { return x.difference(y); }
	// inline dict operator ^(const dict& x, const dict& y) { return x.crossed(y); }
	// inline dict& operator &=(const dict& r) { return intersect(r); }
	// inline dict& operator |=(const dict& r) { return unionto(r); }
	// inline dict& operator +=(const dict& r) { return unionto(r); }
	// inline dict& operator -=(const dict& r) { return differ(r); }
	// inline dict& operator ^=(const dict& r) { return cross(r); }
	
	/**************************************************
	locate: 
		Find the index of the key if exists or return a empty 
		or dummy entry index to put the key
	**************************************************/
	inline const uint locate(const key& k) {
		uint h=gethash(k);
		// cout<<"key="<<k<<" hash="<<h<<endl;
		return locate(k, h);
	}
	inline const uint locate(const key& k, const hash& h) {
		//first hash
		uint first=h % len;
		uint now=first, times=0, last=-1;
		if (isempty(now)) return now;
		else if (isdummy(now)) {
			if (last==uint(-1)) last=now;
		}
		else if (equals(now, k, h)) return now; 
		
		while (1) {
			//again hash
			next(first, now, times, last, h);
			if (isempty(now)) return (last!=uint(-1))?last:now;
			else if (isdummy(now)) {
				if (last==uint(-1)) last=now;
			}
			else if (equals(now, k, h)) return now;
		}
	}
	
	/**************************************************
	find:	Find a key from this dict. return -1 if not found
	**************************************************/
	inline const uint find(const key& k) {
		uint i=locate(k);
		return isactive(i)?i:-1;
	}
	
	/**************************************************
	haskey:	D.haskey(k) -> True if D has a key k, else False
	**************************************************/
	inline const bool haskey(const key& k) {
		return isactive(locate(k));
	}
	
private:
	/**************************************************
	gethash:	D.gethash(k) -> get hash of a key
	**************************************************/
	template<class K>
	inline const uint gethash(const K& k) const { return k.tohash(); }
	template<class K>
	inline const uint gethash(const K* k) const { return (uint)k; }
	#define Macro__over_load_gethash__KeyType(K)\
	inline const uint gethash(const K& k) const { return (uint)k; }
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
	
	/**************************************************
	isactive:D.isactive(i) -> test whether if the 
		position i is a active entry
	isdummy:	D.isdummy(i) -> test whether if the 
		position i is a dummy pointer
	isempty:	D.isempty(i) -> test whether if the 
		position i is a null pointer
	**************************************************/
	inline const bool isactive(const uint& i) const {
		return seq[i]!=NULL AND seq[i]!=DUMMY_PTR;
	}
	inline const bool isdummy(const uint& i) const {
		return seq[i]==DUMMY_PTR;
	}
	inline const bool isempty(const uint& i) const {
		return seq[i]==NULL;
	}
	
	/**************************************************
	equals:	D.equals(i, key, hash) -> test whether if the 
		position equals to a key and has the same hash
	**************************************************/
	inline const bool equals(const uint& i, const key& k, const hash& h) const {
		return seq[i]->h==h AND seq[i]->k==k;
	}
	
	
	inline const float usage() const {
		return 1.0*(active+dummy)/len;
	}
	inline void next(uint& first, uint& now, uint& times, uint& last, const hash& h) {//again hash strategy
		times+=1;
		now+=1;
		if (now==len) {
			if (usage()>0.8) expand(first, now, last, h);
			else now=0;
		}
	}
	inline void expand(uint& first, uint& now, uint& last, const hash& h) {	//expand
		uint dblen=len*2;
		dict tmp(dblen);
		
		for_n(i, len) if (isactive(i)) {
			uint j=tmp.locate(seq[i]->k, seq[i]->h);
			tmp.seq[j]=seq[i];
		}
		seq=tmp.seq;
		len=tmp.len;
		dummy=0;
		tmp.seq.clear();
		tmp.len=0;
		tmp.active=0;
		tmp.dummy=0;
		
		last=-1;
		first=h % len;
		now=first;
	}
	inline void insert(const uint& i, const key& k, const value& v) {
		if (isdummy(i)) dummy-=1;
		seq[i]=new entry(k, v, gethash(k));
		active+=1;
	}
	inline void remove(const uint& i) {
		assert(isactive(i));
		dummy+=1;
		delete seq[i];
		seq[i]=DUMMY_PTR;
		active-=1;
	}
	inline void clean() {	//clean memory by new
		for_n(i, len) if (isactive(i)) delete seq[i];
	}
public:
	/**************************************************
	get:	
		D.get(k[,d]) -> D[k] if k in D, else d.  
		d defaults to None.
	**************************************************/
	inline value get(const key& k) {
		uint i=locate(k);
		assert(isactive(i));
		return seq[i]->v;
	}
	inline value get(const key& k, const value& d) {
		uint i=locate(k);
		return isactive(i)?seq[i]->v:d;
	}
	
	/**************************************************
	sget:
		D.sget(k[,d]) -> D.get(k,d), 
		At the same time, set D[k]=d if k not in D
	**************************************************/
	inline value sget(const key& k, const value& d=value()) {
		uint i=locate(k);
		if (isactive(i)) return seq[i]->v;
		insert(i, k, d);
		return d;
	}
	
	/**************************************************
	set:	D.set(k, v) -> D[k]=v
	**************************************************/
	inline void set(const key& k, const value& v) {
		uint i=locate(k);
		if (isactive(i)) seq[i]->v=v;
		else insert(i, k, v);
	}
	
	/**************************************************
	operator []: D[k]
		use it to get or set the value of any key
		not that if the k not exists, a new entry will 
		be inserted, no matter when get or set
		(it's better to use it to set: D[k]=v)
	**************************************************/
	inline value& operator [](const key& k) {
		uint i=locate(k);
		if (isactive(i)) return seq[i]->v;
		insert(i, k, value());
		return seq[i]->v;
	}
	
	/**************************************************
	operator (): D(k)
		use it to get or set the value of existed key
		not that the key must exists
		(it's better to use it to get: D(k))
	**************************************************/
	inline value& operator ()(const key& k) {
		uint i=locate(k);
		assert(isactive(i));
		return seq[i]->v;
	}
	
	/**************************************************
	clear:	D.clear() -> None.  Remove all items from D.
	**************************************************/
	inline dict& clear() {
		clean();
		seq.assign(INIT_ENTRY_CNT, NULL);
		len=INIT_ENTRY_CNT;
		active=0;
		dummy=0;
		return *this;
	}
	
	/*************************************************
	copy:
		D.copy() -> new D
		Return a shadow copy of dict D
	*************************************************/
	inline dict copy() {
		return dict(*this);
	}
	
	/*************************************************
	clone:	
		D.clone() -> new D
		Return a deep copy of dict D, which is a clone
		of D.
	*************************************************/
	inline dict clone() {
		dict d=copy();
		for_n(i, len) if (isactive(i)) d.seq[i]=new entry(*seq[i]);
		return d;
	}
	
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
		for_n(i, len) if (isactive(i)) ks.append(seq[i]->k);
		return ks;
	}

	/**************************************************
	values:	D.values() -> list of D's values
	**************************************************/
	inline vlist values() {
		vlist vs;
		for_n(i, len) if (isactive(i)) vs.append(seq[i]->v);
		return vs;
	}
	
	/**************************************************
	pkeys:	D.pkeys() -> list of D's keys as pointers
	**************************************************/
	inline cpklist pkeys() {
		cpklist ks;
		for_n(i, len) if (isactive(i)) ks.append(&(seq[i]->k));
		return ks;
	}

	/**************************************************
	pvalues:	D.pvalues() -> list of D's values as pointers
	**************************************************/
	inline cpvlist pvalues() {
		cpvlist vs;
		for_n(i, len) if (isactive(i)) vs.append(&(seq[i]->v));
		return vs;
	}
	
	/**************************************************
	pitems:
		D.pitems() -> return all entry pointers as items
	**************************************************/
	inline cpelist pitems() {
		cpelist el;
		for_n(i, len) if (isactive(i)) el.append(seq[i]);
		return el;
	}
	
	
	/**************************************************
	del:	D.del(k[,d]) -> v, remove specified key and return the corresponding value
	If key is not found, d is returned if given, otherwise KeyError is raised
	**************************************************/
	inline value del(const key& k) {
		uint i=locate(k);
		assert(isactive(i));
		value v=seq[i]->v;
		remove(i);
		return v;
	}
	inline value del(const key& k, const value& v) {
		uint i=locate(k);
		value ret=v;
		if (isactive(i)) {
			ret=seq[i]->v;
			remove(i);
		}
		return ret;
	}
	
	/**************************************************
	pop:	D.pop()
		remove some (key, value) pair 
	**************************************************/
	inline void pop(uint cnt=1) {
		if (cnt>0 AND active>0) {
			for_n(i, len) if (isactive(i)) {
				remove(i);
				--cnt;
				if (cnt==0) break;
			}
		}
	}
	
	/**************************************************
	update:	D.update(D2) -> None.  
		Update D from E and F: for k in E: D[k] = E[k]
		(if E has keys else: for (k, v) in E: D[k] = v) 
		then: for k in F: D[k] = F[k]
	**************************************************/
	inline void update(dict& d) {
		for_n(i, d.len) if (d.isactive(i)) set(d.seq[i]->k, d.seq[i]->v);
	}
	
	/**************************************************
	foreach:	apply function on each element
	**************************************************/
	template<class Function>
	inline void foreach(Function f) {
		cpelist cpel;
		for_n(i, len) if (isactive(i)) cpel.append(seq[i]);
		std::for_each(cpel.begin(), cpel.end(), f);
	}
	
	/**************************************************
	tohash:	return an uint hash value
	**************************************************/
	inline uint tohash() {
		list<str> ss;
		for_n(i, len) if (isactive(i)) ss.append(seq[i]->k).append(seq[i]->v);
		str signature=ss.glue(",");
		return signature.tohash();
	}
};

typedef dict<str, str> D;

#undef INIT_ENTRY_CNT
#undef DUMMY_PTR

#endif /* DICT_OPEN_ADDR_HPP_1325515224_73 */
