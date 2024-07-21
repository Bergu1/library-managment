#include "../include/PersonManager.h"
#include "../include/library.h"
#include <iostream>
#include <pqxx/pqxx>
#include <string>

void PersonManager::addPerson(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& gender, const std::string& phoneNumber) {
    try{
        // Tworzenie obiektu pqxx::work rozpoczynającego transakcję
        pqxx::work W(*library.getConnection());

        // Wykonanie komendy SQL do dodania osoby
        std::string sql = "INSERT INTO person (reader_id, first_name, last_name, email, gender, phone_number) VALUES (uuid_generate_v4(), "  +
        W.quote(firstName) + ", " + W.quote(lastName) + ", " + W.quote(email) + ", " + W.quote(gender) + ", " + W.quote(phoneNumber) + ");";

        // Wykonanie zapytania SQL w kontekście transakcji
        W.exec(sql); 

        // Zatwierdzenie transakcji
        W.commit();  

        std::cout << "Records created successfully" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

void PersonManager::deletePerson(const std::string& reader_id) {
    try {
        // Tworzenie obiektu pqxx::work rozpoczynającego transakcję
        pqxx::work W(*library.getConnection());

        // Wykonanie komendy SQL do dodania osoby
        std::string sql = "DELETE FROM person WHERE reader_id = " + W.quote(reader_id) + ";";

        // Wykonanie zapytania SQL w kontekście transakcji
        W.exec(sql);

        // Zatwierdzenie transakcji
        W.commit();

        std::cout << "Record deleted successfully" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void PersonManager::searchPerson(const std::string& phoneNumber){
    try {
        pqxx::work W(*library.getConnection());
        std::string sql = "SELECT reader_id, first_name, last_name, email, gender, phone_number FROM person WHERE phone_number = " + W.quote(phoneNumber) + ";";
        pqxx::result result = W.exec(sql);

        if (result.empty()) {
            std::cout << "No user found with phone number: " << phoneNumber << std::endl;
        } else {
            //iterujemy przez cały kontener result i zapisujemy dane do zmiennej row a następnie odczytujemy & - by pracować na orginale nie na kopiach
            for (const auto& row : result){
                //metoda c_str() zwraca zawartość pola jako const char*, co jest przydatne do wyświetlania lub dalszego przetwarzania.
                std::cout << "Reader ID: " << row["reader_id"].c_str() << std::endl; 
                std::cout << "First Name: " << row["first_name"].c_str() << std::endl;
                std::cout << "Last Name: " << row["last_name"].c_str() << std::endl;
                std::cout << "Email: " << row["email"].c_str() << std::endl;
                std::cout << "Gender: " << row["gender"].c_str() << std::endl;
                std::cout << "Phone Number: " << row["phone_number"].c_str() << std::endl;
            }
        }
        W.commit();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}


void PersonManager::updatePerson(const std::string& reader_id, const std::string& newEmail, const std::string& newPhoneNumber, const std::string& new_last_name) {
    try {
        pqxx::work W(*library.getConnection());
        std::string sql = "UPDATE person SET ";

        bool first = true;

        if (!newEmail.empty()) {
            sql += "email = " + W.quote(newEmail);
            first = false;
        }

        if (!newPhoneNumber.empty()) {
            if (!first) {
                sql += ", ";
            }
            sql += "phone_number = " + W.quote(newPhoneNumber);
            first = false;
        }

        if (!new_last_name.empty()) {
            if (!first) {
                sql += ", ";
            }
            sql += "last_name = " + W.quote(new_last_name);
            first = false;
        }

        sql += " WHERE reader_id = " + W.quote(reader_id) + ";";

        W.exec(sql);
        W.commit();
        std::cout << "Record updated successfully" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}