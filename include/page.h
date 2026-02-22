#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <stdint.h>
#include "record.h"

using namespace std;


#define PAGE_SIZE 4096           //(bytes) -> max page size (4 KB)
#define PAGE_HEADER_SIZE 6       //(bytes) -> fixed page header size


//fixed 6 byte page header
struct PageHeader {
    uint16_t page_id;            //page id number
    uint16_t slot_dir_offset;    //slot directory offset from end of page
    uint16_t free_space_start;   //offset where free space begins
};

//dynamic size slot directory
//(grows from bottom of page up)
struct Slot{
    uint16_t offset;             //start of the record
    uint16_t length;             //length of the record (if 0, record removed)
};


class Page { 
    private:
        std::vector<char> data;  //entire page
        PageHeader pageheader;   
        // Slot slotdirectory; not right now

    public:
        Page();                  //default page constructor
        Page(uint16_t pg_id);    //page constructor

        PageHeader return_pg_header(); //getter for page header info
        void serialize_page();
        
};

#endif