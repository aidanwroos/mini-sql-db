#ifndef DATABASE_H
#define DATABASE_H

#include <unordered_map>
#include <memory>


class Database {
    private:
        //all tables in the database 
        std::unordered_map<std::string, std::unique_ptr<Table>> tables;

    public:
        //create a table

        //remove a table

        //list table names


};


#endif