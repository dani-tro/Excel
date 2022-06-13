#ifndef __CELL_HPP
#define __CELL_HPP

#include "Libraries.h"
#include "Basic_functions.h"

class Cell
{
private:
	virtual std::ostream& do_print(std::ostream&) const = 0;
	virtual std::optional<float> do_get_value() const;
public: 
	std::ostream& print(std::ostream& out = std::cout) const;
	std::ostream& println(std::ostream& out = std::cout) const;
	std::optional<float> get_value() const;
};

#endif 
