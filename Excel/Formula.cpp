#include "Formula.h"

std::ostream& Formula::do_print_to_stream(std::ostream& out) const
{
    if (calculated_value == std::nullopt)out << "ERROR";
    else out << std::setprecision(float_fixed_precision) << std::fixed << calculated_value.value();
    return out;
}

std::istream& Formula::do_read_from_file(std::istream& in)
{
    while (in.peek() != ',' && in.peek() != '\n' && in.peek() != -1)
    {
        formula += in.get();
    }
    return in;
}

std::optional<float> Formula::do_get_value()
{
    if (is_being_evaluated == true)return std::nullopt;
    do_evaluate();
    return calculated_value;
}

void Formula::do_evaluate()
{
    is_being_evaluated = true;
    calculated_value = RPN(*this).evaluate();
    is_being_evaluated = false;
}

uint32_t Formula::do_get_length_in_symbols() const
{
    if (calculated_value.has_value() == false)return error_message_length;
    
    int tmp = calculated_value.value();
    int length = (calculated_value.value() < 0) + (tmp == 0);
    while (tmp != 0)
    {
        tmp /= 10;
        length++;
    }
    return length + float_fixed_precision + dot_length;
}

void Formula::do_print_to_file(std::fstream& file) const
{
    file << formula;
}

Formula::operator RPN() const
{ 
    std::string result;
    uint32_t idx = 1, last_result_size = 0;
    std::stack<char> operations;
    operations.push('(');
    while (idx < formula.size())
    {
        while (idx < formula.size() && formula[idx] == ' ')idx++;
        if (formula[idx] == 'R')
        {
            std::pair<int, int> indexes = read_cell_indexes(formula, idx);
            idx--;
            std::optional<float> cell_value = Table::get_instance() -> get_cell_value(indexes.first, indexes.second);
            Cell* cell_ptr = Table::get_instance()->get_cell_ptr(indexes.first, indexes.second);
            if (cell_value.has_value() == false)return RPN{ "1 0 /" };
            if (cell_value.value() < 0)
            {
                result += "0 ";
                operations.push('-');
                cell_value.value() *= (-1);
            }
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
            if (result.size() == last_result_size)
            {
                result += "0 ";
            }
            last_result_size = result.size();
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
    do_evaluate();
}

std::istream& operator>>(std::istream& in, Formula& f)
{
    while (in.peek() == ',' || in.peek() == '\n')
    {
        f.formula += in.get();
    }
    in.get();
    return in;
}


bool is_valid_Formula(const std::string& formula)
{
    bool opened_quotes = false;
    for (uint32_t i = 1; i < formula.size(); i++)
    {
        if (is_digit(formula[i]) == false && is_operation(formula[i]) == false && 
            formula[i] != '(' && formula[i] != ')' && formula[i] != '\"' && formula[i] != ' '
            && formula[i] != '.' && formula[i] != 'R' && formula[i] != 'C' && opened_quotes == false)return false;
        if (formula[i] == '\"')opened_quotes = !opened_quotes;
    }
    uint32_t opened_brackets = 0;
    for (uint32_t i = 0; i < formula.size(); i++)
    {
        if (formula[i] == '(')opened_brackets++;
        else if (formula[i] == ')')opened_brackets--;
        if (opened_brackets < 0)return false;
    }
    if (opened_brackets != 0)return false;
    for (uint32_t i = 0; i < formula.size(); i++)
    {
        if (formula[i] == 'R')
        {
            float row, column;
            row = get_number(formula, ++i);
            if (formula[i] != 'C')return false;
            column = get_number(formula, ++i);
            if (row <= 0 || column <= 0)return false;
            if (fabs(row - int(row)) > eps || fabs(column - int(column)) > eps)return false;
     
        }
    }
    uint32_t number_of_values = 0, number_of_operations = 0;
    for (uint32_t i = 1; i < formula.size(); i++)
    {
        if (is_operation(formula[i]) == true)number_of_operations++;
        else if (is_digit(formula[i]) == true)
        {
            number_of_values++;
            get_number(formula, i);
            i--;
        }
        else if (formula[i] == 'R')
        {
            number_of_values++;
            get_number(formula, ++i);
            get_number(formula, ++i);
            i--;
        }
    }
    if (number_of_operations < number_of_values - 1)return false;
    return true;
}