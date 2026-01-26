#include "StorageManager.h"
#include "record.h"

#include <string>
#include <iostream>


StorageManager::StorageManager(){
    printf("StorageManager: default constructor called\n");
}


//Fires up when StorageManager instance created
//Opens filestream for given table_path
StorageManager::StorageManager(Table table) 
    : file_path(table.return_path()),
    data_file(table.return_path(), ios::binary | ios::out | ios::in | ios::app)
{
    if(!data_file){
        printf("StorageManager: 'Failed to open data file: %s\n", file_path.c_str());
        return;
    }

    //success
    printf("StorageManager: 'Success, opened data file for table path: %s\n", table.return_path().c_str());
}

//Closes filestream, closes instance
StorageManager::~StorageManager(){
    if(data_file.is_open()){
        data_file.close();
    }
}

fstream& StorageManager::file(){
    return data_file;
}


Page StorageManager::read_page(){
    std::streamsize size = data_file.tellg();
    int num_pages = size / 4096;

    Page page;

    if(num_pages == 0){
        //no pages exist in table yet, create new one and return it
        page = Page::create_empty(0);

    }else{
        //pages exist, read last page in table and return it
    }
    


}



