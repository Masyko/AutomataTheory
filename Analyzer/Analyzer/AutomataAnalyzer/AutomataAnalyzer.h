#pragma once
#ifndef _AUTOMATAANALYZER_H_
#define _AUTOMATAANALYZER_H_
#include "../Analyzer/Analyzer.h"
#include <array>
#include <map>
namespace Automata_Analyzer {
	class AutomataAnalyzerContext;

	class AutomataAnalyzer : public Analyzer
	{
	private:
		AutomataAnalyzerContext* _fsm;
		std::string _checking_str;
		std::string _temp_str;
		std::array<std::string, 3> _storage;
		std::map<std::string, std::multimap<std::string, std::string>> _heights;
	public:
		AutomataAnalyzer(
			std::string __input_file_path,
			std::string __output_file_path = "../AutomataAnalyzer/Output/AutomataAnalyzerResults.txt",
			std::string _heights_file_path = "../AutomataAnalyzer/Output/Heights.txt");
		~AutomataAnalyzer();
		virtual void analyze() noexcept override;
		bool is_in_range_latitude(); // ready
		bool is_geo(); // ready
		bool is_u(); // ready
		bool is_in_range_longitude(); // ready
		void Pick_up_symbol(char symbol); // ready
		void ClearTempStr(); // ready
		void Save_latitude(); // ready
		void Save_longitude(); // ready
		void Save_height_zero(); // ready
		void Save_height(); // ready
		void Acceptable(); // ready
		void Unacceptable(); // ready
		void ClearStorageList(); // ready
		void ResetFSM(); // ready
		void AddStorageList(); //
	};
}
#endif
