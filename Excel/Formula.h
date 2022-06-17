#ifndef __FORMULA_HPP
#define __FORMULA_HPP

#include "Cell.h"
#include "RPN.h"
#include "Basic_functions.h"
#include "Table.h"

constexpr uint32_t error_message_length = 5;

class Formula : public Cell
{
private:
	std::string formula;
	std::optional<float> calculated_value = std::nullopt;
	bool is_being_evaluated = false;

	std::ostream& do_print_to_stream(std::ostream&) const override final;
	std::istream& do_read_from_file(std::istream&) override final;
	std::optional<float> do_get_value() override final;
	void do_evaluate() override final;
	uint32_t do_get_length_in_symbols() const override final;
	void do_print_to_file(std::ofstream&) const override final;
	

public:
	Formula() = default;
	Formula(const Formula&) = default;
	Formula(const std::string&);
	operator RPN() const;
	friend std::istream& operator>>(std::istream& in, Formula&);
};

#endif

