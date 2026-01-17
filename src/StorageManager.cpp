#include "StorageManager.h"
#include "record.h"

#include <string>
#include <iostream>


StorageManager::StorageManager(){
    printf("StorageManager: default constructor called\n");
}


//Fires up when StorageManager instance created
//Opens filestream for given table_path
StorageManager::StorageManager(std::string table_path){
    file_path = table_path;

    data_file.open(file_path, ios::binary | ios::out | ios::in | ios::app);
    if(!data_file.is_open()){
        printf("StorageManager: 'Failed to open data file: %s\n", file_path.c_str());
        return;
    }

    //success
    printf("StorageManager: 'Success, opened data file for table path: %s\n", table_path.c_str());

    //initialize data_file (open)
    data_file.open(file_path, std::ios::in | std::ios::out);
}

//Closes filestream, closes instance
StorageManager::~StorageManager(){
    if(data_file.is_open()){
        data_file.close();
    }
}

