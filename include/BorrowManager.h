#ifndef BORROWMANAGER_H
#define BORROWMANAGER_H

#include <string>

class Library;

class BorrowManager {
public:
    BorrowManager(Library& library) : library(library) {}
    void registerBorrow(const std::string& reader_id, const std::string& book_id, const std::string& borrow_date);
    void registerReturn(const std::string& borrow_id, const std::string& return_date);
    void displayBorrowHistory(const std::string& reader_id);

private:
    Library& library;
    
};

#endif // BORROWMANAGER_H