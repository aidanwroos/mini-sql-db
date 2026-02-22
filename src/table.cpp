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
    tableheader.page_size = 4096;
    tableheader.num_columns = numcols;
    tableheader.num_records = 0;
    tableheader.num_pages = 0;
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

//write the tableheader
void Table::write_header(std::ofstream& file){
    std::vector<char> buffer(4096, 0); //header buffer, padding with 0's
    size_t offset = 0;

    //page size
    uint32_t pg_size = tableheader.page_size;
    memcpy(buffer.data() + offset, &pg_size, sizeof(pg_size));
    offset += sizeof(pg_size);

    //num columns
    uint32_t num_columns = tableheader.num_columns;
    memcpy(buffer.data() + offset, &num_columns, sizeof(num_columns));
    offset += sizeof(num_columns);

    //num records
    uint32_t num_records = tableheader.num_records;
    memcpy(buffer.data() + offset, &num_records, sizeof(num_records));
    offset += sizeof(num_records);

    //num pages
    uint32_t num_pages = tableheader.num_pages;
    memcpy(buffer.data() + offset, &num_pages, sizeof(num_pages));
    offset += sizeof(num_pages);

    //3. write column names
    for(const auto& col : schema){
        uint32_t name_len = col.name.size();
        memcpy(buffer.data() + offset, &name_len, sizeof(name_len));
        offset += sizeof(name_len);

        memcpy(buffer.data() + offset, col.name.data(), name_len);
        offset += name_len;
    }

    //finally...write it all at once (table header info + column names etc.)
    file.write(buffer.data(), 4096);
}


//load the table from disk
void Table::load_from_disk(const std::filesystem::path& path){
    std::ifstream file(path, std::ios::binary);
    std::vector<char> buffer(4096);
    file.read(buffer.data(), 4096);

    size_t offset = 0;

    //page size
    memcpy(&tableheader.page_size, buffer.data() + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    //num columns
    memcpy(&tableheader.num_columns, buffer.data() + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    //num records
    memcpy(&tableheader.num_records, buffer.data() + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    //num pages
    memcpy(&tableheader.num_pages, buffer.data() + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    schema.clear();
    schema.reserve(tableheader.num_columns);

    for(uint32_t i=0; i<tableheader.num_columns; ++i){
        uint32_t name_len;
        memcpy(&name_len, buffer.data() + offset, sizeof(name_len));
        offset += sizeof(name_len);

        std::string colname(buffer.data() + offset, name_len);
        offset += name_len;

        schema.push_back(Column{colname});
    }

}

uint32_t Table::return_num_pages(){
    return tableheader.num_pages;
}








void Table::table_info_display(){
    printf("\nTable Information\n");
    printf("-----------------------\n");
    printf("Name: %s\n", name.c_str());
    printf("Path: %s\n", path.c_str());
    printf("Num columns: %d\n", tableheader.num_columns);
    printf("Num records: %d\n", tableheader.num_records);
    printf("Num pages: %d\n", tableheader.num_pages);
    printf("Columns: ");
    for(const auto& x : schema){
        printf("%s ", x.name.c_str());
    }
    printf("\n-----------------------\n");
    printf("\n");
}

void Table::update_header(uint32_t space){
    tableheader.num_records++;
    

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