#ifndef __INT_HPP
#define __INT_HPP

#include "Cell.h"

class Int : public Cell
{
private:
	int value = 0;
	char sign = 0;

	std::ostream& do_print(std::ostream&) const override final;
	std::istream& do_read_from_file(std::istream&) override final;
	std::optional<float> do_get_value() override final;
	void do_evaluate() override final;
	uint32_t do_get_length_in_symbols() const override final;

public:
	Int() = default;
	Int(const Int&) = default;
	Int(int);
};

#endif 
