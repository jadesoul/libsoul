#ifndef PROGRAM_H_1359719965_28
#define PROGRAM_H_1359719965_28
/**
 * File: program.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-02-01 19:59:25.282000
 * Written In: Peking University, beijing, China
 */

#include "config.h"
#include "problem.h"

class Program {
protected:
	ProbDict pde2c;
	ProbDict pdc2e;
	Vocabulary vocab;
	Config& conf;
	
public:
	Program(conf& conf):conf(conf) {
		init();
	}
	
	virtual void init() {
		if (NOT conf.dont_use_e2c_probdict) load_e2c_probdict(pde2c, vocab);
		if (NOT conf.dont_use_c2e_probdict) load_c2e_probdict(pdc2e, vocab);
	}
};

class ChunkAlignProgram : public Program {
protected:
	NPIndexer npindxer;
	VPIndexer vpindxer;
	PosTagSet postagset;
public:
	ChunkAlignProgram(Config& conf):Program(conf) {}
	virtual void init() {
		Program::init();
		
		conf.load_tag_set(postagset);
		
		
		ChunkAlignProplem problem(conf, vocab, npindxer, vpindxer, postagset, pde2c, pdc2e);
		problem.solve();
	}
};

#endif /* PROGRAM_H_1359719965_28 */
