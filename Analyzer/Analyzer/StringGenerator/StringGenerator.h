#pragma once
#ifndef _STRINGGENERATOR_H_
#define _STRINGGENERATOR_H_
#include <fstream>
#include <list>
#include <vector>
#include <iostream>
#include "Object/Geo/geo.h"
#include "Object/Latitude/Latitude.h"
#include "Object/Longitude/Longitude.h"
#include "Object/Height/Height.h"
#include "Object/Distance/Distance.h"

/**
- Создаёт случайные строки определённого формата
- Конструктор принимает имя файла, в который нужно записывать строки
*/
class StringGenerator {
private:
	std::ofstream _output_file;
	std::string _file_path;
	std::list<Object*> _objects;
private:
	std::random_device _random_device;
private:
	void generate_line();
	bool write_line() noexcept;
public:
	/**
	- Принимает путь к файлу
	*/
	StringGenerator(std::string __file_path);
	~StringGenerator();
	/**
	- Принимает количество строк, который нужно сгенерировать
	*/
	void generate(size_t __generate_lines_count);
};
#endif