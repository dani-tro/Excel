#ifndef __FLOAT_HPP
#define __FLOAT_HPP

#include "Cell.h"

constexpr uint32_t float_fixed_precision = 4;
constexpr uint32_t dot_length = 1;

class Float : public Cell
{
private:
	float value = 0.0;
	char sign = 0;

	std::ostream& do_print(std::ostream&) const override final;
	std::istream& do_read_from_file(std::istream&) override final;
	std::optional<float> do_get_value() override final;
	void do_evaluate() override final;
	uint32_t do_get_length_in_symbols() const override final;

public:
	Float() = default;
	Float(float);
};

#endif

