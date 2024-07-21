#include "../include/library.h"
#include "../include/Reports.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>

void Reports::reportCurrentlyBorrowedBooks(){
    try {

        pqxx::work W(*library.getConnection());
        std::string sql =
        "SELECT b.id, b.title, b.author, b.year_published, p.reader_id, p.first_name, p.last_name, br.borrow_date, br.return_date "
        "FROM book b "
        "JOIN borrow br ON b.id = br.book_id "
        "JOIN person p ON br.reader_id = p.reader_id "
        "WHERE br.return_date IS NULL";

        pqxx::result result = W.exec(sql);

        std::cout << "Currently Borrowed Books:\n";
        for (auto row : result) {
            std::cout << "Book ID: " << row["id"].c_str() << ", Title: " << row["title"].c_str()
                    << ", Author: " << row["author"].c_str() << ", Borrower: " << row["first_name"].c_str()
                    << " " << row["last_name"].c_str() << ", Borrow Date: " << row["borrow_date"].c_str() << "\n";
        }

        W.commit();
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void Reports::reportOverdueBorrows() {
    try {     
        pqxx::work W(*library.getConnection());
        std::string sql =
        "SELECT b.id, b.title, b.author, b.year_published, p.reader_id, p.first_name, p.last_name, br.borrow_date, br.return_date, "
        "CURRENT_DATE - br.borrow_date AS days_overdue "
        "FROM book b "
        "JOIN borrow br ON b.id = br.book_id "
        "JOIN person p ON br.reader_id = p.reader_id "
        "WHERE br.return_date IS NULL AND (CURRENT_DATE - br.borrow_date) > 30";

        pqxx::result result = W.exec(sql);

        std::cout << "Overdue Borrows:\n";
        for (auto row : result) {
            std::cout << "Book ID: " << row["id"].c_str() << ", Title: " << row["title"].c_str()
                    << ", Author: " << row["author"].c_str() << ", Borrower: " << row["first_name"].c_str()
                    << " " << row["last_name"].c_str() << ", Borrow Date: " << row["borrow_date"].c_str()
                    << ", Days Overdue: " << row["days_overdue"].as<int>() << "\n";
        }

        W.commit();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void Reports::reportMostFrequentlyBorrowedBooks() {

    try {
        pqxx::work W(*library.getConnection());
        std::string sql =
        "SELECT b.id, b.title, b.author, b.year_published, COUNT(br.book_id) AS borrow_count "
        "FROM book b "
        "JOIN borrow br ON b.id = br.book_id "
        "GROUP BY b.id "
        "ORDER BY borrow_count DESC";

        pqxx::result result = W.exec(sql);

        std::cout << "Most Frequently Borrowed Books:\n";
        for (auto row : result) {
            std::cout << "Book ID: " << row["id"].c_str() << ", Title: " << row["title"].c_str()
                    << ", Author: " << row["author"].c_str() << ", Borrow Count: " << row["borrow_count"].as<int>() << "\n";
        }

        W.commit();
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
