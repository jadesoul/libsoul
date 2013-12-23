#ifndef LEXICON_H_1357304438_3
#define LEXICON_H_1357304438_3
/**
 * File: lexicon.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-04 21:00:38.300000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "token.h"
#include "pos.h"
#include "lemma.h"
#include "iob.h"

//lexicon: a lexicon is a wrapping of a word, containing its token, pos-tagging and vp and np tag, and this is extensible
class Lexicon {
public:
	TokenID token;//the token id
	LemmaID lemma;//the pos-tagging
	PosTagID pos;//the pos tag id
	IOBTagID np;//the np tag id
	IOBTagID vp;//the vp tag id
	// RelayTagID relay;//the relay anasys tag id 依存分析
	// SuperTagID super;//the super tag id超级标记
	
	Lexicon():token(), lemma(), pos(0), np(IOBTagID(0)), vp(IOBTagID(0)) {}
};

const Lexicon* WORD_NULL=(const Lexicon*)-1; //保留给空词
const Lexicon* WORD_BOS=(const Lexicon*)-2; //保留给句子边界，特殊的词
const Lexicon* WORD_BOP=(const Lexicon*)-3; //保留给段落边界，特殊的词
const Lexicon* WORD_MAX_LIMIT=(const Lexicon*)-4; //所有正常的词都小于或等于此值
#define IS_NULL_WORD(w) (w==WORD_NULL)
#define IS_BOS_WORD(w) (w==WORD_BOS)
#define IS_BOP_WORD(w) (w==WORD_BOP)
#define IS_VALID_WORD(w) (w<=WORD_MAX_LIMIT)

class LexiconHistory {
public:
	typedef std::list<Lexicon*> History;
	History history;
	
	LexiconHistory() {}
	
	void seen(Lexicon* lex) {
		if (IS_VALID_WORD(lex)) {
			assert(lex!=NULL);
			history.push_back(lex);
		}
	}
	
	Lexicon& create() {//创建一个非空的正常Lexicon
		Lexicon* lex=new Lexicon;
		seen(lex);
		return *lex;
	}
	
	~LexiconHistory() {
		for_iter(it, History, history) {
			Lexicon* lex=*it;
			// if (lex!=WORD_NULL AND word!=WORD_BOS AND word!=WORD_BOP) delete lex;
			if (IS_VALID_WORD(lex)) delete lex;
		}
	}
};

#endif /* LEXICON_H_1357304438_3 */
