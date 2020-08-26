#pragma once
#ifndef _DISTSNCE_H
#define _DISTSNCE_H
#include "../Object.h"
class Distance : public Object {
public:
	Distance();
private:
	inline static const std::string _distance = ";u=";
};
#endif