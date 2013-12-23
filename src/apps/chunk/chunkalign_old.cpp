/**
 * File: chunkalign.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-06 20:53:37.933301
 * Written In: Peking University, beijing, China
 */

#define APP_NAME "Chunk"
#include "chunkalign.h"


int main (int argc, const char* argv[]) {
	OptionParser parser;
	parser.description("Chunk Alignment Toolkit\n"
				"	When ACTION is align, align all INPUT.en and INPUT.cn, the output will be written to INPUT.align.xml\n"
				"	When ACTION is eval, eval each INPUT.ref file, then output to INPUT.eval.xml, and output all eval statistics to NOW.eval.csv")
		.usage("%prog [OPTIONS] [ACTION]\n"
				"\t%prog [OPTIONS] align INPUT [INPUT] [INPUT] ...")
		.version("1.0")
		.epilog("ACTION can be one of these:\n"
			"  align\n"
			"  eval\n"
			"  rank\n"
			// "  sev		=	save-en-vocab\n"
			// "  scv		=	save-cn-vocab\n"
			// "  se2cd		=	save-e2c-prob-dict\n"
			// "  sc2ed		=	save-c2e-prob-dict\n"
			// "  de2cd		=	dump-e2c-prob-dict\n"
			// "  dc2ed		=	dump-c2e-prob-dict\n"
			"\n"
			"By jadesoul @ 2013-1-7\n"
			"please report bugs to wslgb2006@gmail.com");
	// parser.add_option("-e", "--en-vocab")
		// .action("store")
		// .set_default("en.vcb")
		// .help("the input english vocabulary, default as en.vcb");
	// parser.add_option("-c", "--cn-vocab")
		// .action("store")
		// .set_default("cn.vcb")
		// .help("the input chinese vocabulary, default as cn.vcb");
	// parser.add_option("-E", "--en-vocab-gizapp")
		// .action("store")
		// .set_default("")
		// .help("the input english vocabulary in gizapp format");
	// parser.add_option("-C", "--cn-vocab-gizapp")
		// .action("store")
		// .set_default("")
		// .help("the input chinese vocabulary in gizapp format");
	parser.add_option("-d", "--e2c-prob-dict")
		.action("store")
		.set_default("e2c.pdict")
		.help("the input english to chinese probilistic dictionary in plain format, default as e2c.pdict");
	parser.add_option("-f", "--c2e-prob-dict")
		.action("store")
		.set_default("c2e.pdict")
		.help("the input chinese to english probilistic dictionary in plain format, default as c2e.pdict");
	parser.add_option("-t", "--pos-tag-set")
		.action("store")
		.set_default("pos.tags")
		.help("the input pos tag set list in plain format, default as pos.tags");
	parser.add_option("-x", "--max-en-segs-in-a-chunk")
		.action("store")
		.type("int")
		.set_default(2)
		.help("default as 2");
	parser.add_option("-y", "--max-cn-segs-in-a-chunk")
		.action("store")
		.type("int")
		.set_default(2)
		.help("default as 2");
	parser.add_option("-X", "--enable-cross-align")
		.action("store_true")
		.set_default("0")
		.help("enable cross alignment of two adjacent chunk pair, default is false");
	parser.add_option("-p", "--output-chunk-pairs")
		.action("store_true")
		.set_default("0")
		.help("output chunk pairs when dump a alignmet, default is false");
	parser.add_option("-r", "--output-reference-sentence")
		.action("store_true")
		.set_default("0")
		.help("output reference sentence when dump a segment, default is false");
	parser.add_option("-i", "--output-input-segments")
		.action("store_true")
		.set_default("0")
		.help("output reference sentence when dump a alignment result, default is false");
	parser.add_option("-h", "--output-human-readable-result")
		.action("store_true")
		.set_default("1")
		.help("output human readable alignment result, default is false");
	parser.add_option("-n", "--dont-use-e2c-probdict")
		.action("store_true")
		.set_default("0")
		.help("don't use english to chinese prob dict when align, default is false");
	parser.add_option("-N", "--dont-use-c2e-probdict")
		.action("store_true")
		.set_default("0")
		.help("don't use chinese to english prob dict when align, default is false");
	parser.add_option("-l", "--dont-use-length-ratio")
		.action("store_true")
		.set_default("0")
		.help("don't use english chinese chunk length ratio when align, default is false");
	parser.add_option("-R", "--cn-en-length-ratio")
		.action("store")
		.type("float")
		.set_default(0.3)
		//.set_default(0.634)
		.help("cn en chunk length ratio for align, this indicates how many cn chars per each en char in a chunk, default is 0.3");
	parser.add_option("-g", "--en-length-type-for-ratio")
		.action("store")
		.type("int")
		.set_default(1)
		.help("english chunk length type for caculate length ratio, it can be 0(words) 1(bytes, or chars), default is 1");
	parser.add_option("-G", "--cn-length-type-for-ratio")
		.action("store")
		.type("int")
		.set_default(3)
		.help("chinese chunk length type for caculate length ratio, it can be 0(words) 1(bytes) 2(characters in GBK) 3(characters in UTF8) 4(characters in UNICODE), default is 3");
	parser.add_option("-a", "--alpha")
		.action("store")
		.type("float")
		.set_default(1)
		.help("alpha use to generate prior distribution of align mode x:y, should in [0, 1], default 1");
	parser.add_option("-m", "--lambda")
		.action("store")
		.type("float")
		.set_default(0.5)
		.help("alpha use to generate prior distribution of align mode x:y, if lambda==0 lead to equally distribution, default 0.5");
	parser.add_option("-s", "--system-name")
		.action("store")
		.set_default("eval")
		.help("the system name for evaluation, default is eval");
	parser.add_option("-v", "--verbose")
		.action("store")
		.type("int")
		.set_default(1)
		.help("log level for print status messages to stdlog, default is 1, which means all message will output, if it is set to 0, none will output to stdlog");
	OptionArgs& optargs = parser.parse_args(argc, argv);
	verbose=uint(optargs.get("verbose"));

	if (optargs.arg_size()==0) {
		parser.print_help();
		return 1;
	}
	
	string action=optargs[0];

	if ((action=="align" OR action=="eval" OR action=="rank") AND optargs.arg_size()<=1) {
		parser.print_help();
		return 1;
	}

	Config conf(optargs);
	pconf=&conf;

	log_debug("now in main, verbose="<<verbose<<", action="<<action);
	if (action=="align") {
		log_debug("before conf.load_all_for_alignment()");
		conf.load_all_for_alignment();
		log_debug("after conf.load_all_for_alignment()");
		DynPrgmAligner aligner(conf);
		uint n=optargs.arg_size();
		for_m(i, 1, n) {
			str prefix=optargs[i];
			str fp_cn=prefix+".cn", fp_en=prefix+".en", fp_align=prefix+".align.xml";
			if (path(fp_cn).isnfile() OR path(fp_en).isnfile()) {
				log_error(fp_cn<<" or "<<fp_cn<<" is not a good file path");
				continue;
			}
			ifstream fin_cn(fp_cn.tocstr()), fin_en(fp_en.tocstr());
			ofstream fout(fp_align.tocstr());
			sentlist ensl, cnsl;
			datetime start;
			vocabulary& envcb=conf.get_en_vocab(), cnvcb=conf.get_cn_vocab();
			ensl.parse(fin_en, envcb);
			log_status("parsed "<<fp_en<<" in "<<start.update()<<"s with "<<ensl.size()<<" sents");
			cnsl.parse(fin_cn, cnvcb);
			log_status("parsed "<<fp_cn<<" in "<<start.update()<<"s with "<<cnsl.size()<<" sents");
			
			Chunk ensegs, cnsegs;
			//each segment is a sentence
			for_iter(it, sentlist, ensl) ensegs.append(segment(*it, envcb));
			for_iter(it, sentlist, cnsl) cnsegs.append(segment(*it, cnvcb));

			//each segment is a word
			/*for_iter(it, sentlist, ensl) {
				uint l=it->size();
				for_n(x, l) ensegs.append(segment(*it, x, x+1, envcb));
			}
			for_iter(it, sentlist, cnsl) {
				uint l=it->size();
				for_n(x, l) cnsegs.append(segment(*it, x, x+1, cnvcb));
			}
			*/
			//list<segment> ensegs1=ensegs(0, 100), cnsegs1=cnsegs(5, 105);
			start.update();
			bool ok=aligner.align(ensegs, cnsegs);
			log_status("aligned "<<ensegs.size()<<" ensegs, "<<cnsegs.size()<<" cnsegs in "<<start.update()<<"s");
			log_debug("align returned ok="<<ok);
			fout<<"<?xml version=\"1.0\" encoding=\"utf-8\" ?>"<<endl<<aligner.result;
		}
		return 0;
	} else if (action=="eval") {
		log_debug("before conf.load_all_for_evaluation()");
		conf.load_all_for_evaluation();
		log_debug("after conf.load_all_for_evaluation()");
		DynPrgmAligner aligner(conf);
		uint n=optargs.arg_size();
		//str fp_summary=str(conf.system_name)+"."+datetime().nowfn()+".csv";//for excel
		str fp_eval_detail="eval.csv";//for excel
		str fp_sys_summary="summary.csv";//for system summary
		ofstream fout_eval_detail(fp_eval_detail.tocstr(), ios::app), fout_sys_summary(fp_sys_summary.tocstr(), ios::app);
		//fout_eval_detail<<"SYSTEM-NAME,PRECISION,RECALL,F-MEASURE"<<endl;
		PRFSummary prfsum;
		for_m(i, 1, n) {
			str prefix=optargs[i];
			if (prefix.endswith(".ref")) prefix=prefix(0, -4);
			str fp_ref=prefix+".ref", fp_eval=prefix+"."+conf.system_name+".xml";
			if (path(fp_ref).isnfile()) {
				log_error(fp_ref<<" is not a good file path");
				continue;
			}
			ifstream fin(fp_ref.tocstr());
			ofstream fout(fp_eval.tocstr());

			datetime start;
			Alignment ref(fin);
			log_status("loaded "<<fp_ref<<" in "<<start.update()<<"s with size="<<ref.size());
		
			Evaluator evaluator(ref);
			
			start.update();
			bool ok=aligner.align(ref.get_en_segs(), ref.get_cn_segs());
			log_status("aligned "<<ref.get_en_segs().size()<<" ensegs, "<<ref.get_en_segs().size()<<" cnsegs in "<<start.update()<<"s");
			log_debug("align returned ok="<<ok);

			PRF prf=evaluator.eval(aligner.result);
			prfsum.append(prf);
			fout_eval_detail<<prefix.replaced("/", ",")<<","<<conf.system_name<<","<<prf.pricision()<<","<<prf.recall()<<","<<prf.fmeasure()<<endl;

			fout<<"<?xml version=\"1.0\" encoding=\"utf-8\" ?>"<<endl;
			fout<<"<eval>"<<endl;
			fout<<prf<<endl;
			fout<<"</eval>"<<endl;
			fout<<"<ref>"<<endl;
			fout<<ref;
			fout<<"</ref>"<<endl;
			fout<<"<test>"<<endl;
			fout<<aligner.result;
			fout<<"</test>"<<endl;

		}
		log_info("PRF Summary:\n"<<prfsum);
		fout_sys_summary<<prfsum<<","<<conf.system_name<<endl;
		return 0;
	} else if (action=="rank") {
		log_debug("now in rank");
		conf.load_all_for_rank();
		
		if (optargs.arg_size()!=2) die_error("need prefix");
		str prefix=optargs[1];
		str fp_cn=prefix+".cn", fp_en=prefix+".en", fp_rank=prefix+".rank";
		if (path(fp_cn).isnfile() OR path(fp_en).isnfile()) die_error(fp_cn<<" or "<<fp_cn<<" is not a good file path");
		ifstream fin_cn(fp_cn.tocstr()), fin_en(fp_en.tocstr());
		ofstream fout(fp_rank.tocstr());
		sentlist ensl, cnsl;
		datetime start;
		vocabulary& envcb=conf.get_en_vocab(), cnvcb=conf.get_cn_vocab();
		ensl.parse(fin_en, envcb);
		log_status("parsed "<<fp_en<<" in "<<start.update()<<"s with "<<ensl.size()<<" sents");
		cnsl.parse(fin_cn, cnvcb);
		log_status("parsed "<<fp_cn<<" in "<<start.update()<<"s with "<<cnsl.size()<<" sents");
		
		
		log_debug("now generate cooc ...");
		cooc_table e2c_cooc;
		freqdist en_cooc_sum;
		freqdist cn_cooc_sum;
		
		uint M=ensl.size();
		assert(M==cnsl.size());
		for_n(m, M) {
			sentence& ens=ensl[m];
			sentence& cns=cnsl[m];
			if (m%1000==0) log_debug("process en sent "<<m<<'/'<<M);
			uint I=ens.size(), J=cns.size();
			for_n(i, I) {
				word src=ens[i];
				for_n(j, J) {
					word dst=cns[j];
					e2c_cooc.add(src, dst, 1);
					en_cooc_sum[src]+=1;
					cn_cooc_sum[dst]+=1;
				}
			}
		}
		log_status("generated e2c_cooc in "<<start.update()<<"s with "<<e2c_cooc.size()<<" coocs, "<<en_cooc_sum.size()<<" en_cooc_sums, "<<cn_cooc_sum.size()<<" cn_cooc_sums");
		
		//optional: remove all cooc that is 1
		// log_debug("now remove all cooc that is 1 ...");
		// for_iterc(it, freqdist, en_cooc_sum) {
			// word src=it->first;
			// for_iterc(jt, freqdist, cn_cooc_sum) {
				// word dst=jt->first;
				// uint cooc=0;
				// if (e2c_cooc.get(src, dst, cooc)) {
					// if (cooc==1) {
						// e2c_cooc.set(src, dst, 0);
						// en_cooc_sum[src]-=1;
						// cn_cooc_sum[dst]-=1;
					// }
				// }
			// }
		// }
		// log_status("removed cooc in "<<start.update()<<"s");
		// log_debug("now update en_cooc_sum ...");
		// freqdist en_cooc_sum2;
		// freqdist cn_cooc_sum2;
		// for_iterc(it, freqdist, en_cooc_sum) {
			// word src=it->first;
			// freq en_sum=it->second;
			// if (it->second>0) en_cooc_sum2[src]=en_sum;
		// }
		// uint old_size=en_cooc_sum.size();
		// en_cooc_sum=en_cooc_sum2;
		// log_status("trunked "<<old_size-en_cooc_sum.size()<<" en_cooc_sum from "<<old_size<<" to "<<en_cooc_sum.size()<<" in "<<start.update()<<"s");
		// log_debug("now update cn_cooc_sum ...");
		// for_iterc(it, freqdist, cn_cooc_sum) {
			// word dst=it->first;
			// freq cn_sum=it->second;
			// if (it->second>0) cn_cooc_sum2[dst]=cn_sum;
		// }
		// old_size=cn_cooc_sum.size();
		// cn_cooc_sum=cn_cooc_sum2;
		// log_status("trunked "<<old_size-cn_cooc_sum.size()<<" cn_cooc_sum from "<<old_size<<" to "<<cn_cooc_sum.size()<<" in "<<start.update()<<"s");
		
		
		
		log_debug("now generate e2c and c2e translation table ...");
		trans_table e2c_trans, c2e_trans;
		uint cnt=0;
		for_iter(it, freqdist, en_cooc_sum) {
			if (cnt%1000==0) log_debug("deal with en word "<<cnt<<'/'<<en_cooc_sum.size())
			++cnt;
			word src=it->first;
			freq en_sum=it->second;
			for_iter(jt, freqdist, cn_cooc_sum) {
				word dst=jt->first;
				freq cn_sum=jt->second;
				uint cooc=0;
				if (e2c_cooc.get(src, dst, cooc)) {
					e2c_trans.set(src, dst, double(cooc)/en_sum);
					c2e_trans.set(dst, src, double(cooc)/cn_sum);
				}
			}
		}
		log_status("generated e2c and c2e translation table in "<<start.update()<<"s with "<<e2c_trans.size()<<" e2c entrys, "<<c2e_trans.size()<<" c2e entrys");
		
		log_debug("now assign initial en words weights ...");
		probdist en_weights, cn_weights;
		for_iter(it, freqdist, en_cooc_sum) {
			word src=it->first;
			en_weights[src]=1.0;
		}
		log_status("finished weights initialization in "<<start.update()<<"s");
		
		for_n(i, 100000) {
			log_debug("E-step: calculate cn words weights ...");
			for_iter(jt, freqdist, cn_cooc_sum) {
				word dst=jt->first;
				double dst_weight=0;
				for_iter(it, freqdist, en_cooc_sum) {
					word src=it->first;
					double trans=0;
					e2c_trans.get(src, dst, trans);
					dst_weight+=en_weights[src]*trans;
				}
				cn_weights[dst]=dst_weight;
			}
			log_debug("M-step: re-estimate en words weights ...");
			double diff=0;
			for_iter(it, freqdist, en_cooc_sum) {
				word src=it->first;
				double src_weight=0;
				for_iter(jt, freqdist, cn_cooc_sum) {
					word dst=jt->first;
					double trans=0;
					c2e_trans.get(dst, src, trans);
					src_weight+=cn_weights[dst]*trans;
				}
				diff+=fabs(en_weights[src]-src_weight);
				en_weights[src]=src_weight;
			}
			log_status("finished a EM loop in "<<start.update()<<"s, iter="<<(i+1)<<", diff="<<diff);
			if (diff<1e-5) {
				log_status("stop condition satisfied");
				break;
			}
		}
		
		log_debug("output rank result ...");
		// for_iter(it, freqdist, en_cooc_sum) {
			// word src=it->first;
			// const token& tok=envcb[src];
			// double weight=en_weights[src];
			// fout<<tok<<'\t'<<weight<<endl;
		// }
		// for_iter(it, freqdist, cn_cooc_sum) {
			// word dst=it->first;
			// const token& tok=cnvcb[dst];
			// double weight=cn_weights[dst];
			// fout<<tok<<'\t'<<weight<<endl;
		// }
		
		typedef std::multimap<double, token> multi_map_t;
		multi_map_t mt_map;
		for_iter(it, freqdist, en_cooc_sum) {
			word src=it->first;
			const token& tok=envcb[src];
			double weight=en_weights[src];
			mt_map.insert(pair<double, token>(weight, tok));
		}
		for_iter(it, freqdist, cn_cooc_sum) {
			word dst=it->first;
			const token& tok=cnvcb[dst];
			double weight=cn_weights[dst];
			mt_map.insert(pair<double, token>(weight, tok));
		}
		for_riter(it, multi_map_t, mt_map) {
			double w=it->first;
			token& t=it->second;
			fout<<t<<'\t'<<std::setw(10)<<w<<endl;
		}
		
		
		for_iter(it, freqdist, en_cooc_sum) {
			word src=it->first;
			freq en_sum=it->second;
			for_iter(jt, freqdist, cn_cooc_sum) {
				word dst=jt->first;
				freq cn_sum=jt->second;
				uint cooc=0;
				if (e2c_cooc.get(src, dst, cooc)) {
					double en_weight=en_weights[src];
					double cn_weight=cn_weights[dst];
					assert(cn_weight>0);
					assert(en_weight>0);
					double weight_ratio=en_weight/cn_weight;
					cout<<envcb[src]<<":\t"<<en_weight<<"/"<<en_sum<<'='<<(en_weight/en_sum)<<endl;
					cout<<cnvcb[dst]<<":\t"<<cn_weight<<"/"<<cn_sum<<'='<<(cn_weight/cn_sum)<<endl;
					double trans=0;
					e2c_trans.get(src, dst, trans);
					cout<<envcb[src]<<" -> "<<cnvcb[dst]<<' '<<cooc<<'/'<<en_sum<<'='<<trans<<" -> "<<(trans/weight_ratio)<<'\t'<<(trans*weight_ratio)<<endl;
					trans=0;
					c2e_trans.get(dst, src, trans);
					cout<<cnvcb[dst]<<" -> "<<envcb[src]<<' '<<cooc<<'/'<<cn_sum<<'='<<trans<<" -> "<<(trans*weight_ratio)<<'\t'<<(trans/weight_ratio)<<endl<<endl;
				}
			}
		}
			
			
		return 0;
	// } else if (action=="sev" OR action=="save-en-vocab") {
		// conf.load_en_vocab();
		// datetime start;
		// cout<<conf.get_en_vocab();
		// log_status("saved en vocab in: "<<start.elapse()<<"s");
	// } else if (action=="scv" OR action=="save-cn-vocab") {
		// conf.load_cn_vocab();
		// datetime start;
		// cout<<conf.get_cn_vocab();
		// log_status("saved cn vocab in: "<<start.elapse()<<"s");
	// } else if (action=="se2cd" OR action=="save-e2c-prob-dict") {
		// conf.load_ec_vocab();
		// conf.load_e2c_probdict();
		// datetime start;
		// cout<<conf.get_e2c_probdict();
		// log_status("saved e2c prob dict in: "<<start.elapse()<<"s");
	// } else if (action=="sc2ed" OR action=="save-c2e-prob-dict") {
		// conf.load_ec_vocab();
		// conf.load_c2e_probdict();
		// datetime start;
		// cout<<conf.get_c2e_probdict();
		// log_status("saved c2e prob dict in: "<<start.elapse()<<"s");
	// } else if (action=="de2cd" OR action=="dump-e2c-prob-dict") {
		// conf.load_ec_vocab();
		// conf.load_e2c_probdict();
		// datetime start;
		// conf.get_e2c_probdict().dump(cout, conf.get_en_vocab(), conf.get_cn_vocab());
		// log_status("dumped e2c prob dict in: "<<start.elapse()<<"s");
	// } else if (action=="dc2ed" OR action=="dump-c2e-prob-dict") {
		// conf.load_ec_vocab();
		// conf.load_c2e_probdict();
		// datetime start;
		// conf.get_c2e_probdict().dump(cout, conf.get_cn_vocab(), conf.get_en_vocab());
		// log_status("dumped c2e prob dict in: "<<start.elapse()<<"s");
	} else die_error("unkown action: "<<action);
	return 0;
}

