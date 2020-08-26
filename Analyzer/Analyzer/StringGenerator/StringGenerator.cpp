#include "StringGenerator.h"

StringGenerator::StringGenerator(std::string __file_path) : _file_path(__file_path)
{}

StringGenerator::~StringGenerator()
{}

void StringGenerator::generate_line()
{
    _objects.push_back(new geo);
    _objects.push_back(new Latitude);
    _objects.push_back(new Longitude);
    _objects.push_back(new Height);
    _objects.push_back(new Distance);
}

bool StringGenerator::write_line() noexcept
{
    for (auto&& object : _objects)
    {
        object->Print(_output_file);
        delete object;
    }
    _objects.clear();
    _output_file << std::endl;
}

void StringGenerator::generate(size_t __generate_lines_count)
{
	_output_file.open(_file_path, std::ios_base::trunc);
	if (!_output_file.is_open()) {
		throw std::invalid_argument("String generator: File is not open");
	}
	std::cout << "String generator: File opened" << std::endl;
	std::cout << "String generator: Generating..." << std::endl;
	try {
		for (size_t i = 0; i < __generate_lines_count; ++i) {
			generate_line();
			write_line();
		}
	}
	catch (const std::invalid_argument& __ex) {
		throw std::invalid_argument(__ex);
	}
	std::cout << "String generator: Generating complete" << std::endl;

	_output_file.close();
	std::cout << "String generator: File closed" << std::endl;
}
