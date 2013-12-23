#ifndef SENT_H_1357384110_52
#define SENT_H_1357384110_52
/**
 * File: sent.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-05 19:08:30.520679
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "token.h"
#include "vocab.h"
#include "word.h"

class Sentence : public list<Word> {
public:
	Sentence() {}
	
	template<class iterator>
	Sentence(iterator b, iterator e):list<Word>(b, e) {}
	// void parse(istream& i, vocabulary& v) {
		// token t;
		// while (i>>t) {
			// word w=v(t);
			// append(w);
		// }
	// }
	// void dump(ostream& o, vocabulary& v) {
		// uint n=size();
		// for_n(i, n) {
			// o<<v[at(i)];
			// if (i<n-1) o<<' ';
		// }
	// }
	
	// ostream& save(ostream& o) {
		// uint n=size();
		// for_n(i, n) {
			// o<<at(i);
			// if (i<n-1) o<<' ';
		// }
		// return o;
	// }
	// inline friend ostream& operator<<(ostream& o, Sentence& s) { return s.save(o); }
	
	// istream& load(istream& i) {
		// word w;
		// while (i>>w) append(w);
		// return i;
	// }
	// inline friend istream& operator>>(istream& i, Sentence& s) { return s.load(i); }
};

typedef list<Sentence> SentList;

// class SentList : public list<Sentence> {
// public:
	// void parse(istream& i, vocabulary& v) {
		// string s;
		// while (getline(i, s)) {
			// istringstream iss(s);
			// sentence snt;
			// snt.parse(iss, v);
			// append(snt);
		// }
	// }
	// void dump(ostream& o, vocabulary& v) {
		// uint n=size();
		// for_n(i, n) {
			// at(i).dump(o, v);
			// o<<endl;
		// }
	// }
	
	// ostream& save(ostream& o) {
		// uint n=size();
		// for_n(i, n) o<<at(i)<<endl;
		// return o;
	// }
	// friend inline ostream& operator<<(ostream& o, sentlist& ss) { return ss.save(o); }
	
	// istream& load(istream& i) {
		// string s;
		// while (getline(i, s)) {
			// istringstream iss;
			// sentence snt;
			// snt.load(iss);
			// append(snt);
		// }
		// return i;
	// }
	// friend inline istream& operator>>(istream& i, sentlist& ss) { return ss.load(i); }
// };

#endif /* SENT_H_1357384110_52 */
