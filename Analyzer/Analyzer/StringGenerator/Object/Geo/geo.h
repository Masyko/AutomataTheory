#pragma once
#ifndef _GEO_H_
#define _GEO_H
#include "../Object.h"
class geo :public Object
{
private:
	inline static const std::string _geo = "geo:"; //��� ������������ static � ������ ������
public:
	geo();
};
#endif