#include "Table.h"

Table* Table::instance = nullptr;

std::optional<float> Table::get_cell_value(uint32_t x, uint32_t y) const
{
    x--; y--;
    if (x >= cells.size()) return std::nullopt;
    if (y >= cells[x].size()) return std::nullopt;
    return cells[x][y] -> get_value();
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


