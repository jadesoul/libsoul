#ifndef RESOURCE_H_1360078844_44
#define RESOURCE_H_1360078844_44
/**
 * File: resource.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-02-05 23:40:44.439000
 * Written In: Peking University, beijing, China
 */


#include "config.h"

class Resource {
protected:
	ProbDict pde2c;
	ProbDict pdc2e;
	Vocabulary vocab;
	Config& conf;
	
public:
	Resource(Config& conf):conf(conf) {
		init();
	}
	
	virtual void init() {
		if (NOT conf.dont_use_e2c_probdict) conf.load_e2c_probdict(pde2c, vocab);
		if (NOT conf.dont_use_c2e_probdict) conf.load_c2e_probdict(pdc2e, vocab);
	}
};

class ChunkAlignResource : public Resource {
protected:
	NPIndexer npindxer;
	VPIndexer vpindxer;
	PosTagSet postagset;
public:
	friend class IChunkAligner;
	ChunkAlignResource(Config& conf):Resource(conf) {}
	virtual void init() {
		Resource::init();
		
		conf.load_tag_set(postagset);
		
	}
};

#endif /* RESOURCE_H_1360078844_44 */
