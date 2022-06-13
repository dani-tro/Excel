#include "Cell.h"

std::optional<float> Cell::do_get_value() const
{
	return std::nullopt;
}

std::ostream& Cell::print(std::ostream& out) const
{
	do_print(out);
	return out;
}

std::ostream& Cell::println(std::ostream& out) const
{
	print(out);
	out << std::endl;
	return out;
}

std::optional<float> Cell::get_value() const
{
	return do_get_value();
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
	return cell.print(out);
}
