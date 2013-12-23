#ifndef NORMALIZE_H_1359722479_65
#define NORMALIZE_H_1359722479_65
/**
 * File: normalize.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-02-01 20:41:19.655000
 * Written In: Peking University, beijing, China
 */
 
#include <libsoul>
#include "vocab.h"
#include "sent.h"

template<class container, class sum_type, class ret_type, class sum_selector_type, class div_selector_type, class save_selector_type>
class nomalizer {
	sum_selector_type sum_selector;
	div_selector_type div_selector;
	save_selector_type save_selector;
public:
	void operator ()(container& con) {
		sum_type sum=0;
		for_iter(it, container, con) sum+=sum_selector(*it);
		for_iter(it, container, con) save_selector(*it) = ret_type(div_selector(*it)) / ret_type(sum);
	}
};

template<class type, class nomalizer_type=nomalizer<list<type>, type, type, select_myself<type>, select_myself<type>, select_myself<type> > >
class nomalizable_list : public list<type> {
	nomalizer_type the_nomalizer;
public:
	void normalize() {
		the_nomalizer(*this);
	}
};

typedef nomalizable_list<freq> freqlist;
typedef nomalizable_list<prob> problist;
typedef nomalizable_list<pair<freq, prob>, nomalizer<list<pair<freq, prob> >, freq, prob, select_first<freq, prob>, select_first<freq, prob>, select_second<freq, prob> > > freqproblist;

template<class key, class value, class nomalizer_type=nomalizer<dict<key, value>, value, value, select_second<key, value>, select_second<key, value>, select_second<key, value> > >
class nomalizable_dict : public dict<key, value> {
	nomalizer_type the_nomalizer;
public:
	void normalize() {
		the_nomalizer(*this);
	}
};

// typedef nomalizable_dict<word, Freq> FreqDist;
// typedef nomalizable_dict<word, Prob> ProbDist;
// typedef nomalizable_dict<word, pair<freq, prob>, nomalizer<dict<word, pair<freq, prob> >, freq, prob, select_second_first<word, freq, prob>, select_second_first<word, freq, prob>, select_second_second<word, freq, prob> > > freqprobdist;


// class probdict : public dict<word, probdist> {//probilistic bilingual dictionary
// public:
	// typedef dict<word, probdist> container;
	// probdict() {}
	
	// bool get_prob(const word& src, const word& dst, prob& ret) {
		// iterator i=find(src);
		// if (i==end()) return false;
		// return i->second.get(dst, ret);
	// }

	// void normalize() {
		// probdict& me=*this;
		// for_iter(it, probdict, me) {
			// it->second.normalize();
		// }
	// }
	
	// istream& load(istream& in) {
		// probdict& me=*this;
		// word s, t;
		// prob p;
		// while (in>>s>>t>>p) {
			// iterator i=find(s);
			// if (i==end()) {
				// probdist pd;
				// pd[t]=p;
				// me[s]=pd;
			// } else {
				// probdist& pd=i->second;
				// pd[t]=p;
			// }
		// }
		// return in;
	// }
	// inline friend istream& operator>>(istream& in, probdict& pdict) {
		// return pdict.load(in);
	// }
	
	// ostream& save(ostream& out) {
		// probdict& me=*this;
		// for_iter(i, probdict, me) {
			// word s=i->first;
			// probdist& pd=i->second;
			// for_iter(j, probdist, pd) {
				// word t=j->first;
				// prob p=j->second;
				// out<<s<<' '<<t<<' '<<p<<endl;
			// }
		// }
		// return out;
	// }
	// inline friend ostream& operator<<(ostream& out, probdict& pdict) {
		// return pdict.save(out);
	// }
	
	// void parse(istream& in, vocabulary& src, vocabulary& dst) {
		// probdict& me=*this;
		// token ts, tt;
		// prob p;
		// while (in>>ts>>tt>>p) {
			// word s=src(ts), t=dst(tt);
			// iterator i=find(s);
			// if (i==end()) {
				// probdist pd;
				// pd[t]=p;
				// me[s]=pd;
			// } else {
				// probdist& pd=i->second;
				// pd[t]=p;
			// }
		// }
	// }
	// void dump(ostream& out, vocabulary& src, vocabulary& dst) {
		// probdict& me=*this;
		// for_iter(i, probdict, me) {
			// word s=i->first;
			// probdist& pd=i->second;
			// for_iter(j, probdist, pd) {
				// word t=j->first;
				// prob p=j->second;
				// out<<src[s]<<' '<<dst[t]<<' '<<p<<endl;
			// }
		// }
	// }
// };

#endif /* NORMALIZE_H_1359722479_65 */



