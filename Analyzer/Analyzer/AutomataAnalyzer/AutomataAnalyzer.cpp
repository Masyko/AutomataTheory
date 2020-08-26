#include "AutomataAnalyzer.h"
#include "_sm/AutomataAnalyzer_sm.h"
#include "_sm/AutomataAnalyzer_sm.cpp"
namespace Automata_Analyzer {

	AutomataAnalyzer::AutomataAnalyzer(std::string __input_file_path, std::string __output_file_path, std::string __heights_file_path) :
		Analyzer(
			"AutomataAnalyzer",
			__input_file_path,
			__output_file_path,
			__heights_file_path),
		_fsm(new AutomataAnalyzerContext(*this))
	{}

	void AutomataAnalyzer::analyze() noexcept
	{
		try
		{
			open_files();
			std::cout << _name << ": Analyzing..." << std::endl;
			_fsm->enterStartState();
			while (std::getline(_input_file, _checking_str)) {
				_fsm->begin();
                auto begin_time = std::chrono::steady_clock::now();
				for (size_t i = 0; i < _checking_str.size(); ++i) {
					auto& letter = _checking_str[i];
					if (letter >= '0' && letter <= '9') {
						_fsm->number(letter);
					}
					else if (letter >= 'a' && letter <= 'z')
					{
						_fsm->letter(letter);
					}
					else if (letter == '=')
					{
						_fsm->equal();
					}
					else if (letter == ':')
					{
						_fsm->colon();
					}
					else if (letter == ';')
					{
						_fsm->semicolon();
					}
					else if (letter == ',')
					{
						_fsm->comma();
					}
					else if (letter == '.')
					{
						_fsm->dot(letter);
					}
					else
					{
						_fsm->error();
					}
				}
				_fsm->eos();
                auto end_time = std::chrono::steady_clock::now();
                auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - begin_time);
                if(!_times.empty()) {
                    _times.push_back(_times[_times.size() - 1] + elapsed_ms.count());
                } else
                {
                    _times.push_back(elapsed_ms.count());
                }
			}

			for (auto key_it = _heights.begin(); key_it != _heights.end(); ++key_it) {
				auto& height = (*key_it).first;
				auto& coords = key_it->second;
				for (auto&& coord : coords) {
					_heights_file << "Height : " << height << " Latitude : " << coord.first << " Longitude : " << coord.second << std::endl;
				}
			}


			std::cout << _name << ": Analyzing complete" << std::endl;
			close_files();
		}
		catch (const std::exception & __ex) {
			std::cout << __ex.what() << std::endl;
			close_files();
		}
	}

	AutomataAnalyzer::~AutomataAnalyzer()
	{
		delete _fsm;
	}

	void AutomataAnalyzer::Pick_up_symbol(char symbol)
	{
		_temp_str += symbol;
	}

	void AutomataAnalyzer::Unacceptable()
	{
		_output_file << _checking_str << " - not suitable" << std::endl;
	}

	void AutomataAnalyzer::Acceptable()
	{
		_output_file << _checking_str << " - BINGO!" << std::endl;
	}

	void AutomataAnalyzer::ClearStorageList()
	{
		for (auto&& el : _storage) { el = ""; }
	}

	void AutomataAnalyzer::ResetFSM()
	{
		_checking_str.clear();
	}

	void AutomataAnalyzer::ClearTempStr()
	{
		_temp_str.clear();
	}

	bool AutomataAnalyzer::is_in_range_latitude()
	{
		double latitude = std::stod(_temp_str);
        return latitude <= 90 && latitude >= -90;
    }

	bool AutomataAnalyzer::is_geo()
	{
		return _temp_str == "geo";
	}

	bool AutomataAnalyzer::is_u()
	{
		return _temp_str == "u";
	}

	bool AutomataAnalyzer::is_in_range_longitude()
	{
		double longitude = std::stod(_temp_str);
        return longitude <= 180 && longitude >= -180;
    }

	void AutomataAnalyzer::Save_latitude()
	{
		_storage[0] = _temp_str;
	}

	void AutomataAnalyzer::Save_longitude()
	{
		_storage[1] = _temp_str;
	}

	void AutomataAnalyzer::Save_height_zero()
	{
		_storage[2] = "0";
	}

	void AutomataAnalyzer::Save_height()
	{
		_storage[2] = _temp_str;
	}

	void AutomataAnalyzer::AddStorageList()
	{
		auto key_it = _heights.find(_storage[2].c_str());
		if (key_it != _heights.end()) {
			auto& value = key_it->second;
			value.insert(std::pair{ _storage[0], _storage[1] });
		}
		else {
			std::multimap<std::string, std::string> t;
			t.insert(std::pair{ _storage[0], _storage[1] });
			_heights.insert(std::pair{ _storage[2], std::move(t) });
		}
	}
}