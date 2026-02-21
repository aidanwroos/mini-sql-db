#include "database.h"
#include "record.h"
#include "table.h"

#include <filesystem>
#include <iostream>
#include <iomanip>

namespace fs = std::filesystem;

Database::Database() : db_path("./database/"){
    //Create ./database/ directory if not already created
    if(!fs::exists(db_path)) {
        fs::create_directory(db_path);
    }

    //Check directory for tables, so map of tables can be updated
    //(loading existing tables)
    load_tables_from_disk();

}

Database::~Database(){} //Deconstructor

void Database::create_table(const std::string& name, std::vector<string> column_names){
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

    //1. update in memory table information
    Table t(name, column_names);
    tables[name] = t; //update unorderedmap list of tables

    //2. write table header and schema (column names) to the table file
    t.write_header(file);
    
    printf("Table '%s' created with path: %s\n", name.c_str(), db_path.c_str());
}

void Database::remove_table(const std::string& table_name){
    fs::path table_path = fs::path(db_path) / (table_name + ".tbl");
    if(fs::exists(table_path)){
        fs::remove_all(table_path); //erase from directory
        tables.erase(table_name); //erase from map
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
            std::string name = path.stem().string();
            auto size = fs::file_size(path);
            

            //the specific table we're looking for (using map lookup)
            Table t = tables.at(name);

            auto it = tables.find(name);
            if(it != tables.end()){
                t = it->second;
            }else{
                printf("Table does not exist\n");
            }
            
            printf("%d. %s, SIZE: %ld bytes, COLS: ", i++, name.c_str(), size);

            for(size_t c=0; c < t.schema_size(); c++){
                Column col;
                col = t.return_column(c);
                printf("%s ", (col.name).c_str());
            }

            printf("\n");
        }
    }
}

//search for table, return true false
bool Database::locate_table(std::string table_name){
    
    return tables.find(table_name) != tables.end();
}


//return table object instance
Table Database::return_table(std::string table_name){
    Table t = tables.at(table_name);
    return t;
}

std::vector<Record> Database::select_rows(std::string table_name){
    std::vector<Record> temp;
    return temp;
}

Record Database::find_record(int record_id, std::string table_name){
    Record temp;
    return temp;
}

bool Database::insert_record(Table table, std::vector<std::string>& values){

    //----------------------------------------------------------------------------------------
    //check the table exists                                                            (done)
    //check the number of vals entered                                                  (done)
    //serialize record into contiguous byte buffer                                      (done)
    //Ask the storagemanager for the page the record should go                          (....)
    //Insert the record into the page object                                            (....)
       //-update the objects data buffer, free_space_start, slot_directory, num_slots)
    //Write the page back to disk                                                       (....)
    //Update the table metadata                                                         (....)
    //---------------------------------------------------------------------------------------


    //check if table exists in directory
    std::string table_name = table.return_table_name();
    if(!locate_table(table_name)){
        printf("Database::insert_record(): (error) Table, '%s' not found\n", table_name.c_str());
        return false;
    };

    //check for incorrect number of column values entered
    if(values.size() != table.return_tableheader().num_columns){
        printf("Database::insert_record(): (error) Values entered do not match number of required columns\n");
        return false;
    }
    
    // record byte buffer
    std::vector<char> buffer;

    // get size of all data, so I can resize the buffer with the correct size and capacity
    size_t total_size = 0;
    for(const std::string& x : values){
        total_size += sizeof(uint32_t);
        total_size += x.size();
    }
    buffer.resize(total_size);


    // serializing the record's data into the byte buffer for writing
    size_t offset = 0;
    for(const string& x : values){ 

        //memcpy the value's size
        uint32_t val_size = static_cast<uint32_t>(x.size());
        memcpy(buffer.data() + offset, &val_size, sizeof(val_size));
        offset += sizeof(val_size);
        
        //memcpy the value's characters
        memcpy(buffer.data() + offset, x.data(), val_size);
        offset += val_size;
    }

    //ask storagemanager for page (table offset) where the record should go
    StorageManager m(table);
    
    //sequence of events?:
    //read in the correct page (or create new one if none)
    //  -how do we determine what page to insert into?
    //insert record into page, then update the page's header and slot directory
    //write the page back into the table

    m.read_page();
        
    
    return true;
}

bool Database::drop_record(std::string table_name, int record_id){
    return false;
}

bool Database::update_record(std::string table_name, int record_id, std::string column, std::string value){
    return false;
}

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

void Database::display_record(Record record){

}


// loading each table's metadata into memory during db initialization
void Database::load_tables_from_disk(){
    //Iterate over every file inside db_path
    for(const auto& entry : fs::directory_iterator(db_path)){
        
        //skip anything not a .tbl file
        if(entry.path().extension() != ".tbl") continue;

        //extract the filename without extension
        std::string name = entry.path().stem().string();

        //check if this table is already loaded in memory (our map)
        if(tables.find(name) == tables.end()){
            
            //loading table metadata at initialization (not actual pages and records yet)
            //it's not loaded in memory yet
            //create new table object
            //load object with the table information
            Table t;
            std::string path = db_path + name + ".tbl";
            t.table_info(path, name); //update table info <tbl_path, name>
            t.load_from_disk(entry); //(to load header struct, and update schema)
            
            //add table to the map
            tables.emplace(name, t);
        }
    }

}


std::string Database::return_path(std::string table_name){
    Table t = tables.at(table_name);
    std::string table_path = t.return_path(); //
    return table_path;
}
