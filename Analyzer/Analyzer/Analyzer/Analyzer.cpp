#include "Analyzer.h"
using namespace std;
void Analyzer::open_files()
{
	_input_file.open(_input_file_path);
	if (!_input_file.is_open()) {
		throw invalid_argument(_name + " : Input file is not open");
	}
	cout << _name << " : Input file is open" << endl;
	_output_file.open(_output_file_path, ios_base::trunc/*очистить файл при открытии*/);
	if (!_output_file.is_open()) {
		throw invalid_argument(_name + " : Output file is not open");
	}
	cout << _name << " : Output file is open" << endl;
	_height_file.open(_height_file_path, ios_base::trunc/*очистить файл при открытии*/);
	if (!_height_file.is_open()) {
		throw invalid_argument(_name + " : Height file is not open");
	}
	cout << _name << " : Height file is open" << endl;
}

void Analyzer::close_files()
{
	if (_input_file.is_open()) { _input_file.close(); cout << _name << " : Input file is closed" << endl; }
	if (_output_file.is_open()) { _output_file.close(); cout << _name << " : Output file is closed" << endl; }
	if (_height_file.is_open()) { _height_file.close(); cout << _name << " : Height file is closed" << endl; }
}

Analyzer::Analyzer(std::string __name, std::string __input_file_path, std::string __output_file_path, std::string __height_file_path) :
	_name(__name),
	_input_file_path(__input_file_path),
	_output_file_path(__output_file_path),
	_height_file_path(__height_file_path)
{}
