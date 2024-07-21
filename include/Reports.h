#ifndef REPORTS_H
#define REPORTS_H

class Library;

class Reports {
public:
    Reports(Library& library) : library(library) {}
    void reportCurrentlyBorrowedBooks();
    void reportOverdueBorrows();
    void reportMostFrequentlyBorrowedBooks();

private:
    Library& library;
};

#endif // REPORTS_H
