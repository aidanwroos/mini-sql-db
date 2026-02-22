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
    std::vector<char> page_data(PAGE_SIZE);

    uint16_t pg_id = page.return_pg_header().page_id;
    uint16_t free_space_offset = page.return_pg_header().free_space_start;
    uint16_t slot_dir_offset = page.return_pg_header().slot_dir_offset;
    
    memcpy(page_data.data() + 0, &pg_id, sizeof(pg_id));
    memcpy(page_data.data() + 2, &free_space_offset, sizeof(free_space_offset));
    memcpy(page_data.data() + 4, &slot_dir_offset, sizeof(slot_dir_offset));


    // 4. Load the page object into the StorageManager's page buffer for writing/reading later
    //    -probably have a separate write_page() function or something

    // 5. (maybe not yet?) Write the serialized page data to the table file

}

// read in the last page of the table
void StorageManager::read_page(){

    //calculate the number of pages in the table
    int num_pages = (data_file.tellg() / 4096);

    cout << "Number of pages in table: " << num_pages << endl;

}

