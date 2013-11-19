/**
 * File: test_zlib.cpp
 * Description: 
 *
 * Copyright (c) 2012 Jadesoul (Home Page: http://jadesoul.sinaapp.com)
 * 
 * Date: 2012-06-22 16:15:02.412000
 * Written In: Peking University, beijing, China
 */


#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>
#include <string>



namespace io = boost::iostreams;
using namespace io;
using namespace std;

void compressor()
{
	filtering_ostream out;
	out.push(zlib_compressor());
	out.push(file_sink("my_file.txt"));

	ostream& myout = out;
	for (int i = 0; i < 100; i++)
	{
		myout << "i love you!" << endl;
		myout << "i like you!" << endl;
	}
	cout << "zlib compressor completed!" << endl; 
	system("pause"); 
}

void decompressor()
{
	filtering_istream in;
	in.push(zlib_decompressor());
	in.push(file_source("my_file.txt"));
	istream& myin = in;
	string c;
	while(!myin.eof())
	{
		myin >> c;
		cout << c << endl;
	}
	system("pause"); 
}

int main()
{ 
	compressor();
	decompressor(); 
}