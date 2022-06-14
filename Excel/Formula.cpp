#include "Formula.h"

std::ostream& Formula::do_print(std::ostream& out) const
{
    if (calculated_value == std::nullopt)out << "ERROR";
    else out << formula;
    return out;
}

std::optional<float> Formula::do_get_value() const
{
    return calculated_value;
}

std::optional<float> Formula::evaluate() const
{
    std::optional<float> result = RPN(*this).evaluate();
    return result;
}

Formula::operator RPN() const
{
    std::string result;
    uint32_t idx = 1;
    std::stack<char> operations;
    operations.push('(');
    char tmp;
    while (idx < formula.size())
    {
        while (idx < formula.size() && formula[idx] == ' ')idx++;
        if (formula[idx] == 'N')
        {
            std::pair<int, int> indexes = read_cell_indexes(formula, idx);
            idx--;
            std::optional<float> cell_value = Table::get_instance() -> get_cell_value(indexes.first, indexes.second);
            if (cell_value.has_value() == false)return RPN{ "1 0 /" };
            result += std::to_string(cell_value.value());
            result += " ";
        }
        else if (is_digit(formula[idx]) == true)
        {
            result += std::to_string(get_number(formula, idx));
            idx--;
            result += " ";
        }
        else if (is_operation(formula[idx]) == true)
        {
            if (result.size() == 0)
            {
                result += "0 ";
            }
            while (operations.top() != '(' && priority(operations.top()) >= priority(formula[idx]))
            {
                result += operations.top();
                result += " ";
                operations.pop();
            }
            operations.push(formula[idx]);
        }
        else if (formula[idx] == '(')
        {
            operations.push(formula[idx]);
        }
        else if (formula[idx] == ')')
        {
            while (operations.top() != '(')
            {
                result += operations.top();
                result += " ";
                operations.pop();
            }
            operations.pop();
        }
        else if (formula[idx] == '\"')
        {
            result += std::to_string(get_number(formula, ++idx, '\"'));
            result += " ";
        }
        idx++;
    }
    while(operations.top() != '(')
    {
        result += operations.top();
        result += " ";
        operations.pop();
    }
    return RPN(result);
}

Formula::Formula(const std::string& _formula): formula{_formula}
{
    calculated_value = evaluate();
}


