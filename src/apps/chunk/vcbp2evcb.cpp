/**
 * File: vcbp2evcb.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-06 20:24:38.214270
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "vocab.h"
#include "sent.h"

int main (int argc, char** argv) {
	if (argc!=3) {
		cerr<<"Usage: vcbp2evcb src tgt\nConvert src.vcb into tgt.vcb to s2t.evcb and t2s.evcb\n";
		return 1;
	}
	str src=argv[1], tgt=argv[2];
	path psrc(src+".vcb"), ptgt(tgt+".vcb"), psrc2tgt(src(0, 1)+"2"+tgt[0]+".evcb"), ptgt2src(tgt(0, 1)+"2"+src[0]+".evcb");
	if (psrc.isfile() AND ptgt.isfile()) {
		vocabulary vsrc, vtgt;
		ifstream ifsrc(psrc.tocstr()), iftgt(ptgt.tocstr());
		ofstream ofsrc2tgt(psrc2tgt.tocstr()), oftgt2src(ptgt2src.tocstr());
		datetime start;
		ifsrc>>vsrc;
		clog<<"finish input "<<psrc<<" in: "<<start.update()<<"s"<<endl;
		iftgt>>vtgt;
		clog<<"finish input "<<ptgt<<" in: "<<start.update()<<"s"<<endl;
		equal_vocabulary ev(vsrc, vtgt);
		ev.dump(ofsrc2tgt, oftgt2src);
		clog<<"finish output in: "<<start.update()<<"s"<<endl;
	} else cerr<<"Error: "<<psrc<<" or "<<ptgt<<" is not a good file path\n";
	return 0;
}
