/**
 * File: vcbsnt2txt.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-05 20:29:01.291149
 * Written In: Peking University, beijing, China
 */
 
#include <libsoul>
#include "vocab.h"
#include "sent.h"

int main (int argc, char** argv) {
	if (argc==1) {
		cerr<<"Usage: vcbsnt2txt corpus [ corpus [ ... ] ]\nConvert corpus.vcb and corpus.snt into corpus.txt\n";
		return 1;
	}
	for_any(i, 1, argc-1) {
		str corpus=argv[i];
		path pvcb(corpus+".vcb"), psnt(corpus+".snt"), ptxt(corpus+".txt");
		if (pvcb.isfile() AND pvcb.fsize()>0 AND psnt.isfile() AND psnt.fsize()>0) {
			vocabulary voc;
			ifstream ifvcb(pvcb.tocstr()), ifsnt(psnt.tocstr());
			ifvcb>>voc;
			ofstream oftxt(ptxt.tocstr());
			string line;
			while (getline(ifsnt, line)) {
				sentence snt;
				istringstream iss(line);
				iss>>snt;
				snt.dump(oftxt, voc);
				oftxt<<endl;
			}
		} else cerr<<"Error: "<<pvcb<<" or "<<psnt<<" is not a good file path\n";
	}
	return 0;
}

