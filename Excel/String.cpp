#include "String.h"

std::ostream& String::do_print(std::ostream& out) const
{
	out << str;
	return out;
}

std::optional<float> String::do_get_value() const
{
	return std::optional<float>(* this);
}

String::String(const std::string& _str) : str{_str}
{
}

String::operator std::optional<float>() const
{
	uint32_t number_of_dots = 0;
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == '.')number_of_dots++;
		if (str[i] != '.' && is_digit(str[i]) == false) return 0.0;
	}
	if (number_of_dots > 1)return 0.0;
	uint32_t idx = 0;
	return get_number(str, idx);
}

