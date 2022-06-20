#ifndef __COMMAND_EXECUTOR
#define __COMMAND_EXECUTOR

#include "Basic_functions.h"
#include "Command_line.h"
#include "Table.h"
#include "Int.h"
#include "Float.h"
#include "String.h"
#include "Formula.h"

constexpr uint32_t number_of_valid_commands = 8;
const std::string valid_commands[number_of_valid_commands] = 
{"open", "close", "save", "saveas", "help", "exit", "print", "edit"};
constexpr uint32_t number_of_arguments_for_command[number_of_valid_commands] = { 1, 0, 0, 1, 0, 0, 0, 2 };

bool is_file_valid(const std::string& file_name);
bool is_valid_value(const std::string& value);

class Command_executor
{
private:

	static Command_executor* instance;
	bool done = false;
	bool is_there_a_loaded_file = false;
	std::string loaded_file_name = "";

	Command_executor() = default;
	bool is_done() const;
	void execute(const Command_line&);
	bool is_valid(const Command_line&) const;

	void open(const std::string&);
	void close();
	void save();
	void saveas(const std::string&);
	void help() const;
	void exit();
	void print() const;
	void edit(uint32_t, uint32_t, const std::string&);

public:
	Command_executor(const Command_executor&) = delete;
	Command_executor(const Command_executor&&) = delete;
	Command_executor operator=(const Command_executor&) = delete;
	Command_executor operator=(const Command_executor&&) = delete;
	static Command_executor* get_instance();
	static void free();
	
	void run();
};

#endif