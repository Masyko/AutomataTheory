#pragma once
#ifndef _REGEXANALYZER_H__
#define _REGEXANALYZER_H__
#include "../Analyzer/Analyzer.h"
#include <regex>

class RegExAnalyzer : public Analyzer
{
public:
	RegExAnalyzer(
		std::string __input_file_path, 
		std::string __output_file_path = "../RegExAnalyzer/Output/RegExResults.txt",
		std::string __heights_file_path = "../RegExAnalyzer/Output/Heights.txt");
	~RegExAnalyzer();
	virtual void analyze() noexcept override;
};
#endif