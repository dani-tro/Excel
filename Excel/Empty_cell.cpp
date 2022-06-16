#include "Empty_cell.h"

std::ostream& Empty_cell::do_print(std::ostream& out) const
{
	return out;
}

std::istream& Empty_cell::do_read_from_file(std::istream& in)
{
	return in;
}

std::optional<float> Empty_cell::do_get_value()
{
	return 0;
}

void Empty_cell::do_evaluate()
{
}

uint32_t Empty_cell::do_get_length_in_symbols() const
{
	return 0;
}


