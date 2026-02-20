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


//fixed 6 byte page header
struct PageHeader {
    uint16_t page_id;            //page id number
    uint16_t num_slots;          //number of slot entries
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

    public:
        Page() : data(PAGE_SIZE, 0){} //inline constructor inits/zeros data array

        PageHeader* header(){
            return reinterpret_cast<PageHeader*>(data.data());
        }

        Slot* slot_directory(){
            return reinterpret_cast<Slot*>(data.data() + PAGE_SIZE - header()->num_slots * sizeof(Slot));
        }


        static Page create_empty(uint16_t page_id);
        
        char return_data();
        
};

#endif