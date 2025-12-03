#include "UI.h"
#include <iostream>
#include <sstream>
#include <vector>
//UI.h implementations

//Constructor
UI::UI(Database& db) : database(db) {}

void UI::run(){
    printf("MiniDB\n");
    std::string line;

    print_menu();

    while(line != "quit"){
        printf("> ");
        std::getline(std::cin, line); //read full line
        process_input(line);

    }
        
}


//Print db menu
void UI::print_menu(){
    printf("------------------------------------------------\n");
    printf("create_table <name>       - Create a new table\n");
    printf("list_tables               - List all tables\n");
    printf("insert <table> <values>   - Insert a new record\n");
    printf(".exit                     - Exit program\n");
    printf(".help                     - Show this menu\n");
    printf("------------------------------------------------\n\n");
}

//Clear the screen
void UI::clear_screen(){
    #ifdef _WIN32
        std::system("cls"); // windows
    #else
        std::system("clear");
    #endif
}

//Process the input
int UI::process_input(const std::string& input){
    if(input.find_first_not_of(" \t\r\n") == std::string::npos){
        return -1;
    }
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token){
        tokens.push_back(token);
    }

    if(tokens.empty()){
        return -1;
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
        clear_screen();
        exit(0);
    }
    else if(command == ".help" || command == "clear" || command == "cls"){
        clear_screen();
        print_menu();
    }
    
    else{
        printf("Unknown command: %s\n", command.c_str());
    }

    



    return 0;
}