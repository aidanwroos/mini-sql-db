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

// read in the last page of the table
void StorageManager::read_page(){

    //calculat the number of pages in the table
    int num_pages = (data_file.tellg() / 4096) - 1;

    cout << "Number of pages in table: " << num_pages << endl;

}

