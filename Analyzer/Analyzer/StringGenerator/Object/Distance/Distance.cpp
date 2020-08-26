#include "Distance.h"

Distance::Distance()
{
	std::random_device rd;
	std::uniform_int_distribution<size_t> right_chance_dis(0, 10000);
	size_t limit = 9999;
	std::uniform_int_distribution<size_t> length_dis(0, 3); //количество цифр
	std::uniform_int_distribution<size_t> number_dis('0', '9'); // случайная цифра
	for (size_t i = 0; i < _distance.size(); ++i)
	{
		_name += right_chance_dis(rd) < limit ? _distance[i] : get_random_literal();
	}
	size_t length = length_dis(rd);
	for (size_t i = 0; i < length; ++i)
	{
		_name += right_chance_dis(rd) < limit ? static_cast<char>(number_dis(rd)) : get_random_literal(); // собираем высоту
	}
}
