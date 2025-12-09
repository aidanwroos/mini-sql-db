#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <vector>
#include <filesystem>
#include "table.h"

//     printf("------------------------------------------------\n");
//     printf("create_table <name>       - Create a new table\n");
//     printf("list_tables               - List all tables\n");
//     printf("insert <table> <values>   - Insert a new record\n");
//     printf(".exit                     - Exit program\n");
//     printf(".help                     - Show this menu\n");
//     printf("------------------------------------------------\n\n");



class Database {
    private:
        std::string db_path; // e.g., "./database/"
        
        std::unordered_map<std::string, std::string> tables; // <table_name, path>

    public:
        Database(); //default constructor
        
        ~Database(); //Deconstructor

        //create a table
        void create_table(const std::string& name);

        //insert <table> <values>
        void insert(const std::string& table_name, const std::vector<std::string>& values);

        //remove <table>
        void remove_table(const std::string& table_name);

        //list table names
        void list_tables() const;

        

};


#endif