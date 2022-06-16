#include "RPN.h"

std::optional<float> RPN::evaluate() const
{
    
    float tmp, lhs, rhs;
    std::optional<float> result = 0;
    std::stack<float> numbers;
    uint32_t idx = 0;
    while(idx < expression.size())
    {
        while (expression[idx] == ' ')idx++;
        if (is_digit(expression[idx]) == true)
        {
            tmp = get_number(expression, idx);
            
            numbers.push(tmp);
        }
        else
        {
            rhs = numbers.top();
            numbers.pop();
            lhs = numbers.top();
            numbers.pop();
            result = perform_operation(lhs, expression[idx++], rhs);
            if (result.has_value() == false)return std::nullopt;
            else numbers.push(result.value());
        }
        idx++;
    }
    return result;
}

RPN::RPN(const std::string& _expression): expression(_expression)
{
}

