#pragma once
#ifndef _GEO_H_
#define _GEO_H
#include "../Object.h"
class geo :public Object
{
private:
	inline static const std::string _geo = "geo:"; //для ипользования static в других файлах
public:
	geo();
};
#endif