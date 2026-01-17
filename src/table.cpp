#include "table.h"



Table::Table(){}


//constructor (creates/initializes a new table)
Table::Table(std::string table_name, std::vector<std::string> cols){
    //set in memory information
    name = table_name;            //set table name
    path = "./database/" + name + ".tbl";  //set table path
    printf("Table with path '%s' created!\n", path.c_str());

    //1. update TableHeader struct
    init_table_header(cols.size());

    //2. update schema with column names
    for(size_t i=0; i < cols.size(); i++){ //set table column's names
        Column new_column;
        new_column.name = cols[i];
        schema.push_back(new_column);
    }
}

void Table::init_table_header(int numcols){
    tableheader.num_columns = numcols;
    tableheader.num_records = 0;
    tableheader.page_size = 4096;
    tableheader.free_space_start = 4096;
    tableheader.slot_dir_start = 4096;
}

void Table::table_info(std::string p, std::string n){ //path, name
    path = p;
    name = n;
}


Column Table::return_column(size_t col_index){
    return schema[col_index];
}

size_t Table::schema_size(){
    return schema.size();
}


void Table::write_header(std::ofstream& file){
    
    // file.write(reinterpret_cast<char*>(&tableheader), sizeof(tableheader));

   
    std::vector<char> buffer(4096, 0); //header buffer
    size_t offset = 0;

    //page size
    uint32_t page_size = 4096;
    memcpy(buffer.data() + offset, &page_size, sizeof(page_size));
    offset += sizeof(page_size);

    //num columns
    uint32_t num_columns = schema_size();
    memcpy(buffer.data() + offset, &num_columns, sizeof(num_columns));
    offset += sizeof(num_columns);

    //num records
    uint32_t num_records = 0;
    memcpy(buffer.data() + offset, &num_records, sizeof(num_records));
    offset += sizeof(num_records);

    


    //3. write column names
    for(const Column& col : schema){
        uint32_t name_len = col.name.size();
        file.write(reinterpret_cast<const char*>(&name_len), sizeof(name_len));
        file.write(col.name.data(), name_len);
    }

    //finally...write it all at once (table header info + column names etc.)
    file.write(buffer.data(), 4096);
}



void Table::load_from_disk(const std::filesystem::path& path){
    std::ifstream file(path, std::ios::binary);
    if(!file){
        throw std::runtime_error("Failed to open table file");
    }

    name = path.stem().string();

    //1. Load in the table header info from the file:
    file.read(reinterpret_cast<char*>(&tableheader), sizeof(tableheader));


    //2. Reading number of cols variable in the file
    uint32_t num_cols;
    file.read(reinterpret_cast<char*>(&num_cols), sizeof(num_cols));

    schema.clear();
    schema.reserve(num_cols);

    //3. Load the table's schema vector with the columns
    for(uint32_t i=0; i < num_cols; i++){
        Column col;

        uint32_t name_len;
        file.read(reinterpret_cast<char*>(&name_len), sizeof(name_len));

        col.name.resize(name_len);
        file.read(col.name.data(), name_len);
        
        schema.push_back(col);
    }
}

std::string Table::return_table_name(){
    return name;
}

//returns the table's path (a getter essentially)
std::string Table::return_path(){
    return path;
} 

std::vector<Column> Table::return_schema(){
    return schema;
}

TableHeader Table::return_tableheader(){
    return tableheader;
}