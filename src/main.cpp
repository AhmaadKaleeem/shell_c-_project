#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <cstdlib> // To use getenv()
#include <sstream>
#include <unordered_map>
using namespace std;
namespace fs = filesystem;
class CommandHandler
{
private:
  unordered_map<string, bool> valid_commands;

public:
  CommandHandler()
  {
    valid_commands_intializer();
  }
  void valid_commands_intializer()
  {
    valid_commands = {
        {"echo", true},
        {"exit", true},
        {"type", true}};
  }
  bool is_valid_command(const string &command)
  {
    if (valid_commands.count(command) > 0)
      return true; // count return 1 if key exist
    else
      return false;
  }
  // function to execute a command
  bool execute(const string &command)
  {
    stringstream ss(command); // spliting command name and input
    string command_name, command_input;
    ss >> command_name;
    getline(ss, command_input);
    // erasing extra space in input after command
    if (!command_input.empty() && command_input[0] == ' ')
    {
      command_input.erase(0, 1);
    }
    if (command_name == "exit")
    {
      return false ;
    } // return on exit command
    if (!is_valid_command(command_name))
    {
      cout << command_name << ": command not found\n";
    }
    else if (command_name == "echo")
    {
      execute_echo(command_input);
    }
    else if (command_name == "type")
    {
      execute_type(command_input);
    }
    return true;
  }

  // function to execute echo command
  void execute_echo(const string &command)
  {
    cout << command << "\n";
  }
  void execute_type(const string &command)
  {
    if (is_valid_command(command))
    {
      cout << command << " is a shell builtin\n";
    }
    else
    {
      string full_path = search_in_path(command);
      if (full_path.empty())
      {
        cout << command << ": not found\n";
        return;
      }
      else
      {
        cout << command << " is " << full_path << endl;
      }
    }
  }

  string search_in_path(string command)
  {
    const char *path_env = getenv("PATH"); // path env return char*
    if (!path_env)
      return "";
    string path_str(path_env); // convertin to string
    stringstream ss(path_str);
    string directory;
    while (getline(ss, directory, ':'))
    {
      string full_path = directory + "/" + command;
      if (check_file_execute(full_path))
      {
        return full_path;
      }
    }
    return "";
  }

  // implemetin repl , infinte loop until user eneter exit or closes terminl
  void repl()
  {
    string user_command;
    while (true)
    {
      cout << "$ ";
      getline(cin, user_command);
      if(!execute(user_command)) break; // exit case
    }
  }

  // checking for file and executable permisiion
  bool check_file_execute(string filepath)
  {
    if (fs::exists(filepath))
    {
      auto perms = fs::status(filepath).permissions();
      if (((perms & (fs::perms::owner_exec | fs::perms::group_exec | fs::perms::others_exec)) != fs::perms::none) && fs::is_regular_file(filepath))
      {
        return true;
      }
    }
    return false;
  }
};

int main()
{
  CommandHandler handler;
  handler.repl();
}
