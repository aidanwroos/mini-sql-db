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
    printf("----------------------------SQL Operations-------------------------------\n");
    printf("CREATE TABLE <table_name>                        - Create a new table\n");
    printf("DROP TABLE <table_name>                          - Remove a table from db\n");
    printf("SELECT * FROM table_name                         - List all rows in table\n");
    printf("INSERT INTO <table_name> VALUES val1, val2,...   - Add a new record\n");
    printf("--------------------------------------------------------------------------\n\n");

    printf("----------------------------Basic Operations-----------------------------\n");
    printf("list_tables                                      - List all tables in db");

    printf(".exit                                            - Exit program\n");
    printf(".help                                            - Show menu\n");
    printf("--------------------------------------------------------------------------\n\n");
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
    
    //what the user entered
    std::string full_entry;
    for(size_t i=0; i < tokens.size(); i++){
        full_entry.append(tokens[i]);
    }
    //command (partial for some)
    std::string command = tokens[0].c_str();

    
    if(tokens[0] == "CREATE" && tokens[1] == "TABLE"){
        if(tokens.size() != 3){
            printf("Usage: CREATE TABLE <table_name>\n");
            return -1;
        }
        std::string tableName = tokens[2];
        printf("Creating table: %s\n", tableName.c_str());
        //create table function call
        database.create_table(tableName);
    }
    else if (tokens[0] == "DROP" && tokens[1] == "TABLE"){
        if(tokens.size() != 3){
            printf("Usage: DROP TABLE <table_name>\n");
            return -1;
        }
        //remove table function call
        std::string table_name = tokens[2];
        database.remove_table(table_name);
    }
    else if (command == "list_tables"){
        if(tokens.size() != 1){
            printf("Usage: list_tables\n");
            return -1;
        }
        //list tables function call
        database.list_tables();
    }
    // INSERT INTO <table_name> VALUES val1, val2,...
    else if (tokens[0] == "INSERT" && tokens[1] == "INTO" && tokens[3] == "VALUES"){
        if(tokens.size() < 4){
            printf("INSERT INTO <table_name> VALUES val1, val2,...\n");
            return -1;
        }
        std::string tableName = tokens[1]; // <table_name>
        std::vector<std::string> args;     // row values (val1, val2,...)

        for(int i=4; i < tokens.size(); i++){
            args.push_back(tokens[i]);
        }

        printf("Inserting into %s\n", tableName.c_str());
        //insert function call
        //
        //database.insert(std::string table_name, std::vector<std::string> row_values) ?
    }
    

    else if(command == "quit" || command == "q"){
        printf("Goodbye!\n");
        clear_screen();
        exit(0);
    }
    else if(command == ".help" || command == "clear" || command == "cls"){
        clear_screen();
        print_menu();
    }
    
    else{
        printf("Unknown command: %s\n", full_entry.c_str());
    }


    return 0;
}