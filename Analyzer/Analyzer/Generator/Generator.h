#pragma once
#ifndef _GENERATOR_H_
#define _GENERATOR_H_
#include <string>
#include <fstream>
#include <iostream>
#include <list>
#include "Object/geo/geo.h"
#include "Object/Latitude/Latitude.h"
#include "Object/Longitude/Longitude.h"
#include "Object/Height/Height.h"
#include "Object/Distance/Distance.h"
using namespace std;
class Generator
{
private:
	ofstream _output_file;
	string _path;
	list<Object*> _objects;
private:
	void generate_line();
	void print_line();
public:
	Generator(string __path);
	void Create(size_t __count);
};

#endif