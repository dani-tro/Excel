#include "Float.h"

std::ostream& Float::do_print_to_stream(std::ostream& out) const
{
    if (sign != 0)out << sign;
	out << std::setprecision(float_fixed_precision) << std::fixed << value;
	return out;
}

std::istream& Float::do_read_from_file(std::istream& in)
{
    float dec_power = 1.0;
    bool found_dot = false;
    if (in.peek() == '+' || in.peek() == '-')sign = in.get();
    else sign = 0;
    while ((is_digit(in.peek()) == true || (in.peek() == '.')) && in.peek() != -1)
    {
        if (in.peek() == '.')found_dot = true;
        else if (found_dot == false)value = value * 10 + get_digit(in.peek());
        else
        {
            dec_power /= 10;
            value += get_digit(in.peek()) * dec_power;
        }
        in.get();
    }
    return in;
}

std::optional<float> Float::do_get_value()
{
    if (sign == '-')return -value;
    return value;
}

void Float::do_evaluate()
{
}

uint32_t Float::do_get_length_in_symbols() const
{
    int tmp = value;
    int length = (sign != 0) + (tmp == 0);
    while (tmp > 0)
    {
        tmp /= 10;
        length++;
    }
    return length + float_fixed_precision + dot_length;
}

void Float::do_print_to_file(std::fstream& file) const
{
    do_print_to_stream(file);
}

Float::Float(float _value) : value{_value}
{
}

Float::Float(std::string str)
{
    uint32_t idx = 0;
    value = get_number(str, idx, '\0');
}
