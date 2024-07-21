#include "../include/BorrowManager.h"
#include "../include/library.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <ctime>
#include <iomanip>
#include <sstream>


void BorrowManager::registerBorrow(const std::string& reader_id, const std::string& book_id, const std::string& borrow_date) {
    try {
        pqxx::work W(*library.getConnection());
        std::string borrow_sql = "INSERT INTO borrow (borrow_id, reader_id, book_id, borrow_date) VALUES (uuid_generate_v4(), " +
                          W.quote(reader_id) + ", " + W.quote(book_id) + ", " + W.quote(borrow_date) + ");";
        std::string update_sql = "UPDATE book SET is_available = FALSE WHERE id = " + W.quote(book_id) + ";";
        W.exec(borrow_sql);
        W.exec(update_sql);
        W.commit();
        std::cout << "Book borrowed successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}



void BorrowManager::registerReturn(const std::string& borrow_id, const std::string& return_date) {
    try {
        pqxx::work W(*library.getConnection());
        
        std::string sql = "UPDATE borrow SET return_date = " + W.quote(return_date) + 
                          " WHERE borrow_id = " + W.quote(borrow_id) + " AND return_date IS NULL;";
        W.exec(sql);
        
        sql = "SELECT book_id, borrow_date, return_date FROM borrow WHERE borrow_id = " + W.quote(borrow_id) + 
              " AND return_date = " + W.quote(return_date) + ";";
        pqxx::result R = W.exec(sql);
        
        if (R.size() == 1) {
            std::string book_id = R[0][0].c_str();
            std::string borrow_date_str = R[0][1].c_str();
            std::string return_date_str = R[0][2].c_str();

            std::tm borrow_tm = {};
            std::tm return_tm = {};

            std::istringstream borrow_ss(borrow_date_str);
            std::istringstream return_ss(return_date_str);

            borrow_ss >> std::get_time(&borrow_tm, "%Y-%m-%d %H:%M:%S");
            return_ss >> std::get_time(&return_tm, "%Y-%m-%d %H:%M:%S");

            std::time_t borrow_time = std::mktime(&borrow_tm);
            std::time_t return_time = std::mktime(&return_tm);

            double duration_seconds = std::difftime(return_time, borrow_time);
            int duration_days = duration_seconds / (60 * 60 * 24);

            std::cout << "Book returned successfully. Duration: " << duration_days << " days." << std::endl;

            sql = "UPDATE book SET is_available = TRUE WHERE id = " + W.quote(book_id) + ";";
            W.exec(sql);
        }

        W.commit();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void BorrowManager::displayBorrowHistory(const std::string& reader_id) {
    try {
        pqxx::work W(*library.getConnection());
        std::string sql = "SELECT b.book_id, b.borrow_date, b.return_date, bk.title FROM borrow b "
                          "JOIN book bk ON b.book_id = bk.id "
                          "JOIN person r ON b.reader_id = r.reader_id "
                          "WHERE r.reader_id = " + W.quote(reader_id) + " ORDER BY b.borrow_date;";
        pqxx::result R = W.exec(sql);

        if (R.empty()) {
            std::cout << "No borrow history found for reader: " << reader_id << std::endl;
            return;
        }

        std::cout << "Borrow history for reader: " << reader_id << std::endl;
        for (auto row : R) {
            std::string book_id = row[0].c_str();
            std::string borrow_date = row[1].c_str();
            std::string return_date = row[2].c_str();
            std::string book_title = row[3].c_str();

            std::cout << "Book ID: " << book_id << ", Title: " << book_title 
                      << ", Borrow Date: " << borrow_date 
                      << ", Return Date: " << (return_date.empty() ? "Not returned yet" : return_date) 
                      << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}