#ifndef ALIGNER_H_1359789066_57
#define ALIGNER_H_1359789066_57
/**
 * File: aligner.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-02-02 15:11:06.571000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "config.h"
#include "chunk.h"
#include "alignment.h"
#include "probdict.h"
#include "resource.h"
#include "lexicon.h"

class IChunkAligner {
public:
	//struct cell {
	//	double align_score, likehood_score, likehood_score_e2c, likehood_score_c2e, prior_prob_xy, xlen, ylen, length_penalty;
	//	uint x, y;
	//	cell(): align_score(0.0), likehood_score(0.0), likehood_score_e2c(0.0), likehood_score_c2e(0.0), prior_prob_xy(0.0), xlen(0.0), ylen(0.0), length_penalty(0.0), x(0), y(0) {}
	//};
	
	typedef AlignCell cell;
	typedef matrix2d_heap<cell> memo;
	typedef matrix2d<double> ProbTable;
	
protected:
	//resources
	ProbDict& pde2c;
	ProbDict& pdc2e;
	Vocabulary& vocab;
	NPIndexer& npindxer;
	VPIndexer& vpindxer;
	PosTagSet& postagset;
	LexiconHistory lexhistory;
	
	//configs
	Config& conf;
	uint xmax;
	uint ymax;
	double alpha;
	double lambda;
	
	// input
	SentList ensents, cnsents;
	Chunk ensegs, cnsegs;
	
	//output
	Alignment result;

	//other
	ProbTable* prior;//align mode prior distribution;
	
public:
	IChunkAligner(ChunkAlignResource& res):
		prior(NULL),
		conf(res.conf),
		pde2c(res.pde2c),
		pdc2e(res.pdc2e),
		vocab(res.vocab),
		npindxer(res.npindxer),
		vpindxer(res.vpindxer),
		postagset(res.postagset)
	{
		log_info("now in constructor of IChunkAligner");
		init();
	}

	virtual ~IChunkAligner() {
		clean();
	}
	
protected:
	void clean() {
		if (prior) {
			log_info("now free memory of prior table");
			delete prior;
			prior=NULL;
		}
	}
	
	void init() {
		xmax=conf.max_en_segs_in_a_chunk;
		ymax=conf.max_cn_segs_in_a_chunk;
		lambda=conf.lambda;
		alpha=conf.alpha;

		clean();
		prior=new ProbTable(xmax, ymax);
		assert(prior);
		ProbTable& pt=*prior;
		double total_score=0;
		
		for_n(i, xmax) {
			for_n(j, ymax) {
				int x=i+1, y=j+1;
				double score=exp(-lambda*(alpha*(x+y)+(1-alpha)*abs(x-y)));
				pt(i, j)=score;
				total_score+=score;
			}
		}
		log_info("generated prior prob table, xmax="<<xmax<<", ymax="<<ymax<<", total_score="<<total_score);
		assert(total_score!=0);
		for_n(i, xmax) {
			for_n(j, ymax) {
				pt(i, j)=pt(i, j)/total_score;
				log_info("prior["<<i+1<<", "<<j+1<<"]="<<pt(i, j));
			}
		}
		log_info("finished prior prob table normalization");
	}
	
public:
	bool read_chunk_pair(istream& en, istream& cn) {
		if(read_chunk(en, ensents, ensegs)) {
			log_info("readed an en chunk with "<<ensents.size()<<" sents as "<<ensegs.size()<<" segs");
			if (read_chunk(cn, cnsents, cnsegs)) {
				log_info("readed a cn chunk with "<<cnsents.size()<<" sents as "<<cnsegs.size()<<" segs");
				return true;
			} else {
				log_warn("can not read cn chunk");
			}
		} else {
			log_warn("can not read en chunk");
		}
		return false;
	}

	bool read_chunk(istream& in, SentList& ss, Chunk& segs) {
		ss.clear();
		segs.clear();
		Sentence snt;
		while (read_sent(in, snt)) ss.append(snt);//最后一次读取剩余的1个空白行返回false，2个空白行是chunk边界
		//TODO: convert sents to segs
		if (ss.empty()) return false;//没有读到任何句子
		
		if (conf.align_mode==ALIGN_MODE_SENT) {
			//1. 句子对齐，每个句子是一个segment
			uint n=ss.size();
			log_debug("readed "<<n<<" sentences");
			for_n(i, n) {
				Sentence& s=ss[i];
				Segment seg(s.begin(), s.end());
				segs.append(seg);
			}
			log_debug("got "<<segs.size()<<" segments");
			return true;
		} else if (conf.align_mode==ALIGN_MODE_SUBSENT) {
			//2. 亚句对齐，根据某种机制将句子划分成segs
			
			//现暂时作如下处理：每个单词是一个seg, 句子之间加入特殊的句子边界单词
			uint n=ss.size();
			for_n(i, n) {
				Sentence& s=ss[i];
				uint m=s.size();
				for_n(j, m) {
					Segment seg;
					seg.append(s[j]);
					segs.append(seg);
				}
				if (i!=n-1) {//不是最后一句
					Segment seg;
					Word word((Lexicon*)WORD_BOS);//特殊单词，代表句子边界
					seg.append(word);
					segs.append(seg);
				}
			}
			return true;
		} else {
			//TODO: 其他的诸如, 名词短语动词短语作为一个seg啊,blabla
			return false;
		}
	}
	
	bool read_sent(istream& in, Sentence& sent) {//读取若干的lexicon加1个空白行
		string s;
		bool first=true;
		while (getline(in, s)) {
			if (str(s).striped().empty()) break;
			first=false;
			istringstream iss(s);
			Lexicon& lex=lexhistory.create();
			if (NOT read_lexicon(iss, lex)) {
				log_error("in read_sent, can not read lexicon: "<<s);
				return false;
			}
			//读取成功,将lexicon转成word
			Word word(lex);
			sent.append(word);
		}
		if (first) {
			log_debug("in read_sent, first line is empty or EOF when read sent: "<<s);
			return false;
		}
		//log_debug("return true in read_sent");
		return true;
	}
	
	bool read_lexicon(istream& in, Lexicon& lex) {
		string token, lemma, pos, np, vp;
		if (in>>token>>lemma>>pos>>np>>vp) {//必须每个值都能读到
			lex.token=vocab(token);
			lex.lemma=vocab(lemma);
			lex.pos=postagset(pos);
			lex.np=npindxer(np);
			lex.vp=vpindxer(vp);
			return true;
		}
		return false;
	}
	
	void write_result(ostream& out) {
		datetime now;
		out<<"### Alignment Result Dumped @ "<<now<<endl;
		out<<"### ensents:"<<ensents.size()<<" ensegs:"<<ensegs.size()<<" cnsents:"<<cnsents.size()<<" cnsegs:"<<cnsegs.size()<<endl;
		result.dump(out);
		out<<endl;
	}
	
	double get_log_prob_of_prior_dist(uint x, uint y) {//align mode dist
		ProbTable& pt=*prior;
		assert(x>=1 AND x<=xmax AND y>=1 AND y<=ymax);
		return pt(x-1, y-1);
	}

	virtual bool align()=0;
};

class ILikehood {
public:
	struct cell {
		double likehood;//likehood for seg pair i, j
		bool cached;//is the 2 likehood cached
		
		cell(): likehood(0.0), cached(false) {}
	};
	typedef matrix2d_heap<cell> memo;

protected:
	IChunkAligner& aligner;
	ProbDict& pdict;
	Chunk& src_chunk;
	Chunk& dst_chunk;
	Vocabulary& vocab;
	ChunkInfo src_chunk_info;
	memo mm_seg2seg;//for cache
	memo mm_word2seg;//for cache
	
public:
	ILikehood(
		Vocabulary& vocab, 
		ProbDict& pdict, 
		Chunk& src_chunk, 
		Chunk& dst_chunk, 
		IChunkAligner& aligner
	):
		vocab(vocab), 
		pdict(pdict), 
		src_chunk(src_chunk), 
		dst_chunk(dst_chunk), 
		mm_seg2seg(src_chunk.size(), dst_chunk.size()), 
		src_chunk_info(src_chunk), 
		mm_word2seg(src_chunk_info.total_unique_words(), dst_chunk.size()), 
		aligner(aligner) 
	{}
	virtual ~ILikehood() {}

	//caculate continious segments pairs
	virtual double caculate(uint src_seg_id_begin, uint src_seg_id_end, uint dst_seg_id_begin, uint dst_seg_id_end)=0;

	//caculate non-continious segments pairs
	virtual double caculate(list<uint>& src_seg_ids, list<uint>& dst_seg_ids)=0;

	//caculate likehood for 2 segment pair
	virtual double caculate(uint src_seg_id, uint dst_seg_id)=0;
};

class Model1Likehood : public ILikehood {
public:
	Model1Likehood(
		Vocabulary& vocab, 
		ProbDict& pdict, 
		Chunk& src_chunk, 
		Chunk& dst_chunk, 
		IChunkAligner& aligner
	): ILikehood(vocab, pdict, src_chunk, dst_chunk, aligner) {}
		
	virtual ~Model1Likehood() {}

	//caculate continious segments pairs
	double caculate(uint src_seg_id_begin, uint src_seg_id_end, uint dst_seg_id_begin, uint dst_seg_id_end) {
		uint x=src_seg_id_end-src_seg_id_begin;
		uint y=dst_seg_id_end-dst_seg_id_begin;
		//log_debug("	now caculate likehood, x="<<x<<", y="<<y);
		if (x==0 AND y==0) return -100000.0;//forbid align mode 0:0
		if (x==0) return -1.0*y;//0:N
		if (y==0) return -1.0*x;//N:0

		double score_segs2segs=1.0;
		for_m(src_seg_id, src_seg_id_begin, src_seg_id_end) {
			double score_seg2segs=0;
			for_m(dst_seg_id, dst_seg_id_begin, dst_seg_id_end) {
				double score_seg2seg=0;
				if (mm_seg2seg.is_active(src_seg_id, dst_seg_id)) {
					score_seg2seg=mm_seg2seg(src_seg_id, dst_seg_id).likehood;
				} else {
					score_seg2seg=caculate(src_seg_id, dst_seg_id);
					mm_seg2seg(src_seg_id, dst_seg_id).likehood=score_seg2seg;
				}
				//score_seg2segs+=log(score_seg2seg+0.00001);
				score_seg2segs+=score_seg2seg;
			}
			//score_segs2segs*=max(score_segs2segs*score_seg2segs, 0.001);
			score_segs2segs+=score_seg2segs;
		}
		return score_segs2segs;

	/*	list<uint> src_seg_ids, dst_seg_ids;
		for_m(src_seg_id, src_seg_id_begin, src_seg_id_end) src_seg_ids.append(src_seg_id);
		for_m(dst_seg_id, dst_seg_id_begin, dst_seg_id_end) dst_seg_ids.append(dst_seg_id);

		return caculate(src_seg_ids, dst_seg_ids);*/
	}

	//caculate non-continious segments pairs
	double caculate(list<uint>& src_seg_ids, list<uint>& dst_seg_ids) {
		double score_segs2segs=0;
		for_iter(i, list<uint>, src_seg_ids) {
			uint src_seg_id=*i;
			double score_seg2segs=0;
			for_iter(j, list<uint>, dst_seg_ids) {
				uint dst_seg_id=*j;
				double score_seg2seg=0;
				if (mm_seg2seg.is_active(src_seg_id, dst_seg_id)) {
					score_seg2seg=mm_seg2seg(src_seg_id, dst_seg_id).likehood;
				} else {
					score_seg2seg=caculate(src_seg_id, dst_seg_id);
					mm_seg2seg(src_seg_id, dst_seg_id).likehood=score_seg2seg;
				}
				score_seg2segs+=log(score_seg2seg+0.00001);
			}
			score_segs2segs+=score_seg2segs;
		}
		return score_segs2segs;
	}

	//caculate likehood for 2 segment pair
	double caculate(uint src_seg_id, uint dst_seg_id) {
		
		Segment& src_seg=src_chunk[src_seg_id];
		Segment& dst_seg=dst_chunk[dst_seg_id];

		//using dictionary
		//list<word> en_words, cn_words;
		//en.get_bag_of_words(en_words);
		//cn.get_bag_of_words(cn_words);
		//uint X=en_words.size(), Y=cn_words.size();
		//log_debug("		generated bag of words, en words size="<<X<<", cn words size="<<Y);

		uint total_src_word=src_seg.size(), total_dst_word=dst_seg.size();//words cnt for src and dst seg

		double score_seg2seg=0;
		//double score_seg2seg=1.0;
		for_n(src_word_id, total_src_word) {
			double score_word2seg=0;
			Word src_word=src_seg[src_word_id];
			//now begin caculate likehood of source word s to target segmenet dst_seg
			//firstly, check if this score has been caculated before
			uint src_word_id_in_chunk=src_chunk_info.get_unique_words_index(src_word);
			if (mm_word2seg.is_active(src_word_id_in_chunk, dst_seg_id)) {//if cached
				score_word2seg=mm_word2seg(src_word_id_in_chunk, dst_seg_id).likehood;
			} else {
				for_n(dst_word_id, total_dst_word) {
					Word dst_word=dst_seg[dst_word_id];
					//log_debug("		look up prob dict for word pair e="<<e<<" ("<<conf.get_en_vocab()[e]<<"), c="<<c<<" ("<<conf.get_cn_vocab()[c]<<")");
					Prob trans_prob;
					bool hit=pdict.get(src_word, dst_word, trans_prob);
					if (hit) {
						assert(trans_prob>=0 AND trans_prob<=1);
						//log_debug("		hit e2c dict, e2c="<<e2c<<" score="<<score);
						score_word2seg+=trans_prob;//TODO: count word appear multiple times once
						//TODO: or select the max score of all s2d as score_i
						//TODO: moreover, consider the distance diff of the src word and dst word
						//log_debug("		new score="<<score);
					}
				}
				//word2seg_score/=total_src_word;
				
				//score_word2seg=log(score_word2seg+0.001);

				mm_word2seg(src_word_id_in_chunk, dst_seg_id).likehood=score_word2seg;
			}
			//score_seg2seg*=score_word2seg;
			score_seg2seg+=score_word2seg;
		}
		// return fabs( en.total_words() - cn.total_words() ) * 10;
		//score=10000;
		
		// log_debug("in likehood x="<<x<<" y="<<y<<" score="<<score);
		return score_seg2seg;
	}
};

class DynPrgmChunkAligner : public IChunkAligner {
private:
	//TODO: 禁用拷贝构造
	//DynPrgmChunkAligner(const DynPrgmChunkAligner& r):IChunkAligner(r.res) {}
	
public:
	DynPrgmChunkAligner(ChunkAlignResource& res):IChunkAligner(res) {}

	bool align() {
	
		log_info("now in align(ensegs, cnsegs)");
		log_info("step1. search");
		uint M=ensegs.size(), N=cnsegs.size();
		ChunkInfo en(ensegs), cn(cnsegs);
		memo mm(M+1, N+1);

		//likehood caculator
		ILikehood* likehood_e2c=NULL;
		if_not (conf.dont_use_e2c_probdict) likehood_e2c=new Model1Likehood(vocab, pde2c, ensegs, cnsegs, *this);

		ILikehood* likehood_c2e=NULL;
		if_not (conf.dont_use_c2e_probdict) likehood_c2e=new Model1Likehood(vocab, pdc2e, cnsegs, ensegs, *this);

		uint i, j;
		for_n(i, M+1) {//for each en seg and 0
			for_n(j, N+1) {//for each cn seg and 0
				log_debug("	now in cell i="<<i<<", j="<<j);

				cell& best=mm(i, j);//make it active
				bool first=true;//the first time to update this cell

				if (i==0 AND j==0) {
					best.align_score=0;
					continue;
				}
				
				//log_debug("	cell["<<i<<"]["<<j<<"], initial max_score="<<max_score<<", bestx="<<bestx<<", besty="<<besty);
				
				for_n(x, xmax+1) {
					if (i<x) continue;
					for_n(y, ymax+1) {
						if (j<y) continue;
						assert(mm.is_active(i-x, j-y));//the last cell must be visited
						double partial_score=mm(i-x, j-y).align_score;
						double likehood_score_e2c=likehood_e2c?likehood_e2c->caculate(i-x, i, j-y, j):0;
						double likehood_score_c2e=likehood_c2e?likehood_c2e->caculate(j-y, j, i-x, i):0;
						
						double prior_prob_xy;//=1.0;
						if (x!=0 AND y!=0) prior_prob_xy=get_log_prob_of_prior_dist(x, y);//TODO: for x==0 or y==0
						else if ((x==0 AND y==1) OR (x==1 AND y==0)) prior_prob_xy=1.0/(xmax*ymax);//TODO: sum(prior_prob_xy) is not 1
						else prior_prob_xy=0;

						//length ratio
						double length_penalty=1;
						double xlen=-1;//undefined
						double ylen=-1;//undefined
						if_not (conf.dont_use_length_ratio) {
							double yperx=conf.cn_en_length_ratio;
							
							if (conf.en_length_type_for_ratio==0) xlen=1.0*en.total_words(i-x, i);
							else if (conf.en_length_type_for_ratio==1) xlen=1.0*en.total_tokens_len(vocab, i-x, i);
							else assert(false);

							if (conf.cn_length_type_for_ratio==0) ylen=1.0*cn.total_words(j-y, j);
							else if (conf.cn_length_type_for_ratio==1) ylen=1.0*cn.total_tokens_len(vocab, j-y, j);
							else if (conf.cn_length_type_for_ratio==2) ylen=1.0*cn.total_tokens_len(vocab, j-y, j)/2;
							else if (conf.cn_length_type_for_ratio==3) ylen=1.0*cn.total_tokens_len(vocab, j-y, j)/3;//TODO: utf8 recognizer
							else if (conf.cn_length_type_for_ratio==4) ylen=1.0*cn.total_tokens_len(vocab, j-y, j)/3;//TODO: unicode recognizer
							else assert(false);

							double virtual_ylen=xlen*yperx;
							double virtual_xlen=ylen/yperx;
							if (max(xlen, virtual_xlen)>60) length_penalty=log(6+4.0*min(virtual_ylen, ylen) / max(virtual_ylen, ylen)) / log(10.0);
							
							//score*=length_penalty*penalty_matrix[nx][ny];
						}
						double likehood_score=prior_prob_xy*length_penalty*(likehood_score_e2c+likehood_score_c2e+0.0001);
						double align_score=partial_score+likehood_score;

						//log_debug("	partial_score="<<partial_score<<", likehood_score="<<likehood_score<<", new_score="<<new_score);
						if (first==true OR best.align_score<align_score) {
							if (first) {
								log_debug("		set score: "<<align_score<<" x="<<x<<" y="<<y);
							} else {
								log_debug("		update score: "<<best.align_score<<" -> "<<align_score<<" x="<<x<<" y="<<y);
							}
							best.align_score=align_score;
							best.x=x;
							best.y=y;
							best.likehood_score=likehood_score;
	
							best.likehood_score_e2c=likehood_score_e2c;
							best.likehood_score_c2e=likehood_score_c2e;

							best.prior_prob_xy=prior_prob_xy;

							best.xlen=xlen;
							best.ylen=ylen;
							best.length_penalty=length_penalty;
							first=false;
						}
					}
				}
			}
		}
		
		assert(mm.is_active(M, N));//the M, N cell must have been visited

		log_info("step2. backtrack");
		//list<uint> rxs, rys;//reversed xs and ys
		//list<double> racc_scores;//reversed accumulated scores
		list<cell> rcells;

		i=M, j=N;
		while (i>=0 AND j>=0) {
			cell& best=mm(i, j);
			uint x=best.x, y=best.y;
			double score=best.align_score;
			if (x==0 AND y==0) {
				assert(i==0 OR j==0);
				break;
			}
			log_debug("	x="<<x<<", y="<<y<<" with score="<<score);
			/*rxs.append(x);
			rys.append(y);
			racc_scores.append(score);*/
			rcells.append(best);
			i-=x;
			j-=y;
		}
		
		result.init(rcells);

		//clean likehood caculator
		if (likehood_e2c!=NULL) delete likehood_e2c;
		if (likehood_c2e!=NULL) delete likehood_c2e;
		return true;
	}
};


#endif /* ALIGNER_H_1359789066_57 */
