#ifndef CONFIG_H_1357732737_21
#define CONFIG_H_1357732737_21
/**
 * File: config.h
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-09 19:58:57.211694
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "word.h"
#include "token.h"
#include "pos.h"
#include "lexicon.h"
#include "vocab.h"
#include "sent.h"
#include "cooc.h"
#include "probdict.h"

// #define LOG_LEVEL_NONE 0
// #define LOG_LEVEL_DEBUG 10
// #define LOG_LEVEL_INFO 20
// #define LOG_LEVEL_STATUS 30
// #define LOG_LEVEL_WARN 40
// #define LOG_LEVEL_ERROR 50
// #define LOG_LEVEL_FATAL 60
const uint VERBOSE_DEFAULT=LOG_LEVEL_DEBUG;

const uint ALIGN_MODE_SENT=0;
const uint ALIGN_MODE_SUBSENT=1;
const uint ALIGN_MODE_END=2;
const uint ALIGN_MODE_DEFAULT=ALIGN_MODE_SENT;

const uint XMAX_DEFAULT=2;
const uint YMAX_DEFAULT=2;

const double ALPHA_DEFAULT=1;
const double LAMBDA_DEFAULT=0.5;

const double CN_EN_LENGTH_RATIO_DEFALUT=0.3;//old: 0.634
const uint EN_LENGTH_TYPE_FOR_RATIO_DEFAULT=1;
const uint CN_LENGTH_TYPE_FOR_RATIO_DEFAULT=3;

class Config {
public:
// private:
	// template<class T>
	// void clean(T* ptr) {
		// if (ptr) {
			// delete ptr;
			// ptr=NULL;
		// }
	// }
public:// temperately make data members public for convinience
	
	//for dynamic programming
	int max_en_segs_in_a_chunk;
	int max_cn_segs_in_a_chunk;
	double alpha;
	double lambda;

	//for alignment
	uint align_mode;
	bool dont_use_e2c_probdict;
	bool dont_use_c2e_probdict;
	bool dont_use_length_ratio;
	bool enable_cross_align;
	double cn_en_length_ratio;
	uint en_length_type_for_ratio;
	uint cn_length_type_for_ratio;

	//for debug
	bool output_chunk_pairs;
	bool output_reference_sentence;
	bool output_input_segments;
	bool output_human_readable_result;

	//for evaluation
	str system_name;
	str e2c_prob_dict;
	str c2e_prob_dict;
	str pos_tag_set;

public:
	//空的构造函数，针对python binding设计
	Config(int max_en_segs_in_a_chunk, int max_cn_segs_in_a_chunk) {}
	Config(OptionArgs& optargs) {
		init(optargs);
	}
	
	const bool init(OptionArgs& optargs) {
		log_info("now in constructor of Config");
		
		e2c_prob_dict=(str)optargs["e2c_prob_dict"];
		c2e_prob_dict=(str)optargs["c2e_prob_dict"];
		pos_tag_set=(str)optargs["pos_tag_set"];
		
		align_mode=(uint)optargs.get("align_mode");
		if (align_mode>=ALIGN_MODE_END) {
			log_warn("bad align mode: "<<align_mode<<", now set to default: "<<ALIGN_MODE_DEFAULT);
			align_mode=ALIGN_MODE_DEFAULT;
		}
		
		max_en_segs_in_a_chunk=(uint)optargs.get("max_en_segs_in_a_chunk");
		if (max_en_segs_in_a_chunk==0) {
			log_warn("max_en_segs_in_a_chunk should be lager than 0, now set to default");
			max_en_segs_in_a_chunk=XMAX_DEFAULT;
		}
		max_cn_segs_in_a_chunk=(uint)optargs.get("max_cn_segs_in_a_chunk");
		if (max_cn_segs_in_a_chunk==0) {
			log_warn("max_cn_segs_in_a_chunk should be lager than 0, now set to default");
			max_cn_segs_in_a_chunk=YMAX_DEFAULT;
		}

		alpha=(double)optargs.get("alpha");
		if_not (alpha>=0 AND alpha<=1) {
			log_warn("bad alpha: not in [0, 1], now set to default: "<<ALPHA_DEFAULT);
			alpha=ALPHA_DEFAULT;
		}
		lambda=(double)optargs.get("lambda");
		if_not (lambda>=0) {
			log_warn("bad lambda: should in [0, ~) , now set to default: "<<LAMBDA_DEFAULT);
			lambda=LAMBDA_DEFAULT;
		}

		enable_cross_align=(bool)optargs.get("enable_cross_align");
		output_chunk_pairs=(bool)optargs.get("output_chunk_pairs");
		output_reference_sentence=(bool)optargs.get("output_reference_sentence");
		output_input_segments=(bool)optargs.get("output_input_segments");
		output_human_readable_result=(bool)optargs.get("output_human_readable_result");
		dont_use_e2c_probdict=(bool)optargs.get("dont_use_e2c_probdict");
		dont_use_c2e_probdict=(bool)optargs.get("dont_use_c2e_probdict");
		dont_use_length_ratio=(bool)optargs.get("dont_use_length_ratio");
		
		cn_en_length_ratio=(double)optargs.get("cn_en_length_ratio");
		if_not (cn_en_length_ratio>0) {
			log_warn("bad cn_en_length_ratio: must be positive, now set to default: "<<CN_EN_LENGTH_RATIO_DEFALUT);
			cn_en_length_ratio=CN_EN_LENGTH_RATIO_DEFALUT;
		}

		en_length_type_for_ratio=(uint)optargs.get("en_length_type_for_ratio");
		if_not (en_length_type_for_ratio>=0 AND en_length_type_for_ratio<=1) {
			log_warn("bad en_length_type_for_ratio: should be in [0, 1], now set to default");
			en_length_type_for_ratio=EN_LENGTH_TYPE_FOR_RATIO_DEFAULT;
		}
		cn_length_type_for_ratio=(uint)optargs.get("cn_length_type_for_ratio");
		if_not (cn_length_type_for_ratio>=0 AND cn_length_type_for_ratio<=4) {
			log_warn("bad cn_length_type_for_ratio: should be in [0, 4], now set to default");
			cn_length_type_for_ratio=CN_LENGTH_TYPE_FOR_RATIO_DEFAULT;
		}

		system_name=(str)optargs["system_name"];
		if (system_name.empty()) system_name="default";

		log_info("system_name="<<system_name);
		log_info("max_en_segs_in_a_chunk="<<max_en_segs_in_a_chunk);
		log_info("max_cn_segs_in_a_chunk="<<max_cn_segs_in_a_chunk);
		log_info("alpha="<<alpha);
		log_info("lambda="<<lambda);
		log_info("cn_en_length_ratio="<<cn_en_length_ratio);
		log_info("en_length_type_for_ratio="<<en_length_type_for_ratio);
		log_info("cn_length_type_for_ratio="<<cn_length_type_for_ratio);

		log_info("output_chunk_pairs="<<output_chunk_pairs);
		log_info("output_reference_sentence="<<output_reference_sentence);
		log_info("output_input_segments="<<output_input_segments);
		log_info("output_human_readable_result="<<output_human_readable_result);
		log_info("dont_use_e2c_probdict="<<dont_use_e2c_probdict);
		log_info("dont_use_c2e_probdict="<<dont_use_c2e_probdict);
		log_info("dont_use_length_ratio="<<dont_use_length_ratio);
		
		return true;
	}
	
	void load_probdict(ProbDict& pd, Vocabulary& vcb, str& fp) {
		path p(fp);
		if (p.isfile()) {
			ifstream fin(p.tocstr());
			datetime start;
			pd.load(fin, vcb);
			// pd.normalize();
			log_status("loaded prob dict: "<<fp<<" in "<<start.elapse()<<"s with "<<pd.size()<<" keys");
		} else die_error("bad file path when loading prob dict: "<<fp);
	}

	void load_e2c_probdict(ProbDict& pde2c, Vocabulary& vcb) {
		load_probdict(pde2c, vcb, e2c_prob_dict);
	}
	
	void load_c2e_probdict(ProbDict& pdc2e, Vocabulary& vcb) {
		load_probdict(pdc2e, vcb, c2e_prob_dict);
	}
	
	void load_tag_set(PosTagSet& tagset) {
		str fp=pos_tag_set;
		path p(fp);
		if (p.isfile()) {
			ifstream fin(p.tocstr());
			datetime start;
			tagset.load(fin);
			log_status("loaded tag set: "<<fp<<" in "<<start.elapse()<<"s with "<<tagset.size()<<" items");
		} else die_error("bad file path when loading tag set: "<<fp);
	}
};


#endif /* CONFIG_H_1357732737_21 */
