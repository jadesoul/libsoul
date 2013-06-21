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
};

//multiple alignment merge
//ladder generation

class AlignMode {
public:
	uint x;//en segs in the chunk 
	uint y;//cn segs in the chunk
	
	AlignMode(uint x, uint y):x(x), y(y) {}

	ostream& save(ostream& o) const {
		return o<<x<<":"<<y;
	}
	friend inline ostream& operator<<(ostream& o, const AlignMode& a) {
		return a.save(o);
	}
};

class Ladder {
public:
	uint x;//en seg id, count from 1, 0 is NULL seg
	uint y;//cn seg id, count from 1, 0 is NULL seg

	Ladder(uint x, uint y):x(x), y(y) {}

	inline uint tohash() const { return x*23+y; }
	inline bool operator ==(const Ladder& r) const { return x==r.x && y==r.y; }
	inline bool operator !=(const Ladder& r) const { return !(*this==r); }
	inline bool operator <(const Ladder& r) const { return (x==r.x) ? y<r.y : x<r.x; }
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

	//记录K+1个chunk切分点
	list<uint> ss;//ths chunking index sequence of en: s(0, K), s[0]=0, s[K]=M
	list<uint> ds;//ths chunking index sequence of cn: d(0, K), d[0]=0, d[K]=N
	
	//for enable chunk pair cross alignment 
	//交叉对齐的扭曲表，记录每一个cn chunk对应的en chunk的chunk编号
	//当不支持扭曲是，dis为一一对应的，将不扭曲看做扭曲的特例
	list<uint> diss;//ths chunking index distortion sequence of cn: dis(1, K), for any i in [1..K] dis[i] is in [1..K]
	
	//梯子序列，用于计算PRF
	list<uint> els;//ths ladder sequence of en
	list<uint> cls;//ths ladder sequence of cn
	set<Ladder> ladder_set;
	
	//原始的输入segment序列，看做是两个大chunk
	Chunk ensegs;//en segments sequence
	Chunk cnsegs;//cn segments sequence 
	bool ssinited;//record if ess and css are inited

	sentlist ens;//如果alignment是从human align file构造，用来保存sentence对象
	sentlist cns;

	//生成的对齐结果
	list<ChunkPair> cps;//coressponding chunk pairs sequence

	list<cell> cells;
private:
	void gen_chunk_index() {
		assert(ssinited);//must init ss first
		uint K=xs.size(), M=ensegs.size(), N=cnsegs.size();
		
		ss.clear();
		ss.append(0);
		
		ds.clear();
		ds.append(0);
		
		// if enable distortion
		diss.clear();
		
		uint xacc=0, yacc=0;//accumulate x and y
		for_n(k, K) {
			uint x=xs[k], y=ys[k];
			xacc+=x;
			yacc+=y;
			ss.append(xacc);
			ds.append(yacc);
			diss.append(k);//TODO: 暂时只考虑K个chunk一一对应
		}
		if (xacc!=M OR yacc!=N) {//must be ss[K]==M and ds[k]==N
			die_error("bad alignment result: xacc="<<xacc<<", M="<<M<<", yacc="<<yacc<<", N="<<N);
		}
	}
	
	void gen_ladder() {
		assert(xs.size()+1==ss.size() AND ys.size()+1==ds.size());//确保已经生成了ss, ds
		els.clear();
		cls.clear();
		ladder_set.clear();
		//如果支持交叉chunk，梯子无法严格依次按照第一第二列排序，否则，可以排序
		//使用dis来生成梯子，统一处理扭曲或者不扭曲
		uint K=xs.size();
		for_n(k, K) {//对每个源chunk编号
			uint kk=diss[k];//目标chunk编号

			uint bs=ss[k], es=ss[k+1];//源chunk的segs区间
			assert(bs<=es);
			uint bd=ds[kk], ed=ds[kk+1];//目标chunk的segs区间
			

			if (bs==es) {//源区间为空，说明产生了0:N
				assert(bd<ed);//目标区间不可能为空，否则是0:0
				for_m(j, bd, ed) {//对每个目标segment编号
					els.append(0);//0代表NULL segment
					cls.append(j+1);//从0开始的索引空间，转换到从1开始的编号区间
					ladder_set.add(Ladder(0, j+1));
				}
			} else {//源区间不为空
				assert(bd<=ed);//目标区间可以为空
				if (bd==ed) {
					for_m(i, bs, es) {//对每个源segment编号
						els.append(i+1);
						cls.append(0);
						ladder_set.add(Ladder(i+1, 0));
					}
				} else {
					for_m(i, bs, es) {//对每个源segment编号
						for_m(j, bd, ed) {//对每个目标segment编号
							els.append(i+1);
							cls.append(j+1);
							ladder_set.add(Ladder(i+1, j+1));
						}
					}
				}
			}
		}
	}
	
	void gen_chunkpair() {
		assert(xs.size()+1==ss.size() AND ys.size()+1==ds.size());//确保已经生成了ss, ds
		cps.clear();
		uint K=xs.size();//, M=ess.size(), N=css.size();
		for_n(k, K) {//对每个源chunk编号
			uint kk=diss[k];//目标chunk编号
			uint bs=ss[k], es=ss[k+1];//源chunk的segs区间
			uint bd=ds[kk], ed=ds[kk+1];//目标chunk的segs区间
			Chunk en(ensegs.iter(bs), ensegs.jter(es)), cn(cnsegs.iter(bd), cnsegs.jter(ed));
			// ChunkPair cp(en, cn);
			// cps.append(cp);
			cps.append(ChunkPair(en, cn));
		}
	}
	void gen_cp_scores() {
		//gen cp scores
		uint K=acc_scores.size();
		if (K==0) return;
		cp_scores.append(acc_scores[0]);
		for_m(k, 1, K) cp_scores.append(acc_scores[k]-acc_scores[k-1]);
	}

public:
	Alignment():ssinited(false) {}
	Alignment(istream& in) {//init_from_human_align
		uint x, y, dis;
		vocabulary& envcb=pconf->get_en_vocab();
		vocabulary& cnvcb=pconf->get_cn_vocab();
		string s;
		while(getline(in, s)) {
			//log_info("readed s="<<s);
			istringstream line(s);
			line>>x>>y>>dis;
			assert(x>=0 AND y>=0);
			assert(dis==0);//暂时只处理不交叉的chunk对齐
			log_debug("readed x="<<x<<" and y="<<y);
			for_n(i, x) {
				getline(in, s);
				log_debug("readed en s="<<s);
				
				istringstream iss(s);
				sentence snt;
				snt.parse(iss, envcb);

				ens.append(snt);
				ensegs.append(segment(snt, envcb));
			}
			for_n(i, y) {
				getline(in, s);
				log_debug("readed cn s="<<s);

				istringstream iss(s);
				sentence snt;
				snt.parse(iss, cnvcb);

				cns.append(snt);
				cnsegs.append(segment(snt, cnvcb));
			}

			cells.append(cell(x, y));
			
		}
		ssinited=true;

		uint K=cells.size();
		for_n(k, K) {
			cell& best=cells[k];
			xs.append(best.x);
			ys.append(best.y);
			acc_scores.append(best.align_score);
		}

		gen_cp_scores();
		gen_chunk_index();
		gen_ladder();
		gen_chunkpair();

	}

	void init_input_segs(const Chunk& ensegs, const Chunk& cnsegs) {
		this->ensegs=ensegs;
		this->cnsegs=cnsegs;
		ssinited=true;
	}
	
	//void init_chunk_len_from_reversed(list<uint>& rxs, list<uint>& rys, list<double>& racc_scores) {
	void init_chunk_len_from_reversed(list<cell>& rcells) {
		cells.assign(rcells.rbegin(), rcells.rend());
		uint K=cells.size();

		xs.clear();
		ys.clear();
		acc_scores.clear();
		for_n(k, K) {
			cell& best=cells[k];
			xs.append(best.x);
			ys.append(best.y);
			acc_scores.append(best.align_score);
		}

		gen_cp_scores();
		gen_chunk_index();
		gen_ladder();
		gen_chunkpair();
	}
	
	//返回第k个chunk pair的对齐模式
	AlignMode get_align_mode(uint k) {
		assert(k>=0 AND k<xs.size());
		return AlignMode(xs[k], ys[k]);
	}
	
	uint size() const {//返回chunk pair个数
		assert(xs.size()==cps.size());//确保已经生成了cps
		return cps.size();
	}

	const set<Ladder>& get_ladder_set() const {
		return ladder_set;
	}

	inline const Chunk& get_en_segs() const { return ensegs; }
	inline const Chunk& get_cn_segs() const { return cnsegs; }
	
	//输出便于阅读的对齐结果
	 void dump_human_readable(ostream& o) {
		assert(xs.size()==cps.size());//确保已经生成了cps
		uint K=xs.size();//, M=ess.size(), N=css.size();
		for_n(k, K) {//对每个源chunk编号
			uint kk=diss[k];//目标chunk编号
			uint bs=ss[k], es=ss[k+1];//源chunk的segs区间
			uint bd=ds[kk], ed=ds[kk+1];//目标chunk的segs区间
			//ChunkPair& cp=cps[k];
			//Chunk& en=cp.en;
			//Chunk& cn=cp.cn;
			o<<"# ChunkPair k="<<k+1<<"/K="<<K<<" mode="<<get_align_mode(k)<<" x="<<cells[k].x<<" y="<<cells[k].y<<" xlen="<<cells[k].xlen<<" ylen="<<cells[k].ylen<<"  likehood="<<cp_scores[k]<<endl;
			
			//o<<" align_score="<<cells[k].align_score<<" likehood_score="<<cells[k].likehood_score<<endl;
			o<<"# e2c="<<cells[k].likehood_score_e2c<<" c2e="<<cells[k].likehood_score_c2e<<" length_penalty="<<cells[k].length_penalty<<" prior_prob_xy="<<cells[k].prior_prob_xy<<" accumulate="<<acc_scores[k]<<endl;
			for_m(i, bs, es) {
				segment& seg=ensegs[i];
				o<<i+1<<" : ";
				seg.dump(o);
				o<<endl;
			}
			o<<"--------------------------------------------------------------------"<<endl;
			for_m(j, bd, ed) {
				segment& seg=cnsegs[j];
				o<<j+1<<" : ";
				seg.dump(o);
				o<<endl;
			}
			o<<endl;
		}
	 }
	
	ostream& save(ostream& o) {
		uint K=cps.size();
		o<<"<Alignment>"<<endl;

		//for human readable
		if (pconf->output_human_readable_result) {
			o<<"<HumanReadableResult>"<<endl;
			o<<"<![CDATA["<<endl;
			dump_human_readable(o);
			o<<"]]>"<<endl;
			o<<"</HumanReadableResult>"<<endl;
		}

		// for chunk pairs
		if (pconf->output_chunk_pairs) {
			o<<"<ChunkPairs K="<<K<<">"<<endl;
			for_n(k, K) {
				o<<"<ChunkPair k="<<k<<">"<<endl;
				o<<"<AlignMode>"<<get_align_mode(k)<<"</AlignMode>"<<endl;
				o<<cps[k]<<endl;
				o<<"</ChunkPair>"<<endl;
			}
			o<<"</ChunkPairs>"<<endl;
		}

		// for all alignment mode list
		o<<"<AlignModeList K="<<K<<">"<<endl;
		for_n(k, K) {
			o<<"<AlignMode k="<<k<<" mode="<<get_align_mode(k)<<">";
			uint kk=diss[k];//目标chunk编号
			uint bs=ss[k], es=ss[k+1];//源chunk的segs区间
			uint bd=ds[kk], ed=ds[kk+1];//目标chunk的segs区间
			for_m(i, bs, es) {
				o<<i;
				if (i+1<es) o<<',';
			}
			o<<'-';
			for_m(i, bd, ed) {
				o<<i;
				if (i+1<ed) o<<',';
			}
			o<<"</AlignMode>"<<endl;
		}
		o<<"</AlignModeList>"<<endl;

		// for chunking index
		o<<"<ChunkingIndexList>"<<endl;
		o<<"<!-- Source Index Sequence -->"<<endl;
		o<<"<ss>"<<ss<<"</ss>"<<endl;
		o<<"<!-- Destination Index Sequence -->"<<endl;
		o<<"<ds>"<<ds<<"</ds>"<<endl;
		o<<"</ChunkingIndexList>"<<endl;

		// for chunking distortion table
		o<<"<ChunkingDistortionTable>"<<endl;
		o<<"<!-- Chunk Distortion Sequence -->"<<endl;
		o<<"<diss>"<<diss<<"</diss>"<<endl;
		o<<"</ChunkingDistortionTable>"<<endl;

		// for chunk alignment ladder sequence
		o<<"<ChunkAlignLadder>"<<endl;
		o<<"<!-- English Ladder Sequence -->"<<endl;
		o<<"<els>"<<els<<"</els>"<<endl;
		o<<"<!-- Chinese Ladder Sequence -->"<<endl;
		o<<"<cls>"<<cls<<"</cls>"<<endl;
		o<<"<!-- Chunk Ladders -->"<<endl;
		o<<"<ladders>";
		uint n=cls.size();
		for_n(i, n) o<<els[i]<<'-'<<cls[i]<<' ';
		o<<"</ladders>"<<endl;
		o<<"<ladder_set>";
		o<<ladder_set<<endl;
		o<<"</ladder_set>"<<endl;
		o<<"</ChunkAlignLadder>"<<endl;

		// for original input segments
		if (pconf->output_input_segments) {
			o<<"<InputSegments>"<<endl;
			o<<"<!-- English Segment Sequence -->"<<endl;
			o<<"<ensegs>";
			o<<ensegs;
			o<<"</ensegs>"<<endl;
			o<<"<!-- Chinese Segment Sequence -->"<<endl;
			o<<"<cnsegs>";
			o<<cnsegs;
			o<<"</cnsegs>"<<endl;
			o<<"</InputSegments>"<<endl;
		}



		return o<<"</Alignment>"<<endl;
	}
	
	friend inline ostream& operator<<(ostream& o, Alignment& a) { return a.save(o); }
};

#endif /* ALIGNMENT_H_1357744707_3 */

