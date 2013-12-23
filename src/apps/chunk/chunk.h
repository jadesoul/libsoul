#ifndef CHUNK_H_1357476773_39
#define CHUNK_H_1357476773_39
/**
 * File: chunk.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-06 20:52:53.387267
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "config.h"
#include "segment.h"
#include "probdict.h"

typedef list<Segment> Chunk;

// class Chunk : public list<Segment> {
// public:
	// typedef  list<Segment> container;
	
	// Chunk() {}
	// Chunk(const list<Segment>& segs):container(segs.begin(), segs.end()) {}
	// Chunk(const Chunk& r):container(r.begin(), r.end()) {}
	
	// template<class Iterator>
	// Chunk(Iterator b, Iterator e):container(b, e) {}



	// ostream& save(ostream& o) {
		// uint n=size();
		// for_n(i, n) {
			// o<<"<segment index="<<i<<">"<<endl;
			// o<<at(i)<<endl;
			// o<<"</segment>"<<endl;
		// }
		// return o;
	// }
	
	// friend inline ostream& operator<<(ostream& o, Chunk& c) { return c.save(o); }
// };

class ChunkInfo {
protected:
	// freqprobdist fpdist;//distrubution of all words in this Chunk
	list<Word> unique_words;//all unique words in this chunk;
	dict<Word, uint> word2index;//word to index of unique_words;
	list<Word> bag_of_words;//word sequence in all segments
	Chunk& c;//chunk ref
public:
	ChunkInfo(Chunk& chk):c(chk) {
		//get bag of words
		uint n=c.size();
		for_n(i, n) {
			Segment& seg=c[i];
			bag_of_words.extend(seg.begin(), seg.end());
		}
		
		//gen word indexer
		n=bag_of_words.size();
		for_n(i, n) {
			Word& w=bag_of_words[i];//update unique words
			uint ind;
			if (NOT word2index.get(w, ind)) {
				unique_words.append(w);
				ind=unique_words.size()-1;
				word2index[w]=ind;
			}
			
			// freqprobdist::iterator it=fpdist.find(w);//update freq prob dist
			// if (it==fpdist.end()) fpdist[w]=std::pair<freq, prob>(1, 0);
			// else it->second.first+=1;
		}
		
		// fpdist.normalize();//normalize freq prob dist
	}
	
	// freqprobdist& get_words_freq_prob_dist() {
		// return get_chunk_info().fpdist;
	// }
	
	uint get_unique_words_index(const Word& w) {//只能查找有记录的words
		uint ind;
		bool found=word2index.get(w, ind);
		if_not(found) log_error("Bad word when get_unique_words_index, not exists in the unique_words");
		return found?ind:-1;
	}
	
	inline uint total_unique_words() const { return unique_words.size(); }
	inline uint total_segs() const { return c.size(); }
	
	uint total_words(uint begin=0, uint end=-1) {
		uint n=total_segs();
		if (end==-1) end=n;
		assert(begin>=0 AND begin<=end AND end<=n);
		uint cnt=0;
		for_m(i, begin, end) cnt+=c[i].size();
		return cnt;
	}
	
	uint total_tokens_len(Vocabulary& vocab, uint begin=0, uint end=-1) {
		uint n=total_segs();
		if (begin>=end) return 0;//empty region
		if (end==-1) end=n;
		// log_debug("begin="<<begin);
		// log_debug("end="<<end);
		// log_debug("n="<<n);
		assert(begin>=0 AND begin<=end AND end<=n);
		uint len=0;
		for_m(i, begin, end) {
			Segment& seg=c[i];
			uint m=seg.size();
			for_n(j, m) {
				Word& word=seg[j];
				len+=word.token_len(vocab);
			}
		}
		return len;
	}
	
	list<Word>& get_bag_of_words() {
		return bag_of_words;
	}
};

// struct ChunkPair {
	// Chunk en;
	// Chunk cn;
	
	// ChunkPair() {}
	// ChunkPair(const Chunk& e, const Chunk& c):en(e), cn(c) {}

	// ostream& save(ostream& o) {
		// o<<"<Chunk language=en>"<<endl;
		// o<<en<<endl;
		// o<<"</Chunk>"<<endl;
		// o<<"<Chunk language=cn>"<<endl;
		// o<<cn<<endl;
		// o<<"</Chunk>"<<endl;
		// return o;
	// }

	// friend inline ostream& operator<<(ostream& o, ChunkPair& p) { return p.save(o); }
// };

#endif /* CHUNK_H_1357476773_39 */
