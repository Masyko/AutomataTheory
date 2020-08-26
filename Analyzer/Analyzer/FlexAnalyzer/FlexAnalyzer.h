#pragma once
#ifndef _FLEXANALYZER_H_
#define _FLEXANALYZER_H_
#include "../Analyzer/Analyzer.h"

class FlexAnalyzer : public Analyzer
{
public:
	FlexAnalyzer(
		std::string __input_file_path,
		std::string __output_file_path = "../FlexAnalyzer/Output/FlexResults.txt",
		std::string __heights_file_path = "../FlexAnalyzer/Output/Heights.txt");
	~FlexAnalyzer();
	virtual void analyze() noexcept override;
};
#endif