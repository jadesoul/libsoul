#ifndef ALIGNMENT_H_1357744707_3
#define ALIGNMENT_H_1357744707_3
/**
 * File: alignment.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-09 23:18:27.295355
 * Written In: Peking University, beijing, China
 */
 
#include "config.h"
#include "chunk.h"
#include "probdict.h"

struct AlignCell {
	double align_score, likehood_score, likehood_score_e2c, likehood_score_c2e, prior_prob_xy, xlen, ylen, length_penalty;
	uint x, y;
	AlignCell(): align_score(-1e100), likehood_score(0.0), likehood_score_e2c(0.0), likehood_score_c2e(0.0), prior_prob_xy(0.0), xlen(0.0), ylen(0.0), length_penalty(0.0), x(0), y(0) {}
	AlignCell(uint x, uint y): align_score(-1e100), likehood_score(0.0), likehood_score_e2c(0.0), likehood_score_c2e(0.0), prior_prob_xy(0.0), xlen(0.0), ylen(0.0), length_penalty(0.0), x(x), y(y) {}
	void dump(ostream& o) {
		o<<"# score="<<align_score<<" likehood="<<likehood_score
		<<" c2e="<<likehood_score_c2e<<" e2c="<<likehood_score_e2c
		<<" prior="<<prior_prob_xy<<" xlen="<<xlen<<" ylen="<<ylen
		<<" lenpenalty="<<length_penalty<<endl;
		o<<x<<"\t"<<y<<"\t0\t"<<endl;
	}
};


class Alignment {
public:
	typedef AlignCell cell;
private:
	//用来初始化，计算对齐长度比
	list<uint> xs;//each en chunk length sequence in dp
	list<uint> ys;//each cn chunk length sequence in dp
	list<double> acc_scores;//accumulated align scores
	list<double> cp_scores;//scores for each chunk pair

	//for enable chunk pair cross alignment 
	//交叉对齐的扭曲表，记录每一个cn chunk对应的en chunk的chunk编号
	//当不支持扭曲是，dis为一一对应的，将不扭曲看做扭曲的特例
	list<uint> diss;//ths chunking index distortion sequence of cn: dis(1, K), for any i in [1..K] dis[i] is in [1..K]

	list<cell> cells;
public:
	Alignment() {}
	void init(list<cell>& rcells) {
		cells.clear();
		for_riter(it, list<cell>, rcells) cells.append(*it);
		// cells=list<cell>(rcells.rbegin(), rcells.rend())
	}

	void dump(ostream& o) {
		uint n=cells.size();
		for_n(i, n) {
			cell& best=cells[i];
			best.dump(o);
		}
	}
};

#endif /* ALIGNMENT_H_1357744707_3 */

