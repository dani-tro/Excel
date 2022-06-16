#ifndef __CELL_HPP
#define __CELL_HPP

#include "Libraries.h"
#include "Basic_functions.h"

class Cell
{
private:
	
	virtual std::ostream& do_print(std::ostream&) const = 0;
	virtual std::optional<float> do_get_value();
	virtual std::istream& do_read_from_file(std::istream&) = 0;
	virtual void do_evaluate() = 0;
	std::vector<const Cell*> participates_in_formula;
	virtual uint32_t do_get_length_in_symbols() const = 0;
public:
	virtual ~Cell() noexcept = default;
	std::ostream& print(std::ostream& out = std::cout) const;
	std::ostream& println(std::ostream& out = std::cout) const;
	std::istream& read_from_file(std::istream& in = std::cin);
	std::optional<float> get_value();
	void takes_part_in(const Cell*);
	void evaluate();
	uint32_t get_length_in_symbols() const;
};

#endif 
