#ifndef __STRING_HPP
#define __STRING_HPP

#include "Cell.h"

class String : public Cell
{
private:
	std::string str;

	std::ostream& do_print(std::ostream&) const override final;
	std::optional<float> do_get_value() const override final;
public:
	String(const std::string&);
	operator float() const;
};

#endif

