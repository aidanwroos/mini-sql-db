#include "page.h"


Page::Page(){}

// page constructor
Page::Page(uint16_t pg_id){
    //Initialize the page's header
    pageheader.page_id = pg_id;
    pageheader.slot_dir_offset = PAGE_SIZE;           // starts at end of page, grows backwards
    pageheader.free_space_start = PAGE_HEADER_SIZE;   // size is 16+16+16bits = 6 bytes
}

// just grabs and returns the pageheader object
PageHeader Page::return_pg_header(){
    return pageheader;
}

 

// Table (unknown size) -->    | tableheader 4KB || PAGE 4KB | PAGE 4KB | PAGE 4KB |

// PAGE (4096 bytes, 4KB) -->  | Pageheader 6bytes | Record space | Slot directory |