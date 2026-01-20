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

    //free space start
    uint32_t fst = tableheader.free_space_start;
    memcpy(buffer.data() + offset, &fst, sizeof(fst));
    offset += sizeof(fst);

    //slot dir start
    uint32_t sdt = tableheader.slot_dir_start;
    memcpy(buffer.data() + offset, &sdt, sizeof(sdt));
    offset += sizeof(sdt);

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

    //free space start
    memcpy(&tableheader.free_space_start, buffer.data() + offset, sizeof(uint32_t));
    offset += sizeof(uint32_t);

    //slot dir start
    memcpy(&tableheader.slot_dir_start, buffer.data() + offset, sizeof(uint32_t));
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

void Table::table_info_display(){
    printf("\nTable Information\n");
    printf("-----------------------\n");
    printf("Name: %s\n", name.c_str());
    printf("Path: %s\n", path.c_str());
    printf("Num columns: %d\n", tableheader.num_columns);
    printf("Num records: %d\n", tableheader.num_records);
    printf("Columns: ");
    for(const auto& x : schema){
        printf("%s ", x.name.c_str());
    }
    printf("\nFSS: %d\n", tableheader.free_space_start);
    printf("SDS: %d\n", tableheader.slot_dir_start);
    printf("-----------------------\n");
    printf("\n");
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