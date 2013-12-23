#ifndef POS_H_1357305974_09
#define POS_H_1357305974_09
/**
 * File: pos.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-04 21:26:14.090000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "indexer.h"

typedef uint PosTagID;
typedef str PosTag;
typedef indexer<PosTag, PosTagID> PosTagIndexer;

//定义未知词性的默认词性编号和表示字符串
const PosTagID POS_TAG_ID_UNKOWN=0;
const PosTag POS_TAG_UNKOWN="UNKOWN";

//词性标注集，标注字符串和id的切换
class PosTagSet : public PosTagIndexer {
protected:
	virtual const PosTag& get_default_value() const {
		return POS_TAG_UNKOWN;
	}
	virtual void init() {
		clear();
		add(POS_TAG_UNKOWN);
	}
public:
	PosTagSet():PosTagIndexer() {}
	
	//从流中加载词性列表，流中为词性字符串列表
	virtual void load(istream& in) {
		PosTagSet& me=*this;
		string s;
		while (in>>s) me(s);
	}
	
};

#endif /* POS_H_1357305974_09 */
