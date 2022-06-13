#include "Float.h"

std::ostream& Float::do_print(std::ostream& out) const
{
	out << value;
	return out;
}

std::optional<float> Float::do_get_value() const
{
	return value;
}

