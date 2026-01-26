#include "page.h"



Page Page::create_empty(uint16_t page_id){
    Page p;
    
    p.header()->page_id = page_id;
    p.header()->num_slots = 0;
    p.header()->free_space_start = sizeof(PageHeader);

    return p;
}

