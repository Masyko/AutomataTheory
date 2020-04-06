#pragma once
#ifndef _ANALYZER_H_
#define _ANALYZER_H_
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
class Analyzer
{
protected:
	string _name;
	string _input_file_path;
	string _output_file_path;
	string _height_file_path;
	ifstream _input_file;
	ofstream _output_file;
	ofstream _height_file;
protected:
	void open_files();
	void close_files();
public:
	Analyzer(
		string __name,
		string __input_file_path,
		string __output_file_path,
		string __height_file_path
	);
	virtual void analyze() = 0;
};
#endif