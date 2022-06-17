#ifndef __STRING_HPP
#define __STRING_HPP

#include "Cell.h"

class String : public Cell
{
private:
	std::string str;
	std::optional<float> calculated_value = std::nullopt;
	bool is_calculated = false;

	std::ostream& do_print_to_stream(std::ostream&) const override final;
	std::istream& do_read_from_file(std::istream&) override final;
	std::optional<float> do_get_value() override final;
	void do_evaluate() override final;
	uint32_t do_get_length_in_symbols() const override final;
	void do_print_to_file(std::ofstream&) const override final;

public:
	String() = default;
	String(const std::string&);
	operator float() const;
	friend std::istream& operator>>(std::istream& in, String&);
};

#endif

