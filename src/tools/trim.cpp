/**
 * File: trim.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-20 20:41:25.682000
 * Written In: Peking University, beijing, China
 */

#include <libsoul>

void remove_empty_lines(istream& in, bool left, bool right, bool verbose) {
	// if (verbose) clog<<"now enter void remove_empty_lines(istream& in, bool left, bool right, bool verbose)"<<endl;
	string s;
	string empty_chars="\r \n\t";
	while (getline(in, s)) {
		uint n=s.size();
		if (n>0) {
			if (verbose) clog<<"n="<<n<<endl;
			uint i=0, j=n;
			if (left) for (; i<j AND empty_chars.find(s[i], 0)!=string::npos; ++i);
			if (right) for (; i<j AND empty_chars.find(s[j-1], 0)!=string::npos; --j);
			if (verbose) clog<<"i="<<i<<", j="<<j<<endl;
			if (i==j) cout<<""<<endl;
			else if (i==0 AND j==n) cout<<s<<endl;
			else if (j==n) cout<<s.c_str()+i<<endl;
			else cout<<string(s.begin()+i, s.begin()+j)<<endl;
		} else cout<<s<<endl;
	}
	// if (verbose) clog<<"now exit void remove_empty_lines(istream& in, bool left, bool right, bool verbose)"<<endl;
}

int main (int argc, const char* argv[]) {
	OptionParser parser;
	parser.description("remove the empty chars in each line\n"
			"if no file specified, remove from the standard input\n"
			"by default, the empty chars defines as any of \\r\\n\\t and space char")
		.usage("%prog [OPTIONS] [FILE1] [FILE2] ...")
		.version("1.0")
		.epilog("By jadesoul @ 2012-12-20\n"
			"please report bugs to " JADESOUL_EMAIL);
	parser.add_option("-l", "--left")
		.action("store_true")
		.dest("left")
		.set_default("0")
		.help("only remove from the left of a line");
	parser.add_option("-r", "--right")
		.action("store_true")
		.dest("right")
		.set_default("0")
		.help("only remove from the right of a line");
	parser.add_option("-b", "--both")
		.action("store_true")
		.dest("both")
		.set_default("1")
		.help("remove from both direction of a line (default)");
	parser.add_option("-v", "--verbose")
		.action("store_true")
		.dest("verbose")
		.set_default("0")
		.help("print status messages to stdlog");
	OptionArgs& optargs = parser.parse_args(argc, argv);
	bool verbose=optargs.get("verbose");
	bool left=optargs.get("left");
	bool right=optargs.get("right");
	//bool both=optargs.get("both");
	if (NOT left AND NOT right) {
		left=true;
		right=true;
	}
	
	if (verbose AND left) clog<<"will remove from left"<<endl;
	if (verbose AND right) clog<<"will remove from right"<<endl;
	if (optargs.arg_size()==0) {
		if (verbose) clog<<"process stdout ..."<<endl;
		remove_empty_lines(cin, left, right, verbose);
	} else {
		uint n=optargs.arg_size();
		for_n(i, n) {
			path p(optargs[i]);
			if (p.isfile()) {
				if (verbose) clog<<"process file "<<p.tostr()<<" ..."<<endl;
				ifstream fin(p.tocstr());
				remove_empty_lines(fin, left, right, verbose);
			} else {
				cerr<<"can not open file"<<i+1<<": "<<p.tostr()<<endl;
			}
		}
	}
	return 0;
}

