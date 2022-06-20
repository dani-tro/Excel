#ifndef __BASIC_FUNCTIONS_HPP
#define __BASIC_FUNCTIONS_HPP

#include "Libraries.h"

bool is_digit(char);
int get_digit(char);
float get_number(const std::string&, uint32_t&);
float get_number(const std::string&, uint32_t&, char);
bool is_operation(char);
uint32_t priority(char);
std::optional<float> perform_operation(float, char, float);
std::pair<int, int> read_cell_indexes(const std::string&, uint32_t&);
void tolower(std::string&);
bool does_file_exist(const std::string&);
void remove_spaces_at_the_ends(std::string&);

#endif 


