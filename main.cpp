#include <iostream>
#include "UI.h"
#include "database.h"


using namespace std;


int main(){
    Database db;  //create db instance
    UI ui(db);    //call UI constructor with db instance
    ui.run();     //call run public member function to begin program

    return 0;
}