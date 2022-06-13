#ifndef __TABLE_HPP
#define __TABLE_HPP

#include "Cell.h"

class Table
{
private:

	static Table* instance;
	std::vector<std::vector<Cell*> > cells;
	Table() = default;

public:

	Table(const Table&) = delete;
	Table(const Table&&) = delete;
	Table operator=(const Table&) = delete;
	Table operator=(const Table&&) = delete;
	std::optional<float> get_cell_value(uint32_t, uint32_t) const;
	static Table* get_instance();
	static void free();

};

#endif
