#pragma once
#ifndef _ANALYZER_H_
#define _ANALYZER_H_
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <chrono>

class Analyzer
{
protected:
	std::string _name;
	std::string _input_file_path;
	std::string _output_file_path;
	std::string _heights_file_path;
	std::ofstream _output_file;
	std::ofstream _heights_file;
	std::ifstream _input_file;
	std::vector<size_t> _times;
protected:
	void open_files();
	void close_files();
public:
    const std::vector<size_t>& get_times() {return _times;}
public:
	Analyzer(
		std::string __name,
		std::string __input_file_path,
		std::string __output_file_path,
		std::string __heights_file_path);
	~Analyzer();
	virtual void analyze() noexcept = 0;
};
#endif