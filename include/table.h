#ifndef TABLE_H
#define TABLE_H

#include <cstring>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <stdint.h>
#include <filesystem>

enum DataType {

};

struct TableHeader {
    uint32_t page_size; //4096
    uint32_t num_columns; //whatever user makes it
    uint32_t num_records; //0
    uint32_t free_space_start; //initially headersize
    uint32_t slot_dir_start;   //initially headersize

};

struct Column {
    std::string name;
    //I dont have time to request different types lmao
    //eventually add types here...
    //INT, STRING, FLOAT, etc.
};



class Table {

    private:
        std::string path;
        std::string name;

        TableHeader tableheader;     //table metadata (start/end of data etc.)
        std::vector<Column> schema;  //column names (and eventually types)
        

    public:

        Table();

        //constructor - creating completely new table (users choice)
        Table(std::string table_name, std::vector<std::string> cols);

        void init_table_header(int); //tableheader setter

        void table_info(std::string path, std::string name);

        void write_header(std::ofstream& file); //write header to tbl file
        void load_from_disk(const std::filesystem::path& path); //load table and header from disk

        std::string return_table_name();
        std::string return_path(); //getter for table path

        Column return_column(size_t col_index);

        std::vector<Column> return_schema();

        size_t schema_size();
        
        TableHeader return_tableheader();
};









#endif