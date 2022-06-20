#ifndef __COMMAND_LINE
#define __COMMAND_LINE

#include "Basic_functions.h"

class Command_line
{
private:
	std::vector<std::string> list_of_arguments;
	void parse(const std::string&);
public:
	Command_line(const std::string&);
	uint32_t get_number_of_arguments() const;
	const std::string& operator[](uint32_t) const;
};

#endif