#ifndef PROBLEM_H_1359719956_12
#define PROBLEM_H_1359719956_12
/**
 * File: problem.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-02-01 19:59:16.116000
 * Written In: Peking University, beijing, China
 */

#include "config.h"

class Problem {
protected:
	Config& conf;
public:
	Problem(Config& conf):conf(conf) { init(); }
	virtual void init() {
		//TODO
	}
	virtual void solve(OptionArgs& optargs)=0;
};

class ChunkAlignProplem : public Problem {
protected:
	Vocabulary& vocab;
	NPIndexer& npindxer;
	VPIndexer& vpindxer;
	PosTagSet& tagset;
	ProbDict& pde2c;
	ProbDict& pdc2e;
public:
	ChunkAlignProplem(ChunkAlignResource& resource):
		conf(resource.conf),
		vocab(resource.vocab),
		npindxer(resource.npindxer),
		vpindxer(resource.vpindxer),
		tagset(resource.tagset),
		pde2c(resource.pde2c),
		pdc2e(resource.pdc2e) {}
	
	virtual void init() {
		Problem::init();
	}
	
	virtual void solve(OptionArgs& optargs) {
		

		
	}
};

#endif /* PROBLEM_H_1359719956_12 */
 