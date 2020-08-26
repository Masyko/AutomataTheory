#include "RegExAnalyzer.h"
#include <map>

RegExAnalyzer::RegExAnalyzer(std::string __input_file_path, std::string __output_file_path, std::string __heights_file_path) :
	Analyzer(
		"RegExAnalyzer",
		__input_file_path,
		__output_file_path,
        __heights_file_path
	)
{}

RegExAnalyzer::~RegExAnalyzer()
{}

void RegExAnalyzer::analyze() noexcept
{
	try
	{
		open_files();
		std::cout << _name << ": Analyzing..." << std::endl;

        std::regex Geolocation_regex("(geo\\:)((\\-?)((0*)(9|[0-8]9|[0-8]{1,2})((\\.)(((0*)([0-9]{1,44}))|(0+)))?|(0*)90)|(0+))(\\,)((\\-?)((0*)([0-9]{1,2}|[1-9]|[1][0-7][0-9])((\\.)(((0*)([0-9]{1,44}))|(0+)))?|(0*)180)|(0+))((\\,)([0-9]{1,33}))?(\\;u\\=[0-9]{1,33})?$");
        std::cmatch Result;
        std::string tmp_str;

        std::map<std::string, std::multimap<std::string, std::string>> height_using; //высота(ключ),координаты(широта и долгота)

        size_t latitude_index = 2;
        size_t latitude_low_limit = -90;
        size_t latitude_up_limit = 90;

        size_t longitude_index = 17;
        size_t longitude_low_limit = -180;
        size_t longitude_up_limit = 180;

        size_t height_index = 33;
        while (getline(_input_file, tmp_str))
        {
            auto begin_time = std::chrono::steady_clock::now();
            if (regex_match(tmp_str.c_str() /*перевели строку в указатель на char*/, Result, Geolocation_regex)) {
                std::string latitude = Result[latitude_index];
                std::string longitude = Result[longitude_index];
                _output_file << tmp_str << " - BINGO!" << std::endl;
                std::string height = "0";

                if (Result[height_index].matched) {
                    height = Result[height_index];
                }

                auto key_it = height_using.find(height);
                if (key_it != height_using.end()) {
                    auto& value = key_it->second;
                    value.insert(std::pair{ latitude, longitude });
                }
                else {
                    std::multimap<std::string, std::string> t;
                    t.insert(std::pair{ latitude, longitude });
                    height_using.insert(std::pair{ height, std::move(t) });
                }
            }
            else {
                _output_file << tmp_str << " - not suitable" << std::endl;
            }
            auto end_time = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - begin_time);
            if(!_times.empty()) {
                _times.push_back(_times[_times.size() - 1] + elapsed_ms.count());
            } else
            {
                _times.push_back(elapsed_ms.count());
            }
        }

        for (auto key_it = height_using.begin(); key_it != height_using.end(); ++key_it) { //рассматриваем ту же пару но уже разименованную
            auto& height = (*key_it).first;
            auto& coords = key_it->second;
            for (auto&& coord : coords) {
                _heights_file << "Height : " << height << " Latitude : " << coord.first << " Longitude : " << coord.second << std::endl;
            }
        }


		std::cout << _name << ": Analyzing complete" << std::endl;
		close_files();
	}
	catch (const std::invalid_argument & __ex)
	{
		std::cout << __ex.what() << std::endl;
		close_files();
	}
}
