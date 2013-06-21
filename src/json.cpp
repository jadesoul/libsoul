/**
 * File: json.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-26 20:50:15.224000
 * Written In: Peking University, beijing, China
 */
 
#include "json.h"

//the cpp json implementation
/*
example:
	json:{
		person:[
			{
				name:jadesoul,
				age:27
			},
			{
				name:hi,
				age:39
			}
		]
	}
*/

// dict {
	// name
	// age
// }

void json::item::free() {
	if (ptr) {
		if (isarr()) {
			delete (array*)ptr;
		} else if (isdict()) {
			delete (dictionary*)ptr;
		} else if (isstr()) {
			delete (str*)ptr;
		} else if (isnum()) {
			delete (num*)ptr;
		} else if (isempty()) {
			assert(false);
		} else assert(false);
	}
}

json::item& json::item::operator =(const json::item& r) {
	if (this!=&r) {
		if (ptr!=NULL) {
			assert(ptr!=r.ptr);//for debug
			clear();
		}
		type=r.type;
		if (isarr()) {
			ptr=new array(r.toarr());
		} else if (isdict()) {
			ptr=new dictionary(r.todict());
		} else if (isstr()) {
			ptr=new str(r.tostr());
		} else if (isnum()) {
			ptr=new num(r.tonum());
		} else if (isempty()) {
			//pass
		} else assert(false);
	}
	return *this;
}

const uint json::item::size() const {
	if (isempty()) return 0;
	if (isnum()) return 1;
	if (isstr()) return tostr().size();
	if (isarr()) return toarr().size();
	if (isdict()) return todict().size();
	assert(false);
	return 0;
}

void decode(const str& s) {
	
}


str json::encode(const item& i, str prefix, const bool final) {
	if (i.isarr()) {
		array& a=i.toarr();
		list<str> ss;
		ss.append(prefix+"[");
		uint l=i.size(), cnt=0;
		for_iter(it, array, a) {
			++cnt;
			item& j=*it;
			ss.append(encode(j, prefix+"\t", cnt==l));
		}
		ss.append(prefix+(final?"]":"],"));
		return ss.glue("\n");
	} else if (i.isdict()) {
		dictionary& d=i.todict();
		list<str> ss;
		ss.append(prefix+"{");
		uint l=i.size(), cnt=0;
		for_iter(it, dictionary, d) {
			++cnt;
			const str& k=it->first;
			const item& v=it->second;
			if (v.isstr() OR v.isnum()) ss.append(str('"')+k+"\":"+encode(v, "", cnt==l));
			else ss.append(str('"')+k+"\":"+encode(v, prefix+'\t', cnt==l));
		}
		ss.append(prefix+(final?"}":"},"));
		return ss.glue("\n");
	} else if (i.isstr()) {
		return prefix+"\""+i.tostr()+(final?"\"":"\","); 
	} else {//if (i.isnum()) {
		return prefix+string(i.tonum())+(final?"":",");
	}
}

