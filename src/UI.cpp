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
    printf("--------------------------- DB OPERATIONS ---------------------------------\n");
    printf("CREATE TABLE <table_name>                          - Create a new table\n");
    printf("REMOVE TABLE <table_name>                            - Remove a table from db\n");
    printf("list_tables                                        - List all tables in db\n");
    printf("---------------------------------------------------------------------------\n\n");

    printf("--------------------------- SQL-LIKE OPERATIONS ---------------------------\n");
    printf("SELECT * FROM <table_name>                         - List all rows in table\n");
    printf("SELECT <record_id> FROM <table_name>               - Find specific record\n");             
    printf("INSERT INTO <table_name> VALUES val1, val2,...     - Add a new record\n");        
    printf("DROP <record_id> FROM <table_name>                 - Delete record from table\n");
    printf("UPDATE <table_name> <record_id> <column> <value>   - Update record values");       
    printf("---------------------------------------------------------------------------\n\n");

    printf("--------------------------- OTHER -----------------------------------------\n");
    printf(".exit                                              - Exit program\n");
    printf(".help                                              - Show menu\n");
    printf("---------------------------------------------------------------------------\n\n");
}

//Clear the screen
void UI::clear_screen(){
    #ifdef _WIN32
        std::system("cls"); // windows
    #else
        std::system("clear");
    #endif
}

//Process the user input
int UI::process_input(const std::string& input){
    //Skip empty/white-space input
    if(input.find_first_not_of(" \t\r\n") == std::string::npos) return -1;
    
    //Tokenize input
    std::istringstream iss(input);
    std::vector<std::string> tokens;
    std::string token;
    while (iss >> token) tokens.push_back(token);
    if(tokens.empty()) return -1; //no tokens, return
    
     
    std::string command = tokens[0].c_str(); //command

    //CREATE TABLE
    if(command == "CREATE" && tokens[1] == "TABLE"){
        if(tokens.size() != 3){
            printf("Usage: CREATE TABLE <table_name>\n");
            return -1;
        }
        std::string tableName = tokens[2];
        printf("Creating table: %s\n", tableName.c_str());
        database.create_table(tableName);
    }

    //REMOVE (DROP) TABLE
    else if (tokens[0] == "REMOVE" && tokens[1] == "TABLE"){
        if(tokens.size() != 3){
            printf("Usage: DROP TABLE <table_name>\n");
            return -1;
        }
        printf("Dropping table: %s\n", tokens[2].c_str());
        database.remove_table(tokens[2]);
    }

    //LIST TABLES
    else if (command == "list_tables"){
        if(tokens.size() != 1){
            printf("Usage: list_tables\n");
            return -1;
        }
        database.list_tables();
    }

    //SELECT (ALL) ROWS
    else if(command == "SELECT" && tokens[1] == "*" && tokens[2] == "FROM"){
        if(tokens.size() < 4){
            printf("Usage: SELECT * FROM <table_name>\n");
            return -1;
        }
        database.display_all_records(database.select_rows(tokens[3]));
    }

    //FIND A RECORD
    else if(command == "SELECT" && tokens[2] == "FROM"){
        if(tokens.size() != 4){
            printf("Usage: SELECT <record_id> FROM <table_name>\n");
            return -1;
        }
        database.display_record(database.find_record(std::stoi(tokens[1]), tokens[3]));
    }

    //INSERT RECORD
    else if(tokens[0] == "INSERT" && tokens[1] == "INTO" && tokens[3] == "VALUES"){
        if(tokens.size() < 5){
            printf("Usage: INSERT INTO <table_name> VALUES val1, val2,...\n");
            return -1;
        }
        std::string tableName = tokens[2]; //table_name
        std::vector<std::string> rowValues(tokens.begin() + 4, tokens.end()); //row values
        
        if(!database.insert_record(tableName, rowValues)){
            printf("Error: 'Failed to INSERT record\n");
            return -1;
        }
        printf("Inserting into %s\n", tableName.c_str());
    }

    //DELETE RECORD
    else if(command == "DROP" && tokens[2] == "FROM"){
        if(tokens.size() != 4){
            printf("Usage: DROP <record_id> FROM <table_name>\n");
            return -1;
        }
        if(!database.drop_record(tokens[3], std::stoi(tokens[1]))){
            printf("Error: 'Failed to DROP record (ID: %d)'\n", std::stoi(tokens[1]));
            return -1;
        }
    }
    
    //UPDATE RECORD
    else if(command == "UPDATE"){
        if(tokens.size() < 6){
            printf("Usage: UPDATE <table_name> <record_id> <column> <value>\n");
            return -1;
        }
        if(!database.update_record(tokens[1], std::stoi(tokens[2]), tokens[3], tokens[4])){
            printf("Error: 'Failed to UPDATE record (ID: %d)'\n", std::stoi(tokens[2]));
            return -1;
        }
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
        printf("Unknown command: %s\n", input.c_str());
    }


    return 0;
}