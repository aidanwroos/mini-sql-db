#ifndef PAGE_H
#define PAGE_H

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <stdint.h>
#include "record.h"

using namespace std;


#define PAGE_SIZE 4096 //(bytes) -> max page size (4 KB)


struct Slot{
    uint16_t offset; //start of the record
    uint16_t length; //length of the record (if 0, then the record's been removed)
};

//A righteous man falls down 7 times, and gets back up


class Page { 
    private:
        //1. Page header (metadata about the page)
        //2. Records space (data rows themselves)
        //3. Slot directory

        int page_id;                        //page specific id
        char data[PAGE_SIZE];               //raw page bytes
        int free_space_pointer;             //next free space for record to be inserted
        std::vector<Slot> slot_directory;   //offsets+size of records


    public:
        Page(int pageID);


        //...
};





#endif