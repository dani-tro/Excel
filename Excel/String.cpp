#include "String.h"

std::ostream& String::do_print(std::ostream& out) const
{
	out << str;
	return out;
}

std::optional<float> String::do_get_value() const
{
	return float(* this);
}

String::String(const std::string& _str) : str{_str}
{
}

String::operator float() const
{
	uint32_t idx = 1;
	return get_number(str, idx, '\"');
}

