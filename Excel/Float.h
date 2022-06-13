#ifndef __FLOAT_HPP
#define __FLOAT_HPP

#include "Cell.h"

class Float : public Cell
{
private:
	float value;

	std::ostream& do_print(std::ostream&) const override final;
	std::optional<float> do_get_value() const override final;
public:
};

#endif

