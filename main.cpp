#include <iostream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void menu(){
    printf("------------------------------------------------\n");
    printf("create_table <name>       - Create a new table\n");
    // printf("drop_table <name>         - Delete a table\n");
    printf("list_tables               - List all tables\n");
    printf("insert <table> <values>   - Insert a new record\n");
    printf(".exit                     - Exit program\n");
    printf(".help                     - Show this menu\n");
    
}


void clrScreen(){
    #ifdef _WIN32
        std::system("cls"); // windows
    #else
        std::system("clear");
    #endif
}

int process_input(const std::string& input){
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token){
        tokens.push_back(token);
    }

    std::string command = tokens[0].c_str();
    
    if(command == "create_table"){
        if(tokens.size() < 2){
            printf("Usage: create_table <name>\n");
            return -1;
        }
        std::string tableName = tokens[1];
        printf("Creating table: %s\n", tableName.c_str());
        //create table function call
        //
    }
    else if (command == "list_tables"){
        if(tokens.size() > 2){
            printf("Usage: list_tables\n");
            return -1;
        }
        //list tables function call
        //
    }
    else if (command == "insert"){
        if(tokens.size() < 3){
            printf("Usage: insert <table> <values...>\n");
            return -1;
        }
        std::string tableName = tokens[1];
        printf("Inserting into %s\n", tableName.c_str());
        //insert function call
        //
    }
    else if(command == "quit"){
        printf("Goodbye!\n");
        exit(0);
    }
    else if(command == ".help"){
        clrScreen();
        menu();
    }
    else{
        printf("Unknown command: %s\n", command.c_str());
    }

    



    return 0;
}

int main(){

    printf("MiniDB\n");
    
    std::string line;

    menu();

    while(line != "quit"){
        printf("> ");
        std::getline(std::cin, line); //read full line
        process_input(line);
    }

    return 0;
}