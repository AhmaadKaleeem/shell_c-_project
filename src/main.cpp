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
    cout << "[Error] Unknown Command: '"<< command <<"' \n";
  }
  else {
     cout << "[Success] Executing Command: '"<< command <<"' \n";
  }

 }
};
int main() {
  CommandHandler handler;
  string user_command;
  cout << unitbuf;
  cerr << unitbuf;
  cout << "$ " ;
  getline (cin,user_command);
  handler.execute(user_command);

}
