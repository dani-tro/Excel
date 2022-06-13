#ifndef __RPN_HPP
#define __RPN_HPP

#include "Basic_functions.h"

class RPN
{
private:
	std::string expression;
public:
	std::optional<float> evaluate() const;
	RPN(const std::string&);
};

#endif
