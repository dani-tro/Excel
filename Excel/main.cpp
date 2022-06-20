#include "Command_executor.h"

int main()
{

	Command_executor::get_instance() -> run();
	Command_executor::free();

	return 0;
}

