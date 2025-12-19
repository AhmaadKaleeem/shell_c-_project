#include <iostream>
#include <string>
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
    
  };
 }
 bool is_valid(const string command){
  if (valid_commands.count(command) > 0) return true; // count return 1 if key exist 
  else return false;
 }

 void execute(const string command){
  if (!is_valid(command) ){
    cout << command << ": command not found\n";
  }
  else {
     cout << "[Success] Executing Command: '"<< command <<"' \n";
  }

 }
 
 void repl(){
 while (true){
   string user_command;
  
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
