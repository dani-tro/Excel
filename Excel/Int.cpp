#include "Int.h"

std::ostream& Int::do_print(std::ostream& out) const
{
	if (sign != '0')out << sign;
	out << value;
	return out;
}

std::istream& Int::do_read_from_file(std::istream& in)
{
	if (in.peek() == '+' || in.peek() == '-')sign = in.get();
	else sign = 0;
	while (is_digit(in.peek()) == true && in.peek() != -1)
	{
		value = value * 10 + get_digit(in.get());
	}
	
	return in;
}

std::optional<float> Int::do_get_value()
{
	if (sign == '-')return -value;
	return value;
}

void Int::do_evaluate()
{
}

uint32_t Int::do_get_length_in_symbols() const
{
	int tmp = value;
	int length = (sign != 0) + (tmp == 0);
	while (tmp != 0)
	{
		tmp /= 10;
		length++;
	}
	return length;
}

Int::Int(int _value) : value{ _value }
{
}

