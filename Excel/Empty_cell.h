#ifndef __EMPTY_CELL_HPP
#define __EMPTY_CELL_HPP

#include "Cell.h"

class Empty_cell : public Cell
{
private:

	std::ostream& do_print(std::ostream&) const override final;
	std::istream& do_read_from_file(std::istream&) override final;
	std::optional<float> do_get_value() override final;
	void do_evaluate() override final;
	uint32_t do_get_length_in_symbols() const override final;

public:
};

#endif 
