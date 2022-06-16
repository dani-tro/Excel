#include "Table.h"

Table* Table::instance = nullptr;

void Table::evaluate_the_cells()
{
    
    for (int i = 0; i < cells.size(); i++)
        for (int j = 0; j < cells[i].size(); j++)
        {
            cells[i][j]->evaluate();
        }
}

std::optional<float> Table::get_cell_value(uint32_t x, uint32_t y) const
{
    x--; y--;
    if (x >= cells.size()) return 0.0;
    if (y >= cells[x].size()) return 0.0;
    return cells[x][y] -> get_value();
}

Cell* Table::get_cell_ptr(uint32_t x, uint32_t y) const
{
    x--; y--;
    if (x >= cells.size()) return nullptr;
    if (y >= cells[x].size()) return nullptr;
    return cells[x][y];
}

Table* Table::get_instance()
{
    if (instance == nullptr)instance = new Table();
    return instance;
}

void Table::free()
{
    delete instance;
}

void Table::read_from_file()
{
    columns = 0;
    std::vector<Cell* > tmp;
    Cell* ptr;
    while(!file.eof())
    { 
        ptr = nullptr;
        while (file.peek() == ' ')file.get();
        if (file.peek() == '\"')ptr = new String();
        else if (file.peek() == '=')ptr = new Formula();
        else if (file.peek() == ',')ptr = new Empty_cell();
        else if(file.peek() == '+' || file.peek() == '-' || is_digit(file.peek()) == true)
        {
            int position = file.tellg();
            if (file.peek() == '+' || file.peek() == '-')file.get();
            while (file.peek() != -1 && is_digit(file.peek()) == true)
            {
                file.get();
            }
            if (file.peek() == '.')ptr = new Float();
            else ptr = new Int();
            if (!file.good())file.clear();
            file.seekg(position);
        }
        
        if (ptr != nullptr)
        {
            ptr->read_from_file(file);
            tmp.push_back(ptr);
        }
        while (file.peek() == ' ')file.get();
        if (file.peek() == '\n')
        {
           
            if (tmp.size() > columns)columns = tmp.size();
            cells.push_back(tmp);
            tmp.clear();
        }
        file.get();
        if (file.peek() == -1)
        {
            file.get();
            if (tmp.size() != 0)
            {
                if (tmp.size() > columns)columns = tmp.size();
                cells.push_back(tmp);
            }
        }
    }
    evaluate_the_cells();
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[i].size(); j++)
            {
                if (j >= columns_max_length.size())columns_max_length.push_back(cells[i][j]->get_length_in_symbols());
                else columns_max_length[j] = std::max(columns_max_length[j], cells[i][j]->get_length_in_symbols());
            }
    }
    return;
}

void Table::print(std::ostream& out) const
{
    uint32_t number_of_spaces;
    for (int i = 0; i < cells.size(); i++)
    {
        out << "| ";
        for (int j = 0; j < columns; j++)
        {
            if (j < cells[i].size())number_of_spaces = columns_max_length[j] - cells[i][j]->get_length_in_symbols();
            else number_of_spaces = columns_max_length[j];
            for (int k = 0; k < number_of_spaces; k++)out << " ";
            if(cells[i].size() > j)cells[i][j]->print(out);
            out << " | ";
            
        }
        out << "\n";
    }
    return;
}


