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
#include "probdict.h"



class Chunk : public list<segment> {
public:
	class ChunkInfo {
	public:
		freqprobdist fpdist;//distrubution of all words in this Chunk
		list<word> unique_words;//all unique words in this chunk;
		dict<word, uint> word2index;//word to index in unique_words;
		list<word> bag_of_words;//word sequence in all segments
		Chunk& c;//chunk ref

		ChunkInfo(Chunk& c):c(c) {
			c.get_bag_of_words(bag_of_words);
			uint n=bag_of_words.size();
			for_n(i, n) {
				word& w=bag_of_words[i];
				//update unique words
				uint ind;
				if (NOT word2index.get(w, ind)) {
					unique_words.append(w);
					ind=unique_words.size()-1;
					word2index[w]=ind;
				}
				//update freq prob dist
				freqprobdist::iterator it=fpdist.find(w);
				if (it==fpdist.end()) fpdist[w]=std::pair<freq, prob>(1, 0);
				else it->second.first+=1;
			}
			//normalize freq prob dist
			fpdist.normalize();
		}
	};
protected:
	ChunkInfo* info;
public:

	typedef  list<segment> container;
	//typedef typename container::iterator iterator;
	//typedef typename container::riterator riterator;
	
	Chunk():info(NULL) {}
	Chunk(list<segment> segs):container(segs.begin(), segs.end()), info(NULL) {}
	Chunk(const Chunk& r):container(r.begin(), r.end()), info(NULL) {}
	template<class Iterator>
	Chunk(Iterator b, Iterator e):container(b, e), info(NULL) {}

	~Chunk() {
		if (info) delete info;
	}

	ChunkInfo& get_chunk_info() {
		if (info==NULL) info=new ChunkInfo(*this);
		return *info;
	}

	freqprobdist& get_words_freq_prob_dist() {
		return get_chunk_info().fpdist;
	}

	uint get_unique_words_index(word w) {
		uint ind;
		bool found=get_chunk_info().word2index.get(w, ind);
		assert(found);
		return ind;
	}

	inline uint total_unique_words() {
		return get_chunk_info().unique_words.size();
	}

	inline uint total_segs() { return size(); }

	uint total_words(uint begin=0, uint end=-1) {
		uint n=total_segs();
		if (end==-1) end=n;
		assert(begin>=0 AND begin<=end AND end<=n);
		uint cnt=0;
		for_m(i, begin, end) cnt+=at(i).size();
		return cnt;
	}

	uint total_tokens_len(uint begin=0, uint end=-1) {
		uint n=total_segs();
		if (end==-1) end=n;
		assert(begin>=0 AND begin<=end AND end<=n);
		uint len=0;
		for_m(i, begin, end) len+=at(i).total_tokens_len();
		return len;
	}

	void get_bag_of_words(list<word>& bag) {
		Chunk& me=*this;
		uint n=size();
		for_n(i, n) {
			segment& seg=me[i];
			seg.get_bag_of_words(bag);
		}
	}



	ostream& save(ostream& o) {
		uint n=size();
		for_n(i, n) {
			o<<"<segment index="<<i<<">"<<endl;
			o<<at(i)<<endl;
			o<<"</segment>"<<endl;
		}
		return o;
	}
	
	friend inline ostream& operator<<(ostream& o, Chunk& c) { return c.save(o); }
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
