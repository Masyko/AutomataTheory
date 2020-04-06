#include "Generator.h"

void Generator::generate_line()
{
	_objects.push_back(new geo);
	_objects.push_back(new Latitude);
	_objects.push_back(new Longitude);
	_objects.push_back(new Height);
	_objects.push_back(new Distance);
}

void Generator::print_line()
{
	for (auto&& object : _objects)
	{
		object->Print(_output_file);
		delete object;
	}
	_objects.clear();
	_output_file << std::endl;
}

Generator::Generator(string __path):_path(__path)
{}

void Generator::Create(size_t __count)
{
	_output_file.open(_path, std::ios_base::trunc/*очистить файл при открытии*/); 
	if (!_output_file.is_open()) {
		throw invalid_argument("Generator : Output file is not open");
	}
	std::random_device rd;
	std::uniform_int_distribution<size_t> optional_dis(0,100);
	size_t limit = 80;
	for (size_t i = 0; i < __count; ++i)
	{
		generate_line();
		print_line();
	}
	_output_file.close();
}
