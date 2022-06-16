#ifndef __TABLE_HPP
#define __TABLE_HPP

#include "Cell.h"
#include "String.h"
#include "Int.h"
#include "Float.h"
#include "Formula.h"
#include "Empty_cell.h"

class Table
{
private:

	static Table* instance;
	std::vector< std::vector<Cell* > > cells;
	std::vector<uint32_t> columns_max_length;
	uint32_t columns = 0;
	std::fstream file;
	Table() = default;
	void evaluate_the_cells();

public:

	Table(const Table&) = delete;
	Table(const Table&&) = delete;
	Table operator=(const Table&) = delete;
	Table operator=(const Table&&) = delete;
	std::optional<float> get_cell_value(uint32_t, uint32_t) const;
	Cell* get_cell_ptr(uint32_t, uint32_t) const;
	static Table* get_instance();
	static void free();
	void read_from_file();
	void print(std::ostream&) const;

};

#endif
