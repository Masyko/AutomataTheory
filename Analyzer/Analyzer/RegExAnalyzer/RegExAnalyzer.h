#pragma once
#ifndef REGEXANALYZER_H
#define REGEXANALYZER_H
#include "../Analyzer/Analyzer.h"
#include <sstream>
#include <regex>
using namespace std;
class RegExAnalyzer : public Analyzer
{
public:
	RegExAnalyzer(std::string __input_file_path = "Generator\\Output\\Output.txt",
		std::string __output_file_path = "RegExAnalyzer\\Output\\Output.txt", 
		std::string __height_file_path = "RegExAnalyzer\\Output\\Height.txt" );
	virtual void analyze() override;
};
#endif // !REGEXANALYZER_H
