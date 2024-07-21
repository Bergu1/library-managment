#include "../include/library.h"
#include "../include/BookManager.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>

void BookManager::addBook(const std::string& title, const std::string& author, int year_published) {
    try {
        pqxx::work W(*library.getConnection());
        std::string sql = "INSERT INTO book (id, title, author, year_published) VALUES (uuid_generate_v4(), " +
            W.quote(title) + ", " + W.quote(author) + ", " + W.quote(year_published) + ");";
        W.exec(sql);
        W.commit();
        std::cout << "Book added successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void BookManager::deleteBook(const std::string& book_id) {
    try {
        pqxx::work W(*library.getConnection());
        std::string sql = "DELETE FROM book WHERE id = " + W.quote(book_id) + ";";
        W.exec(sql);
        W.commit();
        std::cout << "Book deleted successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void BookManager::searchBook(const std::string& title, const std::string& id) {
    try {
        pqxx::work W(*library.getConnection());
        std::string sql;

        if (!title.empty()) {
            sql = "SELECT id, title, author, year_published, is_available FROM book WHERE title = " + W.quote(title) + ";";
        } else if (!id.empty()) {
            sql = "SELECT id, title, author, year_published, is_available FROM book WHERE id = " + W.quote(id) + ";";
        } else {
            std::cerr << "No search criteria provided." << std::endl;
            return;
        }
        
        pqxx::result result = W.exec(sql);

        if (result.empty()) {
            if (!title.empty()) {
                std::cout << "No book found with title: " << title << std::endl;
            } else if (!id.empty()) {
                std::cout << "No book found with ID: " << id << std::endl;
            }
        } else {
            for (const auto& row : result) {
                std::cout << "Book ID: " << row["id"].c_str() << std::endl;
                std::cout << "Title: " << row["title"].c_str() << std::endl;
                std::cout << "Author: " << row["author"].c_str() << std::endl;
                std::cout << "Year Published: " << row["year_published"].c_str() << std::endl;
                std::cout << "Is Available: " << row["is_available"].c_str() << std::endl;
            }
        }
        W.commit();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
