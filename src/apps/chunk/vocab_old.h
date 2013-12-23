#ifndef VOCAB_H_1357303907_82
#define VOCAB_H_1357303907_82
/**
 * File: vocab.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-04 20:51:47.824000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "word.h"
#include "token.h"

//word到token之间的转换
//word其实就是token编号
class vocabulary {
private:
	//a list of tokens, the index of each is its word id
	list<token> tokens;
	list<freq> freqs; //and add a freq list
	list<prob> probs; //the prob of each token here
	
	//a mapping from token string to word index
	dict<token, word> dictionary;

	void init() {
		tokens.clear();
		freqs.clear();
		probs.clear();
		dictionary.clear();
		tokens.append(NULL_TOKEN); //add null word as the first word
		freqs.append(0);
		probs.append(0);
		dictionary[NULL_TOKEN]=NULL_WORD;
	}
public:
	vocabulary() { init(); }
	inline uint size() const { return tokens.size(); }
	
	//scan vocabulary from a plain text
	void scan(istream& i) {
		str t;
		while (i>>t) {
			word w=(*this)(t);
			++freqs[w];
		}
		// update_prob();
	}
	
	void update_prob() {
		freq total=sum(freqs);
		// clog<<"total="<<total<<endl;
		if (total==0) return;
		uint n=tokens.size();
		for_n (i, n) probs[i]=1.0*freqs[i]/total;
	}

	//load vocabulary from a gizapp format vocab
	istream& load_from_gizapp_format(istream& in) {
		init();
		
		uint w=1;//add word 1 as gizapp null word
		tokens.append("<GIZAPP_NULL>");
		freqs.append(0);
		probs.append(0);
		
		uint i;
		string t;
		freq f;
		while (in>>i>>t>>f) {
			++w;
			assert(i==w);
			tokens.append(t);
			freqs.append(f);
			probs.append(0);
			dictionary[t]=w;
		}
		return in;
	}
	
	istream& load(istream& in) {
		init();
		string t;
		freq f;
		uint w=0;
		while (in>>t>>f) {
			tokens.append(t);
			freqs.append(f);
			probs.append(0);
			dictionary[t]=++w;
		}
		return in;
	}
	friend inline istream& operator>>(istream& i, vocabulary& v) { return v.load(i); }

	ostream& save(ostream& out) {
		// update_prob();
		uint n=tokens.size();
		// for_m (i, 1, n) out<<tokens[i]<<str(' ')*(20-2*tokens[i].size()/3)+'\t'<<freqs[i]<<"\t\t\t"<<probs[i]<<endl;
		for_m (i, 1, n) out<<tokens[i]<<' '<<freqs[i]<<endl;
		return out;
	}
	friend inline ostream& operator<<(ostream& o, vocabulary& v) { return v.save(o); }

	// word2token, make sure the index exists
	// if the word not exists in the vocabulary, then return NULL_TOKEN
	const token& operator [] (const word& w) const {
		if (w<tokens.size()) return tokens[w];
		else return NULL_TOKEN;
	}
	
	inline bool has_token(const token& t) { return dictionary.find(t)!=dictionary.end(); }

	//token2word, if the token not exists in the vocabulary, then add it
	const word operator () (const token& t) {
		word w;
		//find the key in the dict, if found, fill the value
		if (!dictionary.get(t, w)) {
			w=tokens.size();
			tokens.append(t);
			dictionary[t]=w;
			// clog<<"not found, insert="<<t<<"\tw="<<w<<endl;
			freqs.append(0);
			probs.append(0);
			//prob should update later
		}
		return w;
	}
};

//find equal words in 2 vocabulary
// class equal_vocabulary {
// public:
	// map<word, word> src2tgt;//mapping from src word to equal target word
	// map<word, token> src2tokens;//mapping from token of src word and equal target word
	// map<word, word> tgt2src;//mapping from src word to equal target word
	
// public:
	// equal_vocabulary(vocabulary& src, vocabulary& tgt) {
		// uint n=src.size();
		// for_n(i, n) {
			// const token& t=src[i];
			// if (tgt.has_token(t)) {
				// src2tokens[i]=t;
				// word j=tgt(t);
				// src2tgt[i]=j;
				// tgt2src[j]=i;
			// }
		// }
	// }
	// void dump(ostream& s2t, ostream& t2s) {
		// typedef map<word, word> mapping_t;
		// for_iter(it, mapping_t, src2tgt) {
			// word i=it->first, j=it->second;
			// s2t<<i<<' '<<j<<' '<<src2tokens[i]<<endl;
		// }
		// for_iter(it, mapping_t, tgt2src) {
			// word j=it->first, i=it->second;
			// t2s<<j<<' '<<i<<' '<<src2tokens[i]<<endl;
		// }
	// }
// };

#endif /* VOCAB_H_1357303907_82 */
