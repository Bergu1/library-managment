#ifndef DISPLAY_H
#define DISPLAY_H

#include <string>
#include <iostream>
#include <pqxx/pqxx>
#include "library.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void handlePersonMenu(PersonManager& personManager);
void handleBookMenu(BookManager& bookManager);
void handleBorrowMenu(BorrowManager& borrowManager);
void handleReportsMenu(Reports& reports);

void displayMainMenu(Library& library) {
    int choice;

    while (true) {
        clearScreen();
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Manage Persons\n";
        std::cout << "2. Manage Books\n";
        std::cout << "3. Manage Borrows\n";
        std::cout << "4. Reports\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                handlePersonMenu(library.personManager);
                break;
            case 2:
                handleBookMenu(library.bookManager);
                break;
            case 3:
                handleBorrowMenu(library.borrowManager);
                break;
            case 4:
                handleReportsMenu(library.reports);
                break;
            case 5:
                return;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}


void handlePersonMenu(PersonManager& personManager) {
    int choice;
    std::string firstName, lastName, email, gender, phoneNumber, reader_id, newEmail, newPhoneNumber;

    clearScreen();
    std::cout << "\nPerson Management Menu\n";
    std::cout << "1. Add Person\n";
    std::cout << "2. Delete Person\n";
    std::cout << "3. Search Person\n";
    std::cout << "4. Update Person\n";
    std::cout << "5. Return to Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter First Name: ";
            std::cin >> firstName;
            std::cout << "Enter Last Name: ";
            std::cin >> lastName;
            std::cout << "Enter Email: ";
            std::cin >> email;
            std::cout << "Enter Gender: ";
            std::cin >> gender;
            std::cout << "Enter Phone Number: ";
            std::cin >> phoneNumber;
            personManager.addPerson(firstName, lastName, email, gender, phoneNumber);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 2:
            std::cout << "Enter Reader ID: ";
            std::cin >> reader_id;
            personManager.deletePerson(reader_id);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 3:
            std::cout << "Enter Phone Number: ";
            std::cin >> phoneNumber;
            personManager.searchPerson(phoneNumber);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 4:
            std::cout << "Enter Reader ID: ";
            std::cin >> reader_id;
            
            std::cout << "Which record do you want to change: 1. Email 2. Phone number 3. Last name: ";
            int choice;
            std::cin >> choice;

            switch (choice){
                case 1:
                    std::cout << "Enter New Email: ";
                    std::cin >> newEmail;
                    break;
                case 2:
                    std::cout << "Enter New Phone Number: ";
                    std::cin >> newPhoneNumber;
                    break;
                case 3: 
                    std::cout << "Enter Last Name: ";
                    std::cin >> lastName;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
            }
            
            personManager.updatePerson(reader_id, newEmail, newPhoneNumber, lastName);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;

        case 5:
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}

void handleBookMenu(BookManager& bookManager){
    int choice, year_published;
    std::string title, author, book_id;

    clearScreen();
    std::cout << "\nBook Management Menu\n";
    std::cout << "1. Add Book\n";
    std::cout << "2. Delete Book\n";
    std::cout << "3. Search Book\n";
    std::cout << "4. Return to Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Enter Title: ";
            std::cin.ignore();
            std::getline(std::cin, title);
            std::cout << "Enter Author: ";
            std::getline(std::cin, author);
            std::cout << "Enter Year Published: ";
            std::cin >> year_published;
            bookManager.addBook(title, author, year_published);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 2:
            std::cout << "Enter Book ID: ";
            std::cin >> book_id;
            bookManager.deleteBook(book_id);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 3:
            std::cout << "Search by:\n";
            std::cout << "1. Title\n";
            std::cout << "2. Book ID\n";
            std::cout << "Enter your choice: ";
            int search_choice;
            std::cin >> search_choice;

            if (search_choice == 1) {
                std::cout << "Enter Title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                bookManager.searchBook(title, "");
            } else if (search_choice == 2) {
                std::cout << "Enter Book ID: ";
                std::cin.ignore();
                std::getline(std::cin, book_id);
                bookManager.searchBook("", book_id);
                std::cout << "Press Enter to return to the menu...";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
            break;
        case 4:
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }

}

void handleBorrowMenu(BorrowManager& borrowManager) {
    int choice;
    std::string reader_id, book_id, borrow_date, borrow_id, return_date;

    clearScreen();
    std::cout << "\nBorrow Management Menu\n";
    std::cout << "1. Register Borrow\n";
    std::cout << "2. Register Return\n";
    std::cout << "3. Check history of borrow\n";
    std::cout << "4. Return to Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "Enter Reader ID: ";
            std::cin >> reader_id;
            std::cout << "Enter Book ID: ";
            std::cin >> book_id;
            std::cout << "Enter Borrow Date (YYYY-MM-DD): ";
            std::cin >> borrow_date;
            borrowManager.registerBorrow(reader_id, book_id, borrow_date);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 2:
            std::cout << "Enter Borrow ID: ";
            std::cin >> borrow_id;
            std::cout << "Enter Return Date (YYYY-MM-DD): ";
            std::cin >> return_date;
            borrowManager.registerReturn(borrow_id, return_date);
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 3:
            std::cout << "Enter reader ID:";
            std::cin >> reader_id;
            borrowManager.displayBorrowHistory(reader_id);
            break;
        case 4:
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}


void handleReportsMenu(Reports& reports){
    int choice;
    clearScreen();
    std::cout << "\nReports Management Menu\n";
    std::cout << "1. Currently borrow books\n";
    std::cout << "2. Overdue books\n";
    std::cout << "3. Most frequently borrow books\n";
    std::cout << "4. Return to Main Menu\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
        case 1:
            reports.reportCurrentlyBorrowedBooks();
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 2:
            reports.reportOverdueBorrows();
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 3:
            reports.reportMostFrequentlyBorrowedBooks();
            std::cout << "Press Enter to return to the menu...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 4:
            return;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
    }
}

#endif