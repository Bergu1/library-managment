#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <string>

class Library;

class BookManager {
public:
    BookManager(Library& library) : library(library) {}
    void addBook(const std::string& title, const std::string& author, int year_published);
    void deleteBook(const std::string& book_id);
    void searchBook(const std::string& title, const std::string& id);

private:
    Library& library;

};

#endif // BOOKMANAGER_H
