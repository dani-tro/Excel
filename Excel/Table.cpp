#include "Table.h"

Table* Table::instance = nullptr;

void Table::evaluate_the_cells()
{
    
    for (int i = 0; i < cells.size(); i++)
        for (int j = 0; j < cells[i].size(); j++)
        {
            cells[i][j]->evaluate();
        }
    for (int i = 0; i < columns; i++)columns_max_length[i] = find_max_length_in_column(i);
}

uint32_t Table::find_max_length_in_column(uint32_t col) const
{
    uint32_t max = 0;
    for (int i = 0; i < cells.size(); i++)
    {
        if (col < cells[i].size())
        {
            max = std::max(max, cells[i][col]->get_length_in_symbols());
        }
    }
    return max;
}

void Table::expand(uint32_t r, uint32_t c)
{
    
    while (r >= cells.size())cells.push_back(std::vector<Cell*>());
    while (c >= cells[r].size())cells[r].push_back(new Empty_cell());
    if(cells[r].size() > columns)columns = cells[r].size();
    while (columns_max_length.size() < columns)columns_max_length.push_back(0);
    return;
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

Table::~Table()
{
    for (int i = 0; i < cells.size(); i++)
    {
        for (int j = 0; j < cells[i].size(); j++)delete cells[i][j];
    }
}

void Table::free()
{
    delete instance;
    instance = nullptr;
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
    columns_max_length = std::vector<uint32_t>(columns);
    evaluate_the_cells();
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
            if(cells[i].size() > j)cells[i][j]->print_to_stream(out);
            out << " | ";
            
        }
        out << "\n";
    }
    return;
}

void Table::change_cell(uint32_t x, uint32_t y, const std::string& new_value)
{
    x--;
    y--;
    if (x >= cells.size() || y >= cells[x].size())expand(x, y);

    Cell* ptr = nullptr;
    if (new_value[0] == '\"')ptr = new String(new_value);
    else if (new_value[0] == '=')ptr = new Formula(new_value);
    else if (new_value[0] == '+' || new_value[0] == '-' || is_digit(new_value[0]) == true)
    {
        uint32_t idx = 0;
        if (new_value[idx] == '+' || new_value[idx] == '-')idx++;
        while (new_value[idx] != -1 && is_digit(new_value[idx]) == true)
        {
            idx++;
        }
        if (new_value[idx] == '.')ptr = new Float(new_value);
        else ptr = new Int(new_value);
    }
    delete cells[x][y];
    cells[x][y] = ptr;
    evaluate_the_cells();
    unsaved_changes = true;

    return;
}

void Table::open_file(const std::string& file_name, std::ios_base::openmode openmode)
{
    if (does_file_exist(file_name) == false)
    {
        file.open(file_name, std::ios::out);
        file.close();
    }
    file.open(file_name, openmode);
    return;
}

void Table::close_file()
{
    file.close();
}

bool Table::has_unsaved_changes() const
{
    return unsaved_changes;
}


void Table::save_to_file()
{
    for (int i = 0; i < cells.size(); i++)
    {
        if (cells[i].size() > 0)cells[i][0] -> print_to_file(file);
        for (int j = 1; j < cells[i].size(); j++)
        {
            file << ", ";
            cells[i][j]->print_to_file(file);
        }
        file << "\n";
    }
    unsaved_changes = false;
}




