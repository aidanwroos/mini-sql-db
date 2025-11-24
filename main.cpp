#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void menu(){
    printf("create_table <name>       - Create a new table\n");
    printf("drop_table <name>         - Delete a table\n");
    printf("list_tables               - List all tables\n");
    printf("insert <table> <values>   - Insert a new record\n");
    printf("clear                     - Clear screen\n");
    printf("quit                      - Exit program\n\n");

    printf("> ");
}


void clrScreen(){
    #ifdef _WIN32
        std::system("cls"); // windows
    #else
        std::system("clear");
    #endif
}

int process_input(const std::string& input){
    printf("string entered: %s\n", input.c_str());
    
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token){
        tokens.push_back(token);
    }

    printf("Your tokens are...\n");
    for(int i=0; i<static_cast<int>(tokens.size()); i++){
        printf("Token %d. %s\n", i, tokens[i].c_str());
    }



    return 0;
}

int main(){

    printf("MiniDB\n");
    printf("'.help' for more function info\n");
    printf("'.exit' to quit\n\n");
    
    std::string line;

    menu();

    std::getline(std::cin, line); //read full line
    process_input(line);


    return 0;
}