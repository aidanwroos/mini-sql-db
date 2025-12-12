#include "StorageManager.h"
#include "record.h"

#include <string>
#include <iostream>

//Fires up when StorageManager instance created
//Opens filestream for given table_path
StorageManager::StorageManager(std::string table_path){
    data_file.open(file_path, ios::binary | ios::out | ios::in | ios::trunc);
    if(!data_file.is_open()){
        printf("StorageManager: 'Failed to open data file: %s", file_path.c_str());
        return;
    }
}

//Closes filestream, closes instance
StorageManager::~StorageManager(){
    if(data_file.is_open()){
        data_file.close();
    }
}

