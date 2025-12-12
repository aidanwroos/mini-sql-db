#include "database.h"
#include "record.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

Database::Database() : db_path("./database/"){
    //Create ./database/ directory if not already created
    if(!fs::exists(db_path)) {
        fs::create_directory(db_path);
    }

}

Database::~Database(){} //deconstructor (not needed atm)


void Database::create_table(const std::string& name){
    //locate table (if exists already)
    fs::path tblPath = fs::path(db_path) / (name + ".tbl");
    if(fs::exists(tblPath)){
        printf("Table already exists.\n");
        return;
    }
    
    //create the file path (on disk)
    std::string table_path = db_path + "/" + name + ".tbl";
    std::ofstream file(table_path);
    if(!file){
        std::cout << "Failed to create table file.\n";
        return;
    }

    //update unorderedmap list of tables
    tables[name] = table_path;

    printf("Table '%s' created with path: %s\n", name.c_str(), db_path.c_str());
}

void Database::remove_table(const std::string& table_name){
    fs::path table_path = fs::path(db_path) / (table_name + ".tbl");
    if(fs::exists(table_path)){
        fs::remove_all(table_path);
        printf("Table '%s' removed from location %s\n", table_name.c_str(), table_path.c_str());
        return;
    }
    printf("Table '%s' not found.\n", table_name.c_str());
}


void Database::list_tables() const {
    bool has_tables = false;
    for(const auto& entry : fs::directory_iterator(db_path)){
        if(entry.is_regular_file()){
            has_tables = true;
            break;
        }
    }
    if(!has_tables){//no tables were found
        printf("No tables were found.\n");
        return;
    }

    printf("TABLES\n");
    printf("------\n");
    int i=0;
    for(const auto& entry : fs::directory_iterator(db_path)){
        if(entry.is_regular_file()){
            auto path = entry.path();
            auto name = path.stem().string();
            auto size = fs::file_size(path);

            printf("%d. %s, SIZE: %ld bytes\n", i++, name.c_str(), size);
        }
    }
}

//display all records in a table, given the table's name
void Database::display_all_records(std::vector<Record> records){
    for(const auto& rec : records) {
        const auto& values = rec.getValues();

        printf("VALUES= [ ");

        for(const auto& v : values){
            std::visit([](auto&& val){
                std::cout << val << " | ";
            }, v);
        }

        printf("\n");
    }
}

// Hold onto for a bit...
// void Database::display_all_records(std::vector<Record> records){
//     for(size_t i=0; i < records.size(); i++){
//         std::vector<FieldValue> values = records[i].getValues(); //record's values
//         for(size_t k=0; k<values.size(); k++){
//             values[]
//         }
//     }
// }