#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;
class CommandHandler{
private: 
unordered_map<string,bool> valid_commands;
public:
 CommandHandler() {
  valid_commands_intializer();
 }
 void valid_commands_intializer(){
  valid_commands = {
    {"echo", true},
    {"exit", true}
  };
 }
 bool is_valid(const string& command){
  if (valid_commands.count(command) > 0) return true; // count return 1 if key exist 
  else return false;
 }
// function to execute a command
 void execute(const string& command){
  stringstream ss(command); // spliting command name and input
  string command_name,command_input;
  ss >> command_name;
  getline(ss,command_input);

  if (command_name == "exit") { return ;} // return on exit command
  if (!is_valid(command_name) ){
    cout << command_name << ": command not found\n";
  }
  else if (command_name == "echo"){
    execute_echo(command_input);
  }

 }

  // function to execute echo command
  void execute_echo(const string& command){
   cout << command << "\n";
  }

  // implemetin repl , infinte loop until user eneter exit or closes terminl
 void repl(){
   string user_command;
 while (user_command != "exit" ){
  cout << "$ " ;
  getline (cin,user_command);
  execute(user_command);
 }
 }
};

int main() {
  CommandHandler handler;
 handler.repl();
 

}
