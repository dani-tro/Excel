#include "Cell.h"

std::optional<float> Cell::do_get_value()
{
	return std::nullopt;
}

std::ostream& Cell::print_to_stream(std::ostream& out) const
{
	return do_print_to_stream(out);
}

std::ostream& Cell::println(std::ostream& out) const
{
	print_to_stream(out);
	out << std::endl;
	return out;
}

std::istream& Cell::read_from_file(std::istream& in)
{
	return do_read_from_file(in);
}

std::optional<float> Cell::get_value()
{
	return do_get_value();
}

void Cell::evaluate()
{ 
	do_evaluate();
}

void Cell::print_to_file(std::fstream& file) const
{
	do_print_to_file(file);
}

uint32_t Cell::get_length_in_symbols() const
{
	return do_get_length_in_symbols();
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
	return cell.print_to_stream(out);
}
