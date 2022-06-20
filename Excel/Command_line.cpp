#include "Command_line.h"

void Command_line::parse(const std::string& command_line)
{
	uint32_t idx = 0;
	bool opened_quotes = false;
	std::string current_argument = "";
	while (idx < command_line.size())
	{
		if (command_line[idx] == '\"')
		{
			opened_quotes = !opened_quotes;
		}
		if (command_line[idx] == ' ' && opened_quotes == false)
		{
			if (current_argument.size() != 0)
			{
				list_of_arguments.push_back(current_argument);
				current_argument = "";
			}
		}
		else current_argument += command_line[idx];
		idx++;
	}
	if (current_argument.size() != 0)list_of_arguments.push_back(current_argument);
	if (list_of_arguments.size() > 0)tolower(list_of_arguments[0]);

}

Command_line::Command_line(const std::string& command_line)
{
	parse(command_line);
}

uint32_t Command_line::get_number_of_arguments() const
{
	return list_of_arguments.size();
}

const std::string& Command_line::operator[](uint32_t idx) const
{
	if (idx >= 0 && idx < list_of_arguments.size())return list_of_arguments[idx];
	return "";
}
