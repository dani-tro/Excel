#include "Command_executor.h"

Command_executor* Command_executor::instance = nullptr;

inline bool is_file_valid(const std::string)
{
    return true;
}

Command_executor* Command_executor::get_instance()
{
    if (instance == nullptr)instance = new Command_executor();
    return instance;
}

void Command_executor::free()
{
    delete instance;
}

void Command_executor::execute(const Command_line& cl)
{
    if (is_valid(cl) == false)return;
    std::string command = cl[0];
    if (command == "open")
    {
        if (cl.get_number_of_arguments() > 2)std::cout << cl.get_number_of_arguments() - 2 << " redundant arguments omitted!\n";
        open(cl[1]);
    }
    else if (command == "close")
    {
        if (cl.get_number_of_arguments() > 1)std::cout << cl.get_number_of_arguments() - 1 << " redundant arguments omitted!\n";
        close();
    }
    else if (command == "save")
    {
        if (cl.get_number_of_arguments() > 1)std::cout << cl.get_number_of_arguments() - 1 << " redundant arguments omitted!\n";
        save();
    }
    else if (command == "saveas")
    {
        if (cl.get_number_of_arguments() > 2)std::cout << cl.get_number_of_arguments() - 2 << " redundant arguments omitted!\n";
        saveas(cl[1]);
    }
    else if (command == "help")
    {
        if (cl.get_number_of_arguments() > 1)std::cout << cl.get_number_of_arguments() - 1 << " redundant arguments omitted!\n";
        help();
    }
    else if (command == "exit")
    {
        if (cl.get_number_of_arguments() > 1)std::cout << cl.get_number_of_arguments() - 1 << " redundant arguments omitted!\n";
        exit();
    }
    else if (command == "print")
    {
        if (cl.get_number_of_arguments() > 1)std::cout << cl.get_number_of_arguments() - 1 << " redundant arguments omitted!\n";
        print();
    }
    else if (command == "edit")
    {
        if (cl[1][0] != 'R')
        {
            std::cout << "Invalid coordinates of the cell entered!\n";
            return;
        }
        uint32_t idx = 1;
        int32_t row = get_number(cl[1], idx);
        if (cl[1][idx] != 'C')
        {
            std::cout << "Invalid coordinates of the cell entered!\n";
            return;
        }
        idx++;
        int32_t column = get_number(cl[1], idx);
        if (row <= 0 || column <= 0)
        {
            std::cout << "Invalid coordinates of the cell entered!\n";
            return;
        }
        if (row >= MAX_SIZE || column >= MAX_SIZE)
        {
            std::cout << "The coordinates entered are out of bounds!\n";
            return;
        }
        if (cl.get_number_of_arguments() > 3)std::cout << cl.get_number_of_arguments() - 3 << " redundant arguments omitted!\n";
        edit(row, column, cl[2]);
    }
    return;
}

bool Command_executor::is_done() const
{
    return done;
}

bool Command_executor::is_valid(const Command_line& cl) const
{
    if (cl.get_number_of_arguments() == 0)
    {
        std::cout << "Empty command!\n";
        return false;
    }
    int32_t command_index = -1;
    std::string command = cl[0];
    for (int i = 0; i < number_of_valid_commands; i++)
    {
        if (cl[0] == valid_commands[i])command_index = i;
    }
    if (command_index == -1)
    {
        std::cout << "Invalid command! Type Help to get a list of the correct commands\n";
        return false;
    }
    if (cl.get_number_of_arguments() <= number_of_arguments_for_command[command_index])
    {
        std::cout << "Insufficient number of arguments for command " << cl[0] << " supplied!\n";
        return false;
    }
    if (command == "open" || command == "exit")
    {
        if (is_there_a_loaded_file == true && Table::get_instance() -> has_unsaved_changes() == true)
        {
            std::cout << "You have an open file with unsaved changes, please select close or save first.\n";
            return false;
        }
    }
    if (command != "open" && command != "help" && command != "exit")
    {
        if (is_there_a_loaded_file == false)
        {
            std::cout << "No file is currently opened!\n";
            return false;
        }
    }
    return true; 
}

void Command_executor::open(const std::string& file_name)
{
    if (is_file_valid(file_name) == false)return;
    Table::get_instance()->open_file(file_name, std::ios::in);
    Table::get_instance()->read_from_file();
    Table::get_instance()->close_file();
    is_there_a_loaded_file = true;
    loaded_file_name = file_name;
    std::cout << "Successfully opened " << file_name << std::endl;
    return;
}

void Command_executor::close()
{
    if (Table::get_instance()->has_unsaved_changes() == true)
    {
        std::cout << "Want to save your changes to " << loaded_file_name << "? [Y / N]: ";
        char choice;
        do
        {
            std::cin >> choice;
            std::cin.get();
            if (choice != 'Y' && choice != 'N')std::cout << "Invalid choice! Please, try again. [Y/N]: ";
        } while (choice != 'Y' && choice != 'N');
        if (choice == 'Y')save();
    }
    Table::free();
    std::cout << "Successfully closed " << loaded_file_name << "\n";
    is_there_a_loaded_file = false;
    loaded_file_name = "";
    return;
}

void Command_executor::save()
{
    Table::get_instance()->open_file(loaded_file_name, std::ios::out | std::ios::in | std::ios::trunc);
    Table::get_instance()->save_to_file();
    Table::get_instance()->close_file();
    std::cout << "Successfully saved " << loaded_file_name << std::endl;
    return;
}

void Command_executor::saveas(const std::string& file_name)
{
    if (does_file_exist(file_name) == true)
    {
        std::cout << "The file " << file_name << " already exists. Do you want to replace it? [Y/N]: ";
        char choice;
        do
        {
            std::cin >> choice;
            std::cin.get();
            if (choice != 'Y' && choice != 'N')std::cout << "Invalid choice! Please, try again. [Y/N]: ";
        } 
        while (choice != 'Y' && choice != 'N');
        if (choice == 'N')return;
    }
    loaded_file_name = file_name;
    save();
    return;
}

void Command_executor::help() const
{
    std::cout << "The following commands are supported:" << std::endl;
    std::cout << "open <file>                    opens <file>" << std::endl;
    std::cout << "close                          closes currently opened file" << std::endl;
    std::cout << "save                           saves the currently open file" << std::endl;
    std::cout << "saveas <file>                  saves the currently open file in <file>" << std::endl;
    std::cout << "help                           prints this information" << std::endl;
    std::cout << "exit                           exists the program" << std::endl;
    std::cout << "print                          prints the table to the screen" << std::endl;
    std::cout << "edit  R<N>C<M> <value>         changes the value at row <N> and column <M> to <value>" << std::endl;
    return;
}

void Command_executor::exit()
{
    Table::free();
    done = true;
    std::cout << "Exiting program...\n";
    return;
}

void Command_executor::print() const
{
    Table::get_instance()->print(std::cout);
    return;
}

void Command_executor::edit(uint32_t row, uint32_t column, const std::string& value)
{
    Table::get_instance()->change_cell(row, column, value);
    std::cout << "Successfully changed the value of cell R" << row << "C" << column << " to " << value << std::endl;
    return;
}

void Command_executor::run()
{
    while (is_done() == false)
    {
        std::cout << "> ";
        std::string input_line;
        std::getline(std::cin, input_line);
        Command_line cl{ input_line };
        execute(cl);
    }
    return;
}


