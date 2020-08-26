#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <string>
#include <fstream>
#include <random>
class Object {
protected:
	std::string _name;
	char get_random_literal() {
		std::random_device rd; // ��� ������ random
		std::uniform_int_distribution<size_t> dis('a','z'); // ��������� ����������� ��������� ����� �� ����������
		return dis(rd);
	}
public:
	void Print(std::ofstream& __output_file);
};

#endif