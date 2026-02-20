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
#include <cassert>

enum DataType {
    //nothing here yet...
};

struct TableHeader {
    uint32_t page_size;         //4096 (also tblheader size)
    uint32_t num_columns;       //schema decided by user
    uint32_t num_records;       //0 initially
    uint32_t num_pages;         //0 initially
};

struct Column {
    std::string name;
};


class Table {
    private:
        std::string path;
        std::string name;
        TableHeader tableheader;     
        std::vector<Column> schema;
    public:

        Table();
        Table(std::string table_name, std::vector<std::string> cols);

        void init_table_header(int);                             //tableheader setter
        void table_info(std::string path, std::string name);
        void write_header(std::ofstream& file);                  //write header to tbl file
        void load_from_disk(const std::filesystem::path& path);  //load table and header from disk
        std::string return_table_name();
        std::string return_path();                               //getter for table path
        Column return_column(size_t col_index);
        std::vector<Column> return_schema();
        size_t schema_size();
        TableHeader return_tableheader();
        void table_info_display();                               //display table header information
        void update_header(uint32_t space);                                    //update header after writing record
    };









#endif