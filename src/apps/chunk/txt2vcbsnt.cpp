/**
 * File: txt2vcbsnt.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-05 20:28:43.825177
 * Written In: Peking University, beijing, China
 */

#include <libsoul>
#include "vocab.h"
#include "sent.h"

int main (int argc, char** argv) {
	if (argc==1) {
		cerr<<"Usage: txt2vcbsnt corpus [ corpus [ ... ] ]\nConvert corpus.txt into corpus.vcb and corpus.snt\n";
		return 1;
	}
	for_any(i, 1, argc-1) {
		str corpus=argv[i];
		path ptxt(corpus+".txt"), pvcb(corpus+".vcb"), psnt(corpus+".snt");
		if (ptxt.isfile() AND ptxt.fsize()>0) {
			vocabulary voc;
			ifstream iftxt(ptxt.tocstr()), iftxt2(ptxt.tocstr());
			ofstream ofvcb(pvcb.tocstr()), ofsnt(psnt.tocstr());
			datetime start;
			voc.scan(iftxt);
			clog<<"finish scan txt in: "<<start.update()<<"s"<<endl;
			ofvcb<<voc;
			clog<<"finish save vocabulary in: "<<start.update()<<"s"<<endl;
			string line;
			while (getline(iftxt2, line)) {
				sentence snt;
				istringstream iss(line);
				snt.parse(iss, voc);
				ofsnt<<snt<<endl;
			}
			clog<<"finish save snt in: "<<start.elapse()<<"s"<<endl;
		} else cerr<<"Error: "<<ptxt<<" is not a good file path\n";
	}
	return 0;
}

