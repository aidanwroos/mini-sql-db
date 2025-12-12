#ifndef STORAGEMANAGER_H
#define STORAGEMANAGER_H

#include <filesystem>
#include <fstream>
#include "page.h"

namespace fs = std::filesystem;

class StorageManager {
    private:
        std::string file_path;             // filename of table the storagemanager is currently working on
        fstream data_file;                 // Handles IO binary file operations
        std::vector<Page> page_buffer;     // (max of 3 pages loaded into memory at a time)

    public:
        
    StorageManager(std::string table_path);

    ~StorageManager();

    bool read_in_page(){

    }

};


#endif