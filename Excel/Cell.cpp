#include "Cell.h"

std::optional<float> Cell::do_get_value()
{
	return std::nullopt;
}

std::ostream& Cell::print(std::ostream& out) const
{
	return do_print(out);
}

std::ostream& Cell::println(std::ostream& out) const
{
	print(out);
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

void Cell::takes_part_in(const Cell* ptr)
{
	for (int i = 0; i < participates_in_formula.size(); i++)
		if (participates_in_formula[i] == ptr)return;
	participates_in_formula.push_back(ptr);
}

void Cell::evaluate()
{ 
	do_evaluate();
}

uint32_t Cell::get_length_in_symbols() const
{
	return do_get_length_in_symbols();
}

std::ostream& operator<<(std::ostream& out, const Cell& cell)
{
	return cell.print(out);
}
