#include <fstream>
#include <vector>
#include <map>

struct User {
    std::string name;
    std::string surname;
    std::string age;
    std::string taskName;
};

bool correctName(std::string& name, bool check, bool change) {
    const int dataSize = 15;
    int inputSize = name.size();

    if (check && (inputSize > dataSize || inputSize < 3)) {
        std::cout << "Name can contain from 3 to 15 letters!" << std::endl;
        return false;
    }
    for (int i = 0; i < inputSize && check; ++i) {
        if ((name[i] < 'a' || name[i] > 'z') && (name[i] < 'A' || name[i] > 'Z')) {
            std::cout << "Name can contain only letters!" << std::endl;
            return false;
        }
    }
    if (inputSize < dataSize && change) { name.append(dataSize - inputSize, ' '); }
    return true;
}

bool correctSurname(std::string& surname,bool check, bool change) {
    const int dataSize = 20;
    int inputSize = surname.size();
        
    if (check && (inputSize > dataSize || inputSize < 3)) { std::cout << "Surname can contain from 3 to 20 letters!" << std::endl; return false; }
    for (int i = 0; i < inputSize && check; ++i) {
        if ((surname[i] < 'a' || surname[i] > 'z') && (surname[i] < 'A' && surname[i] > 'Z')) {
            std::cout << "Surname can contain only letters!" << std::endl;
            return false;
        }
    }
    if (inputSize < dataSize && change) { surname.append(dataSize - inputSize, ' '); }
    return true; 
}

bool correctAge (const std::string& age) {
    int inputSize = age.size(); 
    for (int i = 0; i < inputSize; ++i) {
        if (age[i] < '0' || age[i] > '9') { std::cout << "Age can contain only numbers!" << std::endl; return false; }
    }
    if (age < "18" || age > "63") {
        std::cout << "User's age must be from 18 to 63!" << std::endl;
        return false;
    }
    return true;
}

bool correctTaskName(std::string& taskName, bool check, bool change){
    const int dataSize = 30;
    int inputSize = taskName.size();
    if (check && (inputSize > taskName.size())) {
        std::cout << "Task name can contain maximum 30 symbols!" << std::endl;
        return false;
    }
    if (inputSize < dataSize && change) { taskName.append(dataSize - inputSize, ' '); }
    return true;
}

std::vector<std::string> split(const std::string& str) {
    int size = str.length();
    int equalCount  = 0;
    std::vector<std::string> vec;
    std::string word;
    for (int i = 0; i < size; ++i) {
        if (str[i] == '=' && str[i + 1] != '=') {
            word += str[i];
            if (word[0] == '=') { vec[vec.size() - 1] += word; word = ""; continue;}
        vec.push_back(word),
        word = ""; continue; }
        if (str[i] != ' ') { word += str[i]; continue; }
        if (word.length()) { vec.push_back(word); word = "";}
    }
    if (word.length()) { vec.push_back(word); }
    return vec;
}

void create(const std::string& str) {
    User obj;
    std::vector<std::string> vec = split(str);
    
    if (vec.size() < 2) { std::cout << "Wrong command!" << std::endl; return; }
    if (vec[1] != "user") { std::cout << "Command " << vec[1] << " not found!" << std::endl; return; }
    if (vec.size() > 2) { std::cout << "Command " << vec[2] << " not found!" << std::endl; return; }
    do {
        std::cout << "Name: ";
        std::getline(std::cin >> std::ws, obj.name);
    } while (!correctName(obj.name, true, true));
    do {
        std::cout << "Surname: ";
        std::getline(std::cin >> std::ws, obj.surname);
    } while (!correctSurname(obj.surname, true, true));
    do {
        std::cout << "Age: ";
        std::getline(std::cin >> std::ws, obj.age);
    } while (!correctAge(obj.age));
    do {
        std::cout << "Task name: ";
        std::getline(std::cin >> std::ws, obj.taskName);
    } while (!correctTaskName(obj.taskName, true, true));

    std::ifstream fin;
    fin.open("user.data");
    std::ofstream fout;
    std::string tmp;
    fin >> tmp;
    fin.close();
    if (tmp.size() != 0) { fout.open("user.data", std::ios::app); }
    else { fout.open("updatedUser.data", std::ios::app); }
    tmp = obj.name + ' ' + obj.surname + ' ' + obj.age + ' ' + obj.taskName + '\n';
    fout << tmp;
    fout.close();
}

void read(const std::string& str) {
    std::vector<std::string> vec = split(str);
    
    if (vec.size() < 5) { std::cout << "Wrong command!" << std::endl; return; }
    if (vec[1] != "users") { std::cout << "Command " << vec[1] << " not found!" << std::endl; return; }
    if (vec[2] != "where") { std::cout << "Command " << vec[2] << " not found!" << std::endl; return; }
    if (vec.size() > 5) { std::cout << "Command" << vec[5] << " not found!"; return; }

    bool found = false;
    std::ifstream fin;
    std::string tmp;
    fin.open("user.data");
    fin >> tmp;
    fin.close();

    if (tmp.size() == 0) { fin.open("updatedUser.data", std::ios::app); }
    else { fin.open("user.data", std::ios::app); }

        if (vec[3] == "name==") {
        int size = vec[4].length();
        if (!correctName(vec[4], true, false)) { fin.close(); return; }
        const int nameIndex = 0;

        while (!fin.eof()) {
            getline(fin, tmp);
            if(!tmp.length()) { break; }
            if (tmp.substr(nameIndex, size) == vec[4]) {
                found = true;
                std::cout << tmp << std::endl;
            }
        }
    }
    else if (vec[3] == "surname==") {
        int size = vec[4].length();
        if (!correctSurname(vec[4], true, false)) { fin.close(); return; }
        const int surnameIndex = 16;

        while (!fin.eof()) {
            getline(fin, tmp);      
            if(!tmp.length()) { break; }
            if (tmp.substr(surnameIndex, size) == vec[4]) {
                found = true;
                std::cout << tmp << std::endl; 
            }
        }
    }
    else if (vec[3] == "age==") {
        int size = vec[4].length();
        if (!correctAge(vec[4])) { fin.close(); return; }
        const int ageIndex = 37;

        while (!fin.eof()) {
            getline(fin, tmp);      
            if(!tmp.length()) { break; }
            if (tmp.substr(ageIndex, size) == vec[4]) {
                found = true;
                std::cout << tmp << std::endl;
            }
        }
    }
    else if (vec[3] == "taskname==") {
        int size = vec[4].length();
        if (!correctTaskName(vec[4],true, false)) { fin.close(); return; }
        const int taskIndex = 40;

        while (!fin.eof()) {
            getline(fin, tmp);      
            if(!tmp.length()) { break; }
            if (tmp.substr(taskIndex, size) == vec[4]) {
                found = true;
                std::cout << tmp << std::endl;
            }
        }

    }
    else {
        std::cout << "Command " << vec[3] << " not found!" << std::endl;
        fin.close(); return;
    }
    if (!found) { std::cout << "Users not found!" << std::endl; }

    fin.close();
}

void update(const std::string& str) {
    std::vector<std::string> vec = split(str);
    
    if (vec.size() < 8) { std::cout << "Wrong command!" << std::endl; return;
    if (vec[1] != "users") { std::cout << "Command " << vec[1] << " not found!" << std::endl; return; }
    if (vec[2] != "set")   { std::cout << "Command " << vec[2] << " not found!" << std::endl; return; }
    if (vec[5] != "where") { std::cout << "Command " << vec[5] << " not found!" << std::endl; return; }
    if (vec.size() > 8)    { std::cout << "Command " << vec[8] << " not found!" << std::endl; return; }
    if (vec[3] == "name=") { if (!correctName(vec[4], true, false)) {return; } }
    else if (vec[3] == "surname=") { if (!correctSurname(vec[4],true, false)) { return; } }
    else if (vec[3] == "age=") { if (!correctAge(vec[4]))  { return; } }
    else if (vec[3] == "taskname=") { if (!correctTaskName(vec[4], true, false)) { return; } }
    else { std::cout << "Command " << vec[3] << " not found!" << std::endl; return; }

    bool found = false;
    std::ifstream fin;
    fin.open("user.data");
    std::ofstream fout;
    std::string file_delete;
    std::string tmp;
    fin >> tmp;
    fin.close();
    if (tmp.size() == 0) {
        fin.open("updatedUser.data");
        fout.open("user.data", std::ios::app);
        file_delete = "updatedUser.data";
    }
    else {
        fin.open("user.data");
         fout.open("updatedUser.data");
         file_delete = "user.data"; 
    }

    if (vec[6] == "name==") {
        int size = vec[7].length();
        if (!correctName(vec[7], true, false)) { return; }
        const int nameIndex = 0;

        while (!fin.eof()) {
            getline(fin, tmp);
            if(!tmp.length()) { break; }
            if (tmp.substr(nameIndex, size) == vec[7]) {
                found = true;
                std::vector<std::string> vtmp;
                vtmp = split(tmp);
                if (vec[3] == "name=")          { vtmp[0] = vec[4]; }
                else if (vec[3] == "surname=")  { vtmp[1] = vec[4]; }
                else if (vec[3] == "age=")      { vtmp[2] = vec[4]; }
                else if (vec[3] == "taskname=") { vtmp[3] = vec[4]; }
                correctName(vtmp[0], false, true);
                correctSurname(vtmp[1], false, true);
                correctTaskName(vtmp[3], false, true);
                fout << vtmp[0] + ' ' + vtmp[1] + ' ' + vtmp[2] + ' ' + vtmp[3] + '\n';
                continue; 
            }
            fout << tmp + '\n';
        }
    }
    else if (vec[6] == "surname==") {
        int size = vec[7].length();
        if (!correctSurname(vec[7], true, false)) { return; }
        const int surnameIndex = 16;

        while (!fin.eof()) {
            getline(fin, tmp);      
            if(!tmp.length()) { break; }
            if (tmp.substr(surnameIndex, size) == vec[7]) {
                found = true;
                std::vector<std::string> vtmp;
                vtmp = split(tmp);
                if (vec[3] == "name=")          { vtmp[0] = vec[4]; }
                else if (vec[3] == "surname=")  { vtmp[1] = vec[4]; }
                else if (vec[3] == "age=")      { vtmp[2] = vec[4]; }
                else if (vec[3] == "taskname=") { vtmp[3] = vec[4]; }
                correctName(vtmp[0], false, true);
                correctSurname(vtmp[1], false, true);
                correctTaskName(vtmp[3], false, true);
                fout << vtmp[0] + ' ' + vtmp[1] + ' ' + vtmp[2] + ' ' + vtmp[3] + '\n';
                continue; 
            }
            fout << tmp + '\n';
        }
    }
    else if (vec[6] == "age==") {
        int size = vec[7].length();
        if (!correctAge(vec[7])) { return; }
        const int ageIndex = 37;

        while (!fin.eof()) {
            getline(fin, tmp);      
            if(!tmp.length()) { break; }
            if (tmp.substr(ageIndex, size) == vec[7]) {
                found = true;
                std::vector<std::string> vtmp;
                vtmp = split(tmp);
                if (vec[3] == "name=")          { vtmp[0] = vec[4]; }
                else if (vec[3] == "surname=")  { vtmp[1] = vec[4]; }
                else if (vec[3] == "age=")      { vtmp[2] = vec[4]; }
                else if (vec[3] == "taskname=") { vtmp[3] = vec[4]; }
                correctName(vtmp[0], false, true);
                correctSurname(vtmp[1], false, true);
                correctTaskName(vtmp[3], false, true);
                fout << vtmp[0] + ' ' + vtmp[1] + ' ' + vtmp[2] + ' ' + vtmp[3] + '\n';
                continue; 
            }
            fout << tmp + '\n';
        }
    }
    else if (vec[6] == "taskname==") {
        int size = vec[7].length();
        if (!correctTaskName(vec[7],true, false)) { return; }
        const int taskIndex = 40;

        while (!fin.eof()) {
            getline(fin, tmp);      
            if(!tmp.length()) { break; }
            if (tmp.substr(taskIndex, size) == vec[7]) {
                found = true;
                std::vector<std::string> vtmp;
                vtmp = split(tmp);
                if (vec[3] == "name=")          { vtmp[0] = vec[4]; }
                else if (vec[3] == "surname=")  { vtmp[1] = vec[4]; }
                else if (vec[3] == "age=")      { vtmp[2] = vec[4]; }
                else if (vec[3] == "taskname=") { vtmp[3] = vec[4]; }
                correctName(vtmp[0], false, true);
                correctSurname(vtmp[1], false, true);
                correctTaskName(vtmp[3], false, true);
                fout << vtmp[0] + ' ' + vtmp[1] + ' ' + vtmp[2] + ' ' + vtmp[3] + '\n';
                continue; 
            }
            fout << tmp + '\n';
        }

    }
    else {
        std::cout << "Command " << vec[3] << " not found!" << std::endl;
        fin.close(); fout.close(); return;
    }
    if (!found) { std::cout << "Users not found!" << std::endl; }
    fout.close();   
    fout.open(file_delete);
    fout << "";
    fout.close();
    fin.close();
}

void _delete(const std::string& str) {
    std::vector<std::string> vec = split(str);
    
    if (vec.size() < 5) { std::cout << "Wrong command!" << std::endl; return; }
    if (vec[1] != "users") { std::cout << "Command " << vec[1] << " not found!" << std::endl; return; }
    if (vec[2] != "where")   { std::cout << "Command " << vec[2] << " not found!" << std::endl; return; }
    if (vec.size() > 5) { std::cout << "Command " << vec[5] << " not found!" << std::endl; return; }

    bool found = false;
    std::ifstream fin;
    fin.open("user.data");
    std::ofstream fout;
    std::string file_delete;
    std::string tmp;
    fin >> tmp;
    fin.close();
    if (tmp.size() == 0) {
        fin.open("updatedUser.data");
        fout.open("user.data", std::ios::app);
        file_delete = "updatedUser.data";
    }
    else {
        fin.open("user.data");
         fout.open("updatedUser.data");
         file_delete = "user.data"; 
    }

    if (vec[3] == "name==") {
        int size = vec[4].length();
        if (!correctName(vec[4], true, false)) { fin.close(); fout.close(); return; }
        const int nameIndex = 0;

        while (!fin.eof()) {
            getline(fin, tmp);
            if(!tmp.length()) { break; }
            if (tmp.substr(nameIndex, size) == vec[4]) {
                found = true;
                continue; 
            }
            fout << tmp + '\n';
        }
    }
    else if (vec[3] == "surname==") {
        int size = vec[4].length();
        if (!correctSurname(vec[4], true, false)) { fin.close(); fout.close(); return; }
        const int surnameIndex = 16;

        while (!fin.eof()) {
            getline(fin, tmp);      
            if(!tmp.length()) { break; }
            if (tmp.substr(surnameIndex, size) == vec[4]) {
                found = true;
                continue; 
            }
            fout << tmp + '\n';
        }
    }
    else if (vec[3] == "age==") {
        int size = vec[4].length();
        if (!correctAge(vec[4])) { fin.close(); fout.close();return; }
        const int ageIndex = 37;

        while (!fin.eof()) {
            getline(fin, tmp);      
            if(!tmp.length()) { break; }
            if (tmp.substr(ageIndex, size) == vec[4]) {
                found = true;
                continue; 
            }
            fout << tmp + '\n';
        }
    }
    else if (vec[3] == "taskname==") {
        int size = vec[4].length();
        if (!correctTaskName(vec[4],true, false)) { fin.close(); fout.close(); return; }
        const int taskIndex = 40;

        while (!fin.eof()) {
            getline(fin, tmp);      
            if(!tmp.length()) { break; }
            if (tmp.substr(taskIndex, size) == vec[4]) {
                found = true;
                continue; 
            }
            fout << tmp + '\n';
        }

    }
    else {
        std::cout << "Command " << vec[3] << " not found!" << std::endl;
        fin.close(); fout.close(); return;
    }
    if (!found) { std::cout << "Users not found!" << std::endl; }
    fout.close();   
    fout.open(file_delete);
    fout << "";
    fout.close();
    fin.close();
}
