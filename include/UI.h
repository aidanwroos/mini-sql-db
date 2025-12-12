#ifndef UI_H
#define UI_H

#include <string>
#include <thread>
#include <chrono>
#include "database.h"


class UI {
    private:
        Database& database;

    public: 
        
        UI(Database &database);

        void run();
        void print_menu();
        void clear_screen();
        int process_input(const std::string& input);

};



#endif