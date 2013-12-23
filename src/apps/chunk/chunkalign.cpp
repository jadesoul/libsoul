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
	parser.description("Chunk Alignment Toolkit 亚句子级别对齐工具箱\n")
		.usage("%prog [OPTIONS] INPUT [INPUT] [INPUT] ...")
		.version("1.0")
		.epilog("By jadesoul @ 2013-1-7\n"
			"please report bugs to wslgb2006@gmail.com");
	parser.add_option("-d", "--e2c-prob-dict")
		.action("store")
		.set_default("e2c.pdict")
		.help("the input english to chinese probilistic dictionary in plain format, default is e2c.pdict");
	parser.add_option("-f", "--c2e-prob-dict")
		.action("store")
		.set_default("c2e.pdict")
		.help("the input chinese to english probilistic dictionary in plain format, default is c2e.pdict");
	parser.add_option("-t", "--pos-tag-set")
		.action("store")
		.set_default("pos.tags")
		.help("the input pos tag set list in plain format, default as pos.tags");
	parser.add_option("-x", "--max-en-segs-in-a-chunk")
		.action("store")
		.type("int")
		.set_default(XMAX_DEFAULT)
		.help(str("default as ")+XMAX_DEFAULT);
	parser.add_option("-y", "--max-cn-segs-in-a-chunk")
		.action("store")
		.type("int")
		.set_default(YMAX_DEFAULT)
		.help(str("default as ")+YMAX_DEFAULT);
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
		.set_default(CN_EN_LENGTH_RATIO_DEFALUT)
		.help(str("cn en chunk length ratio for align, this indicates how many cn chars per each en char in a chunk, default is ")+CN_EN_LENGTH_RATIO_DEFALUT);
	parser.add_option("-g", "--en-length-type-for-ratio")
		.action("store")
		.type("int")
		.set_default(EN_LENGTH_TYPE_FOR_RATIO_DEFAULT)
		.help(str("english chunk length type for caculate length ratio, it can be 0(words) 1(bytes, or chars), default is ")+EN_LENGTH_TYPE_FOR_RATIO_DEFAULT);
	parser.add_option("-G", "--cn-length-type-for-ratio")
		.action("store")
		.type("int")
		.set_default(CN_LENGTH_TYPE_FOR_RATIO_DEFAULT)
		.help(str("chinese chunk length type for caculate length ratio, it can be 0(words) 1(bytes) 2(characters in GBK) 3(characters in UTF8) 4(characters in UNICODE), default is ")+CN_LENGTH_TYPE_FOR_RATIO_DEFAULT);
	parser.add_option("-a", "--alpha")
		.action("store")
		.type("float")
		.set_default(ALPHA_DEFAULT)
		.help(str("alpha use to generate prior distribution of align mode x:y, should in [0, 1], default is ")+ALPHA_DEFAULT);
	parser.add_option("-m", "--lambda")
		.action("store")
		.type("float")
		.set_default(LAMBDA_DEFAULT)
		.help(str("alpha use to generate prior distribution of align mode x:y, if lambda==0 lead to equally distribution, default is")+LAMBDA_DEFAULT);
	parser.add_option("-s", "--system-name")
		.action("store")
		.set_default("default")
		.help("the system name for evaluation, default is 'default'");
	parser.add_option("-M", "--align-mode")
		.action("store")
		.type("int")
		.set_default(ALIGN_MODE_DEFAULT)
		.help(str("align mode can be:0(sent), 1(sub sent), default as ")+ALIGN_MODE_DEFAULT);
	parser.add_option("-v", "--verbose")
		.action("store")
		.type("int")
		.set_default(VERBOSE_DEFAULT)
		.help(str("log level for print status messages to stdlog, default is ")+VERBOSE_DEFAULT+str(", which means all message will output, if it is set to 0, none will output to stdlog"));
	OptionArgs& optargs=parser.parse_args(argc, argv);
	
	//全局变量
	verbose=(uint)optargs.get("verbose");

	if (optargs.arg_size()==0) {
		parser.print_help();
		parser.error("need more arguments");
		return 1;
	}
	
	Config conf(optargs);
	ChunkAlignResource res(conf);
	DynPrgmChunkAligner aligner(res);
	
	uint n=optargs.arg_size();
	for_n(i, n) {
		str prefix=optargs[i];
		str fp_en=prefix+".iob.en", fp_cn=prefix+".iob.cn", fp_align=prefix+".align."+conf.system_name;
		if (path(fp_en).isnfile() OR path(fp_cn).isnfile()) {
			log_error(fp_en<<" or "<<fp_cn<<" is not a good file path");
			continue;
		}
		ifstream en(fp_en.tocstr()), cn(fp_cn.tocstr());
		ofstream out(fp_align.tocstr());
		while (aligner.read_chunk_pair(en, cn)) {
			aligner.align();
			aligner.write_result(out);
		}
	}
	
	/*
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
		// for_iter(it, sentlist, ensl) {
			// uint l=it->size();
			// for_n(x, l) ensegs.append(segment(*it, x, x+1, envcb));
		// }
		// for_iter(it, sentlist, cnsl) {
			// uint l=it->size();
			// for_n(x, l) cnsegs.append(segment(*it, x, x+1, cnvcb));
		// }
		
		//list<segment> ensegs1=ensegs(0, 100), cnsegs1=cnsegs(5, 105);
		start.update();
		bool ok=aligner.align(ensegs, cnsegs);
		log_status("aligned "<<ensegs.size()<<" ensegs, "<<cnsegs.size()<<" cnsegs in "<<start.update()<<"s");
		log_debug("align returned ok="<<ok);
		fout<<"<?xml version=\"1.0\" encoding=\"utf-8\" ?>"<<endl<<aligner.result;
	
	}
	*/
	return 0;
}
