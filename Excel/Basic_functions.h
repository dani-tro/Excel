#ifndef __BASIC_FUNCTIONS
#define __BASIC_FUNCTIONS

#include "Libraries.h"

bool is_digit(char);
int get_digit(char);
float get_number(const std::string&, uint32_t&);
bool is_operation(char);
uint32_t priority(char);
std::optional<float> perform_operation(float, char, float);
std::pair<int, int> read_cell_indexes(const std::string&, uint32_t&);

#endif 


