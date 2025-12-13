#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <vector>
#include <variant>
#include <filesystem>
#include "StorageManager.h"
#include "record.h"
#include "table.h"

using AnyType = std::variant<int, double, std::string>;


class Database {
    private:
        std::string db_path; // e.g., "./database/"
        
        std::unordered_map<std::string, Table> tables; // <table_name, path>

    public:
        Database(); //default constructor
        
        ~Database(); //Deconstructor

        //LOAD EXISTING TABLES
        void load_tables_from_disk();
        

        //DB OPERATIONS
        void create_table(const std::string& name, std::vector<string> column_names);
        void remove_table(const std::string& table_name); //(drop)
        void list_tables() const;

        //SQL-LIKE OPERATIONS
        std::vector<Record> select_rows(std::string table_name);   //list all rows in table
        Record find_record(int record_id, std::string table_name); //find specific record
        bool insert_record(std::string table_name, std::vector<std::string>& values);
        bool drop_record(std::string table_name, int record_id);
        bool update_record(std::string table_name, int record_id, std::string column, std::string value);
        
        //DISPLAY DATA ---------------------------------------
        void display_all_records(std::vector<Record> records);
        void display_record(Record record);
        //----------------------------------------------------
};


#endif