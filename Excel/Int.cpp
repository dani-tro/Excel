#include "Int.h"

std::ostream& Int::do_print(std::ostream& out) const
{
	out << value;
	return out;
}

std::optional<float> Int::do_get_value() const
{
	return value;
}

