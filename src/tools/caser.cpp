/**
 * File: caser.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2013-01-01 19:28:28.531978
 * Written In: Peking University, beijing, China
 */

#include <libsoul>

void process_truecase(istream& in, bool verbose) {
	int cnt_diff[26];//the count of lower cased letter minus count of its upper case
	for_n(i, 26) cnt_diff[i]=0;
	
	// sometimes all letters in a sentence are uppercased as title	
	vector<bool> is_all_upper; // record if is all upper cased letter for each line
	uint total_lower_now=0; //record total lower till now for current line
	char c;
	while (true) {
		in.get(c);
		if (c=='\n') {// end of a line
			is_all_upper.push_back(total_lower_now==0);
			total_lower_now=0;
		}
		if (islower(c)) {
			++total_lower_now;
			++cnt_diff[c-'a'];
		}
		else if (isupper(c)) --cnt_diff[c-'A'];
		if (in.peek()==EOF) {
			in.putback(c);
			is_all_upper.push_back(total_lower_now==0);//add the last line
			break;
		}
	}
	in.seekg(0);
	string s;
	uint line_id=-1;
	while (getline(in, s)) {
		++line_id;
		if (is_all_upper[line_id]) {
			cout<<str(s).lower()<<endl;
			continue;
		}
		uint l=s.size();
		if (l!=0) {
			uint i=0;
			while (NOT isalpha(s[i]) AND i<l) ++i;
			if (i!=l) {
				char& first=s[i];// the first letter char
				if (isupper(first)) { // not a target, pass
					uint upper_cnt_after_first=0; // peek next two chars
					if (i+1<l AND isupper(s[i+1])) ++upper_cnt_after_first;
					if (i+2<l AND isupper(s[i+2])) ++upper_cnt_after_first;
					if (upper_cnt_after_first==0 AND cnt_diff[first-'A']>0) first+='a'-'A';// replace as true case
				}
			}
		}
		cout<<s<<endl;
	}
}

void process(istream& in, bool verbose, bool uppercase, bool swapcase, bool truecase) {
	if (verbose) {
		clog<<"uppercase="<<uppercase<<endl;
		clog<<"swapcase="<<swapcase<<endl;
		clog<<"truecase="<<truecase<<endl;
	}
	
	if (truecase) return process_truecase(in, verbose);

	string s;
	while (getline(in, s)) {
		if (uppercase) cout<<str(s).upper();
		else if (swapcase) cout<<str(s).swapcase();
		else cout<<str(s).lower();
		cout<<endl;
	}
}

int main (int argc, const char* argv[]) {
	OptionParser parser;
	parser.description("transfrom between english cases, by default, transform english uppercased letters into lowercased.")
		.usage("%prog [OPTIONS] [FILE]")
		.version("1.0")
		.epilog("By jadesoul @ 2012-12-24\n"
			"please report bugs to " JADESOUL_EMAIL);
	parser.add_option("-u", "--uppercase")
		.action("store_true")
		.set_default("0")
		.help("uppercase all the letters");
	parser.add_option("-s", "--swapcase")
		.action("store_true")
		.set_default("0")
		.help("swap all the letter case");
	parser.add_option("-t", "--truecase")
		.action("store_true")
		.set_default("0")
		.help("replace the starting letter of a english sentence with its true case, often the first letter is uppercased, if the count of the lower cased letter is much more then the uppercased in the whole corpus, then replace the upper case with lower case, other wise leave the same");
	parser.add_option("-v", "--verbose")
		.action("store_true")
		.set_default("0")
		.help("print status messages to stdlog");
	OptionArgs& optargs = parser.parse_args(argc, argv);
	bool verbose=optargs.get("verbose");
	bool uppercase=optargs.get("uppercase");
	bool swapcase=optargs.get("swapcase");
	bool truecase=optargs.get("truecase");
	
	argc=(int)optargs.arg_size();
	if (argc==0) process(cin, verbose, uppercase, swapcase, truecase);
	else if (argc==1) {
		ifstream fin(optargs[0].c_str());
		process(fin, verbose, uppercase, swapcase, truecase);
	}
	else parser.print_help();
	return 0;
}
