#include "String.h"

std::ostream& String::do_print_to_stream(std::ostream& out) const
{
	for (int i = 1; i < str.size() - 1; i++)
	{
		if(str[i] == '\\' && str[i - 1] == '\\' || str[i] == '"' && 
			str[i - 1] == '\\' || str[i] != '"' && str[i] != '\\')out << str[i];
	}
	return out;
}

std::istream& String::do_read_from_file(std::istream& in)
{
	while (in.peek() != ',' && in.peek() != '\n' && in.peek() != -1)
	{
		str += in.get();
	}
	return in;
}

std::optional<float> String::do_get_value()
{
	if (is_calculated == false)do_evaluate();
	return calculated_value;
}

void String::do_evaluate()
{
	is_calculated = true;
	calculated_value = float(*this);
}

uint32_t String::do_get_length_in_symbols() const
{
	uint32_t length = 0;
	for (int i = 1; i < str.size() - 1; i++)
	{
		if (str[i] == '\\' && str[i - 1] == '\\' || str[i] == '"' &&
			str[i - 1] == '\\' || str[i] != '"' && str[i] != '\\')length++;
	}
	return length;
}

void String::do_print_to_file(std::fstream& file) const
{
	file << str;
}

String::String(const std::string& _str) : str{_str}
{
}

String::operator float() const
{
	uint32_t idx = 1;
	return get_number(str, idx, '"');
}

bool is_valid_String(const std::string& string)
{
	if (string[string.size() - 1] != '\"')return false;
	bool opened_quote = false;
	for (int i = 0; i < string.size(); i++)if (string[i] == '\"')opened_quote = !opened_quote;
	if (opened_quote == true)return false;
	return true;
}

std::istream& operator>>(std::istream& in, String& s)
{
	while (in.peek() == ',' || in.peek() == '\n')
	{
		s.str += in.get();
	}
	return in;
}
