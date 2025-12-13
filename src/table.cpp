#include "table.h"




Table::Table(){}


//constructor (creating new table)
Table::Table(std::string table_name, std::vector<std::string> cols){
    //set in memory information
    name = table_name;            //set table name
    path = "./database/" + name;  //set table path
    printf("Table with path '%s' created!\n", path.c_str());

    for(size_t i=0; i < cols.size(); i++){ //set table column's names
        Column new_column;
        new_column.name = cols[i];
        schema.push_back(new_column);
    }

    //write schema to header
}

void Table::table_info(std::string path, std::string name){
    path = path;
    name = name;
}


Column Table::return_column(size_t col_index){
    return schema[col_index];
}

size_t Table::schema_size(){
    return schema.size();
}


void Table::write_header(std::ofstream& file){
    uint32_t num_cols = schema_size();
    file.write(reinterpret_cast<const char*>(&num_cols), sizeof(num_cols));

    //write column names
    for(const Column& col : schema){
        uint32_t name_len = col.name.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(col.name.data(), name_len);
    }
}

void Table::load_from_disk(const std::filesystem::path& path){
    std::ifstream file(path, std::ios::binary);
    if(!file){
        throw std::runtime_error("Failed to open table file");
    }

    name = path.stem().string();

    uint32_t num_cols;
    file.read(reinterpret_cast<char*>(&num_cols), sizeof(num_cols));

    schema.clear();
    schema.reserve(num_cols);

    for(uint32_t i=0; i < num_cols; i++){
        Column col;

        uint32_t name_len;
        file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));

        col.name.resize(name_len);
        file.read(col.name.data(), name_len);
        
        schema.push_back(col);
    }
}