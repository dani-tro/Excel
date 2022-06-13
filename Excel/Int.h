#ifndef __INT_HPP
#define __INT_HPP

#include "Cell.h"

class Int : public Cell
{
private:
	int value;

	std::ostream& do_print(std::ostream&) const override final;
	std::optional<float> do_get_value() const override final;
public:

};

#endif 
