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
    current_table = table; // set current table we're working with

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

// create new page to add to the specific table file
// (once page is created, then records can be added to it later)
void StorageManager::create_page(){
    
    // 1. Firstly, create the new page_id we need. Located in the tableheader file!
    uint32_t page_id = current_table.return_tableheader().num_pages + 1;

    // 2. Instantiate a Page object passing in the page_id
    Page page(page_id);


    // 3. Serialize the whole page data (header, records(empty now), slot dir (empty now)) into byte stream
    
    // 4. Write the serialized page data to the table file
 


}

// read in the last page of the table
void StorageManager::read_page(){

    //calculate the number of pages in the table
    int num_pages = (data_file.tellg() / 4096);

    cout << "Number of pages in table: " << num_pages << endl;

}

