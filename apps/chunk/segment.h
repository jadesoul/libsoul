#ifndef SEGMENT_H_1359786605_64
#define SEGMENT_H_1359786605_64
/**
 * File: segment.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-02-02 14:30:05.673000
 * Written In: Peking University, beijing, China
 */

#include "sent.h"
typedef list<Word> Segment;

// class Segment {
// public:// sentence* snt;
	// list<Word> words;
	// vocabulary* vcb;
	// uint begin, end;//所在的原始sentence中的位置
// public:
	// segment(sentence& s, vocabulary& v):vcb(&v), words(s.begin(), s.end()), begin(0), end(s.size()) {}
	// segment(sentence& s, uint b, vocabulary& v):vcb(&v), words(s.begin()+b, s.end()), begin(b), end(s.size()) {}
	// segment(sentence& s, uint b, uint e, vocabulary& v):vcb(&v), words(s.begin()+b, s.begin()+e), begin(b), end(e) {}
	
	// inline uint size() const { return words.size(); }//get words cnt of this segment
	// inline const word& operator [] (uint i) const { return words[i]; }//get the i-th word of this segment

	// void get_bag_of_words(list<word>& bag) {
		// bag.extend(words.begin(), words.end());
	// }

	// uint total_tokens_len() {
		// uint l=0, n=words.size();
		// for_n(i, n) {
			// word w=words[i];
			// l+=(*vcb)[w].size();
		// }
		// return l;
	// }

	
	// void dump(ostream& o) {// show plain text
		// uint  n=words.size();
		// for_n(i, n) {
			// word w=words[i];
			// if (vcb) o<<(*vcb)[w];
			// else o<<w;
			// if (i+1<n) o<<' ';
		// }
	// }

	// ostream& save(ostream& o) {
		// o<<"<length>"<<end-begin<<"</length>"<<endl;
		// o<<"<begin>"<<begin<<"</begin>"<<endl;
		// o<<"<end>"<<end<<"</end>"<<endl;

		//if (pconf->output_reference_sentence) {
		//	o<<"<!-- Reference Sentence -->"<<endl;
		//	o<<"<sentence len="<<snt->size()<<">"<<endl;
		//	o<<"<words>"<<endl;
		//	o<<*snt<<endl;
		//	o<<"</words>"<<endl;
		//	if (vcb) {
		//		o<<"<tokens>"<<endl;
		//		o<<"<![CDATA["<<endl;
		//		snt->dump(o, *vcb);
		//		o<<endl<<"]]>"<<endl;
		//		o<<"</tokens>"<<endl;
		//	}
		//	o<<"</sentence>"<<endl;
		//}

		// o<<"<words>"<<endl;
		// o<<words<<endl;
		// o<<"</words>"<<endl;
		
		// if (vcb) {
			// o<<"<tokens>"<<endl<<"<![CDATA["<<endl;
			// for (uint i=begin; i<end; ++i) o<<(*vcb)[words[i-begin]]<<" ";
			// o<<endl<<"]]>"<<endl<<"</tokens>"<<endl;
			// o<<"<combine>"<<endl<<"<![CDATA["<<endl;
			// for (uint i=begin; i<end; ++i) o<<words[i-begin]<<'('<<(*vcb)[words[i-begin]]<<')'<<' ';
			// o<<endl<<"]]>"<<endl<<"</combine>"<<endl;
		// }
		// return o;
	// }
	// friend inline ostream& operator<<(ostream& o, segment& s) {
		// return s.save(o);
	// }
// };


#endif /* SEGMENT_H_1359786605_64 */
