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



struct Column {
    std::string name;
    //I dont have time to request different types lmao
};



class Table {

    private:
        std::string path;
        std::string name;
        std::vector<Column> schema;

    public:

        Table();

        //constructor - creating completely new table (users choice)
        Table(std::string table_name, std::vector<std::string> cols);

        
        void table_info(std::string path, std::string name);

        void write_header(std::ofstream& file); //write header to tbl file
        void load_from_disk(const std::filesystem::path& path); //load table from disk



        Column return_column(size_t col_index);

        size_t schema_size();

};


#endif