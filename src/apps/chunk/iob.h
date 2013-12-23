#ifndef IOB_H_1359713645_43
#define IOB_H_1359713645_43
/**
 * File: iob.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-02-01 18:14:05.428000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "indexer.h"

enum IOBTagID {
	IOB_TAG_ID_B_NP=0,
	IOB_TAG_ID_I_NP,
	IOB_TAG_ID_B_VP,
	IOB_TAG_ID_I_VP,
	IOB_TAG_ID_O,
};

typedef str IOBTag;
const IOBTag IOB_TAG_B_NP="B-NP";
const IOBTag IOB_TAG_I_NP="I-NP";
const IOBTag IOB_TAG_B_VP="B-VP";
const IOBTag IOB_TAG_I_VP="I-VP";
const IOBTag IOB_TAG_O="O";

typedef indexer<IOBTag, IOBTagID> IOBIndexer;

class NPIndexer : public IOBIndexer {
protected:
	virtual const IOBTag& get_default_value() const {
		return IOB_TAG_O;
	}
	virtual void init() {
		IOBIndexer::clear();
		add(IOB_TAG_O);
		add(IOB_TAG_B_NP);
		add(IOB_TAG_I_NP);
	}
public:
	NPIndexer():IOBIndexer() {}
};

class VPIndexer : public IOBIndexer {
protected:
	virtual const IOBTag& get_default_value() const {
		return IOB_TAG_O;
	}
	virtual void init() {
		IOBIndexer::clear();
		add(IOB_TAG_O);
		add(IOB_TAG_B_VP);
		add(IOB_TAG_I_VP);
	}
public:
	VPIndexer():IOBIndexer() {}
};
#endif /* IOB_H_1359713645_43 */
