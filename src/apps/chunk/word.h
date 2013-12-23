#ifndef WORD_H_1356447873_56
#define WORD_H_1356447873_56
/**
 * File: word.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-25 23:04:33.557000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "lexicon.h"
#include "vocab.h"
#include "token.h"

typedef double Prob;
typedef uint Freq;

// typedef Lexicon* Word; //define the id/index of a lexicon as a word
class Word {
protected:
	Lexicon* plex;
public:
	Word():plex(NULL) {}
	Word(Lexicon* plex):plex(plex) {}
	Word(Lexicon& lex):plex(&lex) {
		assert(plex!=NULL AND is_valid_word());
	}
	
	~Word() {
		//析构函数中不析构Lexicon
		//Lexicon在LexiconHistory中析构
	}
	

	
	inline const bool is_null_word() const { return IS_NULL_WORD(plex); }
	inline const bool is_bos_word() const { return IS_BOS_WORD(plex); }
	inline const bool is_bop_word() const { return IS_BOP_WORD(plex); }
	inline const bool is_valid_word() const { return IS_VALID_WORD(plex); }
	
	TokenID token_id() const {
		if (is_null_word()) return TOKEN_ID_NULL;
		else if (is_bos_word()) return TOKEN_ID_BOS;
		else if (is_bop_word()) return TOKEN_ID_BOP;
		else return plex->token;
	}
	inline Token token(Vocabulary& vocab) {
		return vocab[token_id()];
	}
	inline uint tohash() const {//token id即为hash
		return token_id();
	}
	inline uint token_len(Vocabulary& vocab) {//BOS和BOP长度为0
		if (is_valid_word()) return vocab[plex->token].size();
		else return 0;
	}

	bool operator ==(const Word& r) const { 
		if (is_valid_word() AND r.is_valid_word()) return plex->token==r.plex->token;
		else if (!is_valid_word() AND !r.is_valid_word()) return plex==r.plex;
		else return false;
	}
	inline bool operator !=(const Word& r) const { return !(*this==r); }
	inline bool operator <(const Word& r) const { return tohash()<r.tohash(); }
};



#endif /* WORD_H_1356447873_56 */

