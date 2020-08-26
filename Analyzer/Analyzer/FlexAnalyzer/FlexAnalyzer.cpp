#include <sstream>
#include "FlexAnalyzer.h"
#include "lex.yy.cc"

FlexAnalyzer::FlexAnalyzer(std::string __input_file_path, std::string __output_file_path, std::string __heights_file_path) :
	Analyzer(
		"FlexAnalyzer",
		__input_file_path,  
		__output_file_path,
        __heights_file_path
	)
{}

FlexAnalyzer::~FlexAnalyzer()
{}

void FlexAnalyzer::analyze() noexcept
{
	try
	{
		open_files();
		std::cout << _name << ": Analyzing..." << std::endl;

        yyFlexLexer lexer;
        std::string str;
        while (std::getline(_input_file,str)) {
            std::istringstream str_stream(str + "\n");
            str_stream.seekg(std::ios_base::end);
            auto str_stream_size = str_stream.tellg();
            str_stream.seekg(std::ios_base::beg);
            auto buf = lexer.yy_create_buffer(str_stream, str_stream_size);
            lexer.yy_switch_to_buffer(buf);

            auto begin_time = std::chrono::steady_clock::now();
            int result = lexer.yylex();
            auto end_time = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - begin_time);
            if(!_times.empty()) {
                _times.push_back(_times[_times.size() - 1] + elapsed_ms.count());
            } else
            {
                _times.push_back(elapsed_ms.count());
            }
            if (result == 1) {
                _output_file << str << " - BINGO!" << std::endl;
            }
            if(result == 0) {
                _output_file << str << " - not suitable" << std::endl;
            }
            lexer.yy_delete_buffer(buf);
            ++line;
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
	catch (const std::invalid_argument& __ex)
	{
		std::cout << __ex.what() << std::endl;
		close_files();
	}
}
