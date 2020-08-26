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
- ������ ��������� ������ ������������ �������
- ����������� ��������� ��� �����, � ������� ����� ���������� ������
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
	- ��������� ���� � �����
	*/
	StringGenerator(std::string __file_path);
	~StringGenerator();
	/**
	- ��������� ���������� �����, ������� ����� �������������
	*/
	void generate(size_t __generate_lines_count);
};
#endif