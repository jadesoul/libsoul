#ifndef JSON_H_1356526212_78
#define JSON_H_1356526212_78
/**
 * File: json.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 20:50:12.775000
 * Written In: Peking University, beijing, China
 */

#include "corelib.h"

class num {
public:
	num(int n=0):n(n) {}
	inline bool operator <(const num& r) const { return n<r.n; }
	inline operator string() { return str(n).tostr(); }
	friend ostream& operator<<(ostream& o, const num& r) { return o<<r.n; }
protected:
	int n;
};

class json {
public:
	class item;
	typedef list<item> array;
	typedef dict<str, item> dictionary;
	
	class item {
	public:
		char type;	//array(A) or dictionary(D) or str(S) or num(N) or empty(E)
		void* ptr;
		// ptr=new array;
		// ptr=new dictionary;
		// ptr=new str;
		// ptr=new num;
		item():type('E'), ptr(NULL) {}
		item(const str& s):type('S'), ptr(new str(s)) {}
		item(const array& a):type('A'), ptr(new array(a)) {}
		item(const num& n):type('N'), ptr(new num(n)) {}
		item(const dictionary& d):type('D'), ptr(new dictionary(d)) {}
		item(const item& i, bool shallow_copy_tag):type(i.type), ptr(i.ptr) {} //shallow copy
		item(const item& i) { *this=i; } //deep copy
		virtual ~item() { free(); }
		
		void free();
		inline void clear() { free(); ptr=NULL; type='E'; }

		inline num& tonum() const { return *((num*)ptr); }
		inline str& tostr() const { return *((str*)ptr); }
		inline array& toarr() const { return *((array*)ptr); }
		inline dictionary& todict() const { return *((dictionary*)ptr); }
		
		inline const bool isnum() const { return type=='N'; }
		inline const bool isstr() const { return type=='S'; }
		inline const bool isarr() const { return type=='A'; }
		inline const bool isdict() const { return type=='D'; }
		inline const bool isempty() const { return type=='E'; }
		inline const bool issimple() const { return isnum() OR isstr() OR isempty(); }
		inline const bool iscomplex() const { return isarr() OR isdict(); }
		
		item& operator =(const item& r);
		inline bool operator <(const item& r) { return this<&r; }
		const uint size() const;
		friend inline ostream& operator<<(ostream& o, const item& i) {
			return o<<"[json::item type="<<i.type<<" size="<<i.size()<<"]";
		}
	} root;
	
	json() {}
	
	void decode(const str& s);
	str encode(const item& i, str prefix="", const bool final=true);
	
	inline str encode() { return encode(root); }
	friend inline ostream& operator<<(ostream& o, json& j) { return o<<j.encode(); }
};


#endif /* JSON_H_1356526212_78 */
