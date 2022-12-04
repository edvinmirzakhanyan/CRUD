/** Commands examples 
 * create user
 * update users set taskname=New_task where age==24
 * select users where name==John
 * delete users where name==Max
 **/
#include <iostream>

#include "functions.h"

int main () {
    std::string op;
    std::getline(std::cin, op);
    std::map<std::string, void (*) (const std::string&)> fcall;
    std::string fname = "";
    for (int i = 0; i < op.size(); ++i) {
        if (op[i] != ' ') { fname += op[i]; }
        else if(op[i] == ' ' && fname.length()) { break; }
    };
    
    fcall["create"] = &create;
    fcall["select"] =   &read;
    fcall["update"] = &update;
    fcall["delete"] = &_delete;
    if(!fcall.contains(fname)) { std::cout << "Command " << fname << " not found!" << std::endl; return 0; }
    fcall[fname](op);
}