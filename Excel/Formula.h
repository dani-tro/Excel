#ifndef __FORMULA_HPP
#define __FORMULA_HPP

#include "Cell.h"
#include "RPN.h"
#include "Basic_functions.h"
#include "Table.h"

class Formula : public Cell
{
private:
	std::string formula;
	std::optional<float> calculated_value = std::nullopt;

	std::ostream& do_print(std::ostream&) const override final;
	std::optional<float> do_get_value() const override final;
	std::optional<float> evaluate() const;
public:
	operator RPN() const;
	Formula(const std::string&);
};

#endif

