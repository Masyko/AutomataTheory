#include "geo.h"

geo::geo()
{
	std::random_device rd;
	std::uniform_int_distribution<size_t> right_chance_dis(0, 100);
	size_t limit = 90;
	for (size_t i = 0; i < _geo.size(); ++i)
	{
		_name += right_chance_dis(rd) < limit ? _geo[i] : get_random_literal();
	}
}
