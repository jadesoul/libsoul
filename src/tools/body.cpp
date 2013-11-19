/**
 * File: body.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-12-24 13:08:43.601166
 * Written In: Peking University, beijing, China
 */

#include <libsoul>

void process(istream& in, int start, int lines, bool verbose, bool line_number) {
	string s;
	uint i=0;
	if (start<0) {
		vector<string> ss;
		while (getline(in, s)) ss.push_back(s);
		uint n=ss.size();
		if (start==min_sint4) i=static_cast<uint>(max(0, (static_cast<int>(n)-lines)/2));
		else i=n+start;
		uint j=min<uint>(n, i+lines);
		if (verbose) clog<<"total lines="<<n<<" , will output from i="<<i<<" to j="<<j<<endl;
		uint w=1;
		for (uint k=j; k>=10; k/=10) w+=1;
		for (; i<j; ++i) {
			if (line_number) cout<<std::setw(w)<<i+1<<": ";
			cout<<ss[i]<<endl;
		}
	} else {//start must be >0, lines must be >0
		uint a=static_cast<uint>(start), b=static_cast<uint>(start+lines);
		uint w=1;
		for (uint k=b; k>=10; k/=10) w+=1;
		if (verbose) clog<<"will output lines between a="<<a<<" and b="<<b<<endl;
		while (getline(in, s)) {
			++i;
			if (i<a) ;//pass
			else if (i>=b) break;
			else {
				if (line_number) cout<<std::setw(w)<<i<<": ";
				cout<<s<<endl;
			}
		}
	}
}

int main (int argc, const char* argv[]) {
	OptionParser parser;
	parser.description("show n lines of a files, starting from the i-th line. "
			"if no file specified, process from the standard input. "
			"by default, the i is LINES-OF-FILE/2-n/2 and n is 10, which means "
			"at most 10 lines in the middle of the file will be output.")
		.usage("%prog [OPTIONS] [FILE]")
		.version("1.0")
		.epilog("By jadesoul @ 2012-12-24\n"
			"please report bugs to wslgb2006@gmail.com");
	parser.add_option("-s", "--start")
		.action("store")
		.type("int")
		.set_default(min_sint4)
		.help("the i-th line starting to output");
	parser.add_option("-n", "--lines")
		.action("store")
		.type("int")
		.set_default(10)
		.help("how many lines to be output");
	parser.add_option("-l", "--line-number")
		.action("store_true")
		.set_default("0")
		.dest("line_number")
		.help("show line number when output");
	parser.add_option("-v", "--verbose")
		.action("store_true")
		.set_default("0")
		.help("print status messages to stdlog");
	OptionArgs& optargs = parser.parse_args(argc, argv);
	int start=optargs.get("start");
	int lines=optargs.get("lines");
	bool verbose=optargs.get("verbose"); 
	bool line_number=optargs.get("line_number");

	if (lines<=0) {
		if (verbose) clog<<"lines is non-postive, no lines will be output"<<endl;
		return 1;
	}

	if (verbose) {
		clog<<"will output "<<lines<<" lines ";
		if (start==min_sint4) clog<<"in the middle of the file";
		else clog<<"from the "<<start<<" th line";
		clog<<endl;
		if (line_number) clog<<"and will show line number"<<endl;
	}
	
	uint n=optargs.arg_size();
	if (n>1) {
		parser.error("you just need to specify 1 file");
	} else if (n==1) {
		path p(optargs[0]);
		if (p.isfile()) {
			ifstream fin(p.tocstr());
			process(fin, start, lines, verbose, line_number);
		} else {
			cerr<<"error: is not a file: "<<p.tostr()<<endl;
		}
	} else {
		if (verbose) clog<<"now deal with std input..."<<endl;
		process(cin, start, lines, verbose, line_number);
	}
	if (verbose) clog<<"now exit."<<endl;
	return 0;
}

