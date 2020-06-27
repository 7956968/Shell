
#include "command.hpp"
#include <sstream>

using namespace std;

command::command(string command_string)
{
    assign(command_string);
}

istream &operator>>(istream &is, command &newCommand)
{
    string command_string;
    getline(is, command_string);
    newCommand.assign(command_string);
    return is;
}

bool command::assign(string &command_string)
{
    if (command_string.length() == 0)
        return false;
    pair<string, vector<string>> parsedCommand = parseRaw(command_string);
    this->commandName = parsedCommand.first;
    this->arguments = parsedCommand.second;
    return true;
}

pair<string, vector<string>> command::parseRaw(string command_string)
{
    string commandName;
    string arg;
    vector<string> args;

    stringstream ss(command_string);
    ss >> commandName;

    while (ss >> arg)
        args.push_back(arg);

    return make_pair(commandName, args);
}

char *const *command::getArguments()
{
    int number_of_arguments = this->arguments.size();
    char **arguments = new char *[number_of_arguments+2];
    arguments[0] = const_cast<char *>(this->getCommandName());
    for (int index = 1; index < number_of_arguments+1; index++)
        arguments[index] = const_cast<char *>(this->arguments[index].c_str());
    arguments[number_of_arguments+1] = NULL;

    return arguments;
}
const char *command::getCommandName()
{
    return this->commandName.c_str();
}

std::ostream &operator<<(std::ostream &os,const command &command)
{
    os << command.commandName;
    return os;
}