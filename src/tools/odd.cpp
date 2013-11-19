/**
 * File: odd.cpp
 * Description: 
 *
 * Copyright (c) 2010-2013 Jadesoul (Home Page: http://jadesoul.sinaapp.com) <shenglan.wsl@alibaba-inc.com>
 * 
 * Date: 2013-11-19 14:35:40.733047
 * Written In: Alibaba-inc, Hangzhou, China
 */

#include <libsoul>

int main (int argc, const char* argv[]) {
	OptionParser parser;
	parser.description("split input file by odd lines and even lines into two files\n"
		"input from stdin, output odd lines to stdout, even lines to stderr")
		.usage("%prog [OPTIONS] < INPUT > ODD_LINES 2> EVEN_LINES")
		.version("1.0")
		.epilog("By jadesoul @ 2013-11-19 14:47:14\n"
			"please report bugs to " JADESOUL_EMAIL);
	parser.add_option("-v", "--verbose")
		.action("store_true")
		.dest("verbose")
		.set_default("0")
		.help("print status messages to stdlog");
	OptionArgs& optargs = parser.parse_args(argc, argv);
	bool verbose=optargs.get("verbose");
	
	if (verbose) cout<<"begin ..."<<endl;
	
	uint i=0;
	string s;
	while (getline(cin, s))
		if (++i%2==1) cout<<s<<endl;
		else cerr<<s<<endl;
		
	if (verbose) cout<<"finished"<<endl;
	return 0;
}
