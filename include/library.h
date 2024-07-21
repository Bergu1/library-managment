#ifndef LIBRARY_H
#define LIBRARY_H

#include <pqxx/pqxx>
#include "PersonManager.h"
#include "BookManager.h"
#include "BorrowManager.h"
#include "Reports.h"

class Library {
public:
    Library();
    ~Library();

    friend class PersonManager;
    friend class BookManager;
    friend class BorrowManager;
    friend class Reports;

    PersonManager personManager;
    BookManager bookManager;
    BorrowManager borrowManager;
    Reports reports;

protected:

    pqxx::connection* getConnection() const {
        return conn;
    }


private:
    pqxx::connection* conn;

};

#endif // LIBRARY_H
