#include "page.h"


Page::Page(){}

// page constructor
Page::Page(uint16_t pg_id){

    //Initialize the page's header
    pageheader.page_id = pg_id;
    pageheader.num_slots = 0;
    pageheader.free_space_start = sizeof(PageHeader); // size is 16+16+16bits = 6 bytes


}




// Table (unknown size) -->    | tableheader 4KB || PAGE 4KB | PAGE 4KB | PAGE 4KB |

// PAGE (4096 bytes, 4KB) -->  | Pageheader 6bytes | Record space | Slot directory |