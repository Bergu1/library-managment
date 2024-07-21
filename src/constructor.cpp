#include "../include/library.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>

Library::Library() : conn(nullptr), 
      personManager(*this), 
      bookManager(*this), 
      borrowManager(*this), 
      reports(*this)
{
    try {
        conn = new pqxx::connection("dbname=library user=postgres password=2003 hostaddr=127.0.0.1 port=5432");
        if (conn -> is_open()){
            std::cout << "Opened database successfully: " << conn -> dbname() << std::endl;
        } else{
            std::cout << "Can't open database" << std::endl;
        }
    } catch (const std::exception& e){
        std::cerr << e.what() << std::endl;
    }
}

Library::~Library() {
    if (conn != nullptr) {
        conn->disconnect();
        delete conn;
    }
}

