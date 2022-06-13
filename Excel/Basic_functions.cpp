#include "Basic_functions.h"

bool is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

int get_digit(char c)
{
    return c - '0';
}

float get_number(const std::string& str, uint32_t& begin)
{
    float result = 0.0, dec_power = 1.0;
    bool found_dot = false;
    while (begin < str.size() && (is_digit(str[begin]) == true || (str[begin] == '.')))
    {
        if (str[begin] == '.')found_dot = true;
        else if (found_dot == false)result = result * 10 + get_digit(str[begin]);
        else
        {
            dec_power /= 10;
            result += get_digit(str[begin]) * dec_power;
        }
        begin++;
    }
    return result;
}

bool is_operation(char c)
{
    return (c == '+' || c == '-' || c == '/' || c == '*' || c == '^');
}

uint32_t priority(char c)
{
    switch (c)
    {
        case '+' : case '-' :
            return 1;
            break;
        case '*': case '/':
            return 2;
            break;
        case '^':
            return 3;
            break;
        default:
            return 0;
            break;
    }
    return 0;
}


std::optional<float> perform_operation(float lhs, char operation, float rhs)
{
    switch (operation)
    {
    case '+':
        return lhs + rhs;
    case '-':
        return lhs - rhs;
    case '/':
        if (rhs != 0) return lhs / rhs;
        else return std::nullopt;
    case '*':
        return lhs * rhs;
    case '^':
        return (float)pow(lhs, rhs);
    default:
        return std::nullopt;
    }
    return std::nullopt;
}

std::pair<int, int> read_cell_indexes(const std::string& str, uint32_t& begin)
{
    std::pair<int, int> result;
    result.first = get_number(str, ++begin);
    result.second = get_number(str, ++begin);
    return result;

}

