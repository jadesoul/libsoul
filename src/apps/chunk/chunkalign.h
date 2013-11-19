#ifndef CHUNKALIGN_H_1357476812_01
#define CHUNKALIGN_H_1357476812_01
/**
 * File: chunkalign.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-06 20:53:32.012777
 * Written In: Peking University, beijing, China
 */

#include "config.h"
#include "chunk.h"
#include "alignment.h"
#include "probdict.h"
#include "aligner.h"

// class PRF {
// private:
	// double p, r;
// public:
	// template<class T>
	// PRF(const set<T>& ref, const set<T>& test) {
		// if (test.size()==0 OR ref.size()==0) {
			// p=0;
			// r=0;
		// } else {
			// set<T> same=ref;
			// same.intersect(test);
			// p=1.0*same.size()/test.size();
			// r=1.0*same.size()/ref.size();
		// }
	// }

	// inline double pricision() { return p; }
	// inline double recall() { return r; }

	// double fmeasure(double alpha=0.5) {
		// assert(alpha>=0 AND alpha<=1);
		// double fz=p*r;
		// double fm=alpha*r+(1-alpha)*p;
		// if (float_equal(fm, 0)) return 0;
		// else return fz/fm;
	// }

	// ostream& save(ostream& o) {
		// o<<"PRECISION:\t\t"<<p<<endl;
		// o<<"RECALL:\t\t"<<r<<endl;
		// o<<"F-MEASURE:\t\t"<<fmeasure()<<endl;
		// o<<"F-MEASURE(0.1):\t\t"<<fmeasure(0.1)<<endl;
		// o<<"F-MEASURE(0.3):\t\t"<<fmeasure(0.3)<<endl;
		// o<<"F-MEASURE(0.5):\t\t"<<fmeasure(0.5)<<endl;
		// o<<"F-MEASURE(0.7):\t\t"<<fmeasure(0.7)<<endl;
		// o<<"F-MEASURE(0.9):\t\t"<<fmeasure(0.9)<<endl;
		// return o;
	// }

	// friend inline ostream& operator<<(ostream& o, PRF& r) {
		// return r.save(o);
	// }
// };

// class PRFSummary : public list<PRF> {
// public:
	// PRFSummary() {}

	// double average_pricision() {
		// uint n=size();
		// if (n==0) return 0;
		// double sum=0;
		// for_n(i, n) sum+=at(i).pricision();
		// return sum/n;
	// }

	// double average_recall() {
		// uint n=size();
		// if (n==0) return 0;
		// double sum=0;
		// for_n(i, n) sum+=at(i).recall();
		// return sum/n;
	// }

	// double average_fmeasure(double alpha=0.5) {
		// uint n=size();
		// if (n==0) return 0;
		// double sum=0;
		// for_n(i, n) sum+=at(i).fmeasure(alpha);
		// return sum/n;
	// }

	// ostream& save(ostream& o) {
		// uint n=size();//for_n(i, n) o<<"P="<<at(i).pricision()<<"\tR="<<at(i).recall()<<"\tF="<<at(i).fmeasure()<<endl;
		// o<<average_pricision()<<","<<average_recall()<<","<<average_fmeasure();
		// return o;
	// }

	// friend inline ostream& operator<<(ostream& o, PRFSummary& r) {
		// return r.save(o);
	// }
// };

// class Evaluator {
// private:
	// Alignment& ref;

// public:
	// Evaluator(Alignment& ref):ref(ref) {}

	// PRF eval(Alignment& test) {
		// return PRF(ref.get_ladder_set(), test.get_ladder_set());
	// }
// };

#endif /* CHUNKALIGN_H_1357476812_01 */
