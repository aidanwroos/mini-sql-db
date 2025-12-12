#include "page.h"



Page::Page(int pageID){
    page_id = pageID;               //initially not assigned
    free_space_pointer = 0;     //initially zero records (at the beginning)
    slot_directory.clear();     //no slots yet

    memset(data, 0, PAGE_SIZE); //initially all bytes in data are zero
}