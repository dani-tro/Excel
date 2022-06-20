#ifndef __TABLE_HPP
#define __TABLE_HPP

#include "Cell.h"
#include "String.h"
#include "Int.h"
#include "Float.h"
#include "Formula.h"
#include "Empty_cell.h"

constexpr uint32_t MAX_SIZE = 8192;

class Table
{

private:

	static Table* instance;
	std::vector< std::vector<Cell* > > cells;
	std::vector<uint32_t> columns_max_length;
	uint32_t columns = 0;
	std::fstream file;
	bool unsaved_changes = false;

	Table() = default;
	void evaluate_the_cells();
	uint32_t find_max_length_in_column(uint32_t) const;
	void expand(uint32_t, uint32_t);

public:
	Table(const Table&) = delete;
	Table(const Table&&) = delete;
	Table operator=(const Table&) = delete;
	Table operator=(const Table&&) = delete;
	~Table();
	std::optional<float> get_cell_value(uint32_t, uint32_t) const;
	Cell* get_cell_ptr(uint32_t, uint32_t) const;
	static Table* get_instance();
	static void free();
	void read_from_file();
	void print(std::ostream&) const;
	void change_cell(uint32_t, uint32_t, const std::string&);
	void save_to_file();
	void open_file(const std::string&, std::ios_base::openmode);
	void close_file();
	bool has_unsaved_changes() const;
};

#endif
