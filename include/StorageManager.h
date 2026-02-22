#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <filesystem>
#include <fstream>
#include "page.h"
#include "table.h"

namespace fs = std::filesystem;

class StorageManager {
    
    public: 
    std::string file_path;             // file path of table the storagemanager is currently working on
    fstream data_file;                 // Handles IO binary file operations
    std::vector<Page> page_buffer;     // (max of 3 pages loaded into memory at a time)
    Table current_table;               // the current table we're working on
        
    
    StorageManager();

    StorageManager(Table table);

    ~StorageManager();

    fstream& file();    // return data_file by REFERENCE (not VALUE headass)

    void create_page(); // create a new page to add to the table
    void read_page();   // read in last page of table, or create new page if none exist
    
    Page free_page();   // return free page to insert record into

};

// storage manager will read in pages from a table
// and write pages to a table


#endif