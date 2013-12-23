#ifndef PROBDICT_H_1357542784_75
#define PROBDICT_H_1357542784_75
/**
 * File: probdict.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-07 15:13:04.753185
 * Written In: Peking University, beijing, China
 */
 
#include <libsoul>
#include "token.h"
#include "vocab.h"
#include "word.h"

class TokenIDPair {
public:
	TokenID src, dst;
	TokenIDPair(const TokenID& src, const TokenID& dst):src(src), dst(dst) {}
	inline uint tohash() const { return src*23+dst; }
	inline bool operator ==(const TokenIDPair& r) const { return src==r.src && dst==r.dst; }
	inline bool operator !=(const TokenIDPair& r) const { return !(*this==r); }
	inline bool operator <(const TokenIDPair& r) const { return (src==r.src) ? dst<r.dst : src<r.src; }
};

template<class Value>
class FastDict : public dict<TokenIDPair, Value> {
public:
	typedef dict<TokenIDPair, Value> container;
	//typedef typename container::iterator iterator;

	FastDict() {}
	
	void set(const TokenID& src, const TokenID& dst, const Value& val) {
		TokenIDPair key(src, dst);
		FastDict& me=*this;
		me[key]=val;
	}
	void add(const TokenID& src, const TokenID& dst, const Value& val) {
		TokenIDPair key(src, dst);
		FastDict& me=*this;
		me[key]+=val;
	}
	bool get(const TokenID& src, const TokenID& dst, Value& val) {
		TokenIDPair key(src, dst);
		
		typename container::iterator i=container::find(key);
		if (i==container::end()) return false;
		val=i->second;
		return true;
		
		// if (NOT container::haskey(key)) return false;
		// FastDict& me=*this;
		// val=me[key];
		// return true;
	}
};

// typedef FastDict<Freq> CoocDict;

class ProbDict : public FastDict<Prob> {//probilistic bilingual dictionary
public:
	typedef FastDict<Prob> container;
	ProbDict() {}
	
	bool get(const Word& src, const Word& dst, Prob& ret) {
		return container::get(src.token_id(), dst.token_id(), ret);
	}
	
	void load(istream& in, Vocabulary& vcb) {
		ProbDict& me=*this;
		Token s, t;
		Prob p;
		while (in>>s>>t>>p) {
			TokenID src=vcb(s), dst=vcb(t);
			TokenIDPair key(src, dst);
			me[key]=p;
		}
	}
	
	void dump(ostream& out, Vocabulary& vcb) {
		ProbDict& me=*this;
		for_iter(i, ProbDict, me) {
			TokenIDPair key=i->first;
			Prob p=i->second;
			out<<vcb[key.src]<<' '<<vcb[key.dst]<<' '<<p<<endl;
		}
	}
	
	// void normalize() {
		// ProbDict& me=*this;
		// for_iter(it, ProbDict, me) {
			// it->second.normalize();
		// }
	// }
};

#endif /* PROBDICT_H_1357542784_75 */
